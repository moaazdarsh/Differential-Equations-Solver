# Differential Equations Solver
After studying differential equations, C++, and system dynamics, I was able to immediately apply this knowledge by making a numerical DEs solver.
It is currently capable of solving first order ODEs, nth order LTI ODEs, and the heat equation in 1 or 2 dimensions. I hope you can try it and tell your opinions.

# Dependencies
You will need to have multiple things installed to run this code.
- The C++ compiler g++
- python
- matplotlib for visualization
- pandas

# How to Use
## First Order
First, write the derivative equation as a callable function and feed as a parameter in a `ODE_1st` object.  
In this example I'm using y` = y.

`double sample_derivative(double x, double y) {return y;}`  
then,  
`ODE_1st ode(sample_derivative);`

Run the solver function `euler` or `runge_kutta_4th`, it takes $x_0$, $y_0$, $\Delta x$, and number of iterations as input parameters.  
`ode.runge_kutta_4th(0.0, 1.0, 0.1, 100);`  
Notice that in this case the output of the function will be calculated in the interval [0, 10] since it's doing 100 iterations of 0.1 increments.

To get the output write  
`ode.export_output();`  
This is necessary if you want visualization or terminal output.

If you want a CSV file with the output instead run  
`ode.export_to_CSV("CSVs/solution.csv");`

## nth Order
Write the coefficients of the differential equation to be solved as the parameters of a `nth_order` object.

`nth_ODE ode({1, 1, 25}); // y'' + y' + 25y = 0`

Run the euler function to solve the ODE, it takes $x_0$, initial state vector, $\Delta x$, and number of iterations as input parameters.  
In this case, the state vector is a vector with y and y\`. In general it's the initial value of y and the next n-1 derivatives or in other words it's the initial value of the first n derivatives starting from 0.  
`ode.euler(0.0, Eigen::Vector2d(1.0, 0.0), 0.1, 10000);`  

And you can run the same functions as before for output.