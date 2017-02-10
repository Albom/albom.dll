
/*
 * Copyright 2011-2016, Oleksandr Bogomaz (albom85@yandex.ru)
 */

#include "direct.h"

///===============================

/**
* Spectrum calculation using a simplified formula
* (for 1 sort of ions)
*/

double spectrum_1(double m1, double ti, double te, double freq)
    {

    double t, alpha, theta, theta2;
    int theta_int;
    double A, B, C;

    alpha = WAVELENGTH/(4*M_PI)*sqrt(ATOMIC_CONSTANT*m1/(2*BOLTZMANN*ti));

    theta = 2*M_PI*alpha*freq;

    if (theta < 0)
        theta = 0;

    if (theta > 19.999)
        theta = 19.999;

    theta_int = (int)(theta*1000);

    theta2 = -theta*theta;
    t = te/ti;

    A = alpha*exp(theta2);
    B = 1+t*(1-PHI_0_20_0001[theta_int]);
    C = t*theta*exp(theta2);

    return A/(B*B+M_PI*C*C);
    }

///===============================

/**
* ACF calculation using spectrum calculated with simplified formula
* (for 1 sort of ions)
*/

int acf_1(double m1, double ti, double te, double acf[], int len)
    {
    int i, j;
    double spectrum[300];

    for (i = 0; i < 300; i++)
        spectrum[i] = spectrum_1(m1, ti, te, i*50);

    double param = 2*M_PI*30.555e-6*50;

    for (j = 0 ; j < len; j++)
        {
        acf[j] = 0;
        for (i = 0 ; i < 300-2; i+=2)
            acf[j] += (spectrum[i]*cos(param*j*i)+
                       4*spectrum[i+1]*cos(param*j*(i+1))
                       +spectrum[i+2]*cos(param*j*(i+2)));
        }

    for (j = len-1 ; j > -1; j--)
        acf[j] /= acf[0];

    return len;
    }



///===============================

/**
* Spectrum calculation using a simplified formula
* (for 2 sorts of ions)
*/

double spectrum_2(double m1, double m2, double g1, double ti, double te, double freq)
    {

    double t, alpha, theta, theta2;
    double g2;
    double m2m1;
    double sqrt_m2m1;
    int theta_int1;
    int theta_int2;
    double A, B, C;

    g2 = 1 - g1;

    m2m1 = m2/m1;
    sqrt_m2m1 = sqrt(m2m1);

    alpha = WAVELENGTH/(4*M_PI)*sqrt(ATOMIC_CONSTANT*m1/(2*BOLTZMANN*ti));

    theta = 2*M_PI*alpha*freq;

    if (theta < 0)
        theta = 0;

    if (theta > 19.999)
        theta = 19.999;

    theta_int1 = (int)(theta*1000);

    if (theta*sqrt_m2m1 > 19.999)
        theta_int2 = (int)(19.999*1000);
    else
        theta_int2 = (int)(theta*sqrt_m2m1*1000);

    theta2 = -theta*theta;
    t = te/ti;

    A = alpha*( g1*exp(theta2) + g2*sqrt_m2m1*exp(m2m1*theta2));
    B = 1+t*(1-g1*PHI_0_20_0001[theta_int1]-g2*PHI_0_20_0001[theta_int2]);
    C = t*theta*(g1*exp(theta2)+g2*sqrt_m2m1*exp(m2m1*theta2));

    return A/(B*B+M_PI*C*C);
    }

///===============================

/**
* ACF calculation using spectrum calculated with simplified formula
* (for 2 sorts of ions)
*/

int acf_2(double m1, double m2, double g1, double ti, double te, double acf[], int len)
    {
    int i, j;
    double spectrum[300];

    for (i = 0; i < 300; i++)
        spectrum[i] = spectrum_2(m1, m2, g1, ti, te, i*50);

    double param = 2*M_PI*30.555e-6*50;

    for (j = 0 ; j < len; j++)
        {
        acf[j] = 0;
        for (i = 0 ; i < 300-2; i+=2)
            acf[j] += (spectrum[i]*cos(param*j*i)+
                       4*spectrum[i+1]*cos(param*j*(i+1))
                       +spectrum[i+2]*cos(param*j*(i+2)));
        }

    for (j = len-1 ; j > -1; j--)
        acf[j] /= acf[0];

    return len;
    }

