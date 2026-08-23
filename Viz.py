import matplotlib.pyplot as plt
import matplotlib.animation as animation
import pandas as pd
import subprocess
import io
from pathlib import Path

project_dir = Path(__file__).resolve().parent

# ============ ODE VISUALIZATION ============

subprocess.run(['g++', 'Solver/ODE.cpp', 'Solver/Heat.cpp', 'main.cpp', '-o', 'Build/main.exe'], cwd=project_dir, check=True, capture_output=True, text=True)
cpp_process = subprocess.run([str(project_dir / 'Build/main.exe')], cwd=project_dir, capture_output=True, text=True)

plot_type = cpp_process.stdout.split('\n')[0]
# =========== ODE PLOTTING ============
if plot_type == 'ODE':
    data = pd.read_csv(io.StringIO("\n".join(cpp_process.stdout.split('\n')[1:])), header=None, names=['x', 'y'])
    plt.plot(data['x'], data['y'])
    plt.xlabel('x')
    plt.ylabel('y')
    plt.title('Solution')
    plt.show()

# ============ 1D HEAT EQUATION VISUALIZATION ============
elif plot_type.split(' ')[0] == "Heat1D":
    data = pd.read_csv(io.StringIO("\n".join(cpp_process.stdout.split('\n')[1:])), header=None)
    fig, ax = plt.subplots()

    map = []

    xrange = int(plot_type.split(' ')[1])

    heat = data.iloc[0].values
    heat_plot = ax.plot(range(xrange), heat)

    def next_t(t):
        heat = data.iloc[t].values
        heat_plot[0].set_ydata(heat)
        return heat_plot

    ani = animation.FuncAnimation(fig, next_t, frames=len(data)//1, interval=100, blit=True)
    plt.title('1D Heat Equation Simulation')
    plt.show()

# ============ 2D HEAT EQUATION VISUALIZATION ============
elif plot_type.split(' ')[0] == "Heat2D":
    data = pd.read_csv(io.StringIO("\n".join(cpp_process.stdout.split('\n')[1:])), header=None)
    fig, ax = plt.subplots()

    map = []

    xrange = int(plot_type.split(' ')[1].split('x')[1])
    yrange = int(plot_type.split(' ')[1].split('x')[0])

    for i in range(yrange):
        row = data.iloc[0, xrange * i:xrange * (i+1)].values
        map.append(row)

    contour = ax.imshow(map, cmap='hot', interpolation='nearest')

    def next_t(t):
        map = []
        for i in range(yrange):
            row = data.iloc[t, xrange * i:xrange * (i+1)].values
            map.append(row)
        contour.set_data(map)
        return contour,

    ani = animation.FuncAnimation(fig, next_t, frames=len(data)//1, interval=100, blit=True)
    plt.title('2D Heat Equation Simulation')
    plt.show()