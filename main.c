#include "exkey.h"


int main() {
    int  i = 0, flag = 1;
    struct bit bitA, bitB, bita, bitb;
  //  printf("假定错误率为0.2!\n");
  //  printf("字符串长度：%d\n\n", num);
    //scanf("%d", &num);
    char *a = (char *)malloc(num * sizeof(char));
    init(a, num);
    bitA = set(a, num);
    free(a);
  //  printf("Alice send message:\n");
  //  show(bitA);
    bitB = change_rand(bitA);
 //   printf("\nBob receive message:\n");
  //  show(bitB);

//优先提取
    while(i < 2) {
     //   printf("第%d次优先提取：\n", i + 1);
     //   printf("Alice message'xor:\n");
        bita = xor(bitA);
      //  show(bita);
      //  printf("\nBob message'xor:\n");
        bitb = xor(bitB);
      //  show(bitb);

        bitA = ADcmp(bitA, bitb);
     //   printf("\nAlice after delete:\n");
      //  show(bitA);
        bitB = ADcmp(bitB, bita);
      //  printf("\nBob after delete:\n");
      //  show(bitB);
        flag = cmp_all(bitA, bitB);
        Free(bita);
        Free(bitb);
        i++;
    }

//信息协调
    i = 0;
    while(flag) {
        perm_rand(bitA);
        perm_rand(bitB);

     //   printf("第%d次信息协调：\n", i + 1);
     //   printf("Alice message getcheck:\n");
        bita = getcheck(bitA);
      //  show(bita);
     //   printf("\nBob message getcheck:\n");
        bitb = getcheck(bitB);
      //  show(bitb);

        bitA = HMcmp_A(bitA, bitb);
        bitB = HMcmp_B(bitB, bita);
     //   printf("\nAlice after delete:\n");
      //  show(bitA);
      //  printf("\nBob after delete:\n");
      //  show(bitB);
        i++;

        flag = cmp_all(bitA, bitB);
     //   printf("flag=%d\n", flag);
        Free(bita);
        Free(bitb);
    }
    Free(bitA);
    Free(bitB);
    return 0;
}
