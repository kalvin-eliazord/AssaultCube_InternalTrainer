#include "header.h"

Vector3 Aimbot::CalculateAngles(Player* pEntity)
{
	Vector3 calculatedAngles{};

	Player* localPlayer{ MemManager::GetLocalPlayer() };

	const Vector3 delta{ GetDelta(localPlayer->m_HeadCoords, pEntity->m_HeadCoords) };

	// use atan2f y/x
	calculatedAngles.x = ::atanf(delta.x / delta.y) * -57.2957795f;
	// use asinf
	calculatedAngles.y = ::atanf(delta.z / ::sqrtf(
		delta.x * delta.x + delta.y * delta.y))
		* -57.2957795f;

	if (delta.y < 0.0f)
		calculatedAngles.x += 180.0f;

	while (calculatedAngles.x < 0.0f)
		calculatedAngles.x += 360.f;

	while (calculatedAngles.x >= 360.0f)
		calculatedAngles.x -= 360.0f;

	calculatedAngles.y = std::clamp(calculatedAngles.y, -90.0f, 90.0f);
	
	return calculatedAngles;
}

Vector3 Aimbot::GetDelta(Vector3 pCoords1, Vector3 pCoords2)
{
	return { (pCoords1.x - pCoords2.x)
		  ,(pCoords1.y - pCoords2.y)
		  ,(pCoords1.z - pCoords2.z) };
}

float Aimbot::GetMagnitude(Vector3 pDelta)
{
	return ::sqrtf(pDelta.x * pDelta.x 
		 + pDelta.y * pDelta.y 
		 + pDelta.z * pDelta.z);
}