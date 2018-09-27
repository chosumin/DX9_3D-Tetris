#include "../stdafx.h"
#include "cCommand.h"

cCommand::cCommand()
	:Position(0, 0, 0)
	, Direction(0, 0, 0), Rotation(0, 0, 0)
	, Angle(0,0,0), PrevTime(timeGetTime())
	, m_spaceKeyDown(false)
{
	D3DXMatrixIdentity(&World);
}

cCommand::~cCommand()
{
}

bool cCommand::RotationKeyDown()
{
	if (cKeyboard::Get()->KeyDown('Q'))
		Angle.x = 90;
	else if (cKeyboard::Get()->KeyDown('A'))
		Angle.x = -90;

	else if (cKeyboard::Get()->KeyDown('W'))
		Angle.y = 90;
	else if (cKeyboard::Get()->KeyDown('S'))
		Angle.y = -90;

	else if (cKeyboard::Get()->KeyDown('E'))
		Angle.z = 90;
	else if (cKeyboard::Get()->KeyDown('D'))
		Angle.z = -90;
	else
		return false;
	
	return true;
}

bool cCommand::DirectionKeyDown()
{
	auto curTime = timeGetTime();
	if (curTime - PrevTime > 1500)
	{
		Direction.y -= 1.0f;
		PrevTime = curTime;
	}
	else if (cKeyboard::Get()->KeyDown(VK_RIGHT))
		Direction.x += 1.0f;
	else if (cKeyboard::Get()->KeyDown(VK_LEFT))
		Direction.x -= 1.0f;
	else if (cKeyboard::Get()->KeyDown(VK_UP))
		Direction.z += 1.0f;
	else if (cKeyboard::Get()->KeyDown(VK_DOWN))
		Direction.z -= 1.0f;
	else if (cKeyboard::Get()->KeyDown(VK_SPACE))
		Direction.y -= 1.0f;
	else
		return false;

	return true;
}

void cCommand::Reflect()
{
	Direction *= -1.0f;
	Angle *= -1.0f;
}

void cCommand::UpdateWorld()
{
	m_quaternion.w = 
	Rotation.x = Angle.x + (int)Rotation.x % 360;
	Rotation.y = Angle.y + (int)Rotation.y % 360;
	Rotation.z = Angle.z + (int)Rotation.z % 360;

	auto rY = Rotation.y * D3DX_PI / 180;
	auto rZ = Rotation.z * D3DX_PI / 180;
	auto rX = Rotation.x * D3DX_PI / 180;

	Position += Direction;
	D3DXMATRIXA16 matR, matT;
	
	D3DXMATRIXA16 invRT, RT;
	D3DXMatrixTranslation(&invRT, 0, (float)-m_yCount, 0);
	{
		//D3DXMatrixRotationYawPitchRoll(&matR, rY, rX, rZ);
		auto q = CreateQuaternion(rZ, rX, rY);
		D3DXMatrixRotationQuaternion(&matR, &q);
	}
	D3DXMatrixTranslation(&RT, 0, (float)m_yCount, 0);
	matR = invRT * matR * RT;

	D3DXMatrixTranslation(&matT, Position.x, Position.y, Position.z);
	
	World = matR * matT;
}

void cCommand::ResetRotAndDir()
{
	Angle		= { 0,0,0 };
	Direction	= { 0,0,0 };
	m_spaceKeyDown = false;
}

void cCommand::ResetPosition()
{
	Position = { 0, 0, 0 };
}

D3DXQUATERNION cCommand::CreateQuaternion(float roll, float pitch, float yaw) const
{
	D3DXQUATERNION	quaternion;

	float cr, cp, cy, sr, sp, sy, cpcy, spsy;

	// calculate trig identities 

	cr = cos(roll / 2); cp = cos(pitch / 2);
	cy = cos(yaw / 2); sr = sin(roll / 2);
	sp = sin(pitch / 2);
	sy = sin(yaw / 2);
	cpcy = cp * cy;
	spsy = sp * sy;
	quaternion.w = cr * cpcy + sr * spsy;
	quaternion.x = sr * cpcy - cr * spsy;
	quaternion.y = cr * sp * cy + sr * cp * sy;
	quaternion.z = cr * cp * sy - sr * sp * cy;

	return quaternion;
}
