#define MD5_HASH_SIZE 16

struct md5_context {
    // state
    unsigned int a;
    unsigned int b;
    unsigned int c;
    unsigned int d;
    // number of bits, modulo 2^64 (lsb first)
    unsigned int count[2];
    // input buffer
    unsigned char input[64];
    // current block
    unsigned int block[16];
};

struct md5_digest {
    unsigned char bytes[MD5_HASH_SIZE];
};

void md5_init(struct md5_context *ctx);
void md5_update(struct md5_context* ctx, const void* buffer, unsigned int buffer_size);
void md5_finalize(struct md5_context* ctx, struct md5_digest* digest);
char* md5(const char* input);