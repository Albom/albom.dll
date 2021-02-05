
/*
 * Copyright 2011-2021, Oleksandr Bogomaz (o.v.bogomaz1985@gmail.com)
 */

#include "files.h"

/// =============================

int filelist_get(char *dir_name, char *filelist) {

    int i;
    DIR *dir;
    struct dirent *d1;
    char temp[FILENAME_MAX];

    if (filelist == NULL)
        return 0;

    *filelist = '\0';

    dir = opendir (dir_name);

    for (i = 0; ; i++) {
        d1 = readdir(dir);
        if (d1 == NULL)
            break;
        if ( strcmp(".", d1->d_name) && strcmp("..", d1->d_name)) {
            sprintf(temp, "%s\n", d1->d_name);
            strcat(filelist, temp);
        } else i--;
    }

    closedir(dir);

    return i;
}


/// =============================

int filelist_get_filename(char *filelist, char *filename, int num) {
    int i, j, c;

    j = c = 0;
    for (i = 0; ; i++, j++) {
        *(filename+j) = *(filelist+i);
        if (*(filename+j) == '\0')
            return 0;
        if ( *(filelist+i) == '\n' ) {
            if (c < num) {
                j = -1;
                c++;
            } else {
                *(filename+j) = '\0';
                return 1;
            }
        }
    }

    return 0;
}

/// =============================

int file_add_i(
    char *fname,
    int *in,
    int il,
    char *format
) {

    int	i;
    FILE *f;

    f = fopen(fname, "at");
    if (NULL == f)
        return 0;

    for (i = 0; i < il; i++)
        fprintf(f, format, *(in+i));

    fclose(f);
    return il;
}

/// =============================

int file_add_d(
    char *fname,
    double *in,
    int il,
    char *format
) {

    int	i;
    FILE *f;

    f = fopen(fname, "at");
    if (NULL == f)
        return 0;

    for (i = 0; i < il; i++)
        fprintf(f, format, *(in+i));

    fclose(f);
    return il;
}
/// =============================

int file_add_sh(
    char *fname,
    short *in,
    int il,
    char *format
) {

    int	i;
    FILE *f;

    f = fopen(fname, "at");
    if (NULL == f)
        return 0;

    for (i = 0; i < il; i++)
        fprintf(f, format, *(in+i));

    fclose(f);
    return il;
}
/// =============================

int file_add_s(
    char *fname,
    char *in,
    char *format
) {

    FILE *f;

    f = fopen(fname, "at");
    if (NULL == f)
        return 0;

    fprintf(f, format, in);

    fclose(f);
    return 1;
}

/// =============================

int file_creat_and_add_s(
    char *fname,
    char *in
) {
    FILE *f;
    int length;

    f = fopen(fname, "wt");
    if (NULL == f)
        return 0;

    length = strlen(in);
    if (length == 0) {
        fclose(f);
        return 1;
    }

    fwrite(in, length, 1, f);

    fclose(f);
    return 1;
}



/// =============================

int    file_creat (
    char *fname
) {

    FILE	*f;

    f = fopen(fname, "wt");
    if (f == NULL)
        return 0;

    fclose(f);

    return 1;
}

/// =============================

int file_add_bin_d(
    char *fname,
    double *in,
    int il
) {
    FILE *f;

    f = fopen(fname, "ab");
    if (NULL == f)
        return 0;

    fwrite(in, il*sizeof(double), 1, f);

    fclose(f);
    return il;
}

/// =============================

int    file_newline (
    char *fname
) {
    FILE	*f;

    f = fopen(fname, "at");
    if (NULL == f)
        return 0;

    fprintf(f, "\n");

    fclose(f);
    return 1;
}

/// =============================

int file_load_all_d (
    char *fname,
    double *buf
) {
    FILE	*f;
    int fsize;

    fsize = file_size (fname);
    if (fsize <= 0)
        return 0;

    f = fopen(fname, "rb");
    if (NULL == f)
        return 0;

    fsize = fread(buf, fsize, 1, f);

    fclose(f);
    return fsize;
}

/// =============================

int file_size (char *fname) {
    FILE	*f;
    int     len;

    f = fopen(fname, "rb");
    if (NULL == f)
        return -1;

    fseek(f, 0, SEEK_END);
    len = ftell(f);

    fclose(f);
    return len;

}

/// =============================

int buffer_clear(char *buf) {
    *buf = '\0';
    return 0;
}

/// =============================

int buffer_add_s(char *buf, char *in, char *format) {
    char *tmp;
    tmp = (char*) malloc(4096);
    if ( (tmp == NULL) || (buf == NULL) )
        return 0;
    sprintf(tmp, format, in);
    strcat(buf, tmp);
    free(tmp);
    return 1;
}

/// =============================

int  buffer_newline (
    char *buf
) {
    if (buf == NULL)
        return 0;

    strcat(buf, "\n");
    return 1;
}

/// =============================

int buffer_add_i(
    char *buf,
    int *in,
    int il,
    char *format
) {

    int	i;
    char *tmp;

    tmp = (char*) malloc(4096);
    if ( (tmp == NULL) || (buf == NULL) )
        return 0;

    for (i = 0; i < il; i++) {
        sprintf(tmp, format, *(in+i));
        strcat(buf, tmp);
    }

    free(tmp);
    return il;
}

/// =============================

int buffer_add_d(
    char *buf,
    double *in,
    int il,
    char *format
) {
    int	i;
    char *tmp;

    tmp = (char*) malloc(4096);
    if ( (tmp == NULL) || (buf == NULL) )
        return 0;

    for (i = 0; i < il; i++) {
        sprintf(tmp, format, *(in+i));
        strcat(buf, tmp);
    }

    free(tmp);
    return il;
}

/// =============================

char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace(*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace(*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}

/// =============================

int file_table_load(char *filename, int *c, int *r, double *arr) {

    if (arr == NULL){
        return 0;
    }

    int MAX_LENGTH = 128*1024;

    *c = 0;
    *r = 0;

    FILE *f = fopen(filename, "rt");
    if (f == NULL) {
        return 0;
    }

    char *buffer = (char*) malloc(MAX_LENGTH*sizeof(char));

    int num = 0;
    while (NULL != fgets(buffer, MAX_LENGTH, f) ) {
        if (strlen(trimwhitespace(buffer)) > 0) {
            *c = 0;
            char *b = strtok(buffer, " \t;,\n");
            while (b) {
                sscanf(b, "%lf", arr+num);
                b = strtok(NULL, " \t;,\n");
                (*c)++;
                num++;
            }
        (*r)++;
        }

    }

    free(buffer);
    fclose(f);

    return num;
}

