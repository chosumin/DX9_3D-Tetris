#pragma once

class cGrid;
class cArray;
class cBackground
{
public:
	cBackground();
	~cBackground();
public:
	void Setup();
	void Render();

	cArray* GetArray() const;

	bool IsGameOver();
private:
	void CreateGrid(D3DXVECTOR3 center, D3DXVECTOR3 numHalfTile
					, int deltaX, int deltaY, int deltaZ);
private:
	vector<cGrid*>	m_vecGrid;
	cArray*			m_pArray;
};