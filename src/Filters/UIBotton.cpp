#include "UIBotton.h"

UIBotton::UIBotton(float _x, float _y, float _w, float _h, string _name){
    setup(_x, _y, _w, _h, _name);
}

void UIBotton::setup(float _x, float _y, float _w, float _h, string _name){
    x = _x;
    y = _y;
    w = _w;
    h = _h;
    name = _name;
    
    on = click = false;
}

void UIBotton::update(){
    click = false;
}

void UIBotton::draw(){
    ofSetColor(50);
    if(on) ofSetColor(60);
    ofDrawRectangle(x, y, w, h);
    
    ofSetColor(255);
    float ww = font->stringWidth(name);
    font->drawString(name, x+w*0.5-ww*0.5, y+h*0.66);
    //ofDrawBitmapString(name, x, y-4);
}

void UIBotton::mouseMoved(int mouseX, int mouseY){
    on = (mouseX >= x && mouseX <= x+w && mouseY >= y && mouseY <= y+h);
}

void UIBotton::mousePressed(int mouseX, int mouseY, int button){
    on = (mouseX >= x && mouseX <= x+w && mouseY >= y && mouseY <= y+h);
    value = click = on;
}

void UIBotton::mouseDragged(int mouseX, int mouseY){
    
}

void UIBotton::mouseReleased(int mouseX, int mouseY){
    on = click = false;
}

float UIBotton::getValue() {
    return value;
}

void UIBotton::setValue(float val) {
    value = val;
}


void UIBotton::randValue() {
    value = false;
}
