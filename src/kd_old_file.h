
/*
 * Copyright 2011-2021, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#ifndef _Included_seans
#define _Included_seans


#ifndef _POSIX_SOURCE
    #define _POSIX_SOURCE 2
#endif


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>

#include "header.h"
#include "integer.h"
#include "mytime.h"



typedef struct __attribute__((packed))
{
int day;
int month;
int year;
int hour;
int minute;
int second;
} seans1kd_data;



#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

DLL_EXPORT int seans1kd_load(char *filename, seans1kd_data *seans);

#ifdef __cplusplus
}
#endif

#endif // _Included_seans
