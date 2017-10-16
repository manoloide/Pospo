#include "FilterChromaticAberration.h"

FilterChromaticAberration::FilterChromaticAberration(){
    
    name = "CHROMATIC ABERRATION";
    
    layout.setup(0, 0, 260, 60, name);
    chroma.setup(10, 40, 240, 8, 0, 1, 0,  "Chroma");
    
    layout.addComponent(&chroma);
    
    aberration.load("shaders/aberration/aberration");
}

void FilterChromaticAberration::process(ofFbo * image){
    
    ofFbo pass1;
    pass1.allocate(image->getWidth(), image->getHeight());
    
    
    pass1.begin();
    aberration.begin();
    aberration.setUniform2f("resolution", image->getWidth(), image->getHeight());
    aberration.setUniform1f("chroma", chroma.value);
    image->draw(0, 0);
    aberration.end();
    pass1.end();
    
    
    image->begin();
    pass1.draw(0, 0);
    image->end();
    
}
