#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetBackgroundColor(40);
    
    ui.setup(ofGetWidth()-260, 0, 260, ofGetHeight());
    
    ofImage initImage;
    initImage.load("init.jpg");
    images.push_back(initImage);
    pospo.allocate(initImage.getWidth(), initImage.getHeight());
    
    globals = Globals::Instance();
    globals->init(&pospo);
    
    loadPresset();
    process();
}

//--------------------------------------------------------------
void ofApp::update(){
    ui.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofTranslate((ofGetWidth()-260)/2, ofGetHeight()/2);
    ofTranslate(camera.x, camera.y);
    float sca = pow(1.5, zoom);
    ofScale(sca, sca);
    ofSetColor(80);
    ofDrawRectangle(-2, -2, 4, 4);
    ofSetColor(255);
    if(viewOriginal) {
        if(images[imageIndex].isAllocated())
            images[imageIndex].draw(images[imageIndex].getWidth()*-0.5, images[imageIndex].getHeight()*-0.5);
    }
    else {
        if(pospo.isAllocated())
            pospo.draw(pospo.getWidth()*-0.5, pospo.getHeight()*-0.5);
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ui.draw();
    
    ofDrawBitmapStringHighlight(ofToString(imageIndex+1)+"/"+ofToString(images.size()), 10, 15);
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '+') zoom = ofClamp(zoom+1, -5, 5);
    if(key == '-') zoom = ofClamp(zoom-1, -5, 5);
    if(key == 'r') {
        loadPresset();
        process();
    }
    if(key == 's') savePresset();
    if(key == 'p') process();
    if(key == ' ') viewOriginal = true;
    
    if(key == 'h') {
        for(int i = 0; i < filters.size(); i++){
            filters[i]->layout.hidden = true;
        }
        updateUI();
    }
    
    if(key == OF_KEY_LEFT){
        imageIndex--;
        if(imageIndex < 0)
            imageIndex = images.size()-1;
        pospo.allocate(images[imageIndex].getWidth(), images[imageIndex].getHeight());
        globals->init(&pospo);
        process();
    }
    if(key == OF_KEY_RIGHT) {
        imageIndex++;
        imageIndex = imageIndex%images.size();
        pospo.allocate(images[imageIndex].getWidth(), images[imageIndex].getHeight());
        globals->init(&pospo);
        process();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key == ' ') viewOriginal = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if(movedCamera) {
        camera.x += mouseX-ofGetPreviousMouseX();
        camera.y += mouseY-ofGetPreviousMouseY();
    }
    
    ui.mouseDragged(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    movedCamera = x<ofGetWidth()-260;
    
    ui.mousePressed(x, y, button);
    updateUI();
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    movedCamera = false;
    
    ui.mouseReleased(x, y);
    updateUI();
    
    process();
}


//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){
    float w = ofGetWidth()-260;
    float h = ofGetHeight();
    if(x<w) {
        float azoom = zoom;
        zoom += scrollY*0.2;
        zoom = ofClamp(zoom, -5, 5);
        
        float mx = x-w*0.5;
        float my = y-h*0.5;
        camera.x -= (mx-camera.x)*(zoom-azoom)*0.41;
        camera.y -= (my-camera.y)*(zoom-azoom)*0.41;
    }
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    ui.setup(ofGetWidth()-260, 0, 260, ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    ofImage aux;
    aux.load(dragInfo.files[0]);
    
    if(aux.isAllocated()){
        imageIndex = images.size();
        images.push_back(aux);
        pospo.allocate(aux.getWidth(), aux.getHeight());
        globals->init(&pospo);
        
        process();
    }
}

void ofApp::loadPresset(){
    
    filters.clear();
    
    if (presset.open("presset.json")){
        cout << "load presset succeed" << endl;
        
        for(int i = 0; i < presset["filters"].size(); i++){
            ofxJSON json = presset["filters"][i];
            string name = json["name"].asString();
            
            Filter * filter = NULL;
            if(name == "BASIC") {
                filter = new FilterBasic();
            }
            else if(name == "BLOOM") {
                filter = new FilterBloom();
            }
            else if(name == "BLUR") {
                filter = new FilterBlur();
            }
            else if(name == "CHROMATIC ABERRATION") {
                filter = new FilterChromaticAberration();
            }
            else if(name == "FILM") {
                filter = new FilterFilm();
            }
            else if(name == "GRAIN") {
                filter = new FilterGrain();
            }
            else if(name == "LENS DISTORTION") {
                filter = new FilterLensDistortion();
            }
            else if(name == "VIGNETTE") {
                filter = new FilterVignette();
            }
            
            
            if(filter != NULL) {
                filter->setJson(json);
                filters.push_back(filter);
            }
        }
    }
    else {
        cout << "load presset fail" << endl;
        
        filters.push_back(new FilterBasic());
        filters.push_back(new FilterLensDistortion());
        filters.push_back(new FilterChromaticAberration());
        filters.push_back(new FilterBlur());
        filters.push_back(new FilterBloom());
        filters.push_back(new FilterBloom());
        filters.push_back(new FilterBloom());
        filters.push_back(new FilterBloom());
        filters.push_back(new FilterBloom());
        filters.push_back(new FilterBloom());
        filters.push_back(new FilterVignette());
        filters.push_back(new FilterGrain());
        filters.push_back(new FilterFilm());
        
        savePresset();
    }
    
    updateUI();
}

void ofApp::savePresset(){
    
    presset = ofxJSON();
    
    for(int i = 0; i < filters.size(); i++){
        presset["filters"][i] = filters[i]->getJson();
    }
    
    if (!presset.save("presset.json", true)){
        cout << "save presset fail" << endl;
    } else {
        cout << "save presset succeed" << endl;
    }
}

void ofApp::filtersReorder() {
    for(int i = 0; i < filters.size(); i++) {
        if(filters[i]->layout.toDown && i < filters.size()-1){
            Filter * aux = filters[i];
            filters.erase(filters.begin()+i);
            filters.insert(filters.begin()+i+1, aux);
            i--;
            aux->layout.toDown = false;
        }
        if(filters[i]->layout.toUp && i > 0){
            Filter * aux = filters[i];
            filters.erase(filters.begin()+i);
            filters.insert(filters.begin()+i-1, aux);
            aux->layout.toUp = false;
        }
        /*
         if(filters[i]->layout.remove){
            filters.erase(filters.begin()+i);
            i--;
         }
         */
    }
}

void ofApp::updateUI(){
    ui.clear();
    
    filtersReorder();
    
    float auxHeight = 0;
    for(int i = 0; i < filters.size(); i++){
        filters[i]->layout.y = auxHeight;
        ui.addComponent(&filters[i]->layout);
        auxHeight += filters[i]->layout.getHeight();
    }
    
}

void ofApp::process(){
    ofSetColor(255);
    pospo.begin();
    images[imageIndex].draw(0, 0);
    pospo.end();
    for(int i = 0; i < filters.size(); i++) {
        if(filters[i]->getEnable()) filters[i]->process(&pospo);
    }
}
