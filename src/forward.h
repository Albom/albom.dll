
/*
 * Copyright 2011-2021, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#ifndef _Included_forward
#define _Included_forward

#include <math.h>
#include <string.h>
#include "math.h"

#include "data_phi_0_20_0001.h"

#define SPEED_OF_LIGHT      (2.99792458e8)

#define FREQUENCY_KHARKIV   (158.0036e6)    // Kharkiv
#define FREQUENCY_MILLSTONE (440.2e6)       // Millstone Hill

#define WAVELENGTH_KHARKIV ((double)SPEED_OF_LIGHT/(double)FREQUENCY_KHARKIV)     // Kharkiv
#define WAVELENGTH_MILLSTONE ((double)SPEED_OF_LIGHT/(double)FREQUENCY_MILLSTONE) // Millstone Hill

#define WAVELENGTH WAVELENGTH_KHARKIV

#define EPSILON0        (8.854187817e-12)
#define BOLTZMANN       (1.3806504e-23)
#define ATOMIC_CONSTANT (1.6605402e-27)
#define MASS_ELECTRON   (9.10938188e-31)
#define CHARGE_ELECTRON (-1.602176487e-19)

#define M_SQRTPI 1.7724538509055160272981674833411

#ifndef MAX_PATH
#define MAX_PATH (260)
#endif // MAX_PATH

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

DLL_EXPORT double spectrum_1(double m1, double ti, double te, double freq);
DLL_EXPORT int acf_1(double m1, double ti, double te, double acf[], int len);

DLL_EXPORT double spectrum_2(double m1, double m2, double g1, double ti, double te, double freq);
DLL_EXPORT int acf_2(double m1, double m2, double g1, double ti, double te, double acf[], int len);

DLL_EXPORT double spectrum_3(double m1, double m2, double m3, double g1, double g2, double ti, double te, double freq);
DLL_EXPORT int acf_3(double m1, double m2, double m3, double g1, double g2, double ti, double te, double acf[], int len);

DLL_EXPORT double spectrum_3_full(double m1, double m2, double m3, double g1, double g2, double ti, double te, double ne, int iskD, double freq);
DLL_EXPORT int acf_3_full(double m1, double m2, double m3, double g1, double g2, double ti, double te, double ne, int iskD, double acf[], int len, double dt);

DLL_EXPORT double spectrum_3_full_millstone(double m1, double m2, double m3, double g1, double g2, double ti, double te, double ne, int iskD, double freq);
DLL_EXPORT int acf_3_full_millstone(double m1, double m2, double m3, double g1, double g2, double ti, double te, double ne, int iskD, double acf[], int len, double dt);

DLL_EXPORT int acf_library_light_short(FILE *f, int *temperatures, int temperatures_len, double ti, double te, double *acf, int len);
DLL_EXPORT int acf_library_light_short_conv(FILE *f, int *temperatures, int temperatures_len, double ti, double te, double *acf, int len);
DLL_EXPORT int library_light_list_of_temperatures_get(int *temperatures);
DLL_EXPORT int library_light_list_of_temperatures_get2(int *temperatures);
DLL_EXPORT int library_light_list_get(char* prefix, int he_percent_int, char *filelist);
DLL_EXPORT int library_light_list_get_filename(char *filename, char *filelist, int num);

DLL_EXPORT int library_heavy_list_of_temperatures_get(int *temperatures);
DLL_EXPORT int acf_library_heavy(FILE *f, int *temperatures, int temperatures_len, double ti, double te, double *acf, int len);

DLL_EXPORT int library_oxygen_list_of_temperatures_get(int *temperatures);
DLL_EXPORT int acf_library_oxygen(FILE *f, int *temperatures, int temperatures_len, double ti, double te, double *acf, int len);

DLL_EXPORT int library_millstone_list_of_temperatures_get(int *temperatures);
DLL_EXPORT int acf_library_millstone(FILE *f, int *temperatures, int temperatures_len, double ti, double te, float *acf, int len);

DLL_EXPORT int acf_3_kharkiv_22(double g1, double g2, double ti, double te, double acf[]);

#ifdef __cplusplus
}
#endif

#endif // _Included_forward
