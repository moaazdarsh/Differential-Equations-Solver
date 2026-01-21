#include <iostream>
#include <functional>
#include <cmath>
#include <fstream>
#include "Solver.h"

double sample_derivative(double x, double y) {
    return 1/(y*y*y); // Example: dy/dx = 2
}

int main() {
    /*
    ODE_1st ode(sample_derivative);
    ode.runge_kutta_4th(0.0, 1.0, 0.01, 500); // Initial conditions: x0=0, y0=0, delta=0.1, iterations=1000

    //for (int i = 0; i <= 1000; i++) {
        cout << ode.y_at(i * 0.1) << " ";
    }

    ode.export_to_CSV("ode_solution.csv");
*/
    vector<double> initial_temp = {100, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // Initial temperature distribution
    heat_eqn_1D heat_eq(0.2, initial_temp);
    heat_eq.solve(1.0, 0.5, 10000); // dx=1.0, dt=0.1, iterations=1000
    
    auto mesh = heat_eq.get_mesh();
    for (size_t i = 0; i < mesh.size(); ++i) {
        cout << mesh[i] << " ";
    }
    cout << "\n";
    heat_eq.export_to_CSV("heat_equation_solution.csv");  
    return 0;
}