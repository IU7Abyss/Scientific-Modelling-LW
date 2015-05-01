# ODE
### Methods
- explicit Runge–Kutta 4 for ODE;
- implicit Trapezoidal rule.

### How it's works

For computation just the model by two methods

```
$ ./ode initial_values.csv I_T0_n.csv T_Sigma.csv out-Runge.csv out-Trapezoidal.csv 
```

Or just use `script/run.sh`. This script uses `gnuplot` to generate graphs

```
$ ./run.sh initial_values.csv I_T0_n.csv T_Sigma.csv
```
