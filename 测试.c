//
// Created by wangj on 2025/12/11.
//

#include <stdio.h>

int sum(int a, int b) {
    return a + b;
}
int main() {
    int a= 10;
    int b = 20;
    int ret = sum(a, b);
    printf("Hello World:%d",ret);
};