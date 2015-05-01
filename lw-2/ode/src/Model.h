//
//  Model.h
//  lw-2
//
//  Created by James Took on 21/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#ifndef __lw_2__Model__
#define __lw_2__Model__

#include <map>
#include <vector>

using Model = std::map< double, std::vector<double> >;

extern
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
             const std::map<double, double> &map_T_Sigma);

extern
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
                 const std::map<double, double> &map_T_Sigma);


#endif /* defined(__lw_2__Model__) */
