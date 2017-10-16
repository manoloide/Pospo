#ifndef UILayout_h
#define UILayout_h

#include "ofMain.h"
#include "UIComponent.h"

class UILayout : public UIComponent{
public:
    UILayout();
    
    void setup(float x, float y, float w, float h);
    void update();
    void draw();
    
    void mousePressed(int mouseX, int mouseY);
    void mouseDragged(int mouseX, int mouseY);
    void mouseReleased(int mouseX, int mouseY);
    
    void addComponent(UIComponent * component);
    UIComponent * getComponent(string name);
    void removeComponent(UIComponent * component);
    void clear();
    
    vector<UIComponent *> components;
};

#endif
