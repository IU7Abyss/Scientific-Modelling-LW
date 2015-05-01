//
//  FunctorDerivativeI.h
//  lw-2
//
//  Created by James Took on 21/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#ifndef __lw_2__FunctorDerivativeI__
#define __lw_2__FunctorDerivativeI__

class FunctorRp;

class FunctorDerivativeI {
private:
    double m_Rk;
    double m_Lk;
    const FunctorRp *m_Rp;
public:
    FunctorDerivativeI (double Rk, double Lk, const FunctorRp *Rp)
    : m_Rk(Rk), m_Lk(Lk), m_Rp(Rp)
    { }
public:
    double operator () (double I, double Uc) const;
};

#endif /* defined(__lw_2__FunctorDerivativeI__) */
