
/*
 * Copyright 2011-2019, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#include "mymath.h"

/// =============================
/// Вычисление мат. ожидания

double stat_mean_d
(
    double *in,
    int len
) {
    double result;
    int i;

    result = 0;
    for (i = 0; i < len; i++)
        result += in[i];
    return result/len;
}

/// =============================
/// Вычисление СКО

double stat_deviation_d
(
    double *in,
    int len
) {
    double result, mean, r;
    int i;

    if (len == 0)
        return 0;

    mean = stat_mean_d(in, len);

    result = 0;
    for (i = 0; i < len; i++) {
        r = mean - in[i];
        result += r*r;
    }

    return sqrt(result/(len-1));
}

/// =============================
/// Вычисление дисперсии

double stat_variance_d
(
    double *in,
    int len
) {
    double result, mean, r;
    int i;

    if (len == 0)
        return 0;

    mean = stat_mean_d(in, len);

    result = 0;
    for (i = 0; i < len; i++) {
        r = mean - in[i];
        result += r*r;
    }

    return result/(len-1);
}


/// =============================
/// Закон распределения

int stat_distribution_d
(
    double *in,
    int in_len,
    double *out,
    int out_len,
    double start,
    double step
) {
    int i, j;
    double *limits;

    limits = (double*) malloc(out_len*sizeof(double));

    for (i = 0; i < out_len; i++)
        limits[i] = start + step*i;

    for (i = 0; i < out_len; i++)
        out[i] = 0;

    for (i = 0; i < in_len; i++)
        for (j = 0; j < out_len-1; j++)
            if ( (in[i] >= limits[j]) && (in[i] < limits[j+1]) ) {
                out[j]++;
                break;
            }


    free(limits);

    return 0;
}


/// ===============================================
/// Счётчик TSC (Time Stamp Counter)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
int random_rdtsc() {
    __asm__ volatile ("rdtsc"); // x86 only
}
#pragma GCC diagnostic pop

/// ===============================================
/// Установка начального значения генератора случайных чисел

int random_randomize(int num) {
    srand( num );
    return 0;
}

///================================
/// Генератор случайных вещественных чисел от 0 до 1

double random_rnd(void) {
    static const double rndbasemaxr = 1.0/RAND_MAX;
    return rndbasemaxr*rand();
}

///================================
/// Генератор случайных вещественных чисел от 0 до 1 с гауссовым законом распределения

double gauss_save_d;
int gauss_save_i = 0;

double random_gauss() {

    double x1, x2, w, y1, y2;

    do {
        x1 = 2.0 * random_rnd() - 1.0;
        x2 = 2.0 * random_rnd() - 1.0;
        w = x1 * x1 + x2 * x2;
    } while ( w >= 1.0 );

    w = sqrt( (-2.0 * log( w ) ) / w );
    y1 = x1 * w;
    y2 = x2 * w;

    if (gauss_save_i == 0) {
        gauss_save_d = y1;
        gauss_save_i = 1;
        return y2;
    } else {
        gauss_save_i = 0;
        return gauss_save_d;
    }

}

///================================
/// Преобразование фурье

int	fourier_DFT_d
(
    double *in,
    int il,
    double *out,
    int ol,
    double f0,
    double df,
    double dt
) {

    int w, t;
    double *osin;
    double *ocos;

    osin = (double *) malloc( ol * sizeof(double) );
    ocos = (double *) malloc( ol * sizeof(double) );

    for (w = 0; w < ol; w++) {
        *(osin+w) = 0;
        *(ocos+w) = 0;
        for (t = 0; t < il; t++) {
            *(ocos+w) += *(in+t) * cos(2*M_PI * (f0+df*w) * (dt*t)) ;
            *(osin+w) += *(in+t) * sin(2*M_PI * (f0+df*w) * (dt*t)) ;
        }
    }

    for (w = 0; w < ol; w++)
        *(out+w) = sqrt( *(osin+w) **(osin+w) + *(ocos+w) **(ocos+w)) ;

    free(osin);
    free(ocos);

    return 0;
}


///================================
/// Косинусное преобразование фурье

int	fourier_DCT_d
(
    double *in,
    int il,
    double *out,
    int ol,
    double f0,
    double df,
    double dt
) {

    int w, t;

    for (w = 0; w < ol; w++) {
        *(out+w) = 0;
        for (t = 0; t < il; t++)
            *(out+w) += *(in+t) * cos(2*M_PI * (f0+df*w) * (dt*t)) ;
    }

    return 0;
}


///================================

int	__fourier_FFT_d
(
    double in1[],
    double in2[],
    double out1[],
    double out2[],
    int nn,
    int isign
)

{

    int i, j, n, m, mmax, istep;
    double tempr, tempi, wtemp, theta, wpr, wpi, wr, wi;
    double *data;

    data = (double*) malloc(nn * 2 *sizeof(double));

    for (i = 0; i < nn; i++) {
        data[i*2] = in1[i];
        data[i*2+1] = in2[i];
    }

    n = nn << 1;
    j = 1;
    i = 1;

    while( i < n ) {
        if( j > i ) {
            tempr = data[i-1];
            data[i-1] = data[j -1];
            data[j-1] = tempr;
            tempr = data[i];
            data[i] = data[j];
            data[j] = tempr;
        }
        m = n >> 1;
        while( ( m >= 2 ) && ( j > m ) ) {
            j -= m;
            m >>= 1;
        }
        j += m;
        i += 2;
    }

    mmax = 2;
    while( n > mmax ) {
        istep = 2 * mmax;
        theta = -2.0 * M_PI / (isign*mmax);
        wpr = cos(theta);
        wpi = sin(theta);
        wr = 1.0;
        wi = 0.0;
        m = 1;
        while( m < mmax ) {
            i = m;
            while( i < n ) {
                j = i + mmax;
                tempr = wr * data[j-1] - wi * data[j];
                tempi = wr * data[j] + wi * data[j-1];
                data[j-1] = data[i-1] - tempr;
                data[j] = data[i] - tempi;
                data[i-1] = data[i-1] + tempr;
                data[i] = data[i] + tempi;
                i += istep;
            }
            wtemp = wr;
            wr = wr * wpr - wi * wpi;
            wi = wi * wpr + wtemp * wpi;
            m += 2;
        }
        mmax = istep;
    }

    if (isign == -1) {     // Обратное FFT
        for (i = 0; i < nn*2; i++ )
            data[i] = data[i] / nn;
    }

    for( i = 0; i < nn; i++ ) {
        out1[i] = data[ i * 2 ];
        out2[i] = data[ i * 2 + 1];
    }

    free(data);

    return 0;
}

///================================

int fourier_FFT_d
(
    double in1[],
    double in2[],
    double out1[],
    double out2[],
    int nn
) {
    __fourier_FFT_d (in1, in2, out1, out2, nn, 1);
    return 0;
}

///================================

int fourier_IFFT_d
(
    double in1[],
    double in2[],
    double out1[],
    double out2[],
    int nn
) {
    __fourier_FFT_d (in1, in2, out1, out2, nn, -1);
    return 0;
}

///================================

int fourier_get_spectrum_from_acf(double *c, double *s, int len, double deltaTau, double *sp, int nF) {

    double *sum = (double*)malloc(sizeof(double)*nF);
    if (sum == NULL) {
        return -1;
    }

    double spn = 0;
    for (int tau = 0; tau < len; tau++) {
        spn += c[tau];
    }
    spn = spn*2 + 1;

    for (int f = 0; f < nF; f++) {
        sum[f] = 0;
        for (int tau = 0; tau < len; tau++) {
            sum[f] += c[tau]*cos(2*M_PI*(f-nF/2)*tau*deltaTau) -
                      s[tau]*sin(2*M_PI*(f-nF/2)*tau*deltaTau);
        }
        double arg = M_PI*f*deltaTau;
        if (arg != 0) {
            sp[f] = (1+2*sin(arg)/arg*sum[f])/spn;
        } else
            sp[f] = (1+2*sum[f])/spn;
    }

    free(sum);
    return 0;
}

///================================

int fourier_get_acf_from_spectrum(double *sp, int nF, double *c, double *s, int len, double deltaTau) {
    for (int tau = 0; tau < len; tau++) {
        c[tau] = 0;
        s[tau] = 0;
        for (int f = 0; f < nF; f++) {
            c[tau] += sp[f]*cos(2*M_PI*(f-nF/2)*tau*deltaTau);
            s[tau] -= sp[f]*sin(2*M_PI*(f-nF/2)*tau*deltaTau);
        }
    }
    return 0;
}

///================================

int array_sub_d(double *in1, double *in2, double *out, int len) {
    int i;

    for (i = 0; i < len; i++)
        out[i] = in1[i]-in2[i];

    return 0;
}

///================================

int array_add_d(double *in1, double *in2, double *out, int len) {
    int i;

    for (i = 0; i < len; i++)
        out[i] = in1[i]+in2[i];

    return 0;
}

///================================

int array_mul_d(double *in1, double *in2, double *out, int len) {
    int i;

    for (i = 0; i < len; i++)
        out[i] = in1[i]*in2[i];

    return 0;
}

///================================

int array_div_d(double *in1, double *in2, double *out, int len) {
    int i;

    for (i = 0; i < len; i++)
        out[i] = in1[i]/in2[i];

    return 0;
}

/// =============================
/// Поиск максимума

double  array_max_d
(
    double *in,
    int len
) {
    int i;
    double max = in[0];
    for (i = 1; i < len; i++)
        if (in[i] > max)
            max = in[i];
    return max;
}

/// =============================
/// Поиск минимума

double  array_min_d
(
    double *in,
    int len
) {
    int i;
    double min = in[0];
    for (i = 1; i < len; i++)
        if (in[i] < min)
            min = in[i];
    return min;
}

///================================

int array_norm_d(double *in1, double *out, double num, int len) {
    int i;

    for (i = 0; i < len; i++)
        out[i] = in1[i]/num;

    return 0;
}

///================================

int array_norm0_d(double *in, double *out, int len) {
    int i;

    for (i = len-1; i > -1; i--)
        out[i] = in[i]/in[0];

    return 0;
}

///================================

double array_linear_d(double x, double *in_x, double *in_y, int len) {
    int i;

    if (x >= in_x[len-1])
        return in_y[len-1]+(in_y[len-1]-in_y[len-1-1])*(x - in_x[len-1])/(in_x[len-1]-in_x[len-1-1]);

    for (i = 1; i < len; i++)
        if (in_x[i] > x)
            return in_y[i-1]+(in_y[i]-in_y[i-1])*(x - in_x[i-1])/(in_x[i]-in_x[i-1]);
    return 0;
}


///================================

double array_error_d(double *in1, double *in2, int len) {
    int i;
    double res = 0;

    for (i = 0; i < len; i++)
        res += (in1[i]-in2[i])*(in1[i]-in2[i]);

    return sqrt(res/len);
}


///================================

int array_trand_d(double *in1, double *in2, int num, int len) {
    int i, j;

    if (num < 1)
        return 0;
    /*
    // заполнение средины тренда
        for (i = 0; i < len-num; i++)
            {
            in2[i+num/2]=0;
            for (j = 0; j < num; j++)
                {
                in2[i+num/2] += in1[i+j];
                }
            in2[i+num/2] /= num;
            }

    // заполнение начала тренда
        for (i = 0; i < num/2; i++)
            in2[i] = in2[num/2];

    // заполнение конца тренда
        for (i = len-num/2; i < len; i++)
            in2[i] = in2[len-1-num/2];
    */

    for (i = 0; i < len; i++) {
        if ( (i < num/2) || (i+num/2 > len-1) )
            in2[i] = in1[i];
        else {
            in2[i] = 0;
            for (j = 0; j < num; j++)
                in2[i] += in1[i+j-num/2];
            in2[i] /= num;
        }

    }

    return len;
}


