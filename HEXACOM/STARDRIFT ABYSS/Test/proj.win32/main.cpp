#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"
#include "DisplayHandler.h"

USING_NS_CC;

int WINAPI _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	//creates a console window and doesn't actually cause an error
	DISPLAY->createDebugConsole();
    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}
