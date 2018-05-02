#include "Image.h"

Image::Image(string filename){
    this->filename = filename;
    
    name = filename;
    directory = "";
    int pos = filename.rfind('/');
    if(pos != string::npos){
        name = filename.substr(pos+1);
        directory = filename.substr(0, pos+1);
    }
    
    pos = name.rfind('.');
    if(pos != string::npos) ext = name.substr(pos+1);
    
    cout << filename << " " << ext << " " << name << " " << directory << endl;
    
    image.load(filename);
}

string Image::getSavePathName(){
    return directory + "/post_" + name;
}
