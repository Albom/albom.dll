
/*
 * Copyright 2011-2016, Oleksandr Bogomaz (albom85@yandex.ru)
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
