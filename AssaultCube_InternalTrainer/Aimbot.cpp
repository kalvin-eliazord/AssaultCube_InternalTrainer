#include "header.h"

Vector3 Aimbot::CalculateAngles(Player* pEntity)
{
	Vector3 calculatedAngles{};

	Player* localPlayer{ MemManager::GetLocalPlayer() };

	//get Delta
	const Vector3 delta{ GetDelta(localPlayer->m_Coords, pEntity->m_Coords) };

	// NEED TO GRASP THE CONCEPT OF TRIG
	//calculatedAngles.x = ::atan2f(delta.y, delta.x);
	//calculatedAngles.y = ::asinf(GetMagnitude(delta));

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