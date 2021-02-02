// The four core functions for MD5.
// F and G are optmized per the Colin Plumb implementation.
#define F(x, y, z) (z ^ (x & (y ^ z)))
#define G(x, y, z) F(z, x, y)
#define H(x, y, z) (x ^ y ^ z)
#define I(x, y, z) (y ^ (x | ~z))

#define ROTATE_LEFT(x, s) (x<<s | x>>(32-s))
