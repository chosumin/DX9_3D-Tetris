#pragma once

class cCubeNode;
class cCubeMan
{
public:
	cCubeMan();
	~cCubeMan();
public:
	virtual void Setup();
	virtual void Update();
	virtual void Render();
private:
	void AddChild(cCubeNode* node, float deltaX);
public:
	static D3DXVECTOR2	g_vSize;
protected:
	cCubeNode *		m_pRoot;
	LPDIRECT3DTEXTURE9	m_pTexture;
};