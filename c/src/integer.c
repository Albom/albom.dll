
/*
 * Copyright 2011-2019, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#include "integer.h"

/// =============================

int makeint(unsigned char c[4])
{
return ( ((c[0]<<24)&0xff000000)|((c[1]<<16)&0xff0000) |((c[2]<<8)&0xff00)|((c[3])&0xff));
}

/// =============================

void makearray(unsigned char c[4], int i)
{
c[0] = (i & 0xff000000) >> 24;
c[1] = (i & 0xff0000) >> 16;
c[2] = (i & 0xff00) >> 8;
c[3] = (i & 0xff);
}

/// =============================
