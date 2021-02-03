
/*
 * Copyright 2011-2021, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#include "mymath.h"

#include "filters.h"
#include "data_filter_func.h"
#include "data_filter_freq_resp.h"


/// =============================

int razr_load(char *filename, double *array, int len)
{
FILE *f;
int i;
double h;

f = fopen(filename, "rt");
if (f == NULL) // если файл не открылся
    return 0;

for (i = 0; i < len; i++)
    {
    if ( feof(f) )
        {
        fclose(f);
        return i-1;
        }
    fscanf(f, "%lf %lf", &h, array+i);
    }
fclose(f);
return i;
}

/// =============================

int filter_load(char *filtername, double *array, int len)
{
int l;
int i;

if (len < 36)
    l = len;
else
    l = 36;

for ( i = 0; i < l; i++ )
    {
    switch ( filtername[0] )
        {
        case 'y':
        case 'Y':
            array[i] = FILTER_FUNCTION_30USEC[0][i];
            break;

        case 'c':
        case 'C':
            array[i] = FILTER_FUNCTION_30USEC[1][i];
            break;

        case 'o':
        case 'O':
            array[i] = FILTER_FUNCTION_30USEC[2][i];
            break;

        case 'n':
        case 'N':
            array[i] = FILTER_FUNCTION_30USEC[3][i];
            break;

        case 'k':
        case 'K':
            array[i] = FILTER_FUNCTION_30USEC[4][i];
            break;

        default:
            array[i] = FILTER_FUNCTION_30USEC[5][i];
            break;

        };

    }

if (len > 36)
    for (i = 35; i < len; i++)
        array[i] = 0;

return i;
}

/// =============================

double filter_freq_resp(char *filtername, double freq) // Frequency response (АЧХ)
{
if ( (*filtername == 'O')||(*filtername == 'o') )
    {
    if (freq < FILTER_FREQ_O[FILTER_LEN_O-1]) // без экстраполяции
        return array_linear_d(freq, FILTER_FREQ_O, FILTER_FR_O, FILTER_LEN_O);
    else
        return 0;
    }
else
    return 0;
}

/// =============================
