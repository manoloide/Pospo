#ifndef FilterVignette_h
#define FilterVignette_h

#include "ofMain.h"
#include "filter.h"
#include "UISlider.h"


class FilterVignette : public Filter {
public:
    
    FilterVignette();
    void process(ofFbo * image);
    
    ofShader vignette;
    UISlider amount, form, size, smooth, centerX, centerY;
};

#endif
