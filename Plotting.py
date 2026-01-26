import matplotlib.pyplot as plt
import matplotlib.animation as animation
import pandas as pd

# ============ ODE VISUALIZATION ============
'''
data = pd.read_csv('ode_solution.csv')
plt.plot(data['x'], data['y'], label='ODE Solution')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Solution of ODE using Runge-Kutta 4th Order Method')
plt.show()
'''

# ============ 2D HEAT EQUATION VISUALIZATION ============

data = pd.read_csv('heat2D_equation_solution.csv', header=None)
fig, ax = plt.subplots()

map = []

xrange = 50
yrange = 50

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
plt.xlabel('Position along the rod')
plt.ylabel('Temperature')
plt.title('2D Heat Equation Simulation')
plt.show()