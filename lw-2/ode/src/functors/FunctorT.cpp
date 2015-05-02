//
//  FunctorT.cpp
//  lw-2
//
//  Created by James Took on 18/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#include "FunctorT.h"

#include "algorithms/approx.h"

#include <cmath>



FunctorT::FunctorT (double T_w, double I, const std::map< double, std::vector<double> > &aTable)
{
    m_T_w = T_w;
    
    if (I < 0.0 || std::isnan(I) || T_w < 0.0 || std::isnan(T_w)) {
        m_T_0 = std::nan(NULL);
        m_n = std::nan(NULL);
    } else if (I < aTable.begin()->first) {
        auto   it   = aTable.begin();
       
        double x_0  = it->first;
        double y_00 = (it->second)[0], y_01 = (it->second)[1];
        
        ++it;
        
        double x_1  = it->first;
        double y_10 = (it->second)[0], y_11 = (it->second)[1];
        
        m_T_0 = lerp(I, x_0, y_00, x_1, y_10);
        m_n   = lerp(I, x_0, y_01, x_1, y_11);
    } else if (is_approx(I, aTable.begin()->first)) {
        m_T_0 = (aTable.begin()->second)[0];
        m_n   = (aTable.begin()->second)[1];
    } else if (is_approx(I, (--aTable.cend())->first)) {
        m_T_0 = ((--aTable.cend())->second)[0];
        m_n   = ((--aTable.cend())->second)[1];
    } else if (I > (--aTable.end())->first) {
        auto   it   = aTable.cend(); --it;
        
        double x_1  = it->first;
        double y_10 = (it->second)[0], y_11 = (it->second)[1];
        
        --it;
        
        double x_0  = it->first;
        double y_00 = (it->second)[0], y_01 = (it->second)[1];
        
        m_T_0 = lerp(I, x_0, y_00, x_1, y_10);
        m_n   = lerp(I, x_0, y_01, x_1, y_11);
    } else {
        auto it = aTable.lower_bound(I);
        
        if (is_approx(I, it->first)) {
            m_T_0 = (it->second)[0];
            m_n   = (it->second)[1];
        } else {
            double x_1  = it->first;
            double y_10 = (it->second)[0], y_11 = (it->second)[1];
            
            --it;
            
            double x_0  = it->first;
            double y_00 = (it->second)[0], y_01 = (it->second)[1];
            
            m_T_0 = lerp(I, x_0, y_00, x_1, y_10);
            m_n   = lerp(I, x_0, y_01, x_1, y_11);
        }
    }
}

double FunctorT::operator () (double z) const {
    return (m_T_w - m_T_0)*pow(z, m_n) + m_T_0;
}