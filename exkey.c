#include "exkey.h"

//释放malloc分配出来的内存
void Free(struct bit A)
{
    A.len = 0;
    free(A.bit);
}

//随机产生字符串
void init(char *a, int len) {
    int i;
    srand( time(NULL) );
    for(i = 0; i < len; i++) {
        a[i] = rand() % 2;
    }
}

//将收到的字符串和长度改成结构体存储
struct bit set(char *a, int len) {
    struct bit A;
    A.bit = (char *) malloc(len);
    memcpy(A.bit, a, len);
    A.len = len;
    return A;
}

//随机改变某几位的值 达到正常传输中发生的误比特率
struct bit change_rand(struct bit A) {
    int i, m;
    struct bit B = copy(A);
    srand( A.len );
    for(i = 0; i < B.len / 2; i++) {
        m = rand() % B.len;
        B.bit[m] = !B.bit[m];
    }
    return B;
}

//两位两位异或
struct bit xor(struct bit A) {
    int i, j;
    struct bit B;
    B.len = A.len / 2;
    if(A.len % 2 != 0) {
        B.len++;
    }
    B.bit = (char *) malloc(B.len);
    for(i = 0, j = 0; j < A.len / 2; j++) {
        B.bit[j] = A.bit[i] ^ A.bit[i + 1];
        i += 2;
    }
    if(A.len % 2 != 0) {
        B.bit[j] = A.bit[A.len - 1];
    }
    return B;
}

//复制比特串
struct bit copy(struct bit A) {
    struct bit B;
    B.len = A.len;
    B.bit = malloc(A.len);
    memcpy(B.bit, A.bit, A.len);
    return B;
}

//删除第i位
struct bit delete(struct bit A, int i) {
    struct bit B;
    B.len = A.len - 1;
    B.bit = malloc(A.len - 1);
    memcpy(B.bit, A.bit, i);
    memcpy(B.bit + i, A.bit + i + 1, A.len - 1 - i);
    Free(A);
    return B;
}

//删除比特数中需要删除的数
struct bit del(struct bit A) {
    int i = 0;
    struct bit B;
    B = copy(A);
    Free(A);
    while(i < B.len) {
        if(B.bit[i] == NOP)
            B = delete(B, i);
        else
            i++;
    }
    return B;
}

//显示比特串
void show(struct bit A) {
    int i;
    printf("len:%d\n", A.len);
    printf("bit:");
    for(i = 0; i < A.len; i++) {
        printf("%d", A.bit[i]);
        if((i + 1) % 4 == 0)
            printf(" ");
    }
    printf("\n");
}

//将要删除的位数数值置为NOP 优先提取
struct bit ADcmp(struct bit A, struct bit B) {
    struct bit bita;
    int i = 0;
    bita = xor(A);
    while(i < bita.len) {
        if(bita.bit[i] != B.bit[i]) {
            A.bit[2 * i] = NOP;
            A.bit[2 * i + 1] = NOP;
        } else {
            if(i % 2 == 0) {
                if(A.bit[2 * i + 1] == 1)
                    A.bit[2 * i] = NOP;
                else
                    A.bit[2 * i + 1] = NOP;
            } else {
                if(A.bit[2 * i + 1] == 1)
                    A.bit[2 * i + 1] = NOP;
                else
                    A.bit[2 * i ] = NOP;
            }
        }
        i++;
    }
    Free(bita);
    A = del(A);
    return A;
}

//随机置换(信息协调)
void perm_rand(struct bit A) {
    int i, m;
    char n;
    srand(A.len);
    for(i = 0; i < A.len / 2; i++) {
        m = rand() % A.len;
        n = A.bit[i];
        A.bit[i] = A.bit[m];
        A.bit[m] = n;
    }
}

//得到奇偶校验位
struct bit getcheck(struct bit A) {
    int i = 0, j, count;
    struct bit B;
    B.len = A.len / 8;
    /*  if(A.len % 8 != 0)
          B.len++;*/
    B.bit = malloc(B.len);
    while(i < B.len) {
        j = 0;
        count = 0;
        while(j < 8) {
            if(A.bit[i * 8 + j] == 1)
                count++;
            j++;
        }
        if(count % 2 == 1)
            B.bit[i] = 1;
        else
            B.bit[i] = 0;
        i++;
    }
    j = 0;
   /* while(8 * i + j < A.len) {
        A.bit[i * 8 + j] = NOP;
        j++;
    }*/
    return B;
}

//比较两个数组是否全部相同
int cmp_all(struct bit A, struct bit B) {
    int i = 0, count = 0;
    while(i < A.len) {
        if(A.bit[i] != B.bit[i])
            count++;
        i++;
    }
    return count;
}

char pa[num / 8 * 3] = {0}; //存放计算Alice的伴随式
//将要删除的位数数值置为NOP 信息协调
struct bit HMcmp_A(struct bit A, struct bit B) { //A收到B发来的奇偶校验位进行比较
    struct bit bita;
    int i = 0;
    bita = getcheck(A);
    while(i < bita.len) {
        A.bit[8 * i] = NOP;
        if(bita.bit[i] != B.bit[i]) {
            //74汉明码
            pa[2 + 3 * i] = A.bit[8 * i + 7] ^ A.bit[8 * i + 6] ^ A.bit[8 * i + 5] ^ A.bit[8 * i + 3];
            pa[1 + 3 * i] = A.bit[8 * i + 7] ^ A.bit[8 * i + 6] ^ A.bit[8 * i + 4] ^ A.bit[8 * i + 2];
            pa[3 * i] = A.bit[8 * i + 7] ^ A.bit[8 * i + 5] ^ A.bit[8 * i + 4] ^ A.bit[8 * i + 1];
            A.bit[8 * i + 1] = A.bit[8 * i + 2] = A.bit[8 * i + 3] = NOP;
        }
        i++;
    }
    A = del(A);
    Free(bita);
    return A;
}

struct bit HMcmp_B(struct bit A, struct bit B) { //B收到A发来的奇偶校验位进行比较
    struct bit bitb;
    int i = 0, m, j;
    bitb = getcheck(A);
    char b[3] = {0};
    while(i < bitb.len) {
        if(bitb.bit[i] != B.bit[i]) {
            b[2] = A.bit[8 * i + 7] ^ A.bit[8 * i + 6] ^ A.bit[8 * i + 5] ^ A.bit[8 * i + 3];
            b[1] = A.bit[8 * i + 7] ^ A.bit[8 * i + 6] ^ A.bit[8 * i + 4] ^ A.bit[8 * i + 2];
            b[0] = A.bit[8 * i + 7] ^ A.bit[8 * i + 5] ^ A.bit[8 * i + 3] ^ A.bit[8 * i + 1];
            j = 0;
            while(j < 3) {
                b[j] = b[j] ^ pa[j + 3 * i];
                j++;
            }
            m = b[0] + b[1] * 2 + b[2] * 4;
            A.bit[8 * i + m] = !A.bit[8 * i + m];
            A.bit[8 * i + 1] = A.bit[8 * i + 2] = A.bit[8 * i + 3] = NOP;
        }
        A.bit[8 * i] = NOP;
        i++;
    }
    A = del(A);
    Free(bitb);
    return A;
}

