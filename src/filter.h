#ifndef filter_h
#define filter_h

#include "ofMain.h"
#include "UILayout.h"

class Filter{
public:
    virtual void init(ofFbo * image) = 0;
    virtual void process(ofFbo * image) = 0;
    
    bool enable = true;
    string name;
    UILayout layout;
    
};

#endif
