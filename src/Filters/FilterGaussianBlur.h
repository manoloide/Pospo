#ifndef FilterGaussianBlur_h
#define FilterGaussianBlur_h

#include "ofMain.h"
#include "filter.h"
#include "UISlider.h"

class FilterGaussianBlur : public Filter {
public:
    
    FilterGaussianBlur();
    
    void process(ofFbo * image);
    
    ofShader gaussian;
    UISlider amount;
};

#endif
