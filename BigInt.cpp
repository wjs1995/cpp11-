//
// Created by wangj on 2025/12/10.
//
#include "dep.h"

int main() {
    const string str = "999911119";
    const string str2 = "199911119";
    const int i = str.length() -1;
    const int j = str2.length() -1;
    cout << i << endl;
    cout << j << endl;
    const int k = str[i] - '0' + str2[j] - '0';
    cout << k << endl;

    cout << 9 + '9' - '0' << endl;
    return 0;
}
