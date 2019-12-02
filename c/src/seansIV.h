
/*
 * Copyright 2011-2019, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#ifndef SEANSIV_H_INCLUDED
#define SEANSIV_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#define OK          (0)
#define ERR_FILE    (1)
#define ERR_MEM     (2)

typedef struct __attribute__((packed))
{

char type;
short *data1;
short *data2;

} seansIV_scan ;


typedef struct __attribute__((packed))
{

int ver;
char date[20];
int nR;
int nP;
int dT;

seansIV_scan *scans;

} seansIV_data ;

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

DLL_EXPORT int seansIV_load(char *filename, seansIV_data *seans);
DLL_EXPORT int seansIV_close(seansIV_data *seans);

#ifdef __cplusplus
}
#endif


#endif // SEANSIV_H_INCLUDED