///================================

int func_conv_d(const double *in1, const double *in2, double *out, int len) {

    int i, j;
    double *temp1;
    double *temp2;

    temp1 = (double*)malloc(4*len*sizeof(double));
    temp2 = (double*)malloc(4*len*sizeof(double));

    for (i = 0; i < len; i++) {
        temp1[i+len] = in1[i];
        temp2[i+len] = in2[i];
        temp1[len-i] = in1[i];
        temp2[len-i] = in2[i];
    }

    temp1[0] = 0;
    temp2[0] = 0;

    for (i = 2*len; i < 4*len; i++) {
        temp1[i] = 0;
        temp2[i] = 0;
    }

    for (i = 0; i < 2*len; i++) {
        out[i] = 0;
        for (j = 0; j < 2*len; j++)
            out[i] += temp1[j]*temp2[i+j];
    }

    free(temp1);
    free(temp2);

    return 0;
}

///================================

int spline_bspline3_d(double *in_x, double *in_y, int in_len,
                      double *out_x, double *out_y, int out_len) {
    int *u;
    double increment,interval;
    double x, y;
    int output_index;

    int t = 4;
    int n = in_len-1;

    u = (int*) malloc((n+t+1)*sizeof(int));
    if (u == NULL)
        return 1;

    __compute_intervals(u, n, t);

    increment = (double) (double) (n-t+2)/(out_len-1);  // how much parameter goes up each time
    interval = 0;


    for (output_index=0; output_index<out_len-1; output_index++) {
        __compute_point(u, n, t, interval, in_x, in_y, &x, &y);
        out_x[output_index] = x;
        out_y[output_index] = y;
        interval=interval+increment;  // increment our parameter
    }
    out_x[out_len-1]=in_x[n];   // put in the last point
    out_y[out_len-1]=in_y[n];

    free(u);
    return 0;
}

