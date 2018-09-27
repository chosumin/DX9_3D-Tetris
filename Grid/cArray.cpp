#include "../stdafx.h"
#include "cArray.h"
#include "../BasicObject/cCubeNode.h"

cArray::cArray()
	:m_endCount(8)
{
}

cArray::~cArray()
{
	for (auto y = 0; y < m_yCount; y++)
	{
		for (auto x = 0; x < m_xCount; x++)
		{
			for (auto z = 0; z < m_zCount; z++)
			{
				if (m_Array[y][x][z])
					m_Array[y][x][z]->Destroy();
			}
		}
	}

	SAFE_DELETE_ARRAY(m_Array);
}

void cArray::Setup()
{
	m_Array = new cCubeNode*[m_yCount][m_xCount][m_zCount]();
	for (auto y = 0; y < m_yCount; y++)
	{
		for (auto x = 0; x < m_xCount; x++)
		{
			for (auto z = 0; z < m_zCount; z++)
			{
				m_Array[y][x][z] = nullptr;
			}
		}
	}
}

void cArray::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	for (auto y = 0; y < m_yCount; y++)
	{
		D3DXCOLOR color = ParseColor(y);
		for (auto x = 0; x < m_xCount; x++)
		{
			for (auto z = 0; z < m_zCount; z++)
			{
				if (!m_Array[y][x][z]) continue;

				m_Array[y][x][z]->SetColor(color);
				m_Array[y][x][z]->Render();
			}
		}
	}
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

void cArray::IntersectProcess(cCubeNode * playerBlock)
{
	//받은 블록을 벡터에 추가
	playerBlock->Clone(m_Array);
	
	CheckComplete(); //한칸이 꽉찼는지 확인
	CheckGameOver(); //게임오버 체크
}

bool cArray::IsIntersect(cCubeNode * playerBlock) const
{
	//플레이어 블록과 충돌 판정
	for (auto y = 0; y < m_yCount; y++)
	{
		for (auto x = 0; x < m_xCount; x++)
		{
			for (auto z = 0; z < m_zCount; z++)
			{
				if (!m_Array[y][x][z]) continue;

				if (m_Array[y][x][z]->IsIntersect(playerBlock))
					return true;
			}
		}
	}

	return false;
}

Arr cArray::GetArray()
{
	return m_Array;
}

int cArray::GetYcount() const
{
	return m_yCount;
}

int cArray::GetXcount() const
{
	return m_xCount;
}

int cArray::GetZcount() const
{
	return m_zCount;
}

void cArray::CheckComplete()
{
	while (1)
	{
		int num = TheNumberOfFullFloor();
		//차있는 행 있으면 계속 루프
		if (num == -1) break;
		
		//있으면 지움
		for (int x = 0; x < m_xCount; x++)
		{
			for (int z = 0; z < m_zCount; z++)
			{
				m_Array[num][x][z]->Destroy();
			}
		}

		//블록들을 한칸씩 내림
		for (int y = num + 1; y < m_yCount; y++)
		{
			for (int x = 0; x < m_xCount; x++)
			{
				for (int z = 0; z < m_zCount; z++)
				{
					m_Array[y - 1][x][z] = m_Array[y][x][z];

					if (m_Array[y - 1][x][z] == nullptr) continue;

					m_Array[y - 1][x][z]->SetLocalPos({ (float)(x - m_xCount / 2),(float)y - 1,(float)(z - m_zCount / 2) });
					m_Array[y - 1][x][z]->Setup();
				}
			}
		}
	}
}

bool cArray::CheckGameOver()
{
	for (int x = 0; x < m_xCount; x++)
	{
		for (int z = 0; z < m_zCount; z++)
		{
			if (m_Array[m_endCount][x][z])
				return true;
		}
	}

	return false;
}

int cArray::TheNumberOfFullFloor()
{
	for (auto y = 0; y < m_yCount; y++)
	{
		int count = 0;
		for (auto x = 0; x < m_xCount; x++)
		{
			for (auto z = 0; z < m_zCount; z++)
			{
				count += m_Array[y][x][z] != nullptr ? 1 : 0;
			}
		}

		if (count >= m_zCount * m_xCount)
			return y;
	}

	return -1;
}

D3DXCOLOR cArray::ParseColor(int y)
{
	switch (y)
	{
		case 0:	return 0xa0ff0000;
		case 1:	return 0xa000ff00;
		case 2: return 0xa00000ff;
		case 3: return 0xa0ffff00;
		case 4: return 0xa000ffff;
		case 5: return 0xa0ff00ff;
		case 6: return 0xa0ffffff;
		case 7: return 0xa0ff7f00;
	}

	return 0xffffffff;
}
