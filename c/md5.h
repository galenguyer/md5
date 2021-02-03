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
};

void md5_init(struct md5_context *ctx);