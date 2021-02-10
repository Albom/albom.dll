
/*
 * Copyright 2011-2021, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#ifndef _Included_filters
#define _Included_filters

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
DLL_EXPORT int razr_load(char *filename, double *array, int len);
DLL_EXPORT int filter_load(char *filtername, double *array, int len);
DLL_EXPORT double filter_freq_resp(char *filtername, double freq);  // Frequency response (АЧХ). На входе - частота в герцах
#ifdef __cplusplus
}
#endif

#endif  // _Included_filters
