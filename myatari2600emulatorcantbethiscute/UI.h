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

	static HWND m_hwnd;
	static HWND m_handleForMemoryViewerWindow;
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
	ID2D1SolidColorBrush* m_pCornflowerBlueBrush;
	ID2D1SolidColorBrush* m_pBlackBrush;
	IDWriteFactory* pDWriteFactory_;
	IDWriteTextFormat* pTextFormat_;
	static WNDCLASSEX videoWindowClass;
	static WNDCLASSEX memoryViewerWindowClass;

	const wchar_t* wszText_;
	UINT32 cTextLength_;
	bool videoWindowOpen;
	bool memoryViewerWindowOpen;
	bool videoWindowWindowClassCreated;
	bool memoryViewerWindowClassCreated;

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
	static LRESULT CALLBACK WndProcForMemoryViewer(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

	
	static void AddMenus(HWND hwnd);
	static void createMemoryViewerWindow(WNDCLASSEX& wc, HWND& hwnd, HINSTANCE hInst, int nShowCmd);


};
