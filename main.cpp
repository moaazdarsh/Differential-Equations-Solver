#include <iostream>
#include <functional>
#include <cmath>
#include <fstream>
#include "Solver.h"

double sample_derivative(double x, double y) {
    return 1/(y*y*y); // Example: dy/dx = 2
}

int main() {
    ODE_1st ode(sample_derivative);
    ode.runge_kutta_4th(0.0, 1.0, 0.01, 500); // Initial conditions: x0=0, y0=0, delta=0.1, iterations=1000
/*
    for (int i = 0; i <= 1000; i++) {
        cout << ode.y_at(i * 0.1) << " ";
    }
*/
    ode.export_to_CSV("ode_solution.csv");
    
    return 0;
}