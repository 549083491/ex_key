#ifndef EXKEY_INCLUDED
#define EXKEY_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

#define NOP 2
#define num 4000

struct bit {
    int len;
    char *bit;
};


//释放malloc分配出来的内存
void Free(struct bit A);

//随机产生字符串
void init(char *a, int len);

//将收到的字符串和长度改成结构体存储
struct bit set(char *a, int len);

//随机改变某几位的值 达到正常传输中发生的误比特率
struct bit change_rand(struct bit A);

//两位两位异或
struct bit xor(struct bit A);

//复制比特串
struct bit copy(struct bit A);

//删除第i位
struct bit delete(struct bit A, int i);

//删除比特数中需要删除的数
struct bit del(struct bit A);

//显示比特串
void show(struct bit A);

//将要删除的位数数值置为NOP 优先提取
struct bit ADcmp(struct bit A, struct bit B);

//随机置换(信息协调)
void perm_rand(struct bit A);

//得到奇偶校验位
struct bit getcheck(struct bit A);

//比较两个数组是否全部相同
int cmp_all(struct bit A, struct bit B);

//将要删除的位数数值置为NOP 信息协调
struct bit HMcmp_A(struct bit A, struct bit B); //A收到B发来的奇偶校验位进行比较

struct bit HMcmp_B(struct bit A, struct bit B); //B收到A发来的奇偶校验位进行比较






#endif //EXKEY_INCLUDED
