
/*
 * Copyright 2011-2019, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#ifndef SEANSRD_H_INCLUDED
#define SEANSRD_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define OK          (0)
#define ERR_FILE    (1)
#define ERR_MEM     (2)

typedef struct __attribute__((packed))
{

int day;
int month;
int year;
int hour;
int minute;
int second;

int nr;
int np;
int nc;

double lag;
double freq;

int *dat1;
int *dat2;
int *dat3;
int *dat4;

} seansRd_data ;

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif
DLL_EXPORT int seansRd_load(char *filename, seansRd_data *seans);
DLL_EXPORT int seansRd_close(seansRd_data *seans);
#ifdef __cplusplus
}
#endif

#endif // SEANSRD_H_INCLUDED
