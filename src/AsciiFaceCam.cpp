#include "../resource.h"
#include "ofMain.h"
#include "AsciiFaceCamApp.cpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	ofSetupOpenGL(640, 480, OF_WINDOW);
	HWND hwnd = ofGetWin32Window();
	HICON hMyIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hMyIcon);
	ofRunApp(new App());
}
