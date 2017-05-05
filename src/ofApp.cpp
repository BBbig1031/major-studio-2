#include "ofApp.h"

//--------------------------------------------------------------



ofSoundPlayer bgm;
ofImage gold;
ofVideoPlayer video[5];
int n=0;




void ofApp::setup(){
    
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    //ofSetLogLevel(OF_LOG_VERBOSE);
    
    leap.open();
    
    cam.setOrientation(ofPoint(-20, 0, 0));
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    
    
    //particles
 
    for (int i = 0; i < 1000; i++){
        particle myParticle;
        
        myParticle.setInitialCondition(ofRandom(0,2048),ofRandom(0,1000),0,0);
        
        particles.push_back(myParticle);
    }
    


    
    //video
    for(int i =0; i<5; i++){
        video[i].load(to_string(i)+".mp4");
        
    }
    video[n].play();
    
    
    
    //sound
    bgm.load("bgm.mp3");
    bgm.setVolume(0.5);

    
   
}




//--------------------------------------------------------------
void ofApp::update(){
 
    
    
    
    fingersFound.clear();
    
    //here is a simple example of getting the hands and drawing each finger and joint
    //the leap data is delivered in a threaded callback - so it can be easier to work with this copied hand data
    
    //if instead you want to get the data as it comes in then you can inherit ofxLeapMotion and implement the onFrame method.
    //there you can work with the frame data directly.
    
    
    
    //Option 1: Use the simple ofxLeapMotionSimpleHand - this gives you quick access to fingers and palms.
    
    //video
    video[n].update();
    
    //sound
    ofSoundUpdate();
    
    //particles
    for (int i = 0; i < 1; i++){
        particle myParticle;
        
        myParticle.setInitialCondition(ofRandom(0,2048),ofRandom(0,1000),0,0);
        
        particles.push_back(myParticle);
    }
    
    
    


    
    //leapMotion
    simpleHands = leap.getSimpleHands();
    
    if( leap.isFrameNew() && simpleHands.size() ){
        
        leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
        leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
        leap.setMappingZ(-150, 150, -200, 200);
        
        fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};
        
        for(int i = 0; i < simpleHands.size(); i++){
            for (int f=0; f<5; f++) {
                int id = simpleHands[i].fingers[ fingerTypes[f] ].id;
                ofPoint mcp = simpleHands[i].fingers[ fingerTypes[f] ].mcp; // metacarpal
                ofPoint pip = simpleHands[i].fingers[ fingerTypes[f] ].pip; // proximal
                ofPoint dip = simpleHands[i].fingers[ fingerTypes[f] ].dip; // distal
                
                ofPoint tip = simpleHands[i].fingers[ fingerTypes[f] ].tip; // fingertip
                fingersFound.push_back(id);
                
                
                
            }
        }
    }
    
    

    

    
    
    
    //Option 2: Work with the leap data / sdk directly - gives you access to more properties than the simple approach
    //uncomment code below and comment the code above to use this approach. You can also inhereit ofxLeapMotion and get the data directly via the onFrame callback.
    /*
     vector <Hand> hands = leap.getLeapHands();
     if( leap.isFrameNew() && hands.size() ){
     
     //leap returns data in mm - lets set a mapping to our world space.
     //you can get back a mapped point by using ofxLeapMotion::getMappedofPoint with the Leap::Vector that tipPosition returns
     leap.setMappingX(-230, 230, -ofGetWidth()/2, ofGetWidth()/2);
     leap.setMappingY(90, 490, -ofGetHeight()/2, ofGetHeight()/2);
     leap.setMappingZ(-150, 150, -200, 200);
     
     fingerType fingerTypes[] = {THUMB, INDEX, MIDDLE, RING, PINKY};
     
     for(int i = 0; i < hands.size(); i++){
     for(int j = 0; j < 5; j++){
     ofPoint pt;
     
     const Finger & finger = hands[i].fingers()[ fingerTypes[j] ];
     
     //here we convert the Leap point to an ofPoint - with mapping of coordinates
     //if you just want the raw point - use ofxLeapMotion::getofPoint
     pt = leap.getMappedofPoint( finger.tipPosition() );
     pt = leap.getMappedofPoint( finger.jointPosition(finger.JOINT_DIP) );
     
     fingersFound.push_back(finger.id());
     }
     }
     }
     */
    
    //IMPORTANT! - tell ofxLeapMotion that the frame is no longer new.
    leap.markFrameAsOld();
    

    
    
}





//--------------------------------------------------------------
void ofApp::draw(){


  //leapMotion
    for(int i = 0; i < simpleHands.size(); i++){
        bool isLeft        = simpleHands[i].isLeft;
        ofPoint handPos    = simpleHands[i].handPos;
        ofPoint handNormal = simpleHands[i].handNormal;
        //
      
//        ofTranslate(ofGetWindowWidth()/2, ofGetWindowHeight()/2);
        x = ofMap(handPos.x,-300,700,0,ofGetWindowWidth());
         y = ofMap(handPos.y,-600,500,0,ofGetWindowHeight());
      
       gold.load("gold.jpg");

        
        gold.draw(x,y,5);
        ofSetColor(255);
//        ofDrawSphere(x,y, 15);
//          ofSetColor(255);
        cout<<x<<endl;
    }
    
    
    //particles
    if(n >=1){
    
    
        ofPushStyle();
        ofSetColor(0x000000);
        
        for (int i = 0; i < particles.size(); i++){
            particles[i].draw(0);
            
        }
        ofPopStyle();
    
    }
    
    for (int i = 0; i < particles.size(); i++){
        int distance =center.distance(particles[i].pos);
        //        t = ofVec2f(particles[i].x,particles[i].y);
        //        cout<<distance<<endl;
        
        if(center.distance(particles[i].pos) <= 6){
            particles.erase(particles.begin() +i);
        }
        
        
        particles[i].resetForce();
        particles[i].addRepulsionForce(x,y, 60, 10);
        
        
        particles[i].addAttractionForce(ofGetWidth()/2, ofGetHeight()/2, 1000, 0.1);
        //        cout<<particles[i].x<<endl;
        
        particles[i].addDampingForce();
        particles[i].update();
        
    }

   //    ofSetColor(255,255,255, fontFade);
////    ofBitmapFont();
//    ofDrawBitmapString("PRESS SPACE TO SKIP", ofGetWidth()/2, ofGetHeight()-50);
//    ofSetColor(255);
    
    
    //video
    float pixelRatio = 0.77;
    float pixelHeight =0.84;
    video[n].draw(0,0,video[n].getWidth()*pixelRatio, video[n].getHeight()*pixelHeight);
//    video[n].draw(0,0,1024,768);
    
  

    

    
    
    //leapMotion
    

        	ofPushMatrix();
            ofRotate(90, 0, 0, 1);
        	ofPopMatrix();
    
    
    


    

 
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    
    if (key == ' '){
        video[n].stop();
    
        bgm.play();
        n++;
        if(n>=5) n = 1;
        
        video[n].play();
        
        
        
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

//--------------------------------------------------------------
void ofApp::exit(){
    // let's close down Leap and kill the controller
    leap.close();
}
