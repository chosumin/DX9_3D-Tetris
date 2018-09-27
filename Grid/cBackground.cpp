#include "../stdafx.h"
#include "cBackground.h"
#include "cGrid.h"
#include "cArray.h"

cBackground::cBackground()
{
}

cBackground::~cBackground()
{
	for (auto& i : m_vecGrid)
		SAFE_DELETE(i);

	SAFE_DELETE(m_pArray);
}

void cBackground::Setup()
{
	CreateGrid({ -0.5f,-0.5f,-0.5f }, { 3,0,3 }, 1, 0, 1);
	CreateGrid({ -3.5f,3.5f,-0.5f }, { 0,4,3 }, 0, 1, 1);
	CreateGrid({ 2.5f,3.5f,-0.5f }, { 0,4,3 }, 0, 1, 1);
	CreateGrid({ -0.5f,3.5f,-3.5f }, { 3,4,0 }, 1, 1, 0);
	CreateGrid({ -0.5f,3.5f,2.5f }, { 3,4,0 }, 1, 1, 0);

	m_pArray = new cArray();
	m_pArray->Setup();
}

void cBackground::Render()
{
	for (auto i : m_vecGrid)
		i->Render();

	m_pArray->Render();
}

cArray * cBackground::GetArray() const
{
	return m_pArray;
}

bool cBackground::IsGameOver()
{
	return m_pArray->CheckGameOver();
}

void cBackground::CreateGrid(D3DXVECTOR3 center, D3DXVECTOR3 numHalfTile
							 , int deltaX, int deltaY, int deltaZ)
{
	auto grid = new cGrid();
	grid->Setup(center, numHalfTile, deltaX, deltaY, deltaZ);
	m_vecGrid.push_back(grid);
}
