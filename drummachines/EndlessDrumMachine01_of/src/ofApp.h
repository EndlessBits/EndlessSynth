#pragma once

/*
EndlessDrumMachine - drum machine for Raspberry Pi, written in openFrameworks

*/

#include "ofMain.h"
#include "InstrGui.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();
	void save();
	void load();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void start_audio();
	void audioOut(ofSoundBuffer& buffer);
	ofSoundStream soundStream_;

	InstrGui instr_gui_;

};
