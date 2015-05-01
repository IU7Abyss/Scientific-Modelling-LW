//
//  datawriter.h
//  lw-2
//
//  Created by James Took on 30/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#ifndef __lw_2__datawriter__
#define __lw_2__datawriter__

#include <map>
#include <string>
#include <vector>

extern
void
makeCSV (const std::string &filename, const std::string &header, const std::map< double, std::vector<double> > &data);

#endif /* defined(__lw_2__datawriter__) */
