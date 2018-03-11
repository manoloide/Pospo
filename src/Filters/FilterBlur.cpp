#include "FilterBlur.h"

FilterBlur::FilterBlur(){
    
    name = "BLUR";
    
    globals = Globals::Instance();
    
    float ww = globals->menuSize-40;
    layout.setup(0, 0, globals->menuSize, 90, name);
    amount.setup(20, 60, ww, 8, 0, 4, 0,  "Blur amount");
    
    
    layout.addComponent(&amount);
    
    blurX.load("shaders/blur/blurX");
    blurY.load("shaders/blur/blurY");
}

void FilterBlur::process(ofFbo * image){
    
    ofFbo * pass1 = globals->pass1;
    ofFbo * pass2 = globals->pass2;
    
    
    pass1->begin();
    blurX.begin();
    blurX.setUniform1f("blur", amount.value);
    image->draw(0, 0);
    blurX.end();
    pass1->end();
    
    pass2->begin();
    blurY.begin();
    blurY.setUniform1f("blur", amount.value);
    pass1->draw(0, 0);
    blurY.end();
    pass2->end();
    
    
    image->begin();
    pass2->draw(0, 0);
    image->end();
    
}
