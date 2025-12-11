#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// 定义布隆过滤器结构体
typedef struct {
    unsigned char *bits; // 位数组，使用字节数组存储位
    size_t size_bytes;   // 位数组的总字节数
    size_t size_bits;    // 位数组的总位数 (m)
    size_t num_hashes;   // 哈希函数的数量 (k)
} BloomFilter;

// 初始化布隆过滤器
// size_bits: 位数组的总位数 (m)
// num_hashes: 哈希函数的数量 (k)
BloomFilter* bf_init(size_t size_bits, size_t num_hashes) {
    if (size_bits == 0 || num_hashes == 0) {
        return NULL;
    }

    BloomFilter *bf = (BloomFilter*)malloc(sizeof(BloomFilter));
    if (bf == NULL) {
        return NULL;
    }

    // 计算所需的字节数：(size_bits + 7) / 8 向上取整
    bf->size_bits = size_bits;
    bf->size_bytes = (size_bits + 7) / 8;
    bf->num_hashes = num_hashes;

    // 分配并初始化位数组
    bf->bits = (unsigned char*)calloc(bf->size_bytes, sizeof(unsigned char));
    if (bf->bits == NULL) {
        free(bf);
        return NULL;
    }

    return bf;
}

// 销毁布隆过滤器
void bf_destroy(BloomFilter *bf) {
    if (bf) {
        free(bf->bits);
        free(bf);
    }
}

// 设置位数组中的第 index 位为 1
void bf_set_bit(BloomFilter *bf, size_t index) {
    if (index >= bf->size_bits) return;

    // 确定所在的字节索引
    size_t byte_index = index / 8;
    // 确定在字节中的位偏移量 (从低位开始 0 到 7)
    size_t bit_offset = index % 8;

    // 使用位或操作设置位
    bf->bits[byte_index] |= (1 << bit_offset);
}

// 检查位数组中的第 index 位是否为 1
bool bf_get_bit(const BloomFilter *bf, size_t index) {
    if (index >= bf->size_bits) return false;

    size_t byte_index = index / 8;
    size_t bit_offset = index % 8;

    // 使用位与操作检查位是否为 1
    return (bf->bits[byte_index] & (1 << bit_offset)) != 0;
}

// 基础哈希函数 1: DJB2
static size_t hash_djb2(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    return (size_t)hash;
}

// 基础哈希函数 2: SDBM
static size_t hash_sdbm(const char *str) {
    unsigned long hash = 0;
    int c;
    while ((c = *str++)) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return (size_t)hash;
}

// 模拟 k 个哈希函数的索引计算
// 使用公式: index_i = (h1 + i * h2) % m
static size_t get_index(size_t h1, size_t h2, size_t i, size_t size_bits) {
    // 确保结果在 size_t 范围内，并对 m (size_bits) 取模
    return (h1 + i * h2) % size_bits;
}


// 向布隆过滤器中添加一个元素
void bf_add(BloomFilter *bf, const char *key) {
    size_t h1 = hash_djb2(key);
    size_t h2 = hash_sdbm(key);

    for (size_t i = 0; i < bf->num_hashes; ++i) {
        size_t index = get_index(h1, h2, i, bf->size_bits);
        bf_set_bit(bf, index);
    }
}

// 检查元素是否可能存在于布隆过滤器中
// 返回 true: 元素可能存在（有误判风险）
// 返回 false: 元素一定不存在（无误判）
bool bf_possibly_contains(const BloomFilter *bf, const char *key) {
    size_t h1 = hash_djb2(key);
    size_t h2 = hash_sdbm(key);

    for (size_t i = 0; i < bf->num_hashes; ++i) {
        size_t index = get_index(h1, h2, i, bf->size_bits);
        if (!bf_get_bit(bf, index)) {
            // 只要有一个位是 0，则一定不存在
            return false;
        }
    }
    // 所有位都是 1，则可能存在
    return true;
}



// 打印 unsigned char 数组中的所有位
// bits: 指向位数组的指针
// size_bytes: 位数组的长度（以字节为单位）
void print_bit_array(const unsigned char *bits, size_t size_bytes) {
    printf("Bit Array (Total %zu bytes, %zu bits):\n", size_bytes, size_bytes * 8);

    // 1. 逐字节遍历
    for (size_t i = 0; i < size_bytes; ++i) {
        unsigned char current_byte = bits[i];

        // 打印字节索引，例如 [Byte 0]:
        printf("[%zu]: ", i);

        // 2. 逐位检查和打印（从最高位到最低位）
        // 一个 char 有 8 位，所以 j 从 7 循环到 0
        for (int j = 7; j >= 0; --j) {
            // 使用位与操作 (current_byte & (1 << j)) 检查第 j 位是否为 1
            // (1 << j) 会创建一个只有一个 1 在第 j 位的掩码

            // 如果位运算结果非零，说明该位是 1，否则是 0
            if (current_byte & (1 << j)) {
                printf("1");
            } else {
                printf("0");
            }
        }
        printf(" "); // 字节之间用空格分隔
    }
    printf("\n");
}
// --- 完整示例：使用和测试 ---

int main() {
    // 假设预期插入 100 个元素 (n)
    size_t expected_elements = 100;
    // 设定可接受的误判率 (p)
    double false_positive_rate = 0.01;

    // --- 理论参数计算（最佳 m 和 k）---
    // 最佳位数 m = -(n * ln(p)) / (ln(2)^2)
    // 最佳哈希函数个数 k = (m / n) * ln(2)

    // 简化：这里我们手动选择一组参数 (实际应用需计算优化)
    // 位数 m
    size_t m = 1000;
    // 哈希函数个数 k
    size_t k = 7;

    BloomFilter *bf = bf_init(m, k);
    if (!bf) {
        fprintf(stderr, "Error: Failed to initialize Bloom Filter.\n");
        return 1;
    }

    // 1. 添加元素
    bf_add(bf, "apple");
    bf_add(bf, "banana");
    bf_add(bf, "cherry");

    printf("--- Test Queries ---\n");

    // 2. 查询存在的元素
    printf("Contains 'apple': %s\n", bf_possibly_contains(bf, "apple") ? "YES (Possibly)" : "NO (Definitely)");

    // 3. 查询不存在的元素
    printf("Contains 'grape': %s\n", bf_possibly_contains(bf, "grape") ? "YES (False Positive or Possibility)" : "NO (Definitely)");
    printf("Contains 'orange': %s\n", bf_possibly_contains(bf, "orange") ? "YES (False Positive or Possibility)" : "NO (Definitely)");
    printf("str: %s", bf->bits);
    print_bit_array(bf->bits,bf->size_bytes);
    // 销毁
    bf_destroy(bf);

    return 0;
}