///================================

double __blend(int k, int t, int *u, double v) { // calculate the blending value
    double value;

    if (t==1) {		// base case for the recursion
        if ((u[k]<=v) && (v<u[k+1]))
            value=1;
        else
            value=0;
    } else {
        if ((u[k+t-1]==u[k]) && (u[k+t]==u[k+1]))  // check for divide by zero
            value = 0;
        else if (u[k+t-1]==u[k]) // if a term's denominator is zero,use just the other
            value = (u[k+t] - v) / (u[k+t] - u[k+1]) * __blend(k+1, t-1, u, v);
        else if (u[k+t]==u[k+1])
            value = (v - u[k]) / (u[k+t-1] - u[k]) * __blend(k, t-1, u, v);
        else
            value = (v - u[k]) / (u[k+t-1] - u[k]) * __blend(k, t-1, u, v) +
                    (u[k+t] - v) / (u[k+t] - u[k+1]) * __blend(k+1, t-1, u, v);
    }
    return value;
}

///================================

void __compute_intervals(int *u, int n, int t) { // figure out the knots
    int j;

    for (j=0; j<=n+t; j++)
        if (j<t)
            u[j]=0;
        else if ((t<=j) && (j<=n))
            u[j]=j-t+1;
        else if (j>n)
            u[j]=n-t+2;  // if n-t=-2 then we're screwed, everything goes to 0
}

