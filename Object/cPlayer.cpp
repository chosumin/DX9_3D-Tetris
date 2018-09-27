#include "../stdafx.h"
#include "cPlayer.h"
#include "../BasicObject/cCubeNode.h"
#include "../Grid/cArray.h"
#include "cCommand.h"
#include "cBlockFactory.h"

cPlayer::cPlayer(cArray* array)
	:m_pArray(array)
{
}

cPlayer::~cPlayer()
{
	SAFE_DELETE(m_pCommand);
	SAFE_DELETE(m_pFactory);
}

void cPlayer::Setup()
{
	m_pFactory = new cBlockFactory(m_pArray->GetYcount());
	m_pFactory->Setup();

	m_pCommand = new cCommand();

	m_pBlock = m_pFactory->Change(&m_pCommand->World);
}

void cPlayer::Update()
{
	bool key =	m_pCommand->DirectionKeyDown() ? true :
				m_pCommand->RotationKeyDown();

	//위치 조정
	m_pCommand->UpdateWorld();
	m_pBlock->Update();

	//블록과 충돌 혹은 맨 밑에 도착
	if (m_pBlock->IsIntersect(m_pArray->GetArray())
		|| m_pBlock->IsOutOfArray(m_pArray->GetXcount()
		, m_pArray->GetYcount(), m_pArray->GetZcount()))
	{
		//받은 회전과 디렉션을 * -1 => 반대로 움직여줌
		m_pCommand->Reflect();

		//위치 재조정
		OffsetPlayerBlock();

		IntersectWidthArray();
	}

	m_pCommand->ResetRotAndDir();
}

void cPlayer::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	m_pBlock->Render();
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void cPlayer::IntersectWidthArray()
{
	auto direction = m_pCommand->Direction;
	auto angle = m_pCommand->Angle;

	//현재 블록이 배열에 추가되어야 함.
	if (fabs(direction.y) > D3DX_16F_EPSILON)
	{
		m_pArray->IntersectProcess(m_pBlock);
	
		//플레이어 블록 모양 변경
		m_pBlock = m_pFactory->Change(&m_pCommand->World);

		//위치 리셋
		m_pCommand->ResetPosition();
	}
}

void cPlayer::OffsetPlayerBlock()
{
	while (m_pArray->IsIntersect(m_pBlock)
		   || m_pBlock->IsOutOfArray(m_pArray->GetXcount()
		   , m_pArray->GetYcount(), m_pArray->GetZcount()))
	{
		m_pCommand->UpdateWorld();
		m_pBlock->Update();
	}
}
