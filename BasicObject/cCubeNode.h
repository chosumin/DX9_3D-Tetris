#pragma once
#include "cCubePC.h"

class cCubeNode;
using Arr = cCubeNode * (*)[m_xCount][m_zCount];

class cCubeNode : public cCubePC
{
public:
	cCubeNode(D3DXVECTOR3 translation);
	~cCubeNode();
public:
	virtual void Setup() override;
	void Update();
	virtual void Render() override;

	virtual void AddChild(cCubeNode* pChild);
	virtual void Destroy();

	bool IsIntersect(cCubeNode* node) const;
	bool IsIntersect(vector<cCubeNode*>& nodes) const;
	bool IsIntersect(Arr nodes) const;
	bool IsIntersect(D3DXVECTOR3 coord) const;

	bool IncludesYCoord(int yCount);
	bool IsOutOfArray(int xCount, int yCount, int zCount);

	void Clone(OUT Arr& arr);

	void SetColor(D3DXCOLOR color);
public:
	const D3DXMATRIXA16&		GetWorld() const;
	const D3DXVECTOR3			GetTransformCoord() const;
	const vector<cCubeNode*>&	GetChild() const;
	float						GetY();
protected:
	D3DXMATRIXA16	m_matLocalTM;
	D3DXMATRIXA16	m_matWorldTM;

	vector<cCubeNode*> m_vecChild;

	SYNTHESIZE(D3DXVECTOR3, m_vLocalPos, LocalPos);
	SYNTHESIZE(D3DXMATRIXA16*, m_pParentWorldTM, ParentWorldTM);
};