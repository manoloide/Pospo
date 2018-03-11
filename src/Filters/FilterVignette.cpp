#include "FilterVignette.h"

FilterVignette::FilterVignette(){
    
    name = "VIGNETTE";
    
    globals = Globals::Instance();
    
    float ww = globals->menuSize-20;
    layout.setup(0, 0, globals->menuSize, 210, name);
    amount.setup(10, 40, ww, 8, -1.0, 1.0, 0.0,  "Amount");
    form.setup(10, 70, ww, 8, 0, 1, 0.5,  "Form");
    size.setup(10, 100, ww, 8, 0.5, 3, 1.0,  "Size");
    smooth.setup(10, 130, ww, 8, 0.01, 1, 0.4,  "Smooth");
    centerX.setup(10, 160, ww, 8, -0.5, 0.5, 0.0,  "Center X");
    centerY.setup(10, 190, ww, 8, -0.5, 0.5, 0.0,  "Center Y");
    
    layout.addComponent(&amount);
    layout.addComponent(&form);
    layout.addComponent(&size);
    layout.addComponent(&smooth);
    layout.addComponent(&centerX);
    layout.addComponent(&centerY);
    
    vignette.load("shaders/vignette/vignette");
}

void FilterVignette::process(ofFbo * image){
    
    ofFbo * pass1 = globals->pass1;
    
    pass1->begin();
    vignette.begin();
    vignette.setUniform1f("amount", amount.value);
    vignette.setUniform1f("form", form.value);
    vignette.setUniform1f("size", size.value);
    vignette.setUniform1f("smoothed", smooth.value);
    vignette.setUniform2f("center", centerX.value, centerY.value);
    vignette.setUniform2f("resolution", image->getWidth(), image->getHeight());
    image->draw(0, 0);
    vignette.end();
    pass1->end();
    
    
    image->begin();
    pass1->draw(0, 0);
    image->end();
    
}
