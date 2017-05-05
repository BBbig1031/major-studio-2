//
//  particles.cpp
//  example
//
//  Created by BBbig on 29/04/2017.
//
//

#include "particles.hpp"
#include "ofMain.h"


//------------------------------------------------------------
particle::particle(){
    setInitialCondition(0,0,0,0);
    damping = 0.07f;
    
}

//------------------------------------------------------------
void particle::resetForce(){
    frc.set(0,0);
}

//------------------------------------------------------------
void particle::addForce(float x, float y){
    frc.x = frc.x + x;
    frc.y = frc.y + y;
}

//------------------------------------------------------------
void particle::addDampingForce(){
    
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
}


//------------------------------------------------------------
void particle::addRepulsionForce( float px, float py, float radius, float strength){
    
    
    ofVec2f posOfForce;
    posOfForce.set(px, py);
    
    ofVec2f diff = pos - posOfForce;
    
    if (diff.length() < radius){
        float pct = 1 - (diff.length() / radius);
        diff.normalize();
        frc.x += diff.x * pct * strength;
        frc.y += diff.y * pct * strength;
    }
    
}

//------------------------------------------------------------
void particle::addAttractionForce( float px, float py, float radius, float strength){
    
    
    ofVec2f posOfForce;
    posOfForce.set(px, py);
    
    ofVec2f diff = pos - posOfForce;
    
    if (diff.length() < radius){
        float pct = 1 - (diff.length() / radius);
        diff.normalize();
        frc.x -= diff.x * pct * strength;
        frc.y -= diff.y * pct * strength;
    }
    
}


//------------------------------------------------------------
void particle::addClockwiseForce( float px, float py, float radius, float strength){
    
    
    ofVec2f posOfForce;
    posOfForce.set(px, py);
    
    ofVec2f diff = pos - posOfForce;
    
    if (diff.length() < radius){
        float pct = 1 - (diff.length() / radius);
        //        float pct = diff.length();
        diff.normalize();
        frc.x = diff.y  *pct * strength;
        frc.y += diff.x  * pct * strength;
    }
    
}

//------------------------------------------------------------
void particle::addCounterClockwiseForce( float px, float py, float radius, float strength){
    
    
    ofVec2f posOfForce;
    posOfForce.set(px, py);
    
    ofVec2f diff = pos - posOfForce;
    
    if (diff.length() < radius){
        float pct = 1 - (diff.length() / radius);
        diff.normalize();
        frc.x += diff.y * pct * strength;
        frc.y -= diff.x * pct * strength;
    }
    
}





//------------------------------------------------------------
void particle::setInitialCondition(float px, float py, float vx, float vy){
    pos.set(px,py);
    vel.set(vx,vy);
}

//------------------------------------------------------------
void particle::update(){	
    vel = vel + frc;
    pos = pos + vel;
}

//------------------------------------------------------------
void particle::draw(int length){
    ofSetColor(0);
    
    ofDrawCircle(pos.x, pos.y, 4);
//    ofDrawCircle(pos.x+500,pos.y,2);
    
}

