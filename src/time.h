
/*
 * Copyright 2011-2021, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#ifndef _Included_mytime
#define _Included_mytime

#include <stdio.h>
#include <string.h>
#include <time.h>

#ifdef BUILD_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

DLL_EXPORT time_t date_2unixtime(int DD, int MM, int YY, int hh, int mm, int ss);
DLL_EXPORT int unixtime_2date(time_t timestamp, int *DD, int *MM, int *YY, int *hh, int *mm, int *ss);
DLL_EXPORT double time_2decimal(int hh, int mm, int ss);
DLL_EXPORT int time_2str(int hh, int mm, int ss, char *timestr);
DLL_EXPORT int date_2str(int dd, int mm, int yy, char *datestr);
DLL_EXPORT int time_2sec(int hh, int mm, int ss);
DLL_EXPORT int time_accum_num(int minutes);
DLL_EXPORT int date_year_leap(int year);
DLL_EXPORT int date_next(int *day, int *month, int *year);
DLL_EXPORT int date_valid(int day, int month, int year);
DLL_EXPORT int time_from_str(int *hh, int *mm, int *ss, const char *timestr);
DLL_EXPORT void tdatetime_2date(double tdatetime, int *DD, int *MM, int *YY, int *hh, int *mm, int *ss, int *ms);
DLL_EXPORT int date_from_str(int *dd, int *mm, int *yy, const char *datestr);
DLL_EXPORT int time_linear(double *arr, int length);
DLL_EXPORT int time_normalize(double *arr, int length);
#ifdef __cplusplus
}
#endif

#endif  // _Included_mytime
