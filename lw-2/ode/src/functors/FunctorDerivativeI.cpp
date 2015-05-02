//
//  FunctorDerivativeI.cpp
//  lw-2
//
//  Created by James Took on 21/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#include "FunctorDerivativeI.h"

#include "FunctorRp.h"

#include <cmath>


double
FunctorDerivativeI::operator () (double I, double Uc) const
{
    if (I < 0.0 || Uc < 0.0 || std::isnan(I) || std::isnan(Uc))
        return std::nan(NULL);
    
    double Rp = (*m_Rp)(I);
    
    return std::isnan(Rp) ? std::nan(NULL) : (Uc - (m_Rk + Rp)*I) / m_Lk;
}