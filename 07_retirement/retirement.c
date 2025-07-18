#include <stdio.h>
#include <stdlib.h>

struct _retire_info{
    int months;
    double contribution;
    double rate_of_return;
};
typedef struct _retire_info retire_info;

void retirement (int startAge,   //in months
                       double initial, //initial savings in dollars
                       retire_info working, //info about working
                       retire_info retired) //info about being retired
{
    int start_year = startAge / 12;
    int start_month = startAge % 12;
    double cur = initial;
    printf("Age %3d month %2d you have $%.2lf\n", start_year, start_month, cur);

    for (int i = 1; i <= working.months; i++) {
        if (start_month < 11) {
            start_month++;
        } else {
            start_year++;
            start_month = 0;
        }
        cur = cur * working.rate_of_return / 12 + cur + working.contribution;
        printf("Age %3d month %2d you have $%.2lf\n", start_year, start_month, cur);
    }

    for (int i = 1; i < retired.months; i++) {
        if (start_month < 11) {
            start_month++;
        } else {
            start_year++;
            start_month = 0;
        }
        cur = cur * retired.rate_of_return / 12 + cur + retired.contribution;
        printf("Age %3d month %2d you have $%.2lf\n", start_year, start_month, cur);
    }
}



int main(void) {

    retire_info working;
    working.months = 489;
    working.contribution = 1000;
    working.rate_of_return = 0.045;

    retire_info retired;
    retired.months = 384;
    retired.contribution = -4000;
    retired.rate_of_return = 0.01;

    retirement(327, 21345, working, retired);
    return EXIT_SUCCESS;

}

