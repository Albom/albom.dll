
/*
 * Copyright 2011-2021, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#include <stdio.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
#endif

double spectrum_1(double m1, double ti, double te, double freq);
int acf_1(double m1, double ti, double te, double acf[], int len);

double spectrum_2(double m1, double m2, double g1, double ti, double te, double freq);
int acf_2(double m1, double m2, double g1, double ti, double te, double acf[], int len);

double spectrum_3(double m1, double m2, double m3, double g1, double g2, double ti, double te, double freq);
int acf_3(double m1, double m2, double m3, double g1, double g2, double ti, double te, double acf[], int len);

double spectrum_3_full(double m1, double m2, double m3, double g1, double g2, double ti, double te, double ne, int iskD, double freq);
int acf_3_full(double m1, double m2, double m3, double g1, double g2, double ti, double te, double ne, int iskD, double acf[], int len, double dt);

int acf_library_light_short(FILE *f, int *temperatures, int temperatures_len, double ti, double te, double *acf, int len);
int acf_library_light_short_conv(FILE *f, int *temperatures, int temperatures_len, double ti, double te, double *acf, int len);
int library_light_list_of_temperatures_get(int *temperatures);
int library_light_list_get(char *prefix, int he_percent_int, char *list);
int library_light_list_get_filename(char *filename, char *filelist, int num);

int library_heavy_list_of_temperatures_get(int *temperatures);
int acf_library_heavy(FILE *f, int *temperatures, int temperatures_len, double ti, double te, double *acf, int len);

int library_oxygen_list_of_temperatures_get(int *temperatures);
int acf_library_oxygen(FILE *f, int *temperatures, int temperatures_len, double ti, double te, double *acf, int len);

double stat_mean_d(
    double *in,
    int len);

double stat_deviation_d(
    double *in,
    int len);

double stat_variance_d(
    double *in,
    int len);

int stat_distribution_d(
    double *in,
    int in_len,
    double *out,
    int out_len,
    double start,
    double step);

double random_rnd(void);
int random_randomize(int num);
int random_rdtsc(void);

double random_gauss();

int fourier_DFT_d(
    double *in,
    int il,
    double *out,
    int ol,
    double f0,
    double df,
    double dt);

int fourier_DCT_d(
    double *in,
    int il,
    double *out,
    int ol,
    double f0,
    double df,
    double dt);

int fourier_FFT_d  // пр¤мое быстрое преобразование ‘урье
    (
        double in1[],   // входные вещественные
        double in2[],   // входные мнимые
        double out1[],  // выходные вещественные
        double out2[],  // выходные мнимые
        int len         // размер массивов
    );

int fourier_IFFT_d  // обратное быстрое преобразование ‘урье
    (
        double in1[],   // входные вещественные
        double in2[],   // входные мнимые
        double out1[],  // выходные вещественные
        double out2[],  // выходные мнимые
        int len         // размер массивов
    );

int array_sub_d(
    double *in1,
    double *in2,
    double *out,
    int len);

int array_add_d(
    double *in1,
    double *in2,
    double *out,
    int len);

double array_max_d(
    double *in,
    int len);

double array_min_d(
    double *in,
    int len);

int array_mul_d(
    double *in1,
    double *in2,
    double *out,
    int len);

int array_div_d(
    double *in1,
    double *in2,
    double *out,
    int len);

int array_norm_d(
    double *in1,
    double *out,
    double num,
    int len);

int array_norm0_d(
    double *in,
    double *out,
    int len);

double array_error_d(
    double *in1,
    double *in2,
    int len);

double array_linear_d(
    double x,
    double *in_x,
    double *in_y,
    int len);

int array_trand_d(
    double *in1,
    double *in2,
    int num,
    int len);

int func_conv_d(
    const double *in1,
    const double *in2,
    double *out,
    int len);

int spline_bspline3_d(
    double *in_x,
    double *in_y,
    int in_len,
    double *out_x,
    double *out_y,
    int out_len);

int approx_poly_coeff_d(
    double *in_x,
    double *in_y,
    int in_len,
    double *out_coeff,
    int N);

int filelist_get(char *dir_name, char *filelist);
int filelist_get_filename(char *filelist, char *filename, int num);

int file_add_i(
    char *fname,
    int *in,
    int il,
    char *format);

int file_add_d(
    char *fname,
    double *in,
    int il,
    char *format);

int file_newline(
    char *fname);

int file_creat(
    char *fname);

int file_creat_and_add_s(
    char *fname,
    char *in);

int file_add_s(
    char *fname,
    char *in,
    char *format);

int file_add_bin_d(
    char *fname,
    double *in,
    int il);

int file_load_all_d(
    char *fname,
    double *buf);

int file_size(char *fname);

int buffer_clear(char *buf);

int buffer_newline(
    char *buf);

int buffer_add_s(
    char *buf,
    char *in,
    char *format);

int file_add_sh(
    char *fname,
    short *in,
    int il,
    char *format);

int buffer_add_i(
    char *buf,
    int *in,
    int il,
    char *format);

int buffer_add_d(
    char *buf,
    double *in,
    int il,
    char *format);

time_t date_2unixtime(int DD, int MM, int YY, int hh, int mm, int ss);
int unixtime_2date(time_t timestamp, int *DD, int *MM, int *YY, int *hh, int *mm, int *ss);
double time_2decimal(int hh, int mm, int ss);
int time_2str(int hh, int mm, int ss, char *timestr);
int date_2str(int dd, int mm, int yy, char *datestr);
int time_2sec(int hh, int mm, int ss);
int time_accum_num(int min);
int date_year_leap(int year);
int date_next(int *day, int *month, int *year);
int date_valid(int day, int month, int year);
int time_from_str(int *hh, int *mm, int *ss, const char *timestr);
void tdatetime_2date(double tdatetime, int *DD, int *MM, int *YY, int *hh, int *mm, int *ss, int *ms);
int time_linear(double *arr, int length);
int time_normalize(double *arr, int length);

#ifdef __cplusplus
}
#endif
