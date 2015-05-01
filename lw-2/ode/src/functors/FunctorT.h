//
//  FunctorT.h
//  lw-2
//
//  Created by James Took on 18/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#ifndef __lw_2__FunctorT__
#define __lw_2__FunctorT__

#include <map>
#include <vector>



class FunctorT {
private:
    double m_T_w, m_T_0, m_n;
public:
    FunctorT (double T_w, double I, const std::map< double, std::vector<double> > &aTable);
public:
    double operator () (double z) const;
};

#endif /* defined(__lw_2__FunctorT__) */
