#include "header.h"

void Aimbot::RunAimbot()
{
    // start AIMBOT //

    Entity* localPlayer{ EntityManager::GetLocalPlayerAddr() };

    bool  bTargetFound   { false };
    float closestDistance{ 1000000.0f };
    float currentDistance{ NULL };
    int   entityDistIndex{ -1 };

      // iterate all the entities to find the closest 
    for (int i{ 1 }; i < *EntityManager::GetNumberOfPlayer(); ++i)
    {
        Entity* entity{ EntityManager::GetEntity(i) };

        if (!EntityManager::IsValid(entity))
            continue;

        const Vector3 delta{ Aimbot::GetDelta(entity->m_Coords, localPlayer->m_Coords) };

        currentDistance = Aimbot::GetMagnitude(delta);

        if (currentDistance < closestDistance && currentDistance != NULL)
        {
            closestDistance = currentDistance;
            entityDistIndex = i;
            bTargetFound    = true;
        }
    }

    // error, stop the program
    if (entityDistIndex == -1)
        std::cout << "No target found. \n";

    if (bTargetFound)
    {
        Entity* closestTarget{ EntityManager::GetEntity(entityDistIndex) };
        const Vector3 targetAngle{ Aimbot::CalculateAngles(closestTarget) };

        // right click to shoot at closest target
        if (GetAsyncKeyState(VK_RBUTTON))
        {
            localPlayer->m_Angles.x = targetAngle.x;
            localPlayer->m_Angles.y = targetAngle.y;
        }
    }
    // end AIMBOT //
}

Vector3 Aimbot::CalculateAngles(Entity* pEntity)
{
	Vector3 calculatedAngles{};

	Entity* localPlayer{ EntityManager::GetLocalPlayerAddr() };

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