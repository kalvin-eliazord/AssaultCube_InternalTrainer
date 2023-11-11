#include "header.h"

Vector3 Aimbot::CalculateAngles(Player* pEntity)
{
	Vector3 calculatedAngles{};

	Player* localPlayer{ MemManager::GetLocalPlayer() };

	const Vector3 delta{ GetDelta(localPlayer->m_HeadCoords, pEntity->m_HeadCoords) };

	// yaw
	calculatedAngles.x = ::atan2f(delta.y, delta.x) * (57.29577951307855); // converting rad to degree
	// pitch
	calculatedAngles.y = ::asinf(GetMagnitude(delta)) * (57.29577951307855);

	while (calculatedAngles.x > 360.0f)
		calculatedAngles.x = 0.0f;

	while (calculatedAngles.x < 0.0f)
		calculatedAngles.x = 360.0f;

	if (calculatedAngles.y > 90.0f)
		calculatedAngles.y = 90.0f;

	if (calculatedAngles.y < 0.0f)
		calculatedAngles.y = 0.0f;
	
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