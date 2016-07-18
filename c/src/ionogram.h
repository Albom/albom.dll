
/*
 * Copyright 2011-2016, Oleksandr Bogomaz (albom85@yandex.ru)
 */

#ifndef _Included_ionogram
#define _Included_ionogram

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct __attribute__((packed))
{
int day;
int month;
int year;
int hour;
int minute;
int second;

int nr; // number of repeats (���������� �������� �� ����� �������)
int nf; // number of frequencies (���������� ������)
int nh; // number of altitudes (���������� �����)

unsigned
char data[16][400][250]; // nr, nf, nh

} ionogram_basis;

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif


DLL_EXPORT int ionogram_load(char *filename, ionogram_basis *ionogram);


#ifdef __cplusplus
}
#endif


#endif // _Included_ionogram

