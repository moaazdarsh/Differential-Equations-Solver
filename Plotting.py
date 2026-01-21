import matplotlib.pyplot as plt
import matplotlib.animation as animation
import pandas as pd
'''
data = pd.read_csv('ode_solution.csv')
plt.plot(data['x'], data['y'], label='ODE Solution')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Solution of ODE using Runge-Kutta 4th Order Method')
plt.show()
'''
data = pd.read_csv('heat_equation_solution.csv')
fig, ax = plt.subplots()

x = range(len(data.columns))
line, = ax.plot(x, data.iloc[0, :], color='r')

def next_t(t):
    line.set_ydata(data.iloc[10*t, :])
    return line,

ani = animation.FuncAnimation(fig, next_t, frames=len(data)//10, interval=100, blit=True)
plt.xlabel('Position along the rod')
plt.ylabel('Temperature')
plt.title('1D Heat Equation Simulation')
plt.show()