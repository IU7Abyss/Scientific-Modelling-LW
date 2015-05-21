# ODE
### Methods
- explicit Runge–Kutta 4 for ODE;
- implicit Trapezoidal rule.

### How it's works

To computation only the model by two methods

```
$ ./ode initial_values I_T0_n T_Sigma runge trapezoidal
```

This command make files `runge` and `trapezoidal` with result data. Be care, all data is stored in `CSV`

Or just use `script/run.sh`. This script uses `gnuplot` to generate graphs

```
$ ./run.sh initial_values I_T0_n T_Sigma
```

### For lazy bitches
Ok, don't worry. You can use a predefined examples. Just go in folder `Build/Products/Release/examples` and
```
$ ./example-1.sh
```
or you may
```
$ ./run_all.sh
```
then look `models` folder.