#ifndef SOLVER_H
#define SOLVER_H

#include <functional>
#include <vector>
#include <string>

using namespace std;

class ODE_1st{
    private:
        function<double(double, double)> y_dash; // Function representing the ODE dy/dx = f(x, y)
        
        // Solution details
        bool solved = 0;
        double x_0;
        double y_0;
        double delta_x;
        vector<double> domain;
        vector<double> curve;

        void euler_recurse(double x, double y, double delta, int iterations);
        void RK4_recurse(double x, double y, double delta, int iterations);
    public:
        ODE_1st(function<double(double, double)> derivative);
        void euler(double x0, double y0, double delta, int iterations);
        void runge_kutta_4th(double x0, double y0, double delta, int iterations);
        double y_at(double x);
        void export_to_CSV(string filename);
};

#endif