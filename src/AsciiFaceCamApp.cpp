#include "ofMain.h"

class App : public ofBaseApp {
public:
	ofVideoGrabber vidGrabber;
	int camWidth;
	int camHeight;

	string asciiCharacters;
	ofTrueTypeFont font;

	void setup() {
		ofBackground(0);
		ofEnableAlphaBlending();

		camWidth = 640;
		camHeight = 480;

		vidGrabber.setVerbose(true);
		vidGrabber.setup(camWidth, camHeight);

		font.load("fonts/courier.ttf", 9);

		asciiCharacters = string("  ..,,,'''``--_:;^^**""=+<>iv%&xclrs)/){}I?!][1taeo7zjLunT#@JCwfy325Fp6mqSghVd4EgXPGZbYkOA8U$KHDBWNMR0Q");

	}

	void update() {
		vidGrabber.update();
	}

	void draw() {
		float videoAlphaValue = ofMap(mouseX, 0, ofGetWidth(), 0, 255);

		ofSetColor(255, 255, 255, videoAlphaValue);

		//vidGrabber.draw(0, 0);

		ofPixelsRef pixelsRef = vidGrabber.getPixels();

		ofSetHexColor(0xffffff);

		for (int i = 0; i < camWidth; i += 7) {
			for (int j = 0; j < camHeight; j += 9) {
				float lightness = pixelsRef.getColor(i, j).getLightness();

				int character = powf(ofMap(lightness, 0, 255, 0, 1), 2.5) * asciiCharacters.size();

				font.drawString(ofToString(asciiCharacters[character]), i, j);
			}
		}
	}

	void keyPressed(int key) {
		if (key == 's' || key == 'S') {
			vidGrabber.videoSettings();
		}
	}
};