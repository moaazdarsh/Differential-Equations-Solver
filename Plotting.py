import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv('ode_solution.csv')
plt.plot(data['x'], data['y'], label='ODE Solution')
plt.xlabel('x')
plt.ylabel('y')
plt.title('Solution of ODE using Runge-Kutta 4th Order Method')
plt.show()