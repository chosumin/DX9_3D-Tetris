#pragma once

class cCubeNode;
class cBlockFactory
{
public:
	cBlockFactory(int yCount);
	~cBlockFactory();
public:
	void Setup();
	cCubeNode* Change(D3DXMATRIXA16* parentWorld);
private:
	void CreateNode(D3DXVECTOR3 pos, cCubeNode* parent);
	void CreateLine();
	void CreateRect();
	void CreateZigzag();
	void CreateTwist();
	void CreateSmallLine();
private:
	vector<cCubeNode*>	m_vecBlocks;
	int					m_iYcount;
};