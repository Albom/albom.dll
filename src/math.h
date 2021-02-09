
/*
 * Copyright 2011-2021, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#ifndef _Included_mymath
#define _Included_mymath

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

double __blend(int k, int t, int *u, double v);
void __compute_intervals(int *u, int n, int t);
void __compute_point(int *u, int n, int t, double v, double *control_x, double *control_y,
			double *output_x, double *output_y);

#ifdef __cplusplus
extern "C"
{
#endif

DLL_EXPORT double stat_mean_d
        (
        double *in,
        int len
        );

DLL_EXPORT double stat_deviation_d
        (
        double *in,
        int len
        );

DLL_EXPORT double stat_variance_d
        (
        double *in,
        int len
        );

DLL_EXPORT int stat_distribution_d
        (
        double *in,
        int in_len,
        double *out,
        int out_len,
        double start,
        double step
        );

DLL_EXPORT double  random_rnd(void);
DLL_EXPORT int     random_rnd_int(int n);
DLL_EXPORT int     random_randomize(int num);
DLL_EXPORT int     random_rdtsc(void);

DLL_EXPORT double random_gauss();

DLL_EXPORT int	fourier_DFT_d
        (
		double *in,
		int il,
		double *out,
		int ol,
		double f0,
		double df,
		double dt
		);

DLL_EXPORT int	fourier_DCT_d
        (
		double *in,
		int il,
		double *out,
		int ol,
		double f0,
		double df,
		double dt
		);


DLL_EXPORT int	fourier_FFT_d // пр¤мое быстрое преобразование ‘урье
        (
        double in1[], // входные вещественные
        double in2[], // входные мнимые
        double out1[], // выходные вещественные
        double out2[], // выходные мнимые
        int len // размер массивов
        );

DLL_EXPORT int	fourier_IFFT_d // обратное быстрое преобразование ‘урье
        (
        double in1[], // входные вещественные
        double in2[], // входные мнимые
        double out1[], // выходные вещественные
        double out2[], // выходные мнимые
        int len // размер массивов
        );

DLL_EXPORT int fourier_get_spectrum_from_acf
        (
        double *c,
        double *s,
        int len,
        double deltaTau,
        double *sp,
        int nF
        );

DLL_EXPORT int fourier_get_acf_from_spectrum
        (
        double *sp,
        int nF,
        double *c,
        double *s,
        int len,
        double deltaTau
        );

DLL_EXPORT int array_sub_d
        (
        double *in1,
        double *in2,
        double *out,
        int len
        );

DLL_EXPORT int array_add_d
        (
        double *in1,
        double *in2,
        double *out,
        int len
        );

DLL_EXPORT double  array_max_d
        (
        double *in,
        int len
        );

DLL_EXPORT double  array_min_d
        (
        double *in,
        int len
        );

DLL_EXPORT int  array_mul_d
        (
        double *in1,
        double *in2,
        double *out,
        int len
        );

DLL_EXPORT int  array_div_d
        (
        double *in1,
        double *in2,
        double *out,
        int len
        );

DLL_EXPORT int array_norm_d
        (
        double *in1,
        double *out,
        double num,
        int len
        );

DLL_EXPORT int array_norm0_d
        (
        double *in,
        double *out,
        int len
        );

DLL_EXPORT double array_error_d
        (
        double *in1,
        double *in2,
        int len
        );

DLL_EXPORT double array_linear_d
        (
        double x,
        double *in_x,
        double *in_y,
        int len
        );

DLL_EXPORT int array_trand_d
        (
        double *in1,
        double *in2,
        int num,
        int len
        );

DLL_EXPORT int func_conv_d
        (
        const double *in1,
        const double *in2,
        double *out,
        int len
        );

DLL_EXPORT int spline_bspline3_d
        (
        double *in_x,
        double *in_y,
        int in_len,
        double *out_x,
        double *out_y,
        int out_len
        );

DLL_EXPORT int approx_poly_coeff_d
        (
         double *in_x,
         double *in_y,
         int in_len,
         double *out_coeff,
         int N
         );


#ifdef __cplusplus
}
#endif

#endif // _Included_mymath
