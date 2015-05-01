//
//  approx.h
//  lw-2
//
//  Created by James Took on 19/04/15.
//  Copyright (c) 2015 James Took. All rights reserved.
//

#ifndef __lw_2__approx__
#define __lw_2__approx__

extern
double
lerp (double x,
      double x_0, double y_0,
      double x_1, double y_1);

extern
double
log_lerp (double x,
          double x_0, double y_0,
          double x_1, double y_1);

extern
bool
is_approx (double value1, double value2);


#endif /* defined(__lw_2__approx__) */
