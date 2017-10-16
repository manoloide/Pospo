#ifndef UILayoutFilter_h
#define UILayoutFilter_h

#include "ofMain.h"
#include "UIComponent.h"
#include "UIValue.h"

class UILayoutFilter : public UIComponent{
public:
    UILayoutFilter();
    
    void setup(float x, float y, float w, float h, string name);
    void update();
    void draw();
    
    void mousePressed(int mouseX, int mouseY);
    void mouseDragged(int mouseX, int mouseY);
    void mouseReleased(int mouseX, int mouseY);
    
    void addComponent(UIValue * component);
    UIComponent * getComponent(string name);
    void removeComponent(UIValue * component);
    void clear();
    
    void randValue();
    
    float getHeight();
    
    bool enable, hidden;
    bool toUp, toDown;
    string name;
    vector<UIValue *> components;
};

#endif
