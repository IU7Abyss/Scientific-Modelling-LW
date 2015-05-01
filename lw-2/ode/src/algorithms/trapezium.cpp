//
//  trapezium.cpp
//  lw-2
//
//  Created by James Took on 22/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#include "trapezium.h"

#include <cmath>

namespace trapezium {


double calc_I (double I_prev,
               double Uc_prev,
               double Rp_prev,
               const FunctorRp &Rp_f,
               double t,
               double Rk,
               double Lk,
               double Ck,
               double eps)
{
    using std::abs;

    double k1 = t / Lk;
    double k2 = 0.5 * k1;
    double k3 = 0.25 * k1 * t / Ck;
    
    double k_num = k1 * Uc_prev + I_prev * (1.0 - k3 - k2 * (Rk + Rp_prev));
    double k_den = 1.0 + k3 + k2 * Rk;
    
    double it_I = k_num / (k_den + k2 * Rp_prev);
    double it_I_prev;
    
    do {
        it_I_prev = it_I;
        it_I = k_num / (k_den + k2 * Rp_f(it_I_prev));
    } while (abs(1.0 - it_I_prev / it_I) >= eps);
    
    
    return it_I;
}
    
double calc_Uc (double Uc_prev,
                double I_prev,
                double I,
                double Ck,
                double t)
{
    return Uc_prev - t/(2.0 * Ck) * (I_prev + I);
}

    


}