#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include <fstream>
//#include <Solver.h>

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

        void euler_recurse(double x, double y, double delta, int iterations){
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
        void RK4_recurse(double x, double y, double delta, int iterations){
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
    public:
        vector<double> curve;

        ODE_1st(function<double(double, double)> derivative){
            y_dash = derivative;
        }
        void euler(double x0, double y0, double delta, int iterations){ // iterations is the number of steps
            if (iterations == 0) return;
            x_0 = x0;
            y_0 = y0;
            delta_x = delta;
            curve.clear();
            domain.clear();

            euler_recurse(x0, y0, delta, iterations);
        }
        void runge_kutta_4th(double x0, double y0, double delta, int iterations){
            if (iterations == 0) return;
            x_0 = x0;
            y_0 = y0;
            delta_x = delta;
            curve.clear();
            domain.clear();

            RK4_recurse(x0, y0, delta, iterations);
        }
        double y_at(double x){
            if (!solved) return NAN;

            double steps = (x - x_0) / delta_x;
            if (steps - floor(steps) == 0) return curve[(int)steps];

            double y1 = curve[(int)floor(steps)];
            double y2 = curve[(int)ceil(steps)];
            return y1 + (y2 - y1) * (steps - floor(steps)); // Linear interpolation
        }
        void export_to_CSV(string filename){
            ofstream file;
            file.open(filename);
            file << "x,y\n";
            for (size_t i = 0; i < curve.size(); i++){
                file << domain[i] << "," << curve[i] << "\n";
            }
            file.close();
        }
};

double sample_derivative(double x, double y) {
    return y; // Example: dy/dx = 2
}
int main() {
    ODE_1st ode(sample_derivative);
    ode.runge_kutta_4th(0.0, 1.0, 0.01, 300); // Initial conditions: x0=0, y0=0, delta=0.1, iterations=1000
/*
    for (int i = 0; i <= 1000; i++) {
        cout << ode.y_at(i * 0.1) << " ";
    }
*/
    cout << "\nCurve: ";
    for (double val : ode.curve) {
        cout << val << " ";
    }
    cout << endl;
    ode.export_to_CSV("ode_solution.csv");
    
    return 0;
}