///===============================

/**
* Spectrum calculation using a simplified formula
* (for 3 sorts of ions)
*/

double spectrum_3(double m1, double m2, double m3, double g1, double g2, double ti, double te, double freq)
    {

    double t, alpha, theta, theta2;
    double g3;
    double m2m1;
    double m3m1;
    double sqrt_m2m1;
    double sqrt_m3m1;
    int theta_int1;
    int theta_int2;
    int theta_int3;
    double A, B, C;

    g3 = 1 - g2 - g1;

    m2m1 = m2/m1;
    m3m1 = m3/m1;
    sqrt_m2m1 = sqrt(m2m1);
    sqrt_m3m1 = sqrt(m3m1);

    alpha = WAVELENGTH/(4*M_PI)*sqrt(ATOMIC_CONSTANT*m1/(2*BOLTZMANN*ti));

    theta = 2*M_PI*alpha*freq;

    if (theta < 0)
        theta = 0;

    if (theta > 19.999)
        theta = 19.999;

    theta_int1 = (int)(theta*1000);

    if (theta*sqrt_m2m1 > 19.999)
        theta_int2 = (int)(19.999*1000);
    else
        theta_int2 = (int)(theta*sqrt_m2m1*1000);

    if (theta*sqrt_m3m1 > 19.999)
        theta_int3 = (int)(19.999*1000);
    else
        theta_int3 = (int)(theta*sqrt_m3m1*1000);

    theta2 = -theta*theta;
    t = te/ti;

    A = alpha*( g1*exp(theta2) + g2*sqrt_m2m1*exp(m2m1*theta2) + g3*sqrt_m3m1*exp(m3m1*theta2) );
    B = 1+t*(1-g1*PHI_0_20_0001[theta_int1]-g2*PHI_0_20_0001[theta_int2]-g3*PHI_0_20_0001[theta_int3]);
    C = t*theta*(g1*exp(theta2)+g2*sqrt_m2m1*exp(m2m1*theta2)+g3*sqrt_m3m1*exp(m3m1*theta2));

    return A/(B*B+M_PI*C*C);
    }

///===============================

/**
* ACF calculation using spectrum calculated with simplified formula
* (for 3 sorts of ions)
*/

int acf_3(double m1, double m2, double m3, double g1, double g2, double ti, double te, double acf[], int len)
    {
    int i, j;
    double spectrum[300];

    for (i = 0; i < 300; i++)
        spectrum[i] = spectrum_3(m1, m2, m3, g1, g2, ti, te, i*50);

    double param = 2*M_PI*30.555e-6*50;

    for (j = 0 ; j < len; j++)
        {
        acf[j] = 0;
        for (i = 0 ; i < 300-2; i+=2)
            acf[j] += (spectrum[i]*cos(param*j*i)+
                       4*spectrum[i+1]*cos(param*j*(i+1))
                       +spectrum[i+2]*cos(param*j*(i+2)));
        }

    for (j = len-1 ; j > -1; j--)
        acf[j] /= acf[0];

    return len;
    }

///===============================

int acf_3_full(double m1, double m2, double m3, double g1, double g2, double ti, double te, double ne, int iskD, double acf[], int len, double dt)
    {
    int i, j;

    const int num_of_harm = 5000;
    const double df = 3;
    double spectrum[num_of_harm];
    double param = 2*M_PI*dt*df;

    for (i = 1; i < num_of_harm; i++)
        {
        spectrum[i] = spectrum_3_full(m1, m2, m3, g1, g2, ti, te, ne, iskD, i*df);
        }
    spectrum[0] = spectrum[1];

    for (j = 0 ; j < len; j++)
        {
        acf[j] = 0;
        double paramj = param*j;
        for (i = 0 ; i < num_of_harm-2; i+=2)
            {
            acf[j] += (spectrum[i]*cos(paramj*i)+
                       4*spectrum[i+1]*cos(paramj*(i+1))
                       +spectrum[i+2]*cos(paramj*(i+2)));
            }
        }

    for (j = len-1 ; j > -1; j--)
        {
        acf[j] /= acf[0];
        }


    return len;
    }

