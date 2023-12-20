#include "header.h"

void Aimbot::RunAimbot()
{
    // start AIMBOT //
    Entity* localPlayer{ EntityManager::GetLocalPlayerPtr() };

    float closestDistance{ 1000000.0f };
    float currentDistance{ NULL };
    int   closestEntityIndex{ -1 };

     // start at 1 because the first iteration is equal to NULL
    for (int i{ 1 }; i < *EntityManager::GetNumberOfPlayerPtr(); ++i)
    {
        Entity* iEntity{ EntityManager::GetEntityPtr(i) };

        if (!EntityManager::IsValid(iEntity))
            continue;

        const Vector3 delta{ Aimbot::GetDelta(iEntity->m_Coords, localPlayer->m_Coords) };

        currentDistance = Aimbot::GetMagnitude(delta);

        if (currentDistance < closestDistance && currentDistance != NULL)
        {
            closestDistance = currentDistance;
            closestEntityIndex = i;
        }
    }

    // error
    if (closestEntityIndex == -1)
        std::cout << "No target found. \t \r";
    else
    {
        Entity* closestEntity{ EntityManager::GetEntityPtr(closestEntityIndex) };
        const Vector3 entityAngles{ Aimbot::CalculateAnglesOf(closestEntity) };

        std::cout << "Target is: " << closestEntity->name << " \t \r \n";
        std::cout << "RIGHT CLICK to aim! \n";

        // right click to aim at the closest target
        if (GetAsyncKeyState(VK_RBUTTON))
        {
            localPlayer->m_Angles.x = entityAngles.x;
            localPlayer->m_Angles.y = entityAngles.y;
        }
    }

    // end AIMBOT //
}

Vector3 Aimbot::CalculateAnglesOf(Entity* pEntity)
{
	Vector3 calculatedAngles{};

	Entity* localPlayer{ EntityManager::GetLocalPlayerPtr() };

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