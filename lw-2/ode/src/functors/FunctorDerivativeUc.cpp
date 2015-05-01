//
//  FunctorDerivativeUc.cpp
//  lw-2
//
//  Created by James Took on 21/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#include "FunctorDerivativeUc.h"

double
FunctorDerivativeUc::operator () (double I)
{
    return - I / m_Ck;
}

double
FunctorDerivativeUc::operator () (double I, double Uc)
{
    return (*this)(I);
}