#include "FilterVignette.h"

void FilterVignette::init(ofFbo * image){
    
    name = "VIGNETTE";
    
    layout.setup(0, 0, 260, 180);
    amount.setup(10, 30, 240, 8, -1.0, 1.0, 0.0,  "Amount");
    form.setup(10, 60, 240, 8, 0, 1, 0.5,  "Form");
    size.setup(10, 90, 240, 8, 0.1, 1, 0.5,  "Size");
    smooth.setup(10, 120, 240, 8, 0.01, 1, 0.4,  "Smooth");
    centerX.setup(10, 150, 240, 8, -0.5, 0.5, 0.0,  "Center X");
    centerY.setup(10, 180, 240, 8, -0.5, 0.5, 0.0,  "Center Y");
    
    
    layout.addComponent(&amount);
    layout.addComponent(&form);
    layout.addComponent(&size);
    layout.addComponent(&smooth);
    layout.addComponent(&centerX);
    layout.addComponent(&centerY);
    
    vignette.load("shaders/vignette/vignette");
}

void FilterVignette::process(ofFbo * image){
    
    ofFbo pass1;
    pass1.allocate(image->getWidth(), image->getHeight());
    
    pass1.begin();
    vignette.begin();
    vignette.setUniform1f("amount", amount.value);
    vignette.setUniform1f("form", form.value);
    vignette.setUniform1f("size", size.value);
    vignette.setUniform1f("smoothed", smooth.value);
    vignette.setUniform2f("center", centerX.value, centerY.value);
    vignette.setUniform2f("resolution", image->getWidth(), image->getHeight());
    image->draw(0, 0);
    vignette.end();
    pass1.end();
    
    
    image->begin();
    pass1.draw(0, 0);
    image->end();
    
}
