//
//  FunctorDerivativeI.cpp
//  lw-2
//
//  Created by James Took on 21/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#include "FunctorDerivativeI.h"

#include "FunctorRp.h"


double
FunctorDerivativeI::operator () (double I, double Uc) const
{
    return (Uc - (m_Rk + (*m_Rp)(I))*I) / m_Lk;
}