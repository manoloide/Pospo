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
    hidden = false;
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
    ofSetColor(255);
    ofDrawBitmapString(name, 40, 14);
    
    ofSetColor(30);
    ofDrawRectangle(20, 5, 10, 10);
    ofSetColor(120);
    if(hidden)
        ofDrawTriangle(8, 6, 8, 14, 12, 10);
    else
        ofDrawTriangle(6, 8, 14, 8, 10, 12);
        
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

void UILayoutFilter::mousePressed(int mouseX, int mouseY){
    float mx = mouseX-x;
    float my = mouseY-y;
    
    if(mx >= 5 && mx < 15 && my >= 5 && my <= 15) hidden = !hidden;
    if(mx >= 20 && mx < 30 && my >= 5 && my <= 15) enable = !enable;
    
    if(hidden) return;
    for(int i = 0; i < components.size(); i++){
        components[i]->mousePressed(mx, my);
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

void UILayoutFilter::addComponent(UIComponent * component) {
    components.push_back(component);
}

void UILayoutFilter::removeComponent(UIComponent * component) {
    for(int i = 0; i < components.size(); i++){
        if(components[i] == component){
            
        }
    }
}

void UILayoutFilter::clear(){
    components.clear();
}

float UILayoutFilter::getHeight(){
    if(hidden) return 20;
    return h;
}
