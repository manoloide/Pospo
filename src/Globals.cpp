#include "Globals.h"

Globals* Globals::instance = 0;

Globals* Globals::Instance() {
    if (instance == 0) {
        instance = new Globals;
    }
    return instance;
}

Globals::Globals() {
    
    pass1 = new ofFbo();
    pass2 = new ofFbo();
    pass3 = new ofFbo();
    
    uiFontTitle = new ofTrueTypeFont();
    uiFontTitle->load("Chivo-Regular.otf", 18, true);
    uiFontValue = new ofTrueTypeFont();
    uiFontValue->load("Chivo-Regular.otf", 16, true);
}

void Globals::init(ofFbo * ori){
    pass1->allocate(ori->getWidth(), ori->getHeight());
    pass2->allocate(ori->getWidth(), ori->getHeight());
    pass3->allocate(ori->getWidth(), ori->getHeight());
}
