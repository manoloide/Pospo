#include "FilterGrain.h"


FilterGrain::FilterGrain(){
    
    name = "GRAIN";
    
    globals = Globals::Instance();
    
    float ww = globals->menuSize-20;
    layout.setup(0, 0, globals->menuSize, 100, name);
    amount.setup(10, 50, ww, 8, 0.4, 1.0, 1.0,  "Amount");
    smooth.setup(10, 80, ww, 8, 0, 1, 0.5,  "Smooth");
    
    layout.addComponent(&amount);
    layout.addComponent(&smooth);
    
    grain.load("shaders/grain/grain");
}

void FilterGrain::process(ofFbo * image){
    
    ofFbo * pass1 = globals->pass1;
    
    pass1->begin();
    grain.begin();
    grain.setUniform1f("amount", amount.value);
    grain.setUniform1f("smoothed", smooth.value);
    grain.setUniform1f("seed", ofGetElapsedTimef()*2324.73483);
    image->draw(0, 0);
    grain.end();
    pass1->end();
    
    
    image->begin();
    pass1->draw(0, 0);
    image->end();
    
}
