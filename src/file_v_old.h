
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

int dat_cos[230][11];
int dat_sin[230][11];
int datm_cos[230];
int datm_sin[230];
int m[230];
} seans1v_data;

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

DLL_EXPORT int seans1v_test(char *filename);
DLL_EXPORT int seans1v_load(char *filename, seans1v_data *seans);
DLL_EXPORT int seans1v_saveM0(char *filename);
DLL_EXPORT int seans1v_saveM3(char *filename, seans1v_data *seans);

#ifdef __cplusplus
}
#endif

#endif // _Included_seans
