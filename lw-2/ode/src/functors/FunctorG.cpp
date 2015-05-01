//
//  FunctorG.cpp
//  lw-2
//
//  Created by James Took on 18/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#include "FunctorG.h"

#include "FunctorT.h"
#include "FunctorSigma.h"



double FunctorG::operator () (double z) const
{
    return (*m_Sigma)((*m_T)(z)) * z;
}