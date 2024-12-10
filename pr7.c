#include <stdio.h>
#include <conio.h>
#include "calculation.h"
#define MIN_EPSILON 1e-15
#define MAX_EPSILON 1e-3

int main() {
    printf("This program calculates non-linear equations on interval [a,b]\n");
    do {
        char equation = 0;
        printf(
            "Enter an equation:\n1) cos(y/x) - 2(sin 1/x) + 1/x = 0, x[a,b];\n2) sin(ln x) - cos(ln x) + y ln x = 0, x[a,b];\n");
        double (*choice_of_function)(double, double) = 0;
        double (*derivative)(double, double) = 0;
        do {
            equation = getch();
            switch (equation) {
                case '1': {
                    choice_of_function = function_1;
                    derivative = derivative_1;
                }
                break;
                case '2': {
                    choice_of_function = function_2;
                    derivative = derivative_2;
                }
                break;
                default: {
                    printf("Incorrect input, try again\n");
                    fflush(stdin);
                }
                break;
            }
        } while (equation != '1' && equation != '2');

        double a = 0, b = 0;
        printf("Enter an interval [a,b]\n");
        do {
            do {
                printf("Enter 'a' (not 0)\n");
                if (scanf("%lf", &a) != 1 || a == 0) {
                    printf("Incorrect input of 'a', it can not be ZERO or another character other than numbers\n");
                }
                fflush(stdin);
            } while (a == 0);
            do {
                printf("Enter 'b' (not 0)\n");
                if (scanf("%lf", &b) != 1 || b == 0) {
                    printf("Incorrect input of 'b', it can not be ZERO or another character other than numbers\n");
                }
                fflush(stdin);
            } while (b == 0);
            if (a >= b) {
                printf("'a' can not be greater than 'b' or equals to it\n");
            }
        } while (a == 0 || b == 0 || a >= b);

        double y = 0;
        double validY = 0;
        do {
            printf("Enter 'y':\n");
            validY = scanf("%lf", &y);
            if (validY != 1) {
                printf("Incorrect input of 'y'\n");
            }
            fflush(stdin);
        } while (!validY);
        double e = 0;
        do {
            printf("Enter accuracy from %.0e to %.0e:\n",MIN_EPSILON, MAX_EPSILON);
            if (scanf("%lf", &e) != 1 || e < MIN_EPSILON || e > MAX_EPSILON) {
                printf("Incorrect input, enter valid accuracy:\n");
            }
            fflush(stdin);
        } while (e < MIN_EPSILON || e > MAX_EPSILON);

        calculate(choice_of_function,derivative,a,b,y,e);


        printf("Press 'r' to restart or ANY OTHER key to exit\n");
    } while (getch() == 'r');
    return 0;
}
