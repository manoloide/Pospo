#include "FilterBasic.h"
#include "FilterBlur.h"

FilterBasic::FilterBasic(){
    name = "BASIC";
    
    globals = Globals::Instance();
    
    float ww = globals->menuSize-40;
    layout.setup(0, 0, globals->menuSize, 170, name);
    brightness.setup(20, 60, ww, 10, 0, 2, 1,  "Brightness");
    contrast.setup(20, 100, ww, 10, 0, 2, 1,  "Contrast");
    saturation.setup(20, 140, ww, 10, 0, 2, 1,  "Saturation");

    layout.addComponent(&contrast);
    layout.addComponent(&brightness);
    layout.addComponent(&saturation);
    
    basic.load("shaders/basic/basic");
}

void FilterBasic::process(ofFbo * image){
    
    ofFbo * pass1 = globals->pass1;
    
    pass1->begin();
    basic.begin();
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
