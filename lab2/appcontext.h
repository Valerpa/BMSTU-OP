#ifndef APPCONTEXT_H
#define APPCONTEXT_H
#include "stdio.h"
#include <string>
using namespace std;
#define SIZE 50

enum Operations { //кнопочки
    Open_file,
    Load_data,
    Calculate_metrics,
    Clean_data
};



typedef struct Headers{ //структура для заголовков таблицы (её первая строка)
    char* year_header;
    char* region_header;
    char* npg_header;
    char* birth_rate_header;
    char* death_rate_header;
    char* gdw_header;
    char* urban_header;
}Headers;


typedef struct Dem_unit { //структура для строки таблицы
    int year;
    char* region;
    double npg;
    double birth_rate;
    double death_rate;
    double gdw;
    double urban;
}Dem_unit;

typedef struct Metrics {
    double max_value;
    double min_value;
    double median;
}Metrics;

typedef struct Error_s {
    char err_info[SIZE];
    int error_check = 0;
    int err_line;
}Error_s;

typedef struct Table {
    const char *filename; //имя файла
    size_t lines; //число строк
    size_t fields; //число столбцов
    int invalid_lines;
    Headers headers;
    Dem_unit dem_unit;
    Error_s errors;
}Table;

struct Params {
    const char *chosen_region;
    int column_num;
    int min_year;
    int max_year;
};




#endif // APPCONTEXT_H
