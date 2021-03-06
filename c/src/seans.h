
/*
 * Copyright 2011-2019, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
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

int nseans;
int nr0;
int nr1;

int u1;

int dat[170][18];
int datm[680];
int datp[680];
int m[680];
} seans1s_data;


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

int dat1[360][7];
int dat2[360][7];
int dat0[360];
int m[360];
} seans1c_data;

typedef struct __attribute__((packed))
{
int day;
int month;
int year;
int hour;
int minute;
int second;
} seans1kd_data;


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

DLL_EXPORT double seans1s_alt(int H);
DLL_EXPORT double seans1s_alt_front(int H);
DLL_EXPORT double seans1s_alt_795(int H);

DLL_EXPORT int seans1s_test(char *filename);
DLL_EXPORT int seans1s_load_header(char *filename, seans_header *header);
DLL_EXPORT int seans1s_load(char *filename, seans1s_data *seans);
DLL_EXPORT int seans1s_save(char *filename, seans1s_data *seans);
DLL_EXPORT int seans1s_saveM0(char *filename);
DLL_EXPORT int seans1s_saveM1(char *filename, int m, int num);
DLL_EXPORT int seans1s_saveM2(char *filename, int m[680]);
DLL_EXPORT int seans1s_saveM3(char *filename, seans1s_data *seans);
DLL_EXPORT int seans1s_noise(seans1s_data *seans, double *noise_acf, int len, int alt_start, int alt_end);

DLL_EXPORT double seans1c_alt(int H);
DLL_EXPORT int seans1c_test(char *filename);
DLL_EXPORT int seans1cv_load(char *filename, seans1c_data *seans);
DLL_EXPORT int seans1c_load(char *filename, seans1c_data *seans);
DLL_EXPORT int seans1c_noise1(seans1c_data *seans, double *noise_acf, int len, int alt_start, int alt_end);
DLL_EXPORT int seans1c_noise2(seans1c_data *seans, double *noise_acf, int len, int alt_start, int alt_end);
DLL_EXPORT int seans1c_saveM0(char *filename);
DLL_EXPORT int seans1c_saveM3(char *filename, seans1c_data *seans);

DLL_EXPORT int seans1kd_load(char *filename, seans1kd_data *seans);

DLL_EXPORT int seans1v_test(char *filename);
DLL_EXPORT int seans1v_load(char *filename, seans1v_data *seans);
DLL_EXPORT int seans1v_saveM0(char *filename);
DLL_EXPORT int seans1v_saveM3(char *filename, seans1v_data *seans);

#ifdef __cplusplus
}
#endif

#endif // _Included_seans
