#include "FilterBasic.h"
#include "FilterHue.h"

FilterHue::FilterHue(){
    name = "HUE";
    
    globals = Globals::Instance();
    
    float ww = globals->menuSize-40;
    layout.setup(0, 0, globals->menuSize, 90, name);
    hue.setup(20, 60, ww, 10, 0, 1, 0,  "Hue");
    
    layout.addComponent(&hue);
    
    basic.load("shaders/hue/hue");
}

void FilterHue::process(ofFbo * image){
    
    ofFbo * pass1 = globals->pass1;
    
    pass1->begin();
    basic.begin();
    basic.setUniform1f("hue", hue.value);
    image->draw(0, 0);
    basic.end();
    pass1->end();
    
    image->begin();
    pass1->draw(0, 0);
    image->end();
    
}

