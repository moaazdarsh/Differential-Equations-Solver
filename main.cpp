#include <iostream>
#include <functional>
#include <cmath>
#include "Eigen/Eigen/Dense"
#include <fstream>
#include "Solver/Solver.h"

double sample_derivative(double x, double y) {
    return y; // Example: dy/dx = y
}

int main() {
    /*
    // ===== 1st order ODE Sample Code =====
    ODE_1st ode(sample_derivative);
    ode.runge_kutta_4th(0.0, 1.0, 0.1, 100); // x0=0.0, y0=1.0, dx=0.1, iterations=100
    ode.export_output();
    */

    /*
    // ===== LTI ODE Sample Code =====
    nth_ODE ode({1, 1, 25}); // Underdamped example: y'' + y' + 25y = 0
    ode.euler(0.0, Eigen::Vector2d(1.0, 0.0), 0.1, 10000);

    ode.export_output();
    ode.export_to_CSV("CSVs/ODE_underdamped_solution.csv");
    */

    /*
    // ===== 1D Heat Equation Sample Code =====
    vector<double> initial_temp(50, 0.0);
    initial_temp[0] = 100.0; // Heat up left side (x=0) to 100
    heat_eqn_1D heat_eq(0.1);
    heat_eq.solve(initial_temp, 1.0, 0.2, 5000); // dx=1.0, dt=0.2, iterations=5000

    heat_eq.export_output();
    //heat_eq.export_to_CSV("CSVs/Heat1D_solution.csv");
    */

    /*
    // ===== 2D Heat Equation Sample Code =====
    int nx = 50, ny = 50;
    vector<vector<double>> initial_temp(ny, vector<double>(nx, 0.0));
    
    // Heat up left side (x=0) and bottom side (y=0) to 50
    for (int i = 0; i < ny; i++) {
        initial_temp[i][0] = 50.0; // Left side
    }
    for (int j = 0; j < nx; j++) {
        initial_temp[ny-1][j] = 50.0; // Bottom side
    }
    
    heat_eqn_2D heat_eq(0.1);
    heat_eq.solve(initial_temp, 1.0, 0.2, 5000); // dx=1.0, dt=0.2, iterations=5000
    
    heat_eq.export_output();
    */  
    return 0;
    
}