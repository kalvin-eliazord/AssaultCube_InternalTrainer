#pragma once
namespace Aimbot
{
	Vector3 CalculateAngles(Entity* pEntity);
	Vector3 GetDelta(Vector3 pCoords1, Vector3 pCoords2);
	float   GetMagnitude(Vector3 pDelta);
};