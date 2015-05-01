//
//  FunctorIntegral.cpp
//  lw-2
//
//  Created by James Took on 19/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#include "FunctorIntegral.h"

#include "algorithms/simpson.h"

#include "FunctorG.h"

double
FunctorIntegral::operator () () const
{
    return adaptiveSimpsons(*m_f, m_a, m_b, 1e-4, 5);
}
