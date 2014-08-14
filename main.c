
#include "exkey.h"


int main() {
    int  i = 0, flag = 1;
    struct bit bitA, bitB, bita, bitb;
    char *a = (char *)malloc(num * sizeof(char));
    init(a, num);
    bitA = set(a, num);
    free(a);
    bitB = change_rand(bitA);
//优先提取
    while(i < 2) {
        bita = xor(bitA);
        bitb = xor(bitB);
        bitA = ADcmp(bitA, bitb);
        bitB = ADcmp(bitB, bita);
        flag = cmp_all(bitA, bitB);
        Free(bita);
        Free(bitb);
        i++;
    }
    i = 0;
//信息协调
    while(flag) {
        perm_rand(bitA);
        perm_rand(bitB);
        bita = getcheck(bitA);
        bitb = getcheck(bitB);
        bitA = HMcmp_A(bitA, bitb);
        bitB = HMcmp_B(bitB, bita);
        i++;
        flag = cmp_all(bitA, bitB);
        Free(bita);
        Free(bitb);
    }
    Free(bitA);
    Free(bitB);
    return 0;
}
