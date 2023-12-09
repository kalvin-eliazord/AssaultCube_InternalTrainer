#pragma once
namespace Aimbot
{
	void    RunAimbot();
	Vector3 CalculateAnglesOf(Entity* pEntity);
	Vector3 GetDelta(Vector3 pCoords1, Vector3 pCoords2);
	float   GetMagnitude(Vector3 pDelta);
};