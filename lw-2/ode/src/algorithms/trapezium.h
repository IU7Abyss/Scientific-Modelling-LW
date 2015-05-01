//
//  trapezium.h
//  lw-2
//
//  Created by James Took on 22/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#ifndef __lw_2__trapezium__
#define __lw_2__trapezium__

#include "functors/FunctorRp.h"



namespace trapezium {
    
extern
double calc_I (double I_prev,
               double Uc_prev,
               double Rp_prev,
               const FunctorRp &Rp_f,
               double t,
               double Rk,
               double Lk,
               double Ck,
               double eps);

extern
double calc_Uc (double Uc_prev,
                double I_prev,
                double I,
                double Ck,
                double t);
    
}

#endif /* defined(__lw_2__trapezium__) */
