
/*
 * Copyright 2011-2016, Oleksandr Bogomaz (albom85@yandex.ru)
 */

#ifndef _Included_data_filter_freq_resp
#define _Included_data_filter_freq_resp

const int FILTER_LEN_O = 22;

double FILTER_FREQ_O [] = {

0,
700,
2700,
4200,
6700,
7600,
7800,
8000,
8300,
8500,
8600,
9100,
9500,
9700,
10000,
10200,
10400,
10600,
10800,
11100,
12000,
16300

};

double FILTER_FR_O [] = {

0.98,
0.98,
0.99,
1,
0.99,
0.98,
0.97,
0.96,
0.94,
0.92,
0.9,
0.8,
0.7,
0.62,
0.49,
0.385,
0.28,
0.18,
0.11,
0.05,
0.015,
0.01

};

#endif // _Included_data_filter_freq_resp
