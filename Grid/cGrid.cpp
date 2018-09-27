#include "../stdafx.h"
#include "cGrid.h"

cGrid::cGrid()
{
	D3DXMatrixIdentity(&m_matWorld);
}

cGrid::~cGrid()
{
}

void cGrid::Setup(D3DXVECTOR3 center, D3DXVECTOR3 nNumHalfTile,
				  int deltaX, int deltaY, int deltaZ)
{
	int xMax = (int)nNumHalfTile.x * deltaX;
	int yMax = (int)nNumHalfTile.y * deltaY;
	int zMax = (int)nNumHalfTile.z * deltaZ;

	if (deltaX == 0)
	{
		CreateVertexLRY(center, (int)nNumHalfTile.y, zMax);
		CreateVertexLRZ(center, (int)nNumHalfTile.z, yMax);
	}
	else if (deltaY == 0)
	{
		CreateVertexTBX(center, (int)nNumHalfTile.x, zMax);
		CreateVertexTBZ(center, (int)nNumHalfTile.z, xMax);
	}
	else if (deltaZ == 0)
	{
		CreateVertexFBY(center, (int)nNumHalfTile.y, xMax);
		CreateVertexFBX(center, (int)nNumHalfTile.x, yMax);
	}

	for (auto& i : m_vecVertex)
	{
		i.c = ParseColor((int)(i.p.y - 0.5f));
	}
}

void cGrid::Update()
{
}

void cGrid::Render()
{
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST,
								  m_vecVertex.size() / 2,
								  &m_vecVertex[0],
								  sizeof(ST_PC_VERTEX));
}

void cGrid::CreateVertexTBX(D3DXVECTOR3 center, int nNumHalfTile, int max)
{
	ST_PC_VERTEX v;

	for (int i = 0; i <= nNumHalfTile; i++)
	{
		v.p = D3DXVECTOR3(center.x + i, center.y, max + center.z); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(center.x + i, center.y, -max + center.z); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(center.x - i, center.y, max + center.z); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(center.x - i, center.y, -max + center.z); m_vecVertex.push_back(v);
	}
}

void cGrid::CreateVertexFBX(D3DXVECTOR3 center, int nNumHalfTile, int max)
{
	ST_PC_VERTEX v;

	for (int i = 0; i <= nNumHalfTile; i++)
	{
		v.p = D3DXVECTOR3(center.x + i, max + center.y, center.z); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(center.x + i, -max + center.y, center.z); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(center.x - i, max + center.y, center.z); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(center.x - i, -max + center.y, center.z); m_vecVertex.push_back(v);
	}
}

void cGrid::CreateVertexLRY(D3DXVECTOR3 center, int nNumHalfTile, int max)
{
	ST_PC_VERTEX v;

	for (int i = 0; i <= nNumHalfTile; i++)
	{
		v.p = D3DXVECTOR3(center.x, center.y + i, max + center.z); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(center.x, center.y + i, -max + center.z); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(center.x, center.y - i, max + center.z); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(center.x, center.y - i, -max + center.z); m_vecVertex.push_back(v);
	}
}

void cGrid::CreateVertexFBY(D3DXVECTOR3 center, int nNumHalfTile, int max)
{
	ST_PC_VERTEX v;

	for (int i = 0; i <= nNumHalfTile; i++)
	{
		v.p = D3DXVECTOR3(max + center.x, center.y + i, center.z); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-max + center.x, center.y + i, center.z); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(max + center.x, center.y - i, center.z); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-max + center.x, center.y - i, center.z); m_vecVertex.push_back(v);
	}
}

void cGrid::CreateVertexTBZ(D3DXVECTOR3 center, int nNumHalfTile, int max)
{
	ST_PC_VERTEX v;

	for (int i = 0; i <= nNumHalfTile; i++)
	{
		v.p = D3DXVECTOR3(max + center.x, center.y, center.z + i); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-max + center.x, center.y, center.z + i); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(max + center.x, center.y, center.z - i); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(-max + center.x, center.y, center.z - i); m_vecVertex.push_back(v);
	}
}

void cGrid::CreateVertexLRZ(D3DXVECTOR3 center, int nNumHalfTile, int max)
{
	ST_PC_VERTEX v;

	for (int i = 0; i <= nNumHalfTile; i++)
	{
		v.p = D3DXVECTOR3(center.x, max + center.y, center.z + i); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(center.x, -max + center.y, center.z + i); m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(center.x, max + center.y, center.z - i); m_vecVertex.push_back(v);
		v.p = D3DXVECTOR3(center.x, -max + center.y, center.z - i); m_vecVertex.push_back(v);
	}
}

D3DXCOLOR cGrid::ParseColor(int y)
{
	switch (y)
	{
		case 0:	return 0xffff0000;
		case 1:	return 0xff00ff00;
		case 2: return 0xff0000ff;
		case 3: return 0xffffff00;
		case 4: return 0xff00ffff;
		case 5: return 0xffff00ff;
		case 6: return 0xffffffff;
		case 7: return 0xffff7f00;
	}

	return 0xffffffff;
}
