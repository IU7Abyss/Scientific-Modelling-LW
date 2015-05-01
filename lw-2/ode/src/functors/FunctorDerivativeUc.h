//
//  FunctorDerivativeUc.h
//  lw-2
//
//  Created by James Took on 21/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#ifndef __lw_2__FunctorDerivativeUc__
#define __lw_2__FunctorDerivativeUc__

class FunctorDerivativeUc {
private:
    double m_Ck;
public:
    FunctorDerivativeUc (double Ck)
    : m_Ck(Ck)
    { }
public:
    double operator () (double I);
    double operator () (double I, double Uc);
};

#endif /* defined(__lw_2__FunctorDerivativeUc__) */