///===============================

double spectrum_3_full(double m1, double m2, double m3, double g1, double g2, double ti, double te, double ne, int iskD, double freq)
    {

    double g3;
    double m2m1;
    double m3m1;
    double sqrt_m2m1;
    double sqrt_m3m1;
    double sqrt_m2m1_1000;
    double sqrt_m3m1_1000;
    int theta_int1;
    int theta_int2;
    int theta_int3;

    double alpha, theta;
    double theta2; // theta^2
    double theta_sqrt_pi; // theta*M_SQRTPI
    double t; // te/ti

    double OtnoshMassElect;
    double KorenOtnoshMassElect;
    double RealYelect;
    double sumRealYion;
    double sumImagYion;
    double tsumRealYion;
    double tsumImagYion;
    double modYelectKvadr;
    double koefDeby;
    double Deby;

    if (freq < 0.01)
        freq = 0.01;

    g3 = 1 - g1 - g2;
    t = te/ti;

    m2m1 = m2/m1;
    m3m1 = m3/m1;
    sqrt_m2m1 = sqrt(m2m1);
    sqrt_m3m1 = sqrt(m3m1);
    sqrt_m2m1_1000 = sqrt_m2m1*1000;
    sqrt_m3m1_1000 = sqrt_m3m1*1000;

    alpha = WAVELENGTH/(4*M_PI)*sqrt(ATOMIC_CONSTANT*m1/(2*BOLTZMANN*ti));
    koefDeby = (4*M_PI*WAVELENGTH)*(4*M_PI*WAVELENGTH)*EPSILON0*BOLTZMANN/(CHARGE_ELECTRON*CHARGE_ELECTRON);
    if (ne < 1)
        ne = 1;
    Deby = koefDeby*te/ne;

    OtnoshMassElect = MASS_ELECTRON/(ATOMIC_CONSTANT*m1);
    KorenOtnoshMassElect = sqrt(OtnoshMassElect);


    theta = 2*M_PI*alpha*freq;

    if (theta < 0)
        theta = 0;

    if (theta > 19.999)
        theta = 19.999;

    theta2 = theta*theta;
    theta_sqrt_pi = theta*M_SQRTPI;

    theta_int1 = (int)(theta*1000);

    if (theta*sqrt_m2m1 > 19.999)
        theta_int2 = (int)(19.999*1000);
    else
        theta_int2 = (int)(theta*sqrt_m2m1_1000);

    if (theta*sqrt_m3m1 > 19.999)
        theta_int3 = (int)(19.999*1000);
    else
        theta_int3 = (int)(theta*sqrt_m3m1_1000);

    RealYelect = theta_sqrt_pi*KorenOtnoshMassElect*pow(t, -0.5)*exp(-OtnoshMassElect*theta2/t);

    modYelectKvadr = (1+RealYelect*RealYelect);

    sumRealYion = g1*theta_sqrt_pi*1*exp(-1*theta2) + g2*theta_sqrt_pi*sqrt_m2m1*exp(-m2m1*theta2) + g3*theta_sqrt_pi*sqrt_m3m1*exp(-m3m1*theta2) ;
    sumImagYion = g1*(1-PHI_0_20_0001[theta_int1]) + g2*(1-PHI_0_20_0001[theta_int2]) + g3*(1-PHI_0_20_0001[theta_int3]) ;

    tsumRealYion = t*sumRealYion;
    tsumImagYion = t*sumImagYion;

    return ( modYelectKvadr*sumRealYion + (tsumRealYion*tsumRealYion + (tsumImagYion+iskD*Deby)*(tsumImagYion+iskD*Deby)) * RealYelect ) / ( ((RealYelect+tsumRealYion)*(RealYelect+tsumRealYion) + (1+tsumImagYion+iskD*Deby)*(1+tsumImagYion+iskD*Deby) )*theta ) ;

    }

///===============================

