#include <iostream>
#include <functional>
#include <vector>
#include <cmath>
#include <fstream>
#include "Solver.h"

using namespace std;

// 1D Heat Equation Implementation

heat_eqn_1D::heat_eqn_1D(double a) {
    alpha = a;
}

void heat_eqn_1D::solve(vector<double> mesh0, double dx, double dt, int iterations) {
    mesh_0 = mesh0;
    delta_x = dx;
    delta_t = dt;
    solve_recurse(mesh0, dx, dt, iterations);
}

void heat_eqn_1D::solve_recurse(vector<double> current_mesh, double dx, double dt, int iterations){
    if (iterations == 0) return;
    timeline.push_back(current_mesh);

    vector<double> next_mesh = current_mesh; // Copy current mesh to update values simultaneously

    double c = alpha * delta_t / (delta_x * delta_x);
    for (int i=1; i < current_mesh.size()-1; i++){
        double laplacian = current_mesh[i-1] - 2*current_mesh[i] + current_mesh[i+1];
        next_mesh[i] = current_mesh[i] + c * laplacian;
    }

    solve_recurse(next_mesh, dx, dt, iterations - 1);
}

void heat_eqn_1D::export_to_CSV(string filename) {
    ofstream file;
    file.open(filename);

    for (int i=0; i < mesh_0.size(); i++) {
        file << "x_" << i;
        if (i < mesh_0.size() - 1) file << ",";
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

// 2D Heat Equation Implementation

heat_eqn_2D::heat_eqn_2D(double a) {
    alpha = a;
}

void heat_eqn_2D::solve(vector<vector<double>> mesh0, double dx, double dt, int iterations) {
    mesh_0 = mesh0;
    delta_x = dx;
    delta_t = dt;
    solve_recurse(mesh0, dx, dt, iterations);
}

void heat_eqn_2D::solve_recurse(vector<vector<double>> current_mesh, double dx, double dt, int iterations){
    if (iterations == 0) return;
    timeline.push_back(current_mesh);

    vector<vector<double>> next_mesh = current_mesh; // Copy current mesh to update values simultaneously

    double c = alpha * delta_t / (delta_x * delta_x);
    for (int i=1; i < current_mesh.size()-1; i++){
        for (int j=1; j < current_mesh[i].size()-1; j++){    
            double laplacian = current_mesh[i-1][j] + current_mesh[i+1][j] + current_mesh[i][j-1] + current_mesh[i][j+1] - 4*current_mesh[i][j];
            next_mesh[i][j] = current_mesh[i][j] + c * laplacian;
        }
    }

    solve_recurse(next_mesh, dx, dt, iterations - 1);
}

void heat_eqn_2D::export_to_CSV(string filename) {
        ofstream file;
    file.open(filename);
/*
    for (int i=0; i < mesh_0.size(); i++) {
        file << "x_" << i;
        if (i < mesh_0.size() - 1) file << ",";
    }
    file << "\n";*/

    for (int t=0; t < timeline.size(); t++) {
        for (int i=0; i < timeline[t].size(); i++) {
            for (int j=0; j < timeline[t][i].size(); j++) {
                file << timeline[t][i][j];
                if (!((j == timeline[t][i].size() - 1) && (i == timeline[t].size() - 1))) file << ",";
            }
        }
        file << "\n";
    }
    file.close();
}