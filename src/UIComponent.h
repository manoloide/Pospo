#ifndef UIComponent_h
#define UIComponent_h

#include "ofMain.h"

class UIComponent{
public:
    
    virtual void update() = 0;
    virtual void draw() = 0;
    
    virtual void mouseMoved(int x, int y) = 0;
    virtual void mousePressed(int mouseX, int mouseY, int button) = 0;
    virtual void mouseDragged(int mouseX, int mouseY) = 0;
    virtual void mouseReleased(int mouseX, int mouseY) = 0;
    
    float x, y, w, h;
    string name;
    
    ofTrueTypeFont * font;
};

#endif
