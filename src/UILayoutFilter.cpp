#include "UILayoutFilter.h"

UILayoutFilter::UILayoutFilter(){
    
}

void UILayoutFilter::setup(float _x, float _y, float _w, float _h, string _name){
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    name = _name;
    
    enable = false;
    hidden = true;
    toUp = toDown = false;
}
void UILayoutFilter::update(){
    for(int i = 0; i < components.size(); i++){
        components[i]->update();
    }
}
void UILayoutFilter::draw(){
    ofPushMatrix();
    ofTranslate(x, y);
    ofSetColor(0);
    ofDrawRectangle(0, 0, w, 20);
    
    ofSetColor(30);
    ofDrawRectangle(20, 5, 10, 10);
    ofDrawRectangle(w-45, 5, 10, 10);
    
    ofSetColor(255);
    ofDrawBitmapString(name, 40, 14);
    ofDrawBitmapString("r", w-43, 14);
    
    ofSetColor(120);
    if(hidden)
        ofDrawTriangle(8, 6, 8, 14, 12, 10);
    else
        ofDrawTriangle(6, 8, 14, 8, 10, 12);
    
    ofDrawTriangle(w-25-4, 8, w-25+4, 8, w-25, 12);
    ofDrawTriangle(w-10-4, 12, w-10+4, 12, w-10, 8);
        
    if(enable) ofDrawCircle(25, 10, 3);
    
    if(!hidden){
        ofSetColor(30);
        ofDrawRectangle(0, 20, w, h-20);
        for(int i = 0; i < components.size(); i++){
            components[i]->draw();
        }
    }
    ofPopMatrix();
}

void UILayoutFilter::mousePressed(int mouseX, int mouseY, int button){
    float mx = mouseX-x;
    float my = mouseY-y;
    
    if(my >= 5 && my <= 15){
        if(mx >= 5 && mx < 15) hidden = !hidden;
        if(mx >= 20 && mx < 30) enable = !enable;
        if(mx >= w-45 && mx < w-35) randValue();
        if(mx >= w-30 && mx < w-20) toDown = true;
        if(mx >= w-15 && mx < w-5) toUp = true;
    }
    
    if(hidden) return;
    for(int i = 0; i < components.size(); i++){
        components[i]->mousePressed(mx, my, button);
    }
}
void UILayoutFilter::mouseDragged(int mouseX, int mouseY){
    for(int i = 0; i < components.size(); i++){
        components[i]->mouseDragged(mouseX-x, mouseY-y);
    }
}
void UILayoutFilter::mouseReleased(int mouseX, int mouseY){
    for(int i = 0; i < components.size(); i++){
        components[i]->mouseReleased(mouseX-x, mouseY-y);
    }
}

void UILayoutFilter::addComponent(UIValue * component) {
    components.push_back(component);
}

UIComponent * UILayoutFilter::getComponent(string name){
    for(int i = 0; i < components.size(); i++){
        if(components[i]->name == name){
            return components[i];
        }
    }
    return NULL;
}

void UILayoutFilter::removeComponent(UIValue * component) {
    for(int i = 0; i < components.size(); i++){
        if(components[i] == component){
            components.erase(components.begin()+i);
        }
    }
}

void UILayoutFilter::clear() {
    components.clear();
}

float UILayoutFilter::getHeight() {
    if(hidden) return 20;
    return h;
}

void UILayoutFilter::randValue() {
    for(int i = 0; i < components.size(); i++) {
        components[i]->randValue();
    }
}
