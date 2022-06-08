#pragma once

#include<Windows.h>

//WindowsAPI
class WinApp
{
public:
	static const int window_width = 1280;//����
	static const int window_height = 720;//�c��
public:
	static LRESULT WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
public:
	~WinApp();
	void Initialize();
	bool Update();
	const HWND& GetHwnd(){ return hwnd; }
	const WNDCLASSEX& GetWndClass(){ return wndClass; }
	int GetWindowWidth() { return window_width; }
	int GetWindowHeight() { return window_height; }
private:
	HWND hwnd = nullptr;	//�E�B���h�E�n���h��
	WNDCLASSEX wndClass{};	//�E�B���h�E�N���X
	MSG msg{}; //���b�Z�[�W

};

