//
//  datareader.cpp
//  lw-2
//
//  Created by James Took on 27/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#include "datareader.h"

using std::vector;
using std::map;
using std::move;

using std::string;
using std::getline;
using std::stod;

#include <fstream>

using std::ifstream;

#include <sstream>

using std::istringstream;

// sad. need use iterator and template.


std::map<std::string, double>
read_inputdata (const std::string &filename)
{
    ifstream file(filename);
    
    map<string, double> result;
    
    string row_str;
    string key_str;
    string value_str;
    while (getline(file, row_str)) {
        istringstream row_stream(row_str);
        
        getline(row_stream, key_str, ',');
        
        getline(row_stream, value_str);
        double value = stod(value_str);
        result.insert({ move(key_str), value });
    }
    
    file.close();
    
    return move(result);
}

std::map< double, std::vector<double> >
read_I_T0_n (const std::string &filename)
{
    ifstream file(filename);
    
    map< double, vector<double> > result;
    
    string row_str;
    string value_str;
    while (getline(file, row_str)) {
        istringstream row_stream(row_str);
        
        getline(row_stream, value_str, ',');
        double I = stod(value_str);
        
        vector<double> row;
        row.reserve(3);
        while (getline(row_stream, value_str, ',')) {
            double val = stod(value_str);
            row.push_back(val);
        }
        
        result.insert(result.cend(), { I, move(row) });
    }
    
    file.close();
    
    return move(result);
}


std::map< double, double >
read_T_Sigma (const std::string &filename)
{
    ifstream file(filename);
    
    map<double, double> result;
    
    string row_str;
    string value_str;
    while (getline(file, row_str)) {
        istringstream row_stream(row_str);
        
        getline(row_stream, value_str, ',');
        double T = stod(value_str);
        
        getline(row_stream, value_str, ',');
        double Sigma = stod(value_str);
        
        result.insert(result.cend(), { T, Sigma });
    }
    
    file.close();
    
    return move(result);
}