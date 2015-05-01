//
//  rungekutte4.h
//  lw-2
//
//  Created by James Took on 21/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#ifndef __lw_2__rungekutte4__
#define __lw_2__rungekutte4__

#include <array>

template <typename FuncType>
double
rungekutte4 (FuncType f, double y0, double x, double y, double h)
{
    double halph_h = 0.5 * h;
    
    double k1 = f(x          , y);
    double k2 = f(x + halph_h, y + halph_h*k1);
    double k3 = f(x + halph_h, y + halph_h*k2);
    double k4 = f(x + h      , y + h*k3);
    
    return y0 + h/6.0 * (k1 + 2.0*k2 + 2.0*k3 + k4);
}

template <typename FuncType1, typename FuncType2>
std::array<double, 2>
runge4_ode(FuncType1 f, FuncType2 phi, double yn, double zn, double h)
{
    double k1 = f(yn, zn), q1 = phi(yn, zn);
    
    double halph_h = 0.5 * h;
    
    double theta1 = yn + halph_h*k1, gamma1 = zn + halph_h*q1;
    double k2 = f(theta1, gamma1), q2 = phi(theta1, gamma1);
    
    double theta2 = yn + halph_h*k2, gamma2 = zn + halph_h*q2;
    double k3 = f(theta2, gamma2), q3 = phi(theta2, gamma2);
    
    double theta3 = yn + h*k3, gamma3 = zn + h*q3;
    double k4 = f(theta3, gamma3), q4 = phi(theta3, gamma3);
    
    return {
        yn + h/6.0 * (k1 + 2.0*k2 + 2.0*k3 + k4),
        zn + h/6.0 * (q1 + 2.0*q2 + 2.0*q3 + q4),
    };
}



#endif /* defined(__lw_2__rungekutte4__) */