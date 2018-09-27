#include "../stdafx.h"
#include "cDeviceManager.h"

cDeviceManager::cDeviceManager()
{
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;

	//m_pD3D create
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	HRESULT hr;

	//GetDeviceCaps
	D3DCAPS9 stCaps;
	int nVertexProcessing;
	hr = m_pD3D->GetDeviceCaps
	(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		&stCaps
	);
	assert(SUCCEEDED(hr));

	if (stCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		nVertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	else
		nVertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	//D3DPP
	D3DPRESENT_PARAMETERS stD3DPP;
	ZeroMemory(&stD3DPP, sizeof(D3DPRESENT_PARAMETERS));
	stD3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	stD3DPP.Windowed = true; //âȭ��, false - ��üȭ��
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN; //�˾Ƽ� ���� �����ض�
	stD3DPP.EnableAutoDepthStencil = true;
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D16; //���� ����, �ϴ� �뷮 ���� ��Ƴ���
	stD3DPP.BackBufferWidth = 800;

	//CreateDevice
	hr = m_pD3D->CreateDevice
	(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd,
		nVertexProcessing,
		&stD3DPP,
		&m_pD3DDevice
	);
	assert(SUCCEEDED(hr));
}


cDeviceManager::~cDeviceManager()
{
}

LPDIRECT3DDEVICE9 cDeviceManager::GetDevice()
{
	return m_pD3DDevice;
}

void cDeviceManager::Destroy()
{
	auto ul = m_pD3DDevice->Release();
#ifdef _DEBUG
	assert(ul == 0 && "����̽��̿� ������ ��ü�� �������� ���� ��ü ����");
#endif
	SAFE_RELEASE(m_pD3D);
}
