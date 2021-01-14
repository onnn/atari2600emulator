#pragma once

class UI {


public:
	UI();
	~UI();

	//register window class and call methods for
	//instantiating drawing resources
	HRESULT InitWindowsApp();

	//process and dispatch messages
	void Run();

private:
	
	HRESULT CreateDeviceIndependentResources();

	//initialize device depedent resources
	HRESULT CreateDeviceResources();

	void DiscardDeviceResources();

	//draw content
	HRESULT OnRender();

	void OnResize(UINT width, UINT height);

	//the windows procedure
	static LRESULT CALLBACK WndProc(
		HWND hWnd, UINT message, WPARAM wParam,
		LPARAM lParam);

	HWND m_hwnd;
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
	ID2D1SolidColorBrush* m_pCornflowerBlueBrush;
};
