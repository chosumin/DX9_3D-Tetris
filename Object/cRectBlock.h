#pragma once
#include "../BasicObject/cCubeNode.h"

class cRectBlock : public cCubeNode
{
public:
	cRectBlock(D3DXVECTOR3 translation);
	~cRectBlock();
public:
	void Setup() override;
};