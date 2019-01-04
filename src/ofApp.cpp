#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetBackgroundColor(40);
    
    globals = Globals::Instance();
    
    createUI();
    
    actualImage = NULL;
    /*
    Image initImage("init.jpg");
    images.push_back(initImage);
    imageIndex = 0;
    actualImage = &initImage;
    pospo.allocate(initImage.image.getWidth(), initImage.image.getHeight());
    */
    
    globals->init(&pospo);
    loadPresset();
    
    updateUI();
    process();
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(buttonCancel->click){
        cancel();
    }
    if(buttonSave->click){
        save();
    }
    if(buttonSaveAll->click){
        saveAll();
    }
    
    uiFilter.update();
    uiOptions.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    if(actualImage != NULL){
        ofPushMatrix();
        ofTranslate((ofGetWidth()-globals->menuSize)/2, ofGetHeight()/2);
        ofTranslate(camera.x, camera.y);
        float sca = pow(1.5, zoom);
        ofScale(sca, sca);
        ofSetColor(80);
        ofDrawRectangle(-2, -2, 4, 4);
        ofSetColor(255);
        if(viewOriginal) {
            if(actualImage->image.isAllocated())
                actualImage->image.draw(actualImage->image.getWidth()*-0.5, actualImage->image.getHeight()*-0.5);
        }
        else {
            if(pospo.isAllocated())
                pospo.draw(pospo.getWidth()*-0.5, pospo.getHeight()*-0.5);
        }
        ofPopMatrix();
    }
    
    
    ofPushMatrix();
    uiFilter.draw();
    uiOptions.draw();
    
    globals->uiFontValue->drawString(ofToString(imageIndex+1)+"/"+ofToString(images.size()), 10, 20);
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
    if(key == 'l') loadPresset();
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
            imageIndex = (int)images.size()-1;
        
        actualImage = &images[imageIndex];
        pospo.allocate(actualImage->image.getWidth(), actualImage->image.getHeight());
        globals->init(&pospo);
        process();
        
    }
    
    if(key == OF_KEY_RIGHT) {
        
        imageIndex++;
        if(imageIndex >= images.size())
            imageIndex = 0;
        
        actualImage = &images[imageIndex];
        pospo.allocate(actualImage->image.getWidth(), actualImage->image.getHeight());
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
    
    uiFilter.mouseMoved(x, y);
    uiOptions.mouseMoved(x, y);
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
    if(movedCamera) {
        camera.x += mouseX-ofGetPreviousMouseX();
        camera.y += mouseY-ofGetPreviousMouseY();
    }
    else {
        uiFilter.mouseDragged(x, y);
        uiOptions.mouseDragged(x, y);
    }
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    movedCamera = x<ofGetWidth()-globals->menuSize;
    
    uiFilter.mousePressed(x, y, button);
    uiOptions.mousePressed(x, y, button);
    updateUI();
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    movedCamera = false;
    
    uiFilter.mouseReleased(x, y);
    uiOptions.mouseReleased(x, y);
    updateUI();
    
    process();
    
}


//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){
    
    float w = ofGetWidth()-globals->menuSize;
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
    createUI();
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
    int init = (int)images.size();
    bool add = false;
    
    for(int i = 0; i < dragInfo.files.size(); i++){
        Image aux(dragInfo.files[i]);
        if(aux.image.isAllocated()){
            imageIndex = (int) images.size();
            images.push_back(aux);
            add = true;
        }
    }
    
    if(add) {
        imageIndex = init;
        actualImage = &images[imageIndex];
        pospo.allocate(actualImage->image.getWidth(), actualImage->image.getHeight());
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
            else if(name == "GAUSSIAN BLUR"){
                filter = new FilterGaussianBlur();
            }
            else if(name == "GRAIN") {
                filter = new FilterGrain();
            }
            else if(name == "HUE") {
                filter = new FilterHue();
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
        
        filters.push_back(new FilterHue());
        filters.push_back(new FilterBasic());
        filters.push_back(new FilterLensDistortion());
        filters.push_back(new FilterChromaticAberration());
        filters.push_back(new FilterBlur());
        filters.push_back(new FilterGaussianBlur());
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

void ofApp::createUI(){
    
    uiFilter.setup(ofGetWidth()-globals->menuSize, 0, globals->menuSize, ofGetHeight()-60);
    uiOptions.setup(ofGetWidth()-globals->menuSize, ofGetHeight()-60, globals->menuSize, 60);
    
    buttonCancel = new UIBotton( 25, 10, 130, 40, "CANCEL");
    buttonSave = new UIBotton( 175, 10, 130, 40, "SAVE");
    buttonSaveAll = new UIBotton(325, 10, 130, 40, "SAVE ALL");
    
    uiOptions.addComponent(buttonCancel);
    uiOptions.addComponent(buttonSave);
    uiOptions.addComponent(buttonSaveAll);

}

void ofApp::updateUI(){
    
    uiFilter.clear();
    
    filtersReorder();
    
    float auxHeight = 0;
    for(int i = 0; i < filters.size(); i++){
        filters[i]->layout.y = auxHeight;
        uiFilter.addComponent(&filters[i]->layout);
        auxHeight += filters[i]->layout.getHeight();
    }
    
}

void ofApp::process(){
    
    if(actualImage == NULL) return;
    
    ofSetColor(255);
    pospo.begin();
    images[imageIndex].image.draw(0, 0);
    pospo.end();
    
    for(int i = 0; i < filters.size(); i++) {
        if(filters[i]->getEnable()) filters[i]->process(&pospo);
    }
    
}

void ofApp::cancel(){
    
    cout << "Cancel" << endl;
    ofExit();
    
}

void ofApp::save(){
    
    string path = actualImage->getSavePathName();
    process();
    saveImage(&pospo, path);
    
    //closeImage(actualImage);
    
}

void ofApp::saveAll(){
    
    for(int i = 0; i < images.size(); i++){
        imageIndex = i;
        actualImage = &images[imageIndex];
        string path = actualImage->getSavePathName();
        process();
        saveImage(&pospo, path);
    }
    
    cancel();
    
}


void ofApp::saveImage(ofFbo * fbo, string path){
    
    ofPixels pix;
    fbo->readToPixels(pix);
    ofSaveImage(pix, path);
    
}
