#include "ofMain.h"
#include "ofxGui.h"


class App : public ofBaseApp
{
public:
	// CONTROL PANEL
	ofxPanel cp;

	ofxFloatSlider
		// RADIUS
		r1, r2,
		// MASS
		m1, m2;

	float
		// GRAVITY
		g = 0.9807,
		// ANGLE
		a1 = PI,
		a2 = HALF_PI,
		// ANGLE VELOCITY
		a1_v = 0,
		a2_v = 0,
		// POSITION
		x1, y1,
		x2, y2,
		// PATHS
		px[256], py[256];

	void setup() {
		cp.setup();
		cp.add(r1.setup("Radius 1", 240, 50, 256));
		cp.add(r2.setup("Radius 2", 240, 50, 256));
		cp.add(m1.setup("Mass 1", 25, 1, 50));
		cp.add(m2.setup("Mass 2", 25, 1, 50));

		ofSetWindowTitle("Copyright. 2022 Effort Lab. All Rights Reserved (Fajar Nur Prasetyo | 1122100007)");
		ofEnableAntiAliasing();
	}

	void update() {
		float n1 = -g * (2 * m1 + m2) * sin(a1);
		float n2 = -m2 * g * sin(a1 - 2 * a2);
		float n3 = -2 * sin(a1 - a2) * m2;
		float n4 = a2_v * a2_v * r2 + a1_v * a1_v * r1 * cos(a1 - a2);
		float dn = r1 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
		float a1_a = (n1 + n2 + n3 * n4) / dn;

		n1 = 2 * sin(a1 - a2);
		n2 = (a1_v * a1_v * r1 * (m1 + m2));
		n3 = g * (m1 + m2) * cos(a1);
		n4 = a2_v * a2_v * r2 * m2 * cos(a1 - a2);
		dn = r2 * (2 * m1 + m2 - m2 * cos(2 * a1 - 2 * a2));
		float a2_a = (n1 * (n2 + n3 + n4)) / dn;

		a1_v += a1_a;
		a2_v += a2_a;

		a1 += a1_v;
		a2 += a2_v;

		x1 = r1 * sin(a1);
		y1 = r1 * cos(a1);

		x2 = x1 + r2 * sin(a2);
		y2 = y1 + r2 * cos(a2);

		for (int i = 0; i < 255; i++)
		{
			px[i] = px[i + 1];
			py[i] = py[i + 1];
		}
		px[255] = x2;
		py[255] = y2;
	}

	void draw() {
		ofBackground(0);
		ofSetColor(255);
		ofSetLineWidth(3);

		ofPushMatrix();

		ofTranslate(ofGetWidth() / 2, 100);

		ofDrawLine(0, 0, x1, y1);
		ofDrawCircle(x1, y1, m1 / 2);

		ofDrawLine(x1, y1, x2, y2);
		ofDrawCircle(x2, y2, m2 / 2);

		ofSetLineWidth(1);
		for (int i = 0; i < 255; i++)
		{
			if (px[i + 1] != 0 && py[i + 1] != 0) {
				ofSetColor(i);
				ofDrawLine(px[i], py[i], px[i + 1], py[i + 1]);
			}
		}

		ofPopMatrix();

		cp.draw();
	}
};
