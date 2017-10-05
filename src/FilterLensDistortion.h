#ifndef FilterLensDistortion_hpp
#define FilterLensDistortion_hpp

#include "ofMain.h"
#include "filter.h"
#include "UISlider.h"


class FilterLensDistortion : public Filter {
public:
    
    void init(ofFbo * image);
    void process(ofFbo * image);
    
    ofShader lens;
    UISlider barrel, shift, aberration, defocus;
};

#endif
