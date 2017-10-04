#ifndef FilterChromaticAberration_h
#define FilterChromaticAberration_h

#include "ofMain.h"
#include "filter.h"
#include "UISlider.h"

class FilterChromaticAberration : public Filter {
public:
    
    void init(ofFbo * image);
    void process(ofFbo * image);
    
    ofShader aberration;
    UISlider chroma;
};


#endif
