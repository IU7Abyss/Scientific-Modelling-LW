set datafile separator comma
# set autoscale fix

set term png size 1400,400
set output filename
set multiplot layout 1,3 title "Model" font ",14"
set border 3
set logscale x
unset mxtics
set format x "10^{%T}"
set rmargin 3

set key below

# layout 1
set title "I(t)"
set key off
plot runge4_data using "t":"I" \
                 title "Runge 4" \
                 with lines lw 2, \
     trapezium_data using "t":"I" \
                    title "Trapezium" \
                    with lines lw 2

# layout 2
set title "Uc(t)"
set key on
plot runge4_data using "t":"Uc" \
                 title "Runge 4" \
                 with lines lw 2, \
     trapezium_data using "t":"Uc" \
                    title "Trapezium" \
                    with lines lw 2
# layout 3
set title "Rp(t)"
set key off
plot runge4_data using "t":"Rp" \
                 title "Runge 4" \
                 with lines lw 2, \
     trapezium_data using "t":"Rp" \
                    title "Trapezium" \
                    with lines lw 2

unset multiplot