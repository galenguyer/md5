#include "md5.h"

// The four core functions for MD5.
// F and G are optmized per the Colin Plumb implementation.
#define F(x, y, z) (z ^ (x & (y ^ z)))
#define G(x, y, z) F(z, x, y)
#define H(x, y, z) (x ^ y ^ z)
#define I(x, y, z) (y ^ (x | ~z))

#define ROTATE_LEFT(x, s) (x<<s | x>>(32-s))

#define STEP(f, a, b, c, d, x, s, t) ( \
    a += f(b, c, d) + x + t, \
    a = ROTATE_LEFT(a, s), \
    a += b \
)

void md5_init(struct md5_context* ctx)
{
    ctx->a = 0x67452301;
    ctx->b = 0xefcdab89;
    ctx->c = 0x98badcfe;
    ctx->d = 0x10325476;

    ctx->count[0] = 0;
    ctx->count[1] = 0;
}
