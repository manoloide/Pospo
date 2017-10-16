#ifndef FilterBlur_hpp
#define FilterBlur_hpp

#include "ofMain.h"
#include "filter.h"
#include "UISlider.h"


class FilterBlur : public Filter {
public:
    
    FilterBlur();
    
    void process(ofFbo * image);
    
    ofShader blurX, blurY;
    UISlider amount;
};

#endif
