#pragma once

#include "ofMain.h"
#include "ofxJSON.h"


#include "filter.h"
#include "FilterBasic.h"
#include "FilterBloom.h"
#include "FilterBlur.h"
#include "FilterChromaticAberration.h"
#include "FilterGaussianBlur.h"
#include "FilterGrain.h"
#include "FilterLensDistortion.h"
#include "FilterFilm.h"
#include "FilterVignette.h"

#include "Globals.h"
#include "Image.h"

#include "UILayout.h"
#include "UISlider.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void mouseScrolled(int x, int y, float scrollX, float scrollY);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void loadPresset();
    void savePresset();
    ofxJSON presset;
    
    void filtersReorder();
    void updateUI();
    void process();
    
    bool movedCamera;
    bool viewOriginal;
    
    Globals * globals;
    
    ofFbo pospo;
    ofVec3f camera;
    float zoom;
    
    int imageIndex = 0;
    vector<Image> images;
    vector<Filter *> filters;
    
    UILayout ui;
    
};
