#include <stdio.h>
#include <math.h>

void StandardDeviation(double *ptr1, double *ptr2, double *ptr3, double *ptr4, double *ptr5, double *result) {
    double average = (*ptr1 + *ptr2 + *ptr3 + *ptr4 + *ptr5) / 5;
    double num = pow((*ptr1 - average), 2);
    num += pow((*ptr2 - average), 2);
    num += pow((*ptr3 - average), 2);
    num += pow((*ptr4 - average), 2);
    num += pow((*ptr5 - average), 2);
    *result = sqrt(num / 5);
}

int main(void) {
    double num1, num2, num3, num4, num5, result;
    printf("Enter 5 real numbers: ");
    scanf("%lf %lf %lf %lf %lf", &num1, &num2, &num3, &num4, &num5);
    StandardDeviation(&num1, &num2, &num3, &num4, &num5, &result);
    printf("Standard Deviation = %.3f", result);

    return 0;
}
