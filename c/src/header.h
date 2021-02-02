
/*
 * Copyright 2011-2021, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#ifndef _Included_header
#define _Included_header

typedef struct __attribute__((packed))
{
int day;
int month;
int year;
int hour;
int minute;
int second;

int nseans;
int nr0;
int nr1;

int u1;
} seans_header;

#endif // _Included_header
