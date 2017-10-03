#pragma once

#include "ofMain.h"
#include "filter.h"
#include "FilterBasic.h"
#include "FilterBlur.h"
#include "FilterGrain.h"
#include "FilterVignette.h"
#include "UILayout.h"
#include "UISlider.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void initFilter();
    void updateUI();
    void process();
    
    bool movedCamera;
    bool viewOriginal;
    
    ofImage original;
    ofFbo pospo;
    ofVec3f camera;
    
    vector<Filter *> filters;
    
    UILayout ui;
    UISlider s1;
    UISlider s2;
    UISlider s3;
    UISlider s4;
    
};
