#ifndef FilterHue_h
#define FilterHue_h

#include "ofMain.h"
#include "filter.h"
#include "UISlider.h"

class FilterHue : public Filter {
public:
    
    FilterHue();
    
    void process(ofFbo * image);
    
    ofShader basic;
    UISlider hue;
};

#endif

