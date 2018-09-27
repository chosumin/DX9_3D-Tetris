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
	stD3DPP.Windowed = true; //창화면, false - 전체화면
	stD3DPP.BackBufferFormat = D3DFMT_UNKNOWN; //알아서 포맷 설정해라
	stD3DPP.EnableAutoDepthStencil = true;
	stD3DPP.AutoDepthStencilFormat = D3DFMT_D16; //깊이 포맷, 일단 용량 적게 잡아놓음
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
	assert(ul == 0 && "디바이스이용 생성된 객체중 해제되지 않은 객체 있음");
#endif
	SAFE_RELEASE(m_pD3D);
}
