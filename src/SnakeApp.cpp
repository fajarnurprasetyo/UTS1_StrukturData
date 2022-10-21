#include "ofMain.h"

enum Dir {
	STOP = 0,
	UP = OF_KEY_UP,
	LEFT = OF_KEY_LEFT,
	DOWN = OF_KEY_DOWN,
	RIGHT = OF_KEY_RIGHT,
};

class App : public ofBaseApp
{
public:
	ofTrueTypeFont gameOverTtfSmall, gameOverTtfBig;

	int nextUpdate = 0,

		width = 28,
		height = 18,
		size,

		foodX, foodY,
		foodAnim = 0,
		snakeX[504], snakeY[504],

		snakeLength,
		dir;

	bool canTurn, gameOver;

	void setup() {
		gameOverTtfSmall.load("fonts/game_over.ttf", 48);
		gameOverTtfBig.load("fonts/game_over.ttf", 72);
		size = ofGetViewportWidth() / 30;

		ofSetWindowTitle("Copyright. 2022 Effort Lab. All Rights Reserved (Fajar Nur Prasetyo | 1122100007)");
		ofEnableAntiAliasing();
		ofSetRectMode(OF_RECTMODE_CENTER);

		start();
	}

	void start() {
		snakeX[0] = 2;
		snakeY[0] = 0;
		snakeX[1] = 1;
		snakeY[1] = 0;
		snakeX[2] = 0;
		snakeY[2] = 0;
		snakeLength = 3;
		dir = Dir::STOP;
		generateFood();
		canTurn = true;
		gameOver = false;
	}

	void generateFood() {
		bool repeat = true;
		while (repeat) {
			foodX = ofRandom(width);
			foodY = ofRandom(height);
			repeat = false;
			for (int i = 0; i < snakeLength; i++)
			{
				if (foodX == snakeX[i] && foodY == snakeY[i])
					repeat = true;
			}
		}
	}

	void turn(int dir) {
		if (canTurn) {
			if (dir == Dir::UP && this->dir == Dir::DOWN ||
				dir == Dir::LEFT && (this->dir == Dir::STOP || this->dir == Dir::RIGHT) ||
				dir == Dir::DOWN && this->dir == Dir::UP ||
				dir == Dir::RIGHT && this->dir == Dir::LEFT)
				return;
			this->dir = dir;
			canTurn = false;
		}
	}

	void update() {
		foodAnim += 2;

		if (!gameOver && dir != Dir::STOP && ofGetElapsedTimeMillis() > nextUpdate) {
			if (dir == Dir::UP && snakeY[0] == 0 ||
				dir == Dir::LEFT && snakeX[0] == 0 ||
				dir == Dir::DOWN && snakeY[0] == height - 1 ||
				dir == Dir::RIGHT && snakeX[0] == width - 1) {
				gameOver = true;
				return;
			}

			for (int i = 1; i < snakeLength; i++)
			{
				if (
					dir == Dir::UP && snakeX[0] == snakeX[i] && snakeY[0] - 1 == snakeY[i] ||
					dir == Dir::LEFT && snakeY[0] == snakeY[i] && snakeX[0] - 1 == snakeX[i] ||
					dir == Dir::DOWN && snakeX[0] == snakeX[i] && snakeY[0] + 1 == snakeY[i] ||
					dir == Dir::RIGHT && snakeY[0] == snakeY[i] && snakeX[0] + 1 == snakeX[i]
					) {
					gameOver = true;
					return;
				}
			}

			int prevX = snakeX[0],
				prevY = snakeY[0],
				prevX2, prevY2;

			switch (dir) {
			case Dir::UP:
				snakeY[0]--;
				break;
			case Dir::LEFT:
				snakeX[0]--;
				break;
			case Dir::DOWN:
				snakeY[0]++;
				break;
			case Dir::RIGHT:
				snakeX[0]++;
				break;
			}

			for (int i = 1; i < snakeLength; i++)
			{
				prevX2 = snakeX[i];
				prevY2 = snakeY[i];
				snakeX[i] = prevX;
				snakeY[i] = prevY;
				prevX = prevX2;
				prevY = prevY2;
			}

			if (snakeX[0] == foodX && snakeY[0] == foodY) {
				snakeX[snakeLength] = prevX;
				snakeY[snakeLength] = prevY;
				snakeLength++;
				generateFood();
			}

			nextUpdate = ofGetElapsedTimeMillis() + 300;
			canTurn = true;
		}
	}

	void keyPressed(int key) {
		switch (key)
		{
		case OF_KEY_UP:
		case OF_KEY_LEFT:
		case OF_KEY_DOWN:
		case OF_KEY_RIGHT:
			turn(key);
			break;
		case OF_KEY_RETURN:
			if (gameOver) start();
			break;
		}
	}

	void draw() {
		ofBackground(155, 186, 90);

		// FOOD
		ofFill();
		ofSetColor(0);
		ofSetLineWidth(0);

		ofPushMatrix();
		ofTranslate((foodX + 1.5) * size, (foodY + 1.5) * size);
		ofRotateDeg(foodAnim % 360);
		ofDrawRectangle(0, 0, size / 2, size / 2);
		ofPopMatrix();

		// SNAKE
		ofFill();
		ofSetColor(0);
		ofSetLineWidth(0);

		for (int i = 0; i < snakeLength; i++)
		{
			ofPushMatrix();
			ofTranslate(size * (snakeX[i] + 1.5), size * (snakeY[i] + 1.5));
			ofDrawRectRounded(0, 0, size * .95, size * .95, size * .33);
			ofPopMatrix();
		}

		// WALL
		ofNoFill();
		ofSetColor(0);
		ofSetLineWidth(5);

		ofPushStyle();
		ofSetRectMode(OF_RECTMODE_CORNER);
		ofDrawRectangle(size * .9, size * .9, size * (width + .2), size * (height + .2));
		ofPopStyle();

		// SCORE TEXT
		string scoreString = "Score: ";
		gameOverTtfBig.drawString(scoreString, size, size * (height + 2.5));
		gameOverTtfBig.drawString(to_string(snakeLength - 3), size + gameOverTtfBig.stringWidth(scoreString), size * (height + 2.5));

		// GAME OVER
		if (gameOver) {
			// BACKGROUND
			ofFill();
			ofSetColor(155, 186, 90, 192);
			ofSetLineWidth(0);

			ofPushStyle();
			ofSetRectMode(OF_RECTMODE_CORNER);
			ofDrawRectangle(0, 0, ofGetViewportWidth(), ofGetViewportHeight());
			ofPopStyle();

			// TEXT
			ofFill();
			ofSetColor(0);
			ofSetLineWidth(0);
			string gameOverString = "Game Over";
			gameOverTtfBig.drawString(gameOverString, (ofGetViewportWidth() / 2) - (gameOverTtfBig.stringWidth(gameOverString) / 2), (ofGetViewportHeight() / 2) - gameOverTtfBig.getLineHeight());
			string pressEnterString = "Press enter to play again";
			gameOverTtfSmall.drawString(pressEnterString, (ofGetViewportWidth() / 2) - (gameOverTtfSmall.stringWidth(pressEnterString) / 2), ofGetViewportHeight() / 2);
		}
	}
};
