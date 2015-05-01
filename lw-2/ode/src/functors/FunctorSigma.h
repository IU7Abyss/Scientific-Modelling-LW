//
//  FunctorSigma.h
//  lw-2
//
//  Created by James Took on 18/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#ifndef __lw_2__FunctorSigma__
#define __lw_2__FunctorSigma__

#include <map>
#include <vector>



class FunctorSigma {
private:
    // key = T, value = Sigma
    const std::map<double, double> *m_table;
public:
    FunctorSigma (const std::map<double, double> *aTable)
    : m_table(aTable)
    { }
public:
    double operator () (double T) const;
};

#endif /* defined(__lw_2__FunctorSigma__) */
