//
//  datareader.h
//  lw-2
//
//  Created by James Took on 27/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#ifndef __lw_2__datareader__
#define __lw_2__datareader__

#include <map>
#include <vector>
#include <string>

extern
std::map<std::string, double>
read_inputdata (const std::string &filename);

extern
std::map< double, std::vector<double> >
read_I_T0_n (const std::string &filename);

extern
std::map< double, double >
read_T_Sigma (const std::string &filename);


#endif /* defined(__lw_2__datareader__) */
