#ifndef UIValue_h
#define UIValue_h

#include "ofMain.h"
#include "UIComponent.h"
#include "Globals.h"


class UIValue : public UIComponent{
public:
    
    UIValue(){
        globals = Globals::Instance();
        font = globals->uiFontValue;
    };
    
    virtual float getValue() = 0;
    virtual void setValue(float val) = 0;
    virtual void randValue() = 0;
    
    Globals * globals;
    ofTrueTypeFont * font;
};

#endif
