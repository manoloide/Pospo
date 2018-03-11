#include "FilterBasic.h"
#include "FilterBlur.h"

FilterBasic::FilterBasic(){
    name = "BASIC";
    
    globals = Globals::Instance();
    
    float ww = globals->menuSize-40;
    layout.setup(0, 0, globals->menuSize, 150, name);
    hue.setup(10, 50, ww, 8, 0, 1, 0,  "Hue");
    brightness.setup(10, 80, ww, 8, 0, 2, 1,  "Brightness");
    contrast.setup(10, 110, ww, 8, 0, 2, 1,  "Contrast");
    saturation.setup(10, 140, ww, 8, 0, 2, 1,  "Saturation");
    
    layout.addComponent(&hue);
    layout.addComponent(&contrast);
    layout.addComponent(&brightness);
    layout.addComponent(&saturation);
    
    basic.load("shaders/basic/basic");
}

void FilterBasic::process(ofFbo * image){
    
    ofFbo * pass1 = globals->pass1;
    
    pass1->begin();
    basic.begin();
    basic.setUniform1f("hue", hue.value);
    basic.setUniform1f("brightness", brightness.value);
    basic.setUniform1f("contrast", contrast.value);
    basic.setUniform1f("saturation", saturation.value);
    image->draw(0, 0);
    basic.end();
    pass1->end();
    
    image->begin();
    pass1->draw(0, 0);
    image->end();
    
}
