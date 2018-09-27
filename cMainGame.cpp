#include "stdafx.h"
#include "cMainGame.h"
#include "./Grid/cBackground.h"
#include "./Object/cPlayer.h"

cMainGame::cMainGame()
	:m_pCamera(nullptr), m_pBackground(nullptr), m_pPlayer(nullptr)
{
}


cMainGame::~cMainGame()
{
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pBackground);
}

void cMainGame::Setup()
{
	m_pCamera = new cCamera();
	m_pCamera->Setup(nullptr);

	m_pBackground = new cBackground();
	m_pBackground->Setup();

	m_pPlayer = new cPlayer(m_pBackground->GetArray());
	m_pPlayer->Setup();

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
}

void cMainGame::Update()
{
	if (m_pBackground->IsGameOver())
		return;
	m_pPlayer->Update();
	m_pCamera->Update();
}

void cMainGame::BeginScene()
{
	g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
						0xff000000, 1.0f, 0);
	g_pD3DDevice->BeginScene();
}

void cMainGame::Render()
{
	m_pBackground->Render();

	m_pPlayer->Render();
}

void cMainGame::EndScene()
{
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(0, 0, 0, 0);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	m_pCamera->WndProc(hWnd, message, wParam, lParam);
}
