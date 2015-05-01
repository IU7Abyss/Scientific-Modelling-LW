//
//  FunctorRp.cpp
//  lw-2
//
//  Created by James Took on 22/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#include "FunctorRp.h"

#include "FunctorT.h"
#include "FunctorG.h"
#include "FunctorIntegral.h"

#include <cmath>

double
FunctorRp::operator () (double I) const
{
    FunctorT ft(m_Tw, I, *m_map_I_T0_n);
    FunctorG fg(&ft, &m_fsigma);
    FunctorIntegral integral(&fg, 0.0, 1.0);
    
    double fi = integral();
    
    return fi > 0.0 ? m_l_e / (2.0 * M_PI * m_r * m_r * fi) : 0.0;
}