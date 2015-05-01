//
//  datawriter.cpp
//  lw-2
//
//  Created by James Took on 30/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#include "datawriter.h"

#include <fstream>

std::ostream& operator << (std::ofstream &os, const std::map< double, std::vector<double> > &rhs)
{
    for (auto const &it_m : rhs) {
        os << '\n' << it_m.first;
        
        for (auto const &it_v : it_m.second) {
            os << ',' << it_v;
        }
    }
    
    os.flush();
    
    return os;
}

void makeCSV (const std::string &filename, const std::string &header, const std::map< double, std::vector<double> > &data)
{
    std::ofstream file(filename);
    
    file << header;
    file << data;
}