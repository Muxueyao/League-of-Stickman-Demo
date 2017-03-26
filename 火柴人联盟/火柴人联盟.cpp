// 火柴人联盟.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{

	CPlatForm::Getinstance()->run();

	return 0;

}









