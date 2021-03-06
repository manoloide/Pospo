#include "FilterBloom.h"

FilterBloom::FilterBloom(){
    
    name = "BLOOM";
    
    globals = Globals::Instance();
    
    float ww = globals->menuSize-40;
    layout.setup(0, 0, globals->menuSize, 250, name);
    amount.setup(20, 60, ww, 10, 0, 1, 0,  "Amount");
    size.setup(20, 100, ww, 10, 0, 1, 0,  "Size");
    tone.setup(20, 140, ww, 10, -1, 1, 0,  "Tone");
    shadows.setup(20, 180, ww, 10, -1, 1, 0,  "Shadows");
    highlights.setup(20, 220, ww, 10, -1, 1, 0,  "Highlights");
    
    layout.addComponent(&amount);
    layout.addComponent(&size);
    layout.addComponent(&tone);
    layout.addComponent(&shadows);
    layout.addComponent(&highlights);
    
    gaussian.load("shaders/gaussianblur/gaussianblur");
    bloom.load("shaders/bloom/bloom");
}

void FilterBloom::process(ofFbo * image){
    
    ofFbo * pass1 = globals->pass1;
    ofFbo * pass2 = globals->pass2;
    ofFbo * pass3 = globals->pass3;
    
    pass2->begin();
    image->draw(0, 0);
    pass2->end();
    
    int inter = 8;
    for(int i = 0; i < inter; i++){
        float radius = (inter/2-i/2)*size.value*2;
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
    
    pass3->begin();
    bloom.begin();
    bloom.setUniform1f("amount", amount.value);
    bloom.setUniform1f("tone", tone.value);
    bloom.setUniform1f("shadows", shadows.value);
    bloom.setUniform1f("highlights", highlights.value);
    bloom.setUniformTexture("blur", pass2->getTexture(), 1);
    image->draw(0, 0);
    bloom.end();
    pass3->end();
    
    
    image->begin();
    pass3->draw(0, 0);
    image->end();
    
}
