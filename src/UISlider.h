#ifndef UISlider_h
#define UISlider_h

#include "ofMain.h"
#include "UIValue.h"


class UISlider : public UIValue{
public:
    
    UISlider();
    
    void setup(float x, float y, float w, float h, float min, float max, float val, string name);
    void update() override;
    void draw() override;
    
    void mouseMoved(int mouseX, int mouseY) override;
    void mousePressed(int mouseX, int mouseY, int button) override;
    void mouseDragged(int mouseX, int mouseY) override;
    void mouseReleased(int mouseX, int mouseY) override;

    float getValue() override;
    void setValue(float val) override;
    void randValue() override;
    
    bool on, dragged;
    float min, max, value, def;
};

#endif
