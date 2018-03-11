#include "FilterLensDistortion.h"

FilterLensDistortion::FilterLensDistortion(){
    
    name = "LENS DISTORTION";
    
    globals = Globals::Instance();
    
    float ww = globals->menuSize-20;
    layout.setup(0, 0, globals->menuSize, 150, name);
    barrel.setup(10, 50, ww, 8, 0.0, 2.0, 1.0,  "Barrel"); // -2 2
    shift.setup(10, 80, ww, 8, -1.0, 1.0, 0.0,  "Chromatic Shift");
    aberration.setup(10, 110, ww, 8, 0, 1.0, 0.0,  "Chromatic Aberration");
    defocus.setup(10, 140, ww, 8, 0.0, 1.0, 0.0,  "Defocus");
    
    layout.addComponent(&barrel);
    layout.addComponent(&shift);
    layout.addComponent(&aberration);
    layout.addComponent(&defocus);
    
    lens.load("shaders/lens/lens");
}

void FilterLensDistortion::process(ofFbo * image){
    
    ofFbo * pass1 = globals->pass1;
    
    pass1->begin();
    lens.begin();
    lens.setUniform1f("barrel", barrel.value);
    lens.setUniform1f("shift", shift.value);
    lens.setUniform1f("aberration", aberration.value);
    lens.setUniform1f("defocus", defocus.value);
    lens.setUniform2f("resolution", image->getWidth(), image->getHeight());
    image->draw(0, 0);
    lens.end();
    pass1->end();
    
    
    image->begin();
    pass1->draw(0, 0);
    image->end();
    
}
