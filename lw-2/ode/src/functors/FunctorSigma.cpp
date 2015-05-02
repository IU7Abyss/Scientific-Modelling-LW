//
//  FunctorSigma.cpp
//  lw-2
//
//  Created by James Took on 18/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#include "FunctorSigma.h"

#include "algorithms/approx.h"

#include <cmath>

double
FunctorSigma::operator () (double T) const
{
    double result;
    
    if (T < 0.0 || std::isnan(T)) {
        result = std::nan(NULL);
    } else if (T < m_table->cbegin()->first) {
              auto   it  = m_table->cbegin();
              double x_0 = it->first, y_0 = it->second;
        ++it; double x_1 = it->first, y_1 = it->second;
        
        result = log_lerp(T, x_0, y_0, x_1, y_1);
    } else if (is_approx(T, m_table->cbegin()->first)) {
        result = m_table->cbegin()->second;
    } else if (is_approx(T, (--m_table->cend())->first)) {
        result = (--m_table->cend())->second;
    } else if (T > (--m_table->cend())->first) {
              auto   it  = m_table->cend();
        --it; double x_1 = it->first, y_1 = it->second;
        --it; double x_0 = it->first, y_0 = it->second;
        
        result = log_lerp(T, x_0, y_0, x_1, y_1);
    } else {
        auto it = m_table->lower_bound(T);
        
        if (is_approx(T, it->first)) {
            result = it->second;
        } else {
                  double x_1 = it->first, y_1 = it->second;
            --it; double x_0 = it->first, y_0 = it->second;
            
            result = log_lerp(T, x_0, y_0, x_1, y_1);
        }
    }

    return result;
}