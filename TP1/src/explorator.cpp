#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>

#include "explorator.h"

void Explorator::explore(std::vector<double> x_values, std::vector<double> y_values) {
    for (int i = 0; i < 100; ++i) {
        double x = i * 0.1;
        x_values.push_back(x);
        y_values.push_back(std::sin(x));
    }

    FILE* gnuplotPipe = popen("gnuplot -persist", "w");
    if (gnuplotPipe) {
        fprintf(gnuplotPipe, "set title 'Sine Wave'\n");
        fprintf(gnuplotPipe, "set xlabel 'X-axis'\n");
        fprintf(gnuplotPipe, "set ylabel 'Y-axis'\n");
        fprintf(gnuplotPipe, "plot '-' with lines title 'sin(x)'\n");
        for (size_t i = 0; i < x_values.size(); ++i) {
            fprintf(gnuplotPipe, "%f %f\n", x_values[i], y_values[i]);
        }
        fprintf(gnuplotPipe, "e\n");
        fflush(gnuplotPipe);
        pclose(gnuplotPipe);
    } else {
        std::cerr << "gnuplot not working" << std::endl;
    }
}
