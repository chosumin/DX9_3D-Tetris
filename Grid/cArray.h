#pragma once

class cCubeNode;
using Arr = cCubeNode * (*)[m_xCount][m_zCount];

class cBlock;
class cArray
{
public:
	cArray();
	~cArray();
public:
	void Setup();
	void Render();

	void IntersectProcess(cCubeNode* playerBlock);
	bool IsIntersect(cCubeNode* playerBlock) const;

	Arr GetArray();

	int GetYcount() const;
	int GetXcount() const;
	int GetZcount() const;

	bool CheckGameOver();
private:
	void CheckComplete();
	
	int TheNumberOfFullFloor();

	D3DXCOLOR ParseColor(int y);
private:
	Arr m_Array;
	int	m_endCount;
};