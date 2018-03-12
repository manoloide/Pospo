#include "FilterFilm.h"

FilterFilm::FilterFilm(){
    
    name = "FILM";
    
    globals = Globals::Instance();
    
    float ww = globals->menuSize-40;
    layout.setup(0, 0, globals->menuSize, 490, name);
    r1.setup(20, 60, ww, 10, 0.0, 1.0, 0.5,  "Red Shadows");
    g1.setup(20, 100, ww, 10, 0.0, 1.0, 0.5,  "Green Shadows");
    b1.setup(20, 140, ww, 10, 0.0, 1.0, 0.5,  "Blue Shadows");
    r2.setup(20, 180, ww, 10, 0.0, 1.0, 0.5,  "Red Lights");
    g2.setup(20, 220, ww, 10, 0.0, 1.0, 0.5,  "Green Lights");
    b2.setup(20, 260, ww, 10, 0.0, 1.0, 0.5,  "Blue Lights");
    r3.setup(20, 300, ww, 10, 0.0, 1.0, 0.5,  "Red HighLights");
    g3.setup(20, 340, ww, 10, 0.0, 1.0, 0.5,  "Green HighLights");
    b3.setup(20, 380, ww, 10, 0.0, 1.0, 0.5,  "Blue HighLights");
    faded.setup(20, 420, ww, 10, 0.0, 1.0, 1.0,  "Faded");
    strength.setup(20, 460, ww, 10, 0.0, 1.0, 1.0,  "Strength");
    
    layout.addComponent(&r1);
    layout.addComponent(&g1);
    layout.addComponent(&b1);
    layout.addComponent(&r2);
    layout.addComponent(&g2);
    layout.addComponent(&b2);
    layout.addComponent(&r3);
    layout.addComponent(&g3);
    layout.addComponent(&b3);
    layout.addComponent(&faded);
    layout.addComponent(&strength);
    
    film.load("shaders/film/film");
}

void FilterFilm::process(ofFbo * image){
    
    ofFbo * pass1 = globals->pass1;
    
    pass1->begin();
    film.begin();
    film.setUniform3f("color1", r1.value, g1.value, b1.value);
    film.setUniform3f("color2", r2.value, g2.value, b2.value);
    film.setUniform3f("color3", r3.value, g3.value, b3.value);
    film.setUniform1f("faded", faded.value);
    film.setUniform1f("strength", strength.value);
    image->draw(0, 0);
    film.end();
    pass1->end();
    
    
    image->begin();
    pass1->draw(0, 0);
    image->end();
    
}
