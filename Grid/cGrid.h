#pragma once

class cGrid
{
public:
	cGrid();
	~cGrid();
public:
	void Setup(D3DXVECTOR3 center, D3DXVECTOR3 nNumHalfTile,
			   int deltaX, int deltaY, int deltaZ);
	void Update();
	void Render();
private:
	void CreateVertexTBX(D3DXVECTOR3 center, int nNumHalfTile, int max);
	void CreateVertexFBX(D3DXVECTOR3 center, int nNumHalfTile, int max);
	void CreateVertexLRY(D3DXVECTOR3 center, int nNumHalfTile, int max);
	void CreateVertexFBY(D3DXVECTOR3 center, int nNumHalfTile, int max);
	void CreateVertexTBZ(D3DXVECTOR3 center, int nNumHalfTile, int max);
	void CreateVertexLRZ(D3DXVECTOR3 center, int nNumHalfTile, int max);

	D3DXCOLOR ParseColor(int y);
private:
	D3DXMATRIXA16 m_matWorld;
	vector<ST_PC_VERTEX>	m_vecVertex;
};