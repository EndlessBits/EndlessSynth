#pragma once

//Gui LED

#include "ofMain.h"
#include "GuiConfig.h"
#include "GuiItem.h"

class GuiItemLed: public GuiItem {
public:
	void setup(int2 pos);
	void update();
	void draw();

	virtual bool mouseOver(int x, int y);
	virtual void mouseMoved(int x, int y, int button);
	virtual void mousePressed(int x, int y, int button);
	virtual void mouseDragged(int x, int y, int button);
	virtual void mouseReleased(int x, int y, int button);
	virtual void mouseReleased();

protected:

};

