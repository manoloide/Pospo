#ifndef FilterFilm_h
#define FilterFilm_h

#include "ofMain.h"
#include "filter.h"
#include "UISlider.h"


class FilterFilm : public Filter {
public:
    
    FilterFilm();
    void process(ofFbo * image);
    
    ofShader film;
    UISlider r1, g1, b1, r2, g2, b2, r3, g3, b3, faded, strength;
};

#endif
