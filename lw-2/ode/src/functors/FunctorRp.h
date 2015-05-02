//
//  FunctorRp.h
//  lw-2
//
//  Created by James Took on 22/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#ifndef __lw_2__FunctorRp__
#define __lw_2__FunctorRp__

#include "FunctorSigma.h"



class FunctorRp {
private:
    double m_l_e;
    double m_r;
    double m_Tw;
    const std::map< double, std::vector<double> > *m_map_I_T0_n;
    const FunctorSigma m_fsigma;
public:
    FunctorRp (double l_e, double r, double Tw, const std::map< double, std::vector<double> > *map_I_T0_n, const std::map<double, double> *map_T_sigma)
    : m_l_e(l_e), m_r(r), m_Tw(Tw), m_map_I_T0_n(map_I_T0_n), m_fsigma(map_T_sigma)
    {  }
public:
    double operator () (double I) const;
};

#endif /* defined(__lw_2__FunctorRp__) */
