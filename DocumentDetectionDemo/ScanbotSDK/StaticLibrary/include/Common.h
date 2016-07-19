//
//  Common.h
//  ScanbotSDK
//
//  Created by Sebastian Husche on 30.06.16.
//  Copyright © 2016 doo GmbH. All rights reserved.
//

#ifndef Common_h
#define Common_h

#include <vector>
#include "opencv2/core/core.hpp"
#include "Line2D.hpp"

namespace doo {
    
    struct Contour {
        std::vector<cv::Point> points;
        std::vector<doo::Line2D> lines;
        Contour() {}
        Contour(std::vector<cv::Point> initialPoints) {
            points = initialPoints;
        }
    };
    
    typedef std::vector<Contour> ContourList;
    

}
#endif /* Common_h */
