#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <fstream>
#include "Solver.h"

using namespace std;


void ODE_1st::euler_recurse(double x, double y, double delta, int iterations){
    if (iterations == 0) return;

    if (delta > 0){
    curve.push_back(y);
    domain.push_back(x);
    }
    else if (delta < 0){
    curve.insert(curve.begin(), y);
    domain.insert(domain.begin(), x);
    }

    euler_recurse(x + delta, y + delta * y_dash(x, y), delta, iterations - 1); // Forward step
    solved = 1;
}

void ODE_1st::RK4_recurse(double x, double y, double delta, int iterations){
    if (iterations == 0) return;
    
    if (delta > 0){
    curve.push_back(y);
    domain.push_back(x);
    }
    else if (delta < 0){
    curve.insert(curve.begin(), y);
    domain.insert(domain.begin(), x);
    }

    double k1,k2,k3,k4;
    k1 = delta * y_dash(x,y);
    k2 = delta * y_dash(x + delta/2, y + k1/2);
    k3 = delta * y_dash(x + delta/2, y + k2/2);
    k4 = delta * y_dash(x + delta, y + k3);

    RK4_recurse(x + delta, y + (k1 + 2*k2 + 2*k3 + k4)/6, delta, iterations - 1); // Forward step
    solved = 1;
}

ODE_1st::ODE_1st(function<double(double, double)> derivative){
    y_dash = derivative;
}
void ODE_1st::euler(double x0, double y0, double delta, int iterations){ // iterations is the number of steps
    if (iterations == 0) return;
    x_0 = x0;
    y_0 = y0;
    delta_x = delta;
    curve.clear();
    domain.clear();

    euler_recurse(x0, y0, delta, iterations);
}
void ODE_1st::runge_kutta_4th(double x0, double y0, double delta, int iterations){
    if (iterations == 0) return;
    x_0 = x0;
    y_0 = y0;
    delta_x = delta;
    curve.clear();
    domain.clear();

    RK4_recurse(x0, y0, delta, iterations);
}
double ODE_1st::y_at(double x){
    if (!solved) return NAN;

    double steps = (x - x_0) / delta_x;
    if (steps - floor(steps) == 0) return curve[(int)steps];

    double y1 = curve[(int)floor(steps)];
    double y2 = curve[(int)ceil(steps)];
    return y1 + (y2 - y1) * (steps - floor(steps)); // Linear interpolation
}
void ODE_1st::export_to_CSV(string filename){
    ofstream file;
    file.open(filename);
    file << "x,y\n";
    for (size_t i = 0; i < curve.size(); i++){
        file << domain[i] << "," << curve[i] << "\n";
    }
    file.close();
}