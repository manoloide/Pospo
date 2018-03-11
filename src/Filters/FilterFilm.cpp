#include "FilterFilm.h"

FilterFilm::FilterFilm(){
    
    name = "FILM";
    
    globals = Globals::Instance();
    
    float ww = globals->menuSize-20;
    layout.setup(0, 0, globals->menuSize, 360, name);
    r1.setup(10, 50, ww, 8, 0.0, 1.0, 0.5,  "Red Shadows");
    g1.setup(10, 80, ww, 8, 0.0, 1.0, 0.5,  "Green Shadows");
    b1.setup(10, 110, ww, 8, 0.0, 1.0, 0.5,  "Blue Shadows");
    r2.setup(10, 140, ww, 8, 0.0, 1.0, 0.5,  "Red Lights");
    g2.setup(10, 170, ww, 8, 0.0, 1.0, 0.5,  "Green Lights");
    b2.setup(10, 200, ww, 8, 0.0, 1.0, 0.5,  "Blue Lights");
    r3.setup(10, 230, ww, 8, 0.0, 1.0, 0.5,  "Red HighLights");
    g3.setup(10, 260, ww, 8, 0.0, 1.0, 0.5,  "Green HighLights");
    b3.setup(10, 290, ww, 8, 0.0, 1.0, 0.5,  "Blue HighLights");
    faded.setup(10, 320, ww, 8, 0.0, 1.0, 1.0,  "Faded");
    strength.setup(10, 350, ww, 8, 0.0, 1.0, 1.0,  "Strength");
    
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
