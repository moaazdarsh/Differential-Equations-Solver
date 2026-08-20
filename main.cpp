#include <iostream>
#include <functional>
#include <cmath>
#include "Eigen/Dense"
#include <fstream>
#include "Solver/Solver.h"

double sample_derivative(double x, double y) {
    return x; // Example: dy/dx = 1/y^3
}

int main() {
    // ===== ODE Test =====
    
    //nth_ODE ode({1, 3, 3, 1}); // Example: y''' + 3y'' + 3y' + y = 0 (third order)
    //ode.euler(0.0, Eigen::Vector3d(10.0, 0.0, 0.0), 0.01, 10000);

    ODE_1st ode(sample_derivative);
    ode.runge_kutta_4th(0.0, 0.0, 0.01, 1000);

    ode.export_output();




    /*
    // ===== Heat Equation Test =====
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
    
    cout << "\n";
    heat_eq.export_to_CSV("CSVs/heat2D_equation_solution.csv");  
    return 0;
    */
}