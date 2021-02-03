
/*
 * Copyright 2011-2021, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#ifndef _Included_seans2
#define _Included_seans2

#ifndef _POSIX_SOURCE
    #define _POSIX_SOURCE 2
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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

int dat1[680][19];
int dat2[680][19];
int dat3[680][19];
int dat4[680][19];
int dat01[680];
int dat02[680];
int datps1[680];
int datps2[680];
int dat03[680];
int dat04[680];

int m[680];

} seans2_data ;

int seans2_noise(seans2_data *seans, double *noise_acf, int len, int alt_start, int alt_end, int ch);

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif
DLL_EXPORT int seans2_load(char *filename, seans2_data *seans);
DLL_EXPORT int seans2_save(char *filename, seans2_data *seans);
DLL_EXPORT int seans2_saveM0(char *filename);
DLL_EXPORT int seans2_saveM3(char *filename, seans2_data *seans);
DLL_EXPORT int seans2_test(char *filename);
DLL_EXPORT int seans2_load_header(char *filename, seans_header *header);
DLL_EXPORT double seans2_altL(int num);
DLL_EXPORT double seans2_altS(int num);
DLL_EXPORT double seans2_altL_front(int num);
DLL_EXPORT int seans2_noise1(seans2_data *seans, double *acf_noise, int len, int alt_start, int alt_end);
DLL_EXPORT int seans2_noise2(seans2_data *seans, double *acf_noise, int len, int alt_start, int alt_end);
DLL_EXPORT int seans2_noise3(seans2_data *seans, double *acf_noise, int len, int alt_start, int alt_end);
DLL_EXPORT int seans2_noise4(seans2_data *seans, double *acf_noise, int len, int alt_start, int alt_end);

#ifdef __cplusplus
}
#endif

#endif // _Included_seans2
