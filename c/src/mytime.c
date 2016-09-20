
/*
 * Copyright 2011-2016, Oleksandr Bogomaz (albom85@yandex.ru)
 */

#include "mytime.h"

//=========================

int NDAYS[2][12] = { {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

//=========================

time_t date_2unixtime(int DD, int MM, int YY, int hh, int mm, int ss) {
    unsigned long days = ((YY-1970)*(365+365+366+365)+1)/4 + DD - 1;

    switch (MM) {
    case 2:
        days += 31;
        break;
    case 3:
        days += 31+28;
        break;
    case 4:
        days += 31+28+31;
        break;
    case 5:
        days += 31+28+31+30;
        break;
    case 6:
        days += 31+28+31+30+31;
        break;
    case 7:
        days += 31+28+31+30+31+30;
        break;
    case 8:
        days += 31+28+31+30+31+30+31;
        break;
    case 9:
        days += 31+28+31+30+31+30+31+31;
        break;
    case 10:
        days += 31+28+31+30+31+30+31+31+30;
        break;
    case 11:
        days += 31+28+31+30+31+30+31+31+30+31;
        break;
    case 12:
        days += 31+28+31+30+31+30+31+31+30+31+30;
        break;
    }

    if ( (MM >= 3) && (YY%4 == 0) )
        days ++;

    return days*24*3600 + hh*3600 + mm*60 + ss;
}

//=========================

int unixtime_2date(time_t timestamp, int *DD, int *MM, int *YY, int *hh, int *mm, int *ss) {

    *ss = timestamp % 60;

    timestamp /= 60;       // minutes
    *mm = timestamp % 60;

    timestamp /= 60;       // hours
    *hh = timestamp % 24;

    timestamp /= 24;       // days

    for ( *YY = 1970; timestamp >= 365; (*YY)++ )
        if ( date_year_leap(*YY) )
            timestamp -= 366;
        else
            timestamp -= 365;

    timestamp++; // дни начинаются с 1

    for (*MM = 0; timestamp > NDAYS[0][*MM]; (*MM)++)
        timestamp -= NDAYS[0][*MM];

    if (*MM > 2 && date_year_leap(*YY))
        timestamp--;

    (*MM)++; // месяцы начинаются с 1

    *DD = timestamp;

    return 0;
}


//=========================

void tdatetime_2date(double tdatetime, int *DD, int *MM, int *YY, int *hh, int *mm, int *ss, int *ms) {
    int date = (int)tdatetime;

    int mth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int d = date - 1;

    int m = 0;
    int y = 1900;

    for (;;) {
        if ( d > mth[m] ) {
            if (m == 1) {
                if ( date_year_leap(y) )
                    d-=29;
                else d-=28;
            } else
                d-=mth[m];

            if (m == 11) {
                m = 0;
                y++;
            } else m++;

        } else break;

    }

    m++;

    *DD = d;
    *MM = m;
    *YY = y;

    double time = tdatetime - date;
    *hh = time*24;
    *mm = (time*24 - *hh)*60;
    *ss = ((time*24 - *hh)*60 - *mm)*60;
    *ms = (((time*24 - *hh)*60 - *mm)*60 - *ss)*1000;
}

//=========================

double time_2decimal(int hh, int mm, int ss) {
    return (double)hh + ((double)mm*60+(double)ss)/3600.;
}

//=========================

int time_2str(int hh, int mm, int ss, char *timestr) {

    timestr[0]=hh/10 + '0';
    timestr[1]=hh%10 + '0';
    timestr[2]=':';
    timestr[3]=mm/10 + '0';
    timestr[4]=mm%10 + '0';
    timestr[5]=':';
    timestr[6]=ss/10 + '0';
    timestr[7]=ss%10 + '0';
    timestr[8]='\0';

    return 1;
}

//=========================

int time_from_str(int *hh, int *mm, int *ss, const char *timestr) {

    *hh = (timestr[0] - '0')*10 + (timestr[1] - '0');
    *mm = (timestr[3] - '0')*10 + (timestr[4] - '0');
    *ss = (timestr[6] - '0')*10 + (timestr[7] - '0');

    if ( ( *hh > 23 ) || (*mm > 59) || (*ss > 59) )
        return 0;
    else
        return 1;
}

//=========================

int date_from_str(int *dd, int *mm, int *yy, const char *datestr) {

    *dd = (datestr[0] - '0')*10 + (datestr[1] - '0');
    *mm = (datestr[3] - '0')*10 + (datestr[4] - '0');
    *yy = (datestr[6] - '0')*10 + (datestr[7] - '0');

    if  ( *yy < 70 ) {
        *yy += 2000;
    } else {
        *yy += 1900;
    }
    if (date_valid(*dd, *mm, *yy))
        return 1;
    else
        return 0;
}

//=========================

int date_2str(int dd, int mm, int yy, char *datestr) {
    datestr[0]=dd/10 + '0';
    datestr[1]=dd%10 + '0';
    datestr[2]='.';
    datestr[3]=mm/10 + '0';
    datestr[4]=mm%10 + '0';
    datestr[5]='.';
    datestr[6]=(yy%100)/10 + '0';
    datestr[7]=(yy%100)%10 + '0';
    datestr[8]='\0';

    return 1;
}

//=========================

int time_2sec(int hh, int mm, int ss) {
    return ss+mm*60+hh*3600;
}

//=========================

int time_accum_num(int minutes) {

    if ((60*24)%minutes == 0)
        return (60*24)/minutes;
    else
        return 0;
}

//=========================

int date_year_leap( int year ) {
    if ((((year) % 4) == 0 && ((year) % 100) != 0) || ((year) % 400) == 0)
        return 1;
    else
        return 0;
}

//=========================

int date_valid(int day, int month, int year) {

    int leap;

    leap = date_year_leap(year);

    if ( month > 12 ) // если значение месяца больше 12
        return 0;

    if ( day > NDAYS[leap][month-1] ) //если значение дня больше количества дней в месяце
        return 0;

    return 1;
}

//=========================

int date_next(int *day, int *month, int *year) {

    int leap;

    leap = date_year_leap(*year);

    if (0 == date_valid(*day, *month, *year) )
        return 0;

    if ((*day == 31)&&(*month == 12)) { // если 31 декабря, наращиваем год и возвращаем 1 января
        *day = 1;
        *month = 1;
        (*year) ++;
        return 1;
    }

    if ( *day < NDAYS[leap][*month-1] ) {
        (*day) ++;
        return 1;
    } else {
        *day = 1;
        (*month) ++;
        return 1;
    }

    return 0;

}

//=========================

int time_linear(double *arr, int length){
for (int t = 1; t < length; t++){
    while (arr[t] < arr[t-1]){
        arr[t] += 24.0;
    }
}
return length;
}

//=========================

int time_normalize(double *arr, int length){
for (int t = 0; t < length; t++){
    while (arr[t] > 24.0){
        arr[t] -= 24.0;
    }
}
return length;
}
