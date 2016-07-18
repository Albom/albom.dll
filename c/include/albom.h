
#include <stdio.h>

// direct.h

extern "C"  double spectrum_1(double m1, double ti, double te, double freq);
extern "C"  int acf_1(double m1, double ti, double te, double acf[], int len);

extern "C"  double spectrum_2(double m1, double m2, double g1, double ti, double te, double freq);
extern "C"  int acf_2(double m1, double m2, double g1, double ti, double te, double acf[], int len);

extern "C"  double spectrum_3(double m1, double m2, double m3, double g1, double g2, double ti, double te, double freq);
extern "C"  int acf_3(double m1, double m2, double m3, double g1, double g2, double ti, double te, double acf[], int len);

extern "C"  double spectrum_3_full(double m1, double m2, double m3, double g1, double g2, double ti, double te, double ne, int iskD, double freq);
extern "C"  int acf_3_full(double m1, double m2, double m3, double g1, double g2, double ti, double te, double ne, int iskD, double acf[], int len, double dt);

extern "C"  int acf_library_light_short(FILE *f, int *temperatures, int temperatures_len, double ti, double te, double *acf, int len);
extern "C"  int acf_library_light_short_conv(FILE *f, int *temperatures, int temperatures_len, double ti, double te, double *acf, int len);
extern "C"  int library_light_list_of_temperatures_get(int *temperatures);
extern "C"  int library_light_list_get(char* prefix, int he_percent_int, char *list);
extern "C"  int library_light_list_get_filename(char *filename, char *filelist, int num);

extern "C"  int library_heavy_list_of_temperatures_get(int *temperatures);
extern "C"  int acf_library_heavy(FILE *f, int *temperatures, int temperatures_len, double ti, double te, double *acf, int len);

extern "C"  int library_oxygen_list_of_temperatures_get(int *temperatures);
extern "C"  int acf_library_oxygen(FILE *f, int *temperatures, int temperatures_len, double ti, double te, double *acf, int len);

// mymath.h


extern "C" double stat_mean_d
        (
        double *in,
        int len
        );

extern "C" double stat_deviation_d
        (
        double *in,
        int len
        );

extern "C" double stat_variance_d
        (
        double *in,
        int len
        );

extern "C" int stat_distribution_d
        (
        double *in,
        int in_len,
        double *out,
        int out_len,
        double start,
        double step
        );

extern "C" double  random_rnd(void);
extern "C" int     random_randomize(int num);
extern "C" int     random_rdtsc(void);

extern "C" double random_gauss();

extern "C" int	fourier_DFT_d
        (
		double *in,
		int il,
		double *out,
		int ol,
		double f0,
		double df,
		double dt
		);

extern "C" int	fourier_DCT_d
        (
		double *in,
		int il,
		double *out,
		int ol,
		double f0,
		double df,
		double dt
		);


extern "C" int	fourier_FFT_d // пр€мое быстрое преобразование ‘урье
        (
        double in1[], // входные вещественные
        double in2[], // входные мнимые
        double out1[], // выходные вещественные
        double out2[], // выходные мнимые
        int len // размер массивов
        );

extern "C" int	fourier_IFFT_d // обратное быстрое преобразование ‘урье
        (
        double in1[], // входные вещественные
        double in2[], // входные мнимые
        double out1[], // выходные вещественные
        double out2[], // выходные мнимые
        int len // размер массивов
        );

extern "C" int array_sub_d
        (
        double *in1,
        double *in2,
        double *out,
        int len
        );

extern "C" int array_add_d
        (
        double *in1,
        double *in2,
        double *out,
        int len
        );

extern "C" double  array_max_d
        (
        double *in,
        int len
        );

extern "C" double  array_min_d
        (
        double *in,
        int len
        );

extern "C" int  array_mul_d
        (
        double *in1,
        double *in2,
        double *out,
        int len
        );

extern "C" int  array_div_d
        (
        double *in1,
        double *in2,
        double *out,
        int len
        );

extern "C" int array_norm_d
        (
        double *in1,
        double *out,
        double num,
        int len
        );

extern "C" int array_norm0_d
        (
        double *in,
        double *out,
        int len
        );

extern "C" double array_error_d
        (
        double *in1,
        double *in2,
        int len
        );

extern "C" double array_linear_d
        (
        double x,
        double *in_x,
        double *in_y,
        int len
        );

extern "C" int array_trand_d
        (
        double *in1,
        double *in2,
        int num,
        int len
        );

extern "C" int func_conv_d
        (
        const double *in1,
        const double *in2,
        double *out,
        int len
        );

extern "C" int spline_bspline3_d
        (
        double *in_x,
        double *in_y,
        int in_len,
        double *out_x,
        double *out_y,
        int out_len
        );

extern "C" int approx_poly_coeff_d
        (
         double *in_x,
         double *in_y,
         int in_len,
         double *out_coeff,
         int N
         );

extern "C" int filelist_get(char *dir_name, char *filelist);
extern "C" int filelist_get_filename(char *filelist, char *filename, int num);

extern "C" int file_add_i (
                    char *fname,
                    int *in,
                    int il,
                    char *format
                    );

extern "C" int file_add_d(
        char *fname,
        double *in,
        int il,
        char *format
        );

extern "C" int file_newline (
        char *fname
        );

extern "C" int file_creat (
        char *fname
        );

extern "C" int file_creat_and_add_s(
        char *fname,
        char *in
        );

extern "C" int file_add_s(
        char *fname,
        char *in,
        char *format
        );

extern "C" int file_add_bin_d(
        char *fname,
        double *in,
        int il
        );

extern "C" int file_load_all_d (
        char *fname,
        double *buf
        );

extern "C" int file_size (char *fname);

extern "C" int buffer_clear(char *buf);

extern "C" int  buffer_newline (
        char *buf
        );

extern "C" int buffer_add_s(
        char *buf,
        char *in,
        char *format
        );

extern "C" int file_add_sh(
        char *fname,
        short *in,
        int il,
        char *format
        );

extern "C" int buffer_add_i(
        char *buf,
        int *in,
        int il,
        char *format
        );

extern "C" int buffer_add_d(
        char *buf,
        double *in,
        int il,
        char *format
        );


// mytime.h		
		
extern "C"  time_t date_2unixtime(int DD, int MM, int YY, int hh, int mm, int ss);
extern "C"  int unixtime_2date(time_t timestamp, int *DD, int *MM, int *YY, int *hh, int *mm, int *ss);
extern "C"  double time_2decimal(int hh, int mm, int ss);
extern "C"  int time_2str(int hh, int mm, int ss, char *timestr);
extern "C"  int date_2str(int dd, int mm, int yy, char *datestr);
extern "C"  int time_2sec(int hh, int mm, int ss);
extern "C"  int time_accum_num(int min);
extern "C"  int date_year_leap(int year);
extern "C"  int date_next(int *day, int *month, int *year);
extern "C"  int date_valid(int day, int month, int year);
extern "C"  int time_from_str(int *hh, int *mm, int *ss, const char *timestr);
extern "C"  void tdatetime_2date(double tdatetime, int *DD, int *MM, int *YY, int *hh, int *mm, int *ss, int *ms);


		