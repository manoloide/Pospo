#ifndef UILayoutFilter_h
#define UILayoutFilter_h

#include "ofMain.h"
#include "UIComponent.h"

class UILayoutFilter : public UIComponent{
public:
    UILayoutFilter();
    
    void setup(float x, float y, float w, float h, string name);
    void update();
    void draw();
    
    void mousePressed(int mouseX, int mouseY);
    void mouseDragged(int mouseX, int mouseY);
    void mouseReleased(int mouseX, int mouseY);
    
    void addComponent(UIComponent * component);
    void removeComponent(UIComponent * component);
    void clear();
    
    float getHeight();
    
    bool enable, hidden;
    string name;
    vector<UIComponent *> components;
};

#endif