#ifndef CALCULATION_H
#define CALCULATION_H

#define MAX_ITERATIONS 1e3
#define STEP 1e-6
#include <math.h>

double function_1(double x, double y) {
    return cos(y / x) - 2.0 * sin(1.0 / x) + 1.0 / x;
}

double function_2(double x, double y) {
    return sin(log(x)) - cos(log(x)) + y * log(x);
}

double derivative_1(double x, double y) {
    if (x == 0.0) {
        printf("Error, division by zero\n");
        return NAN;
    }
    return (y * sin(y / x) + 2 * cos(1 / x) - 1) / (x * x);
}

double derivative_2(double x, double y) {
    if (x == 0.0) {
        printf("Error, division by zero\n");
        return NAN;
    }
    return (cos(log(x))+sin(log(x))+y)/x;
}


double half_division(double (*function)(double, double), double a, double b, double y, double e) {
    double fa = function(a, y);
    double fb = function(b, y);
    if (fa * fb >= 0) {
        printf("Error: Fa and Fb must have opposite signs\n");
        return NAN;
    }
    double middle;
    while ((b - a) / 2.0 > e) {
        middle = (a + b) / 2.0;
        double fmiddle = function(middle, y);
        if (fmiddle == 0.0) {
            return middle;
        }
        if (fa * fmiddle < 0) {
            b = middle;
            fb = fmiddle;
        } else {
            a = middle;
            fa = fmiddle;
        }
    }
    return (a + b) / 2.0;
}

double newton(double (*function)(double, double), double (*derivative)(double, double), double x0, double y, double e) {
    double x = x0;
    for (int iter = 0; iter < MAX_ITERATIONS; iter++) {
        const double fx = function(x, y);
        const double fx_prime = derivative(x, y);
        const double x_new = x - fx / fx_prime;
        if (fabs(x_new - x) < e) {
            return x_new;
        }
        x = x_new;
    }
    printf("Newton`s method did not converge after %d iterations.\n", MAX_ITERATIONS);
    return NAN;
}

void calculate(double (*function)(double, double), double (*derivative)(double, double), double a, double b, double y, double e){
    unsigned accuracy = (int)-log10(e);
    printf("Choose method (1 for half division or 2 for Newton`s):\n");
    char method;
    do {
        method = getch();
        switch (method) {
            case '1': {
                double x1 = a;
                double x2 = a + STEP;
                printf("Roots that were found on interval [%.*lf, %.*lf]: \n", accuracy, a, accuracy, b);
                unsigned iteration = 1;
                while (x2 <= b) {
                    double function_a = function(x1, y);
                    double function_b = function(x2, y);
                    if (function_a * function_b < 0) {
                        double root = half_division(function, x1, x2, y, e);
                        if (!isnan(root)) {
                            printf("x%d: %.*lf\n", iteration++, accuracy, root);
                        }
                    }
                    x1 = x2;
                    x2 += STEP;
                }
            }
            break;
            case '2': {
                double roots[150];
                unsigned counter = 0;
                printf("Roots on interval [%.*lf, %.*lf]: \n", accuracy, a, accuracy, b);
                unsigned i = 1;
                for (double x = a; x < b; x += STEP) {
                    double x1 = x, x2 = x + STEP;
                    if (function(x1, y) * function(x2, y) < 0) {
                        double x0 = (x1 + x2) / 2.0;
                        double root = newton(function, derivative, x0, y, e);
                        if (!isnan(root)) {
                            int is_duplicate = 0;
                            for (int j = 0; j < counter; j++) {
                                if (fabs(root - roots[j]) < e) {
                                    is_duplicate = 1;
                                    break;
                                }
                            }
                            if (!is_duplicate) {
                                roots[counter++] = root;
                                printf("x%d: %.*lf\n", i++, accuracy, root);
                            }
                        }
                    }
                }
            }
            break;
            default: {
                printf("Invalid method: %d.\n", method);
            }break;
        }
    } while(method != '1' && method != '2');
}

#endif
