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

	//��ġ ����
	m_pCommand->UpdateWorld();
	m_pBlock->Update();

	//��ϰ� �浹 Ȥ�� �� �ؿ� ����
	if (m_pBlock->IsIntersect(m_pArray->GetArray())
		|| m_pBlock->IsOutOfArray(m_pArray->GetXcount()
		, m_pArray->GetYcount(), m_pArray->GetZcount()))
	{
		//���� ȸ���� �𷺼��� * -1 => �ݴ�� ��������
		m_pCommand->Reflect();

		//��ġ ������
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

	//���� ����� �迭�� �߰��Ǿ�� ��.
	if (fabs(direction.y) > D3DX_16F_EPSILON)
	{
		m_pArray->IntersectProcess(m_pBlock);
	
		//�÷��̾� ��� ��� ����
		m_pBlock = m_pFactory->Change(&m_pCommand->World);

		//��ġ ����
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