int acf_library_light_short_conv(FILE *f, int *temperatures, int temperatures_len, double ti, double te, double *acf, int len)
    {

    const int nPoints = 19;

    int i;
    int ti_int, te_int;
    float acf_library[nPoints];
    int result;

    if (len == 0)
        return 0;

    if (f == NULL)
        return 0;

    if (acf == NULL)
        return 0;

    if ( (ti < 500) || (ti > 4000) )
        return 0;

    if ( (te < 500) || (te > 4000) )
        return 0;

    if ((te/ti < 0.7) || ((te/ti) > 4.0))
        return 0;

    if (len > nPoints)
        len = nPoints;

    ti_int = ( (int)(floor(ti)) /20)*20; // округляем ti
    te_int = ( (int)(floor(te)) /20)*20; // округляем te


    for (i = 0; i < 2*temperatures_len-1; i+=2)
        if ( temperatures[i] == ti_int )
            if (temperatures[i+1] == te_int)
                break;

    if ( i/2 >= temperatures_len)
        return 0;

    result = fseek(f, (i/2)*nPoints*sizeof(float), SEEK_SET) ;
    if (result != 0)
        return 0;

    result = fread(acf_library, sizeof(float), len, f) ;
    if (result != len)
        return 0;

    for (i = 0; i < len; i++)
        acf[i] = acf_library[i];

    return len;

    }


///===============================

int acf_library_light_short(FILE *f, int *temperatures, int temperatures_len, double ti, double te, double *acf, int len)
    {

    const int nPoints = 26;

    int i;
    int ti_int, te_int;
    float acf_library[nPoints];
    int result;

    if (len == 0)
        return 0;

    if (f == NULL)
        return 0;

    if (acf == NULL)
        return 0;

    if ( (ti < 500) || (ti > 4000) )
        return 0;

    if ( (te < 500) || (te > 4000) )
        return 0;

    if ((te/ti < 0.7) || ((te/ti) > 4.0))
        return 0;

    if (len > nPoints)
        len = nPoints;

    ti_int = ( (int)(floor(ti)) /20)*20; // округляем ti
    te_int = ( (int)(floor(te)) /20)*20; // округляем te


    for (i = 0; i < 2*temperatures_len-1; i+=2)
        if ( temperatures[i] == ti_int )
            if (temperatures[i+1] == te_int)
                break;

    if ( i/2 >= temperatures_len)
        return 0;

    result = fseek(f, (i/2)*nPoints*sizeof(float), SEEK_SET) ;
    if (result != 0)
        return 0;

    result = fread(acf_library, sizeof(float), len, f) ;
    if (result != len)
        return 0;

    for (i = 0; i < len; i++)
        acf[i] = acf_library[i];

    return len;

    }

///===============================

int acf_library_oxygen(FILE *f, int *temperatures, int temperatures_len, double ti, double te, double *acf, int len)
    {

    const int nPoints = 27;

    int i;
    int ti_int, te_int;
    int result;

    if (len == 0)
        return 0;

    if (f == NULL)
        return 0;

    if (acf == NULL)
        return 0;

    if ( (ti < 500) || (ti > 4000) )
        return 0;

    if ( (te < 500) || (te > 4000) )
        return 0;

    if ((te/ti < 0.7) || ((te/ti) > 4.0))
        return 0;

    if (len > nPoints)
        len = nPoints;

    ti_int = ( (int)(floor(ti)) /10)*10; // округляем ti
    te_int = ( (int)(floor(te)) /10)*10; // округляем te


    for (i = 0; i < 2*temperatures_len-1; i+=2)
        if ( temperatures[i] == ti_int )
            if (temperatures[i+1] == te_int)
                break;

    if ( i/2 >= temperatures_len)
        return 0;

    result = fseek(f, (i/2)*nPoints*sizeof(double), SEEK_SET) ;
    if (result != 0)
        return 0;

    result = fread(acf, sizeof(double), len, f) ;
    if (result != len)
        return 0;

    return len;

    }



///===============================

int library_light_list_of_temperatures_get(int *temperatures)
    {
    int ti, te;
    int i = 0;

    for (ti = 500; ti <= 4000; ti+=20)
        for (te = 500; te <= 4000; te+=20)
            if ( ( (double)te/ti <= 4.0 ) && ( (double)te/ti >= 0.7 )  )
                {
                temperatures[i] = ti;
                temperatures[i+1] = te;
                i += 2;
                }
    temperatures[i] = 0;
    temperatures[i+1] = 0;
    return i/2;
    }

