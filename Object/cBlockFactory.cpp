#include "../stdafx.h"
#include "cBlockFactory.h"
#include "../BasicObject/cCubeNode.h"

cBlockFactory::cBlockFactory(int yCount)
	:m_iYcount(yCount)
{
}

cBlockFactory::~cBlockFactory()
{
	for(auto& i : m_vecBlocks)
		i->Destroy();
}

void cBlockFactory::Setup()
{
	CreateLine();
	CreateRect();
	CreateZigzag();
	CreateTwist();

	for (auto& i : m_vecBlocks)
	{
		i->SetColor(0xf0a0a0a0);
	}
}

cCubeNode* cBlockFactory::Change(D3DXMATRIXA16* parentWorld)
{
	auto temp = m_vecBlocks[rand() % m_vecBlocks.size()];
	temp->SetParentWorldTM(parentWorld);

	return temp;
}

void cBlockFactory::CreateNode(D3DXVECTOR3 pos, cCubeNode * parent)
{
	auto node = new cCubeNode(pos);
	node->Setup();
	parent->AddChild(node);
}

void cBlockFactory::CreateLine()
{
	auto node = new cCubeNode({ 0,(float)m_iYcount,0 });
	node->Setup();

	CreateNode({ -1,(float)m_iYcount,0 }, node);
	CreateNode({ 1,(float)m_iYcount,0 }, node);
	CreateNode({ -2,(float)m_iYcount,0 }, node);

	m_vecBlocks.push_back(node);
}

void cBlockFactory::CreateRect()
{
	auto node = new cCubeNode({ 0,(float)m_iYcount,0 });
	node->Setup();

	CreateNode({ 1,(float)m_iYcount,0 }, node);
	CreateNode({ 1,(float)m_iYcount,1 }, node);
	CreateNode({ 0,(float)m_iYcount,1 }, node);

	m_vecBlocks.push_back(node);
}

void cBlockFactory::CreateZigzag()
{
	auto node = new cCubeNode({ 0,(float)m_iYcount,0 });
	node->Setup();

	CreateNode({ 0,(float)m_iYcount,1 }, node);
	CreateNode({ 1,(float)m_iYcount,1 }, node);
	CreateNode({ -1,(float)m_iYcount,0 }, node);

	m_vecBlocks.push_back(node);
}

void cBlockFactory::CreateTwist()
{
	auto node = new cCubeNode({ 0,(float)m_iYcount,0 });
	node->Setup();

	CreateNode({ 1,(float)m_iYcount,0 }, node);
	CreateNode({ 1,(float)m_iYcount + 1,0 }, node);
	CreateNode({ 0,(float)m_iYcount,-1 }, node);

	m_vecBlocks.push_back(node);
}

void cBlockFactory::CreateSmallLine()
{
}
