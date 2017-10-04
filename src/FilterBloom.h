#ifndef FilterBloom_h
#define FilterBloom_h

#include "ofMain.h"
#include "filter.h"
#include "UISlider.h"

class FilterBloom : public Filter {
public:
    
    void init(ofFbo * image);
    void process(ofFbo * image);
    
    ofShader blurX, blurY, bloom;
    UISlider amount, size, tone, shadows, highlights;
};

#endif
