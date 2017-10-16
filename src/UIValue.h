#ifndef UIValue_h
#define UIValue_h

#include "ofMain.h"
#include "UIComponent.h"

class UIValue : public UIComponent{
public:
    virtual float getValue() = 0;
    virtual void setValue(float val) = 0;
    virtual void randValue() = 0;    
};

#endif
