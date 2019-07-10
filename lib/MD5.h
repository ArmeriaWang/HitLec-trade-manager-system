
/*
TYPE  HEADER
NAME  MD5.h
PATH  ./lib/MD5.h
*/

#ifndef TRADE_MANAGER_SYSTEM_MD5_H
#define TRADE_MANAGER_SYSTEM_MD5_H

#include "basic_def.h"

#define max_length 128 + 5

char str[max_length * 2];
char tmp[max_length];

unsigned sex[max_length];

unsigned s[64] = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22, \
				   5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20, \
                   4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23, \
				   6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21} ;

unsigned K[64] = { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, \
                   0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, \
                   0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, \
                   0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, \
                   0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, \
                   0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, \
                   0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, \
                   0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, \
                   0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, \
                   0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, \
                   0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, \
                   0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, \
                   0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, \
                   0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, \
                   0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, \
                   0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391} ;

unsigned a0;  //A
unsigned b0;  //B
unsigned c0;  //C
unsigned d0;  //D

unsigned M[16], con_sex[100];

unsigned left_rotate(unsigned val, unsigned n);
void     init_value();
void     convert_to_sexa_str(const char* src, char* dest);
void     convert_to_sexa_num(const char* src, unsigned *dest);
unsigned reverse_sexa(unsigned x);
void     get_MD5(const char* inp, unsigned* dest);

unsigned left_rotate(unsigned val, unsigned n)
{
    return (val >> (32 - n)) | (val << n);
}

void init_value()
{
    for (char i = '0'; i <= '9'; i++) {
        con_sex[(int)i] = (unsigned)i - 48;
    }
    con_sex[(int)'A'] = 10;
    con_sex[(int)'B'] = 11;
    con_sex[(int)'C'] = 12;
    con_sex[(int)'D'] = 13;
    con_sex[(int)'E'] = 14;
    con_sex[(int)'F'] = 15;

    a0 = 0x67452301;  //A
    b0 = 0xefcdab89;  //B
    c0 = 0x98badcfe;  //C
    d0 = 0x10325476;  //D

    memset(M, 0, sizeof(M));
    memset(sex, 0, sizeof(sex));
    str[0] = '\0';
    tmp[0] = '\0';
}

void convert_to_sexa_str(const char* src, char* dest)
{
    dest[0] = '\0';
    int len = (int)strlen(src);
    for (int i = 0; i < len; i++) {
        sprintf(tmp, "%X", (unsigned)src[i]);
        strcat(dest, tmp);
    }

}

void convert_to_sexa_num(const char* src, unsigned *dest)
{
    int len = (int)strlen(src);
    int j = 0;
    for (int i = 0; i < len; i += 2) {
        dest[j] = con_sex[(int)src[i]] * 16 + con_sex[(int)src[i + 1]];
        j++;
    }
}

unsigned reverse_sexa(unsigned x)
{
    unsigned k = (1 << 24), y = 0;
    while (x) {
        y += (x % 256) * k;
        x >>= 8;
        k >>= 8;
    }
    return y;
}

void get_MD5(const char* inp, unsigned* dest)
{
    init_value();

    convert_to_sexa_str(inp, str);

    strcat(str, "8");
    while (strlen(str) % 128 != 112) {
        strcat(str, "0");
    }

    sprintf(tmp, "%X", (int)strlen(inp)*8);
    strcat(str, tmp);
    while (strlen(str) % 128 != 0) {
        strcat(str, "0");
    }

    convert_to_sexa_num(str, sex);

    int len = (int)strlen(str) / 2;
    for (int t = 0; t < len; t += 64) {

        int k = t;
        for (int j = 0; j <= 15; j++) {
            M[j] = sex[k + 3] * (1 << 24) + sex[k + 2] * (1 << 16) \
                 + sex[k + 1] * (1 <<  8) + sex[k];
            k += 4;
        }

        unsigned A = a0, B = b0, C = c0, D = d0;
        for (int i = 0; i < 64; i++) {
            unsigned F;
            int g;
            if (i <= 15) {
                F = (B & C) | ((~B) & D);
                g = i;
            }
            else if (i <= 31) {
                F = (D & B) | ((~D) & C);
                g = (5 * i + 1) % 16;
            }
            else if (i <= 47) {
                F = B ^ C ^ D;
                g = (3 * i + 5) % 16;
            }
            else {
                F = C ^ (B | (~D));
                g = (7 * i) % 16;
            }
            F = F + A + K[i] + M[g];
            A = D;
            D = C;
            C = B;
            B = B + left_rotate(F, s[i]);
        }
        a0 += A;
        b0 += B;
        c0 += C;
        d0 += D;
    }

    dest[1] = reverse_sexa(a0);
    dest[2] = reverse_sexa(b0);
    dest[3] = reverse_sexa(c0);
    dest[4] = reverse_sexa(d0);
}

#endif //TRADE_MANAGER_SYSTEM_MD5_H
