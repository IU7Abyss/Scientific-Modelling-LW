//
//  FunctorG.h
//  lw-2
//
//  Created by James Took on 18/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#ifndef __lw_2__FunctorG__
#define __lw_2__FunctorG__

#include <map>
#include <vector>



class FunctorT;
class FunctorSigma;



class FunctorG {
private:
    const FunctorT     *m_T;
    const FunctorSigma *m_Sigma;
public:
    FunctorG (const FunctorT *T,
              const FunctorSigma *Sigma)
    : m_T(T), m_Sigma(Sigma)
    { }
public:
    double operator () (double z) const;
};

#endif /* defined(__lw_2__FunctorG__) */
