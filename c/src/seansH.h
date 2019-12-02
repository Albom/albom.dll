
/*
 * Copyright 2011-2019, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#ifndef SEANSH_H_INCLUDED
#define SEANSH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __attribute__((packed))
{

int day;
int month;
int year;
int hour;
int minute;
int second;

int nH;
int nP;
int nR;

double dT; // время между отсчётами
double dH; // время между высотами

short magic;

long long dat1[680][114];
long long dat2[680][114];
long long dat3[680][114];
long long dat4[680][114];
long long dat01[680];
long long dat02[680];
long long datps1[680];
long long datps2[680];
long long dat03[680];
long long dat04[680];

} seansH_data ;



#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

DLL_EXPORT int seansH_load(char *filename, seansH_data *seans);

#ifdef __cplusplus
}
#endif

#endif // SEANSH_H_INCLUDED
