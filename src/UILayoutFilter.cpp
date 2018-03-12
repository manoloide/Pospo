#include "UILayoutFilter.h"
#include "Globals.h"

UILayoutFilter::UILayoutFilter(){
    font = Globals::Instance()->uiFontTitle;
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
    ofSetColor(5);
    ofDrawRectangle(0, 0, w, 30);
    
    ofSetColor(35);
    ofDrawRectangle(30, 5, 20, 20);
    //ofDrawRectangle(w-25, 5, 20, 20);
    //ofDrawRectangle(w-50, 5, 20, 20);
    ofDrawRectangle(w-75, 5, 20, 20);
    
    ofSetColor(255);
    //ofDrawBitmapString(name, 40, 14);
    font->drawString(name, 55, 22);
    //ofDrawBitmapString("r", w-43, 14);
    font->drawString("R", w-73, 23);
    
    
    ofSetColor(120);
    if(hidden)
        ofDrawTriangle(15-4, 15-5, 15-4, 15+5, 15+4, 15);
    else
        ofDrawTriangle(15-5, 15-4, 15+5, 15-4, 15, 15+4);
    
    ofDrawTriangle(w-40-8, 15-4, w-40+8, 15-4, w-40, 15+4);
    ofDrawTriangle(w-15-8, 15+4, w-15+8, 15+4, w-15, 15-4);
     
        
    if(enable) ofDrawCircle(40, 15, 5);
    
    if(!hidden){
        ofSetColor(30);
        ofDrawRectangle(0, 30, w, h-30);
        for(int i = 0; i < components.size(); i++){
            components[i]->draw();
        }
    }
    ofPopMatrix();
}
void UILayoutFilter::mouseMoved(int mouseX, int mouseY){
    for(int i = 0; i < components.size(); i++){
        components[i]->mouseMoved(mouseX-x, mouseY-y);
    }
}
void UILayoutFilter::mousePressed(int mouseX, int mouseY, int button){
    float mx = mouseX-x;
    float my = mouseY-y;
    
    if(my >= 5 && my <= 25){
        if(mx >= 5 && mx < 25) hidden = !hidden;
        if(mx >= 30 && mx < 50) enable = !enable;
        if(mx >= w-75 && mx < w-55) randValue();
        if(mx >= w-50 && mx < w-30) toDown = true;
        if(mx >= w-25 && mx < w-5) toUp = true;
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
    if(hidden) return 30;
    return h;
}

void UILayoutFilter::randValue() {
    for(int i = 0; i < components.size(); i++) {
        components[i]->randValue();
    }
}
