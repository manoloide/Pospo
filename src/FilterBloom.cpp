#include "FilterBloom.h"

FilterBloom::FilterBloom(){
    
    name = "BLOOM";
    
    layout.setup(0, 0, 260, 180, name);
    amount.setup(10, 40, 240, 8, 0, 1, 0,  "Amount");
    size.setup(10, 70, 240, 8, 0, 4, 0,  "Size");
    tone.setup(10, 100, 240, 8, -1, 1, 0,  "Tone");
    shadows.setup(10, 130, 240, 8, -1, 1, 0,  "Shadows");
    highlights.setup(10, 160, 240, 8, -1, 1, 0,  "Highlights");
    
    layout.addComponent(&amount);
    layout.addComponent(&size);
    layout.addComponent(&tone);
    layout.addComponent(&shadows);
    layout.addComponent(&highlights);
    
    blurX.load("shaders/blur/blurX");
    blurY.load("shaders/blur/blurY");
    bloom.load("shaders/bloom/bloom");
}

void FilterBloom::process(ofFbo * image){
    
    ofFbo pass1, pass2, pass3;
    pass1.allocate(image->getWidth(), image->getHeight());
    pass2.allocate(image->getWidth(), image->getHeight());
    pass3.allocate(image->getWidth(), image->getHeight());
    
    
    pass1.begin();
    blurX.begin();
    blurX.setUniform1f("blur", size.value);
    image->draw(0, 0);
    blurX.end();
    pass1.end();
    
    pass2.begin();
    blurY.begin();
    blurY.setUniform1f("blur", size.value);
    pass1.draw(0, 0);
    blurY.end();
    pass2.end();
    
    pass3.begin();
    bloom.begin();
    bloom.setUniform1f("amount", amount.value);
    bloom.setUniform1f("tone", tone.value);
    bloom.setUniform1f("shadows", shadows.value);
    bloom.setUniform1f("highlights", highlights.value);
    bloom.setUniformTexture("blur", pass2.getTexture(), 1);
    image->draw(0, 0);
    bloom.end();
    pass3.end();
    
    
    image->begin();
    pass3.draw(0, 0);
    image->end();
    
}
