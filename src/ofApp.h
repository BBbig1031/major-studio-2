#pragma once

#include "ofMain.h"
#include "ofxLeapMotion2.h"
#include "particles.hpp"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void resetParticles();

    
    void keyPressed  (int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
//    void playmusic();
    void exit();
    
    int left = 0;
    int vol = 0;
   
    vector <particle> particles;
    vector <particle> particles2;
    ofVec2f center = ofVec2f(ofGetWidth()/2,ofGetHeight()/2);
    ofVec2f t = ofVec2f(0,0);

    
    ofxLeapMotion leap;
    vector <ofxLeapMotionSimpleHand> simpleHands;
    
    vector <int> fingersFound;
    ofEasyCam cam;
    
    ofPoint mcp;
    ofPoint pip;
    ofPoint dip;
    ofPoint tip;
    ofPoint handPos;
  
    
    int fontFade;
    int y;
    int x;


};

// first point must always be (0,0)
// given a RELATIVE set of ofPoints and a timeout this
// class can coarsely match simple gestures
// BUG: can go unlimited distance beyond if within time limit

