#ifndef SOLVER_H
#define SOLVER_H

#include "../Eigen/Eigen/Dense"
#include <functional>
#include <vector>
#include <string>

using namespace std;

class nth_ODE{
    protected:
        vector<double> coeffs; // Vector representing the ODE coefficients a_n*y^(n) + a_(n-1)*y^(n-1) + ... + a_0*y = 0
        Eigen::MatrixXd state_matrix;

        // Solution details
        bool solved = 0;
        double x_0;
        Eigen::VectorXd initial_state;
        double delta_x;
        vector<double> domain;
        vector<double> curve;

        void euler_recurse(double x, Eigen::VectorXd state_vector, double dx, int iterations);
        //void RK4_recurse(double x, double y, double dx, int iterations);
    public:
        nth_ODE();
        nth_ODE(vector<double> coefficients);
        void euler(double x0, Eigen::VectorXd initial_state_vector, double dx, int iterations);
        //void runge_kutta_4th(double x0, double y0, double dx, int iterations);
        double y_at(double x);
        void export_to_CSV(string filename);
        void export_output();
};

class ODE_1st : public nth_ODE{
    private:
        function<double(double, double)> y_dash; // Function representing the ODE dy/dx = f(x, y)

        double y_0;

        void euler_recurse(double x, double y, double dx, int iterations);
        void RK4_recurse(double x, double y, double dx, int iterations);
    public:
        ODE_1st(function<double(double, double)> derivative);
        ODE_1st(vector<double> coefficients);
        void euler(double x0, double y0, double dx, int iterations);
        void runge_kutta_4th(double x0, double y0, double dx, int iterations);
};

class heat_eqn_1D{
    private:
        double alpha; // Thermal diffusivity
        double delta_x;
        double delta_t;
        vector<double> mesh_0;
        //vector<double> kernel = {1.0/3, 1.0/3, 1.0/3}; // Simple average kernel
        vector<vector<double>> timeline;

        void solve_recurse(vector<double> current_mesh, double dx, double dt, int iterations);
    public:
        heat_eqn_1D(double a);
        void solve(vector<double> mesh0, double dx, double dt, int iterations);
        void export_output();
        void export_to_CSV(string filename);
};


class heat_eqn_2D{
    private:
        double alpha;
        double delta_x;
        double delta_t;
        /*vector<vector<double>> kernel = {
            {0,     1.0/5,     0},
            {1.0/5, 1.0/5, 1.0/5},
            {0,     1.0/5,     0}
        };*/
        vector<vector<double>> mesh_0;
        vector<vector<vector<double>>> timeline;

        void solve_recurse(vector<vector<double>> current_mesh, double dx, double dt, int iterations);
    public:
        heat_eqn_2D(double a);
        void solve(vector<vector<double>> mesh0, double dx, double dt, int iterations);
        void export_output();
        void export_to_CSV(string filename);

};

#endif