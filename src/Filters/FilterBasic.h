#ifndef FilterBasic_h
#define FilterBasic_h

#include "ofMain.h"
#include "filter.h"
#include "UISlider.h"

class FilterBasic : public Filter {
public:
    
    FilterBasic();
    
    void process(ofFbo * image);
    
    ofShader basic;
    UISlider hue, contrast, brightness, saturation;
};

#endif
