#ifndef filter_h
#define filter_h

#include "ofMain.h"
#include "ofxJSON.h"
#include "Globals.h"
#include "UILayoutFilter.h"

class Filter{
public:
    
    virtual void process(ofFbo * image) = 0;
    
    bool getEnable() {
        return layout.enable;
    }
    
    ofxJSON getJson() {
        ofxJSON json;
        
        json["name"] = name;
        json["enable"] = layout.enable;
        json["hidden"] = layout.hidden;
        json["values"] = getValues();
        
        return json;
    }
    
    void setJson(ofxJSON json) {
        layout.enable = json["enable"].asBool();
        layout.hidden = json["hidden"].asBool();
        setValues(json["values"]);
    }
    
    ofxJSON getValues(){
        ofxJSON json;
        for(int i = 0; i < layout.components.size(); i++){
            json[layout.components[i]->name] = layout.components[i]->getValue();
        }
        return json;
    }
    
    void setValues(ofxJSON json){
        for(int i = 0; i < layout.components.size(); i++){
            float value = json[layout.components[i]->name].asFloat();
            layout.components[i]->setValue(value);
        }
    }

    Globals * globals;
    
    string name;
    UILayoutFilter layout;
    
    
};

#endif
