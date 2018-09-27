#include "../stdafx.h"
#include "cCubeMan.h"

D3DXVECTOR2 cCubeMan::g_vSize = { 63,63 };

cCubeMan::cCubeMan()
	:m_pRoot(nullptr), m_pTexture(nullptr)
{
}

cCubeMan::~cCubeMan()
{
	//m_pRoot->Destroy();
	//SAFE_RELEASE(m_pTexture);
}

void cCubeMan::Setup()
{
	//D3DXCreateTextureFromFile(g_pD3DDevice, L"mine2.png", &m_pTexture);
	//cCharacter::Setup();
	//auto pBody = new cBody();
	//pBody->Setup();
	//pBody->SetParentWorldTM(&m_matWorld);
	//m_pRoot = pBody;

	//AddChild(new cHead(), 0);
	//AddChild(new cLeftArm(), -0.1f);
	//AddChild(new cRightArm(), 0.1f);
	//AddChild(new cLeftLeg(), 0.1f);
	//AddChild(new cRightLeg(), -0.1f);
}

void cCubeMan::Update()
{
	//cCharacter::Update();

	//if (m_pRoot)
	//	m_pRoot->Update(m_isWalk);
}

void cCubeMan::Render()
{
	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	//cCharacter::Render();

	//D3DXMATRIXA16 matWorld;
	//D3DXMatrixIdentity(&matWorld);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	//g_pD3DDevice->SetTexture(0, m_pTexture);
	//m_pRoot->Render();
	//g_pD3DDevice->SetTexture(0, nullptr);
}

void cCubeMan::AddChild(cCubeNode * node, float deltaX)
{
	//node->Setup();
	//node->SetRotDeltaX(deltaX);
	//m_pRoot->AddChild(node);
}
