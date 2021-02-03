
/*
 * Copyright 2011-2021, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#ifndef _Included_data_filter_func
#define _Included_data_filter_func

const double FILTER_FUNCTION_30USEC[][36] = {

    {
        /// "y" — фильтр Кауэра (5 кГц)
        1, 0.939, 0.771, 0.534, 0.281, 0.061,
        -0.089, -0.157, -0.153, -0.1, -0.033, 0.023,
        0.053, 0.053, 0.034, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },

    {
        /// "c" — фильтр Кауэра (10 кГц)"
        1, 0.804, 0.362, 0.029, -0.173, -0.098,
        0.028, 0.077, 0.038, -0.022, -0.045, -0.025,
        0.005, 0.017, 0.008, -0.008, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },

    {
        /// "o" — фильтр Кауэра (20 кГц)

        1.0000,
        0.5529,
        -0.0931,
        -0.1326,
        0.0839,
        0.0386,
        -0.0631,
        -0.0026,
        0.0360,
        0.0095,
        0.0135,
        0.0133,
        0.0025,
        -0.0075,
        0.0034,
        0.0002,
        0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },

    {
        /// "n" — фильтр Чебышева (10 кГц)
        1, 0.727, 0.242, -0.054, -0.100, -0.037,
        0.017, 0.026, 0.013, 0.000, -0.005, -0.005,
        -0.003, -0.000, 0.002, 0.002, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },

    {
        /// "k" — фильтр Гаусса (10 кГц)
        1, 0.669, 0.217, 0.028, -0.012, -0.010,
        -0.005, -0.002, 0.000, 0.000, 0.000, 0.001,
        0.000, 0.000, 0.000, 0.000, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    },

    {
        /// другой фильтр
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0
    }

};

#endif // _Included_data_filter_func
