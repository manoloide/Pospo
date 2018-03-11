#include "FilterChromaticAberration.h"

FilterChromaticAberration::FilterChromaticAberration(){
    
    name = "CHROMATIC ABERRATION";
    
    globals = Globals::Instance();
    
    float ww = globals->menuSize-40;
    layout.setup(0, 0, globals->menuSize, 90, name);
    chroma.setup(20, 60, ww, 8, 0, 1, 0,  "Chroma");
    
    layout.addComponent(&chroma);
    
    aberration.load("shaders/aberration/aberration");
}

void FilterChromaticAberration::process(ofFbo * image){
    
    ofFbo * pass1 = globals->pass1;
    
    pass1->begin();
    aberration.begin();
    aberration.setUniform2f("resolution", image->getWidth(), image->getHeight());
    aberration.setUniform1f("chroma", chroma.value);
    image->draw(0, 0);
    aberration.end();
    pass1->end();
    
    
    image->begin();
    pass1->draw(0, 0);
    image->end();
    
}
