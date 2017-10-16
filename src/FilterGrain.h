
#ifndef FilterGrain_h
#define FilterGrain_h

#include "ofMain.h"
#include "filter.h"
#include "UISlider.h"


class FilterGrain : public Filter {
public:
    
    FilterGrain();
    void process(ofFbo * image);
    
    ofShader grain;
    UISlider amount, smooth;
};

#endif
