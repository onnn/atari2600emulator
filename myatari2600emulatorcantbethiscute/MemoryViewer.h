#pragma once


class MemoryViewer {

public:
	MemoryViewer();
	~MemoryViewer();

	//register window class and call methods for
	//instantiating drawing resources
	HRESULT InitWindowsApp();

	//process and dispatch messages
	void Run();

private:

	HWND m_hwnd;
	static HWND m_handleForMemoryViewerWindow;
	ID2D1Factory* m_pDirect2dFactory;
	ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1SolidColorBrush* m_pLightSlateGrayBrush;
	ID2D1SolidColorBrush* m_pCornflowerBlueBrush;
	ID2D1SolidColorBrush* m_pBlackBrush;
	IDWriteFactory* pDWriteFactory_;
	IDWriteTextFormat* pTextFormat_;
	static WNDCLASSEX videoWindowClass;

	static const wchar_t* wszText_;
	UINT32 cTextLength_;
	bool videoWindowOpen;
	bool videoWindowWindowClassCreated;

	HRESULT CreateDeviceIndependentResources();

	//initialize device depedent resources
	HRESULT CreateDeviceResources();

	void DiscardDeviceResources();

	//draw content
	HRESULT RenderVideoWindow();

	void OnResize(UINT width, UINT height);

	//the windows procedure
	static LRESULT CALLBACK WndProc(
		HWND hWnd, UINT message, WPARAM wParam,
		LPARAM lParam);


	void AddMenus(HWND hwnd);
	HRESULT OnClick();
	void DisableMenu(HWND hwnd);


};