///===============================

int library_light_list_of_temperatures_get2(int *temperatures)
    {
    int ti, te;
    int i = 0;

    for (ti = 500; ti <= 5000; ti+=20)
        for (te = 500; te <= 5000; te+=20)
            if ( ( (double)te/ti <= 4.0 ) && ( (double)te/ti >= 0.7 )  )
                {
                temperatures[i] = ti;
                temperatures[i+1] = te;
                i += 2;
                }
    temperatures[i] = 0;
    temperatures[i+1] = 0;
    return i/2;
    }

///===============================

int library_oxygen_list_of_temperatures_get(int *temperatures)
    {
    int ti, te;
    int i = 0;

    for (ti = 500; ti <= 4000; ti+=10)
        for (te = 500; te <= 4000; te+=10)
            if ( ( (double)te/ti <= 4.0 ) && ( (double)te/ti >= 0.7 )  )
                {
                temperatures[i] = ti;
                temperatures[i+1] = te;
                i += 2;
                }
    temperatures[i] = 0;
    temperatures[i+1] = 0;
    return i/2;
    }

///===============================

int library_light_list_get(char* prefix, int he_percent_int, char *filelist)
    {
    int hyd;
    int n;

    char temp[MAX_PATH];

    if (filelist == NULL)
        return 0;

    *filelist = '\0';

    for (hyd = 0, n = 0; hyd <= 1000-he_percent_int*10; hyd+=5, n++)
        {
        sprintf(temp, "%sH=%04d_He=%02d.dat\n", prefix, hyd, he_percent_int);
        strcat(filelist, temp);
        }

    return n;
    }

///===============================


int library_light_list_get_filename(char *filename, char *filelist, int num)
    {
    int i, j, c;

    for (i = 0, j = 0, c = 0  ;  ;  i++, j++)
        {
        *(filename+j) = *(filelist+i);
        if (*(filename+j) == '\0')
            return 0;
        if ( *(filelist+i) == '\n' )
            {
            if (c < num)
                {
                j = -1;
                c++;
                }
            else
                {
                *(filename+j) = '\0';
                return 1;
                }
            }
        }

    return 0;
    }

///===============================

int library_heavy_list_of_temperatures_get(int *temperatures)
    {

    int ti, te;
    int i = 0;

    for (ti = 200; ti <= 4000; ti+=10)
        for (te = 200; te <= 4000; te+=10)
            if ( ( (double)te/ti <= 3.5 ) && ( (double)te/ti >= 0.5 )  )
                {
                temperatures[i] = ti;
                temperatures[i+1] = te;
                i += 2;
                }
    temperatures[i] = 0;
    temperatures[i+1] = 0;
    return i/2;

    }

///===============================

int acf_library_heavy(FILE *f, int *temperatures, int temperatures_len, double ti, double te, double *acf, int len)
{

int i;
int ti_int, te_int;
float acf_fortran[27];
int result;

if (len == 0)
    return 0;

if (f == NULL)
    return 0;

if (acf == NULL)
    return 0;

if ( (ti < 200) || (ti > 4000) )
    return 0;

if ( (te < 200) || (te > 4000) )
    return 0;

if ((te/ti < 0.5) || ((te/ti) > 3.5))
    return 0;

if (len > 27) // в библиотеках хранятся 27 точек АКФ
    len = 27;

ti_int = ( (int)(floor(ti)) /10)*10; // округляем ti
te_int = ( (int)(floor(te)) /10)*10; // округляем te


for (i = 0; i < 2*temperatures_len-1; i+=2)
    if ( temperatures[i] == ti_int )
        if (temperatures[i+1] == te_int)
            break;

if ( i/2 >= temperatures_len)
    return 0;

result = fseek(f, (i/2)*27*sizeof(float), SEEK_SET) ;
if (result != 0)
    return 0;

result = fread(acf_fortran, sizeof(float), len, f) ;
if (result != len)
    return 0;

for (i = 0; i < len; i++)
    acf[i] = acf_fortran[i];

return len;

}

