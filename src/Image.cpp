#include "Image.h"

Image::Image(string filename){
    this->filename = filename;
    
    name = filename;
    directory = "";
    int pos = (int) filename.rfind('/');
    if(pos != string::npos){
        name = filename.substr(pos+1);
        directory = filename.substr(0, pos+1);
    }
    pos = (int) name.rfind('.');
    if(pos != string::npos) ext = name.substr(pos+1);
    
    image.load(filename);
}

string Image::getSavePathName(){
    return directory + "/pospo_" + name;
}
