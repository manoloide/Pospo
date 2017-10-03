#include "FilterBlur.h"

void FilterBlur::init(ofFbo * image){
    
    name = "BLUR";
    
    layout.setup(0, 0, 260, 40);
    amount.setup(10, 30, 240, 8, 0, 4, 0,  "Blur amount");
    
    
    layout.addComponent(&amount);
    
    blurX.load("shaders/blur/blurX");
    blurY.load("shaders/blur/blurY");
}

void FilterBlur::process(ofFbo * image){
    
    ofFbo pass1, pass2;
    pass1.allocate(image->getWidth(), image->getHeight());
    pass2.allocate(image->getWidth(), image->getHeight());
    
    
    pass1.begin();
    blurX.begin();
    blurX.setUniform1f("blur", amount.value);
    image->draw(0, 0);
    blurX.end();
    pass1.end();
    
    pass2.begin();
    blurY.begin();
    blurY.setUniform1f("blur", amount.value);
    pass1.draw(0, 0);
    blurY.end();
    pass2.end();
    
    
    image->begin();
    pass2.draw(0, 0);
    image->end();
    
}
