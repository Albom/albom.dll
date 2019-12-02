
/*
 * Copyright 2011-2019, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#ifndef _Included_myfiles
#define _Included_myfiles

#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

DLL_EXPORT int filelist_get(char *dir_name, char *filelist);
DLL_EXPORT int filelist_get_filename(char *filelist, char *filename, int num);

DLL_EXPORT int file_add_i (
                    char *fname,
                    int *in,
                    int il,
                    char *format
                    );

DLL_EXPORT int file_add_d(
        char *fname,
        double *in,
        int il,
        char *format
        );

DLL_EXPORT int file_newline (
        char *fname
        );

DLL_EXPORT int file_creat (
        char *fname
        );

DLL_EXPORT int file_creat_and_add_s(
        char *fname,
        char *in
        );

DLL_EXPORT int file_add_s(
        char *fname,
        char *in,
        char *format
        );

DLL_EXPORT int file_add_sh(
        char *fname,
        short *in,
        int il,
        char *format
        );

DLL_EXPORT int file_add_bin_d(
        char *fname,
        double *in,
        int il
        );

DLL_EXPORT int file_load_all_d (
        char *fname,
        double *buf
        );

DLL_EXPORT int file_size (char *fname);

DLL_EXPORT int buffer_clear(char *buf);

DLL_EXPORT int  buffer_newline(
        char *buf
        );

DLL_EXPORT int buffer_add_s(
        char *buf,
        char *in,
        char *format
        );

DLL_EXPORT int buffer_add_i(
        char *buf,
        int *in,
        int il,
        char *format
        );

DLL_EXPORT int buffer_add_d(
        char *buf,
        double *in,
        int il,
        char *format
        );

DLL_EXPORT int file_table_load(
        char *filename,
        int *c,
        int *r,
        double *arr
        );

#ifdef __cplusplus
}
#endif

#endif // _Included_myfiles