///================================

void __compute_point(int *u, int n, int t, double v, double *control_x, double *control_y,
                     double *output_x, double *output_y) {
    int k;
    double temp;

// initialize the variables that will hold our outputted point
    *output_x = 0;
    *output_y = 0;

    for (k=0; k<=n; k++) {
        temp = __blend(k,t,u,v);  // same blend is used for each dimension coordinate
        *output_x = *output_x + control_x[k] * temp;
        *output_y = *output_y + control_y[k] * temp;
    }
}

///================================


int approx_poly_coeff_d(double *in_x, double *in_y, int in_len,
                        double *out_coeff, int N) {

    double *sums; // матрица сумм
    double *b;    // свободные члены

    sums = (double*) malloc( (N+1) * (N+1) * sizeof(double));
    b    = (double*) malloc( (N+1) * sizeof(double));

    if ( (sums == NULL) || (b == NULL) )
        return -1;

    for (int i = 0; i < N+1; i++)
        out_coeff[i] = 0;

    for (int i = 0; i < N+1; i++)
        for (int j = 0; j < N+1; j++) {
            sums[i*(N+1)+j] = 0;
            for (int k = 0; k < in_len; k++)
                sums[i*(N+1)+j] += pow(in_x[k], i+j);
        }


    for (int i = 0; i < N+1; i++) {
        b[i] = 0;
        for (int k = 0; k < in_len; k++)
            b[i] += pow(in_x[k], i)*in_y[k];
    }


    for (int i = 0; i < N+1; i++)
        for (int j = i+1; j < N+1; j++) {
            double M = sums[i*(N+1)+j] / sums[i*(N+1)+i];
            for (int k = i; k < N+1; k++)
                sums[j*(N+1)+k] -= M * sums[i*(N+1)+k];
            b[j] -= M * b[i];
        }

    for (int i=(N+1)-1; i>=0; i--) {
        double s = 0;
        for (int j = i; j < N+1; j++)
            s += sums[i*(N+1)+j] * out_coeff[j];

        out_coeff[i] = (b[i] - s) / sums[i*(N+1)+i];
    }


    free(sums);
    free(b);

    return 0;
}


///================================
