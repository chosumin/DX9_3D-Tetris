#include "../stdafx.h"
#include "cRectBlock.h"
#include "../BasicObject/cCubeNode.h"
#include "cCommand.h"

cRectBlock::cRectBlock(D3DXVECTOR3 translation)
	:cCubeNode(translation)
{
}

cRectBlock::~cRectBlock()
{
}

void cRectBlock::Setup()
{
	cCubeNode::Setup();

	auto node1 = new cCubeNode({ 1,8,0 });
	node1->Setup();
	AddChild(node1);
	auto node2 = new cCubeNode({ 1,8,1 });
	node2->Setup();
	AddChild(node2);
	auto node3 = new cCubeNode({ 0,8,1 });
	node3->Setup();
	AddChild(node3);
}
