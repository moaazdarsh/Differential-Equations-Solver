#include <iostream>
#include <functional>
#include <vector>
#include <cmath>
#include <fstream>
#include "Solver.h"

using namespace std;

heat_eqn_1D::heat_eqn_1D(double a, vector<double> initial_temp) {
    alpha = a;
    mesh = initial_temp;
}

void heat_eqn_1D::solve(double dx, double dt, int iterations) {
    delta_x = dx;
    delta_t = dt;
    solve_recurse(dx, dt, iterations);
}

void heat_eqn_1D::solve_recurse(double dx, double dt, int iterations){
    if (iterations == 0) return;
    timeline.push_back(mesh);

    vector<double> new_mesh = mesh; // Copy current mesh to update values simultaneously

    double c = alpha * delta_t / (delta_x * delta_x);
    for (int i=1; i < mesh.size()-1; i++){
        double laplacian = mesh[i-1] - 2*mesh[i] + mesh[i+1];
        new_mesh[i] = mesh[i] + c * laplacian;
    }

    mesh = new_mesh;
    solve_recurse(dx, dt, iterations - 1);
}

vector<double> heat_eqn_1D::get_mesh() {
    return mesh;
}

void heat_eqn_1D::export_to_CSV(string filename) {
    ofstream file;
    file.open(filename);

    for (int i=0; i < mesh.size(); i++) {
        file << "x_" << i;
        if (i < mesh.size() - 1) file << ",";
    }
    file << "\n";

    for (int i=0; i < timeline.size(); i++) {
        for (int j=0; j < timeline[i].size(); j++) {
            file << timeline[i][j];
            if (j < timeline[i].size() - 1) file << ",";
        }
        file << "\n";
    }
    file.close();
}