//
//  Model.cpp
//  lw-2
//
//  Created by James Took on 21/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#include "Model.h"

#include "functors/FunctorRp.h"
#include "functors/FunctorDerivativeI.h"
#include "functors/FunctorDerivativeUc.h"

#include "algorithms/rungekutte4.h"
#include "algorithms/trapezium.h"

#include <cmath>

Model
model_runge (double t0,
             double t_end,
             double t_delta,
             double I0,
             double Uc_0,
             double Ck,
             double Lk,
             double Rk,
             double l_e,
             double R,
             double Tw,
             double eps,
             const std::map< double, std::vector<double> > &map_I_T0_n,
             const std::map<double, double> &map_T_Sigma)
{
    using std::map;
    using std::vector;
    using std::array;
    using std::move;
    using std::round;
    
    FunctorRp Rp_f (l_e, R, Tw, eps, &map_I_T0_n, &map_T_Sigma);
    FunctorDerivativeI I_derivative(Rk, Lk, &Rp_f);
    FunctorDerivativeUc Uc_derivative(Ck);
    
    double Rp_0 = Rp_f(I0);
    
    map< double, vector<double> > result = {
        { t0, { I0, Uc_0, Rp_0 } }
    };
    
    int n = round((t_end - t0) / t_delta);
    for (int i = 1; i <= n; ++i) {
        auto   it_prev = --result.cend();
        double I_prev  = (it_prev->second)[0];
        double Uc_prev = (it_prev->second)[1];
        
        array<double, 2> I_Uc = runge4_ode(I_derivative, Uc_derivative, I_prev, Uc_prev, t_delta);
        if (I_Uc[0] < 0.0 || I_Uc[1] < 0.0) break;
        vector<double> row;
        row.reserve(4);
        row.push_back(I_Uc[0]);
        row.push_back(I_Uc[1]);
        
        double Rp = Rp_f(I_Uc[0]);
        if (Rp < 0.0) break;
        row.push_back(Rp);
        
        double t = t0 + t_delta*i;
        
        result.insert(result.cend(), { t, move(row) });
    }
    
    return move(result);
}

Model
model_trapezium (double t0,
                 double t_end,
                 double t_delta,
                 double I0,
                 double Uc_0,
                 double Ck,
                 double Lk,
                 double Rk,
                 double l_e,
                 double R,
                 double Tw,
                 double eps,
                 const std::map< double, std::vector<double> > &map_I_T0_n,
                 const std::map<double, double> &map_T_Sigma)
{
    using std::map;
    using std::vector;
    using std::move;
    using trapezium::calc_I;
    using trapezium::calc_Uc;
    
    FunctorRp Rp_f (l_e, R, Tw, eps, &map_I_T0_n, &map_T_Sigma);
    
    double Rp_0 = Rp_f(I0);
    
    map< double, vector<double> > result = {
        { t0, { I0, Uc_0, Rp_0 } }
    };
    
    int n = round((t_end - t0) / t_delta);
    for (int i = 1; i <= n; ++i) {
        auto   it_prev = --result.cend();
        double I_prev  = (it_prev->second)[0];
        double Uc_prev = (it_prev->second)[1];
        double Rp_prev = (it_prev->second)[2];
        
        double I = calc_I(I_prev, Uc_prev, Rp_prev, Rp_f, t_delta, Rk, Lk, Ck, eps);
        if (I < 0.0) break;
        vector<double> row;
        row.reserve(4);
        row.push_back(I);
        
        double Uc = calc_Uc(Uc_prev, I_prev, I, Ck, t_delta);
        if (Uc < 0.0) break;
        row.push_back(Uc);
        
        double Rp = Rp_f(I);
        if (Rp < 0.0) break;
        row.push_back(Rp);
        
        double t = t0 + t_delta*i;
        
        result.insert(result.cend(), { t, move(row) });
    }
    
    return move(result);
}
