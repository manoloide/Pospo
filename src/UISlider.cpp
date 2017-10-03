#include "UISlider.h"

UISlider::UISlider(){
}

void UISlider::setup(float _x, float _y, float _w, float _h, float _min, float _max, float _val, string _name){
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    min = _min;
    max = _max;
    value = _val;
    name = _name;
}

void UISlider::update(){
}
void UISlider::draw(){
    ofSetColor(60);
    if(on) ofSetColor(70);
    ofDrawRectangle(x, y, w, h);
    
    float porc = ofMap(value, min, max, 0, 1);
    ofSetColor(255, 80);
    ofDrawRectangle(x, y, w*porc, h);
    
    ofSetColor(255);
    ofDrawBitmapString(name, x, y-4);
}

void UISlider::mousePressed(int mouseX, int mouseY){
    on = (mouseX >= x && mouseX <= x+w && mouseY >= y && mouseY <= y+h);
    dragged = on;
    if(dragged) {
        value = ofClamp(ofMap(mouseX, x, x+w, min, max), min, max);
    }
}

void UISlider::mouseDragged(int mouseX, int mouseY){
    if(dragged) {
        value = ofClamp(ofMap(mouseX, x, x+w, min, max), min, max);
    }
    
}

void UISlider::mouseReleased(int mouseX, int mouseY){
    on = dragged = false;
}