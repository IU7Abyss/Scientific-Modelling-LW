//
//  approx.cpp
//  lw-2
//
//  Created by James Took on 19/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#include "approx.h"

#include <limits>
#include <cmath>



using std::abs;
using std::exp;
using std::log;



double
lerp (double x,
      double x_0, double y_0,
      double x_1, double y_1)
{
    return y_0 + (y_1 - y_0) * ((x - x_0) / (x_1 - x_0));
}

double
log_lerp (double x,
          double x_0, double y_0,
          double x_1, double y_1)
{
    return std::exp(lerp(x, x_0, log(y_0), x_1, log(y_1)));
}

bool
is_approx (double value1, double value2)
{
    return abs(value1 - value2) < std::numeric_limits<double>::epsilon();
}