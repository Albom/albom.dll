
/*
 * Copyright 2011-2021, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#ifndef SEANS3C3_H_INCLUDED
#define SEANS3C3_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define OK          (0)
#define ERR_FILE    (1)
#define ERR_MEM     (2)
#define ERR_TYPE    (3)

typedef struct __attribute__((packed))
{

int np;
int nr;
double lag;

double *tdatetime;

short *dat1;
short *dat2;
short *dat3;

} seans3c3_data ;

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif
DLL_EXPORT int seans3c3_load(char *filename, seans3c3_data *seans);
//DLL_EXPORT int seansRd_close(seansRd_data *seans);
#ifdef __cplusplus
}
#endif


#endif // SEANS3C3_H_INCLUDED
