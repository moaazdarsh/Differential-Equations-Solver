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

        void euler_recurse(double x, double y, double dx, int iterations);
        void RK4_recurse(double x, double y, double dx, int iterations);
    public:
        ODE_1st(function<double(double, double)> derivative);
        void euler(double x0, double y0, double dx, int iterations);
        void runge_kutta_4th(double x0, double y0, double dx, int iterations);
        double y_at(double x);
        void export_to_CSV(string filename);
};

class heat_eqn_1D{
    private:
        double alpha; // Thermal diffusivity
        double delta_x;
        double delta_t;
        vector<double> mesh;
        vector<double> kernel = {1.0/3, 1.0/3, 1.0/3}; // Simple average kernel
        vector<vector<double>> timeline;

        void solve_recurse(double dx, double dt, int iterations);
    public:
        heat_eqn_1D(double a, vector<double> initial_temp);
        void solve(double dx, double dt, int iterations);
        vector<double> get_mesh();
        void export_to_CSV(string filename);
};

/*
class heat_eqn_2D{
    private:
        double alpha;
        vector<vector<double>> kernel = {
            {0,     1.0/5,     0},
            {1.0/5, 1.0/5, 1.0/5},
            {0,     1.0/5,     0}
        };
        double delta_x;
        double delta_t;
        vector<vector<double>> mesh;
    public:


};
*/
#endif