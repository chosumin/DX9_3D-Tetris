#include "../stdafx.h"
#include "cCubePC.h"

cCubePC::cCubePC()
{
}

cCubePC::~cCubePC()
{
}

void cCubePC::Setup()
{
	vector<ST_PC_VERTEX> vecVertex;
	vecVertex.resize(8);

	vecVertex[0].p = { -0.5f,-0.5f,-0.5f };
	vecVertex[1].p = { -0.5f, 0.5f,-0.5f };
	vecVertex[2].p = { 0.5f, 0.5f,-0.5f };
	vecVertex[3].p = { 0.5f,-0.5f,-0.5f };
	vecVertex[4].p = { -0.5f,-0.5f, 0.5f };
	vecVertex[5].p = { -0.5f, 0.5f, 0.5f };
	vecVertex[6].p = { 0.5f, 0.5f, 0.5f };
	vecVertex[7].p = { 0.5f,-0.5f, 0.5f };

	vector<DWORD> vecIndex;
	// : front
	vecIndex.push_back(0);
	vecIndex.push_back(1);
	vecIndex.push_back(2);

	vecIndex.push_back(0);
	vecIndex.push_back(2);
	vecIndex.push_back(3);

	// : back
	vecIndex.push_back(7);
	vecIndex.push_back(6);
	vecIndex.push_back(5);

	vecIndex.push_back(7);
	vecIndex.push_back(5);
	vecIndex.push_back(4);

	// : left
	vecIndex.push_back(4);
	vecIndex.push_back(5);
	vecIndex.push_back(1);

	vecIndex.push_back(4);
	vecIndex.push_back(1);
	vecIndex.push_back(0);

	// : right
	vecIndex.push_back(3);
	vecIndex.push_back(2);
	vecIndex.push_back(6);

	vecIndex.push_back(3);
	vecIndex.push_back(6);
	vecIndex.push_back(7);

	// : top
	vecIndex.push_back(1);
	vecIndex.push_back(5);
	vecIndex.push_back(6);

	vecIndex.push_back(1);
	vecIndex.push_back(6);
	vecIndex.push_back(2);

	// : bottom
	vecIndex.push_back(4);
	vecIndex.push_back(0);
	vecIndex.push_back(3);

	vecIndex.push_back(4);
	vecIndex.push_back(3);
	vecIndex.push_back(7);

	m_vecVertex.resize(36);

	for (size_t i = 0; i < vecIndex.size(); i += 3)
	{
		m_vecVertex[i + 0] = vecVertex[vecIndex[i + 0]];
		m_vecVertex[i + 1] = vecVertex[vecIndex[i + 1]];
		m_vecVertex[i + 2] = vecVertex[vecIndex[i + 2]];
	}
}

void cCubePC::Render()
{
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
								  m_vecVertex.size() / 3,
								  &m_vecVertex[0],
								  sizeof(ST_PC_VERTEX));
}