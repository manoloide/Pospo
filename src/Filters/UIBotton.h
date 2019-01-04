#ifndef UIBotton_h
#define UIBotton_h

#include "ofMain.h"
#include "UIValue.h"

class UIBotton : public UIValue{
public:
    
    UIBotton(float _x, float _y, float _w, float _h, string _name);
    
    void setup(float x, float y, float w, float h, string name);
    void update() override;
    void draw() override;
    
    void mouseMoved(int mouseX, int mouseY) override;
    void mousePressed(int mouseX, int mouseY, int button) override;
    void mouseDragged(int mouseX, int mouseY) override;
    void mouseReleased(int mouseX, int mouseY) override;
    
    float getValue() override;
    void setValue(float val) override;
    void randValue() override;
    
    bool on, click;
    bool value;
};

#endif
