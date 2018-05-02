#include "FilterGaussianBlur.h"

FilterGaussianBlur::FilterGaussianBlur(){
    
    name = "GAUSSIAN BLUR";
    
    globals = Globals::Instance();
    
    float ww = globals->menuSize-40;
    layout.setup(0, 0, globals->menuSize, 90, name);
    amount.setup(20, 60, ww, 10, 0, 1, 0,  "Blur amount");
    
    
    layout.addComponent(&amount);
    
    gaussian.load("shaders/gaussianblur/gaussianblur");
}

void FilterGaussianBlur::process(ofFbo * image){
    
    if(ofGetFrameNum()%120 == 0) gaussian.load("shaders/gaussianblur/gaussianblur");
    
    ofFbo * pass1 = globals->pass1;
    ofFbo * pass2 = globals->pass2;
    
    pass2->begin();
    image->draw(0, 0);
    pass2->end();
    
    
    int inter = 8;
    for(int i = 0; i < inter; i++){
        float radius = (inter/2-i/2)*amount.value*2;
        pass1->begin();
        gaussian.begin();
        if(i%2 == 0) gaussian.setUniform2f("direction", radius, 0.0);
        else gaussian.setUniform2f("direction", 0.0, radius);
        gaussian.setUniform2f("resolution", pass2->getWidth(), pass2->getHeight());
        ofSetColor(255);
        pass2->draw(0, 0);
        gaussian.end();
        pass1->end();
        
        pass2->begin();
        pass1->draw(0, 0);
        pass2->end();
    }
    
    image->begin();
    pass2->draw(0, 0);
    image->end();
    
}
