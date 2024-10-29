#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159

//I Grant Bailey certify that this programming assignment reflects my own work, without the use of any external individuals (other than course/department staff), generative-AI, or any other forbidden resources. I understand/accept the consequences of cheating as outlined in the course syllabus.

//Function declarations:
double * linear_func(int a, int b, const double * values, int size);
double * quadratic_func(int a, int b, const double * values, int size);
double * exp_func(int a, int b, const double * values, int size);
double * sin_func(int a, int b, const double * values, int size);
double * func_derivative(const char * func, double * val_plus, double * val, double * val_minus, int a, int b, int order, double h, int size);

//Function pointer declarations:
double * (*(linFunc_ptr))(int, int, const double *, int) = linear_func;
double * (*(quadFunc_ptr))(int, int, const double *, int) = quadratic_func;
double * (*(expFunc_ptr))(int, int, const double *, int) = exp_func;
double * (*(sinFunc_ptr))(int, int, const double *, int) = sin_func;

int main(int argc, char * argv[]) {
	//Taking in the command line arguments
	int size = argc - 2;
	double * unassignedVals_ptr = (double *) malloc(size * sizeof(double));
	double * valsPlus_ptr = (double *) malloc(size * sizeof(double));
	double * valsMinus_ptr = (double *) malloc(size * sizeof(double));
	for (int i = 0; i < size; i++) {
		*(unassignedVals_ptr + i) = atof(argv[i + 1]);
		*(valsPlus_ptr + i) = atof(argv[i + 1]) + atof(argv[size + 1]);
		*(valsMinus_ptr + i) = atof(argv[i + 1]) - atof( argv[size + 1]);
	}
	const double * vals_ptr = (const double *) unassignedVals_ptr;
	double h = atof(argv[argc - 1]);

	//Consulted StackOverflow for how to free a pointer to a constant double (https://stackoverflow.com/questions/2819535/unable-to-free-const-pointers-in-c)
	free((void *) vals_ptr);
	vals_ptr = NULL;
	free(valsPlus_ptr);
	valsPlus_ptr = NULL;
	free(valsMinus_ptr);
	valsMinus_ptr = NULL;
}

double * linear_func(int a, int b, const double * values, int size) {
	double * linOutput_ptr = (double *) malloc(size * sizeof(double));
	for (int i = 0; i < size; i++) {
		*(linOutput_ptr + i) = (a * (*(values + i))) + b;
	}
	return linOutput_ptr;
}

double * quadratic_func(int a, int b, const double * values, int size) {
	double * quadOutput_ptr = (double *) malloc(size * sizeof(double));
	for (int i = 0; i < size; i++) {
		//Consuted geeksforgeeks.org/power-funciton-c to understand pow() function
		*(quadOutput_ptr + i) = pow(*(values + i), 2) + (a * (*(values + i))) + b;
	}
	return quadOutput_ptr;
}

double * exp_func(int a, int b, const double * values, int size) {
	double * expOutput_ptr = (double *) malloc(size * sizeof(double));
	for (int i = 0; i < size; i++) {
		//Consulted geeksforgeeks.org/c-library-exp-function/ to understand the exp() function
		*(expOutput_ptr + i) = exp(a * (*(values + i)));
	}
	return expOutput_ptr;
}

double * sin_func(int a, int b, const double * values, int size) {
	double * sinOutput_ptr = (double *) malloc(size * sizeof(double));
	for (int i = 0; i < size; i++) {
		//Consulted geeksforgeeks.org/sin-in-c/ to understand the sin() function
		*(sinOutput_ptr + i) = a * sin(b * (*(values + i)));
	}
	return sinOutput_ptr;
}

double * func_derivative(const char * func, double * val_plus, double * val, double * val_minus, int a, int b, int order, double h, int size) {
	double * derivativeOutput_ptr = (double *) malloc(size * sizeof(double));
	double * (*(inputFunc_ptr))(int, int, const double *, int);
	if (*(func) == 's' && *(func + 1) == 'i' && *(func + 2) == 'n' && *(func + 3) == '\0') {
		inputFunc_ptr = sinFunc_ptr;
	} else if (*(func) == 'l' && *(func + 1) == 'i' && *(func + 2) == 'n' && *(func + 3) == '\0') {
		inputFunc_ptr = linFunc_ptr;
	} else if (*(func) == 'e' && *(func + 1) == 'x' && *(func + 2) == 'p' && *(func + 3) == '\0') {
		inputFunc_ptr = expFunc_ptr;
	} else if (*(func) == 'q' && *(func + 1) == 'u' && *(func + 2) == 'a' && *(func + 3) == 'd' && *(func + 4) == '\0') {
		inputFunc_ptr = quadFunc_ptr;
	} else {
		inputFunc_ptr = NULL;
	}
	double * fxPlusH_ptr = inputFunc_ptr(a, b, val_plus, size);
	double * fx_ptr = inputFunc_ptr(a, b, val, size);
	double * fxMinusH_ptr = inputFunc_ptr(a, b, val_minus, size);
	switch (order) {
		case 0:
			for (int i = 0; i < size; i++ ) {
				*(derivativeOutput_ptr + i) = *(fx_ptr + i);
			}
		break;
		case 1:
			for (int i = 0; i < size; i++) {
				*(derivativeOutput_ptr + i) = ((*(fxPlusH_ptr + i)) - (*(fx_ptr + i))) / h;
			}
		break;
		case 2:
			for (int i = 0; i < size; i++) {
				*(derivativeOutput_ptr + i) = ((*(fxPlusH_ptr + i)) - (2 * (*(fx_ptr + i))) + (*(fxMinusH_ptr + i))) / (h * h);
			}
		break;
		default:
			for (int i = 0; i < size; i++) {
				*(derivativeOutput_ptr + i) = PI;
			}
	}
	return derivativeOutput_ptr;
}
