//
//  FunctorDerivativeUc.cpp
//  lw-2
//
//  Created by James Took on 21/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#include "FunctorDerivativeUc.h"

#include <cmath>

double
FunctorDerivativeUc::operator () (double I)
{
    return I < 0.0 ? std::nan(NULL) : - I / m_Ck;
}

double
FunctorDerivativeUc::operator () (double I, double Uc)
{
    return (I < 0.0 || std::isnan(I) || Uc < 0.0 || std::isnan(Uc)) ? std::nan(NULL) : (*this)(I);
}