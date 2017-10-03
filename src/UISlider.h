#ifndef UISlider_h
#define UISlider_h

#include "ofMain.h"
#include "UIComponent.h"


class UISlider : public UIComponent{
public:
    
    UISlider();
    
    void setup(float x, float y, float w, float h, float min, float max, float val, string name);
    void update() override;
    void draw() override;
    
    void mousePressed(int mouseX, int mouseY) override;
    void mouseDragged(int mouseX, int mouseY) override;
    void mouseReleased(int mouseX, int mouseY) override;
    
    bool on, dragged;
    float min, max, value;
    string name;
};

#endif
