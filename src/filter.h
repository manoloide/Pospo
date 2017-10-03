#ifndef filter_h
#define filter_h

#include "ofMain.h"
#include "UILayoutFilter.h"

class Filter{
public:
    virtual void init(ofFbo * image) = 0;
    virtual void process(ofFbo * image) = 0;
    
    bool getEnable() {
        return layout.enable;
    }
    
    bool enable = true;
    string name;
    UILayoutFilter layout;
    
};

#endif
