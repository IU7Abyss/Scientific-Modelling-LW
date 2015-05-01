//
//  FunctorIntegral.h
//  lw-2
//
//  Created by James Took on 19/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#ifndef __lw_2__FunctorIntegral__
#define __lw_2__FunctorIntegral__

class FunctorG;

class FunctorIntegral {
private:
    const FunctorG *m_f;
    double m_a, m_b;
    double m_eps;
    int m_depth;
public:
    FunctorIntegral(const FunctorG *f, double a, double b, double eps, int depth)
    : m_f(f), m_a(a), m_b(b), m_eps(eps), m_depth(depth)
    { }
    FunctorIntegral(const FunctorG *f, double a, double b)
    : FunctorIntegral(f, a, b, 1e-4, 5)
    { }
public:
    double operator () () const;
};

#endif /* defined(__lw_2__FunctorIntegral__) */
