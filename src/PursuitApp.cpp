#include "ofMain.h"

class App : public ofBaseApp
{
public:
	float
		// YOU
		yourX = 0,
		yourY = 0;

	void setup() {
		ofSetWindowTitle("Copyright. 2022 Effort Lab. All Rights Reserved (Fajar Nur Prasetyo | 1122100007)");
		ofEnableAntiAliasing();
	}

	void start() {
	}

	void update() {
	}

	void draw() {
		ofBackground(192);

		ofTranslate(yourX, yourY);
	}

	void keyPressed(int key) {
		switch (key)
		{
		case OF_KEY_UP:
		case OF_KEY_LEFT:
		case OF_KEY_DOWN:
		case OF_KEY_RIGHT:
			break;
		}
	}

};
