#ifndef Image_h
#define Image_h

#include "ofMain.h"

class Image {
public:
    Image(string source);
    
    string directory, filename, name, ext;
    ofImage image;
    
    string getSavePathName();
};

#endif
