//借鉴自：https://blog.csdn.net/QQ1084283172/article/details/52334027?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522165000137816782092933784%2522%252C%2522scm%2522%253A%252220140713.130102334.pc%255Fall.%2522%257D&request_id=165000137816782092933784&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~first_rank_ecpm_v1~rank_v31_ecpm-6-52334027.142^v9^pc_search_result_cache,157^v4^control&utm_term=md5%E7%AE%97%E6%B3%95c%2B%2B&spm=1018.2226.3001.4187
#ifndef MD5_H  
#define MD5_H  
#include <stdio.h>
#include <string.h>
 
typedef struct
{
	unsigned int count[2];
	unsigned int state[4];
	unsigned char buffer[64];
}MD5_CTX;
 
 
#define F(x,y,z) ((x & y) | (~x & z))  
#define G(x,y,z) ((x & z) | (y & ~z))  
#define H(x,y,z) (x^y^z)  
#define I(x,y,z) (y ^ (x | ~z))  
#define ROTATE_LEFT(x,n) ((x << n) | (x >> (32-n)))  
 
#define FF(a,b,c,d,x,s,ac) { \
a += F(b, c, d) + x + ac; \
a = ROTATE_LEFT(a, s); \
a += b; \
}
 
#define GG(a,b,c,d,x,s,ac) { \
	a += G(b, c, d) + x + ac; \
	a = ROTATE_LEFT(a, s); \
	a += b; \
}
 
#define HH(a,b,c,d,x,s,ac) { \
	a += H(b, c, d) + x + ac; \
	a = ROTATE_LEFT(a, s); \
	a += b; \
}
#define II(a,b,c,d,x,s,ac) { \
	a += I(b, c, d) + x + ac; \
	a = ROTATE_LEFT(a, s); \
	a += b; \
}

class MD5
{
private:
    MD5_CTX * context;
public:
    MD5();
    ~MD5();
    void MD5Update(MD5_CTX *context, unsigned char *input, unsigned int inputlen);
    void MD5Final(MD5_CTX *context, unsigned char digest[16]);
    void MD5Transform(unsigned int state[4], unsigned char block[64]);
    void MD5Encode(unsigned char *output, unsigned int *input, unsigned int len);
    void MD5Decode(unsigned int *output, unsigned char *input, unsigned int len);
    MD5_CTX * getContext();
};


 
#endif  
