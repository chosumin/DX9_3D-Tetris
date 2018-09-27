#pragma once

class cCamera;
class cBackground;
class cPlayer;
class cMainGame
{
public:
	cMainGame();
	~cMainGame();
public:
	void Setup();
	void Update();
	void BeginScene();
	void Render();
	void EndScene();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
private:
	cCamera*		m_pCamera;
	cBackground*	m_pBackground;
	cPlayer*		m_pPlayer;
};