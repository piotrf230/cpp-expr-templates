#include <iostream>

#include "functional-expressions.h"

template <typename F>
double integrate(const F& function, double from, double to, double step) {
	double result = 0;
	for (; from < to; from += step) {
		result += (function(from) + function(from + step)) * step / 2;
	}
	return result;
}

using namespace FuncExpr;

int main() {
	Variable x;
	Constant a(2), b(3);

	std::cout << integrate(
		a * pow(x, a) - b * x + b,
		0.0,
		3.0,
		.001
	) << std::endl;
}