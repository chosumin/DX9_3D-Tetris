#include "../stdafx.h"
#include "cCubeNode.h"
#include "../Object/cCubeMan.h"

cCubeNode::cCubeNode(D3DXVECTOR3 translation)
	:m_pParentWorldTM(nullptr), m_vLocalPos(translation)
{
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMatrixIdentity(&m_matWorldTM);
}

cCubeNode::~cCubeNode()
{
}

void cCubeNode::Setup()
{
	cCubePC::Setup();

	D3DXMATRIXA16 matT;
	D3DXMatrixTranslation(&matT, m_vLocalPos.x, m_vLocalPos.y, m_vLocalPos.z);

	for (auto& i : m_vecVertex)
	{
		D3DXVec3TransformCoord(&i.p, &i.p, &matT);
	}
}

void cCubeNode::Update()
{
	D3DXMATRIXA16 matR, matT;
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	m_matLocalTM = matR * matT;
	m_matWorldTM = m_matLocalTM;

	if (m_pParentWorldTM)
		m_matWorldTM *= *m_pParentWorldTM;

	for (auto p : m_vecChild)
		p->Update();
}

void cCubeNode::Render()
{
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
	cCubePC::Render();
	for (auto p : m_vecChild)
		p->Render();
}

void cCubeNode::AddChild(cCubeNode * pChild)
{
	pChild->m_pParentWorldTM = &m_matWorldTM;
	m_vecChild.push_back(pChild);
}

void cCubeNode::Destroy()
{
	for (auto& p : m_vecChild)
	{
		p->Destroy();
	}

	delete this;
}

const D3DXMATRIXA16 & cCubeNode::GetWorld() const
{
	return m_matLocalTM;
}

bool cCubeNode::IsIntersect(cCubeNode * node) const
{
	//현재 좌표와 받아온 노드의 모든 좌표와 충돌 체크
	auto vec = GetTransformCoord();
	bool isIntersect = node->IsIntersect(vec);

	//자식 좌표와 받아온 노드의 모든 
	for (auto i : m_vecChild)
	{
		isIntersect |= i->IsIntersect(node);
	}

	return isIntersect;
}

bool cCubeNode::IsIntersect(vector<cCubeNode*>& nodes) const
{
	bool isIntersect = false;

	for (auto i : nodes)
	{
		isIntersect |= IsIntersect(i);
	}

	return isIntersect;
}

bool cCubeNode::IsIntersect(Arr nodes) const
{
	bool isIntersect = false;
	for (auto y = 0; y < m_yCount; y++)
	{
		for (auto x = 0; x < m_xCount; x++)
		{
			for (auto z = 0; z < m_zCount; z++)
			{
				cCubeNode* node = nodes[y][x][z];
				if(node)
					isIntersect |= IsIntersect(node);
			}
		}
	}

	return isIntersect;
}

bool cCubeNode::IsIntersect(D3DXVECTOR3 coord) const
{
	auto vec = GetTransformCoord();

	bool isIntersect = fabs(vec.x - coord.x) <= D3DX_16F_EPSILON;

	isIntersect &= fabs(vec.y - coord.y) <= D3DX_16F_EPSILON;

	isIntersect &= fabs(vec.z - coord.z) <= D3DX_16F_EPSILON;

	for (auto i : m_vecChild)
	{
		isIntersect |= i->IsIntersect(coord);
	}

	return isIntersect;
}

bool cCubeNode::IncludesYCoord(int yCount)
{
	D3DXVECTOR3 vec;
	D3DXVec3TransformCoord(&vec, &m_vLocalPos, &m_matWorldTM);

	bool flag = fabs(vec.y - yCount) <= D3DX_16F_EPSILON;

	for (auto i : m_vecChild)
	{
		flag |= i->IncludesYCoord(yCount);
	}

	if (flag)
	{
		cout << m_matWorldTM._42 << " ";
		for (auto i : m_vecChild)
			cout << i->GetY() << " ";
		cout << endl;
	}
	return flag;
}

bool cCubeNode::IsOutOfArray(int xCount, int yCount, int zCount)
{
	auto vec = GetTransformCoord();
	bool out = IncludesYCoord(-1);
	out |= vec.x > (xCount / 2 - 1) || vec.x < (-xCount / 2);
	out |= vec.z > (zCount / 2 - 1) || vec.z < (-zCount / 2);

	for (auto i : m_vecChild)
	{
		out |= i->IsOutOfArray(xCount, yCount, zCount);
	}

	return out;
}

void cCubeNode::Clone(OUT Arr & arr)
{
	auto vec = GetTransformCoord();
	int outX = (int)(vec.x < 0.0f ? vec.x - 0.5f : vec.x + 0.5f);
	int outY = (int)(vec.y < 0.0f ? vec.y - 0.5f : vec.y + 0.5f);
	int outZ = (int)(vec.z < 0.0f ? vec.z - 0.5f : vec.z + 0.5f);

	float x = (float)outX;
	float y = (float)outY;
	float z = (float)outZ;
	auto node = new cCubeNode({ x, y, z });
	node->Setup();

	arr[outY][outX + m_xCount / 2][outZ + m_zCount / 2] = node;

	for (auto& i : m_vecChild)
	{
		i->Clone(arr);
	}
}

void cCubeNode::SetColor(D3DXCOLOR color)
{
	for (auto& i : m_vecVertex)
	{
		i.c = color;
	}

	for (auto i : m_vecChild)
	{
		i->SetColor(color);
	}
}

float cCubeNode::GetY()
{
	return m_matWorldTM._42;
}

const D3DXVECTOR3 cCubeNode::GetTransformCoord() const
{
	D3DXVECTOR3 vec;
	D3DXVec3TransformCoord(&vec, &m_vLocalPos, &m_matWorldTM);
	return vec;
}

const vector<cCubeNode*>& cCubeNode::GetChild() const
{
	return m_vecChild;
}