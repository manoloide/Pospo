#include "FilterGrain.h"


void FilterGrain::init(ofFbo * image){
    
    name = "GRAIN";
    
    layout.setup(0, 0, 260, 100, name);
    amount.setup(10, 40, 240, 8, 0.4, 1.0, 1.0,  "Amount");
    smooth.setup(10, 70, 240, 8, 0, 1, 0.5,  "Smooth");
    
    layout.addComponent(&amount);
    layout.addComponent(&smooth);
    
    grain.load("shaders/grain/grain");
}

void FilterGrain::process(ofFbo * image){
    
    ofFbo pass1;
    pass1.allocate(image->getWidth(), image->getHeight());
    
    pass1.begin();
    grain.begin();
    grain.setUniform1f("amount", amount.value);
    grain.setUniform1f("smoothed", smooth.value);
    grain.setUniform1f("seed", ofGetElapsedTimef()*2324.73483);
    image->draw(0, 0);
    grain.end();
    pass1.end();
    
    
    image->begin();
    pass1.draw(0, 0);
    image->end();
    
}
