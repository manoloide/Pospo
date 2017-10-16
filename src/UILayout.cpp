#include "UILayout.h"


UILayout::UILayout(){
    
}

void UILayout::setup(float _x, float _y, float _w, float _h){
    x = _x;
    y = _y;
    w = _w;
    h = _h;
}
void UILayout::update(){
    for(int i = 0; i < components.size(); i++){
        components[i]->update();
    }
}
void UILayout::draw(){
    ofPushMatrix();
    ofTranslate(x, y);
    ofSetColor(30);
    ofDrawRectangle(0, 0, w, h);
    for(int i = 0; i < components.size(); i++){
        components[i]->draw();
    }
    ofPopMatrix();
}

void UILayout::mousePressed(int mouseX, int mouseY){
    for(int i = 0; i < components.size(); i++){
        components[i]->mousePressed(mouseX-x, mouseY-y);
    }
}
void UILayout::mouseDragged(int mouseX, int mouseY){
    for(int i = 0; i < components.size(); i++){
        components[i]->mouseDragged(mouseX-x, mouseY-y);
    }
}
void UILayout::mouseReleased(int mouseX, int mouseY){
    for(int i = 0; i < components.size(); i++){
        components[i]->mouseReleased(mouseX-x, mouseY-y);
    }
}

void UILayout::addComponent(UIComponent * component) {
    components.push_back(component);
}

UIComponent * UILayout::getComponent(string name){
    for(int i = 0; i < components.size(); i++){
        if(components[i]->name == name){
            return components[i];
        }
    }
    return NULL;
}

void UILayout::removeComponent(UIComponent * component) {
    for(int i = 0; i < components.size(); i++){
        if(components[i] == component){
            components.erase(components.begin()+i);
        }
    }
}

void UILayout::clear(){
    components.clear();
}
