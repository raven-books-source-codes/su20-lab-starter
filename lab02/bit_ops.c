#include "bit_ops.h"
#include <stdio.h>

// Return the nth bit of x.
// Assume 0 <= n <= 31
unsigned get_bit(unsigned x, unsigned n) { return (x >> n) & 1; }
// Set the nth bit of the value of x to v.
// Assume 0 <= n <= 31, and v is 0 or 1
void set_bit(unsigned *x, unsigned n, unsigned v) {
  // YOUR CODE HERE
  // The key formula is ( a^b^a = b )
  *x ^= ((*x) & (1 << n)) ^ (v << n);
}
// Flip the nth bit of the value of x.
// Assume 0 <= n <= 31
void flip_bit(unsigned *x, unsigned n) {
  // YOUR CODE HERE
  set_bit(x, n, !get_bit(*x, n));
}
