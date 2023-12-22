#pragma once

struct Vector3 { float x, y, z; };

class Entity
{
	struct ActualWeapon
	{
		struct weaponAttributes
		{
		public:
			char pad_0000[260]; //0x0000
			int16_t N00000753; //0x0104
			int16_t N00000764; //0x0106
			int16_t N00000754; //0x0108
			int16_t shootingInterval; //0x010A
			int16_t N00000755; //0x010C
			int16_t N00000768; //0x010E
			int16_t N00000756; //0x0110
			int16_t N0000076A; //0x0112
			int16_t N00000757; //0x0114
			int16_t entityRecoilAmount; //0x0116
			int16_t N00000758; //0x0118
			int16_t N0000076E; //0x011A
			int16_t shootingAnimation; //0x011C
			int16_t N00000770; //0x011E
			int16_t N0000075A; //0x0120
			int16_t weaponRecoilAmount; //0x0122
			int16_t N0000075B; //0x0124
			int16_t N00000774; //0x0126
			char pad_0128[4]; //0x0128
		}; //Size: 0x012C

	public:
		char pad_0000[4]; //0x0000
		int32_t id; //0x0004
		class Entity* weaponOwnerPtr; //0x0008
		struct weaponAttributes* weaponAttributesPtr; //0x000C
		int* magAmmoPtr; //0x0010
		int* ammoPtr; //0x0014
		int* attackFramePtr; //0x0018
		char pad_001C[16]; //0x001C
	};

	public:
		int32_t VTable; //0x0000
		Vector3 m_HeadCoords; //0x0004
		char pad_0010[36]; //0x0010
		Vector3 m_Coords; //0x0034
		Vector3 m_Angles; //0x0040
		char pad_004C[172]; //0x004C
		int32_t m_health; //0x00F8
		int32_t m_armor; //0x00FC
		char pad_0100[292]; //0x0100
		char name[12]; //0x0224
		char pad_0230[252]; //0x0230
		int32_t teamId; //0x032C
		char pad_0330[64]; //0x0330
		struct ActualWeapon actualWeaponPtr; //0x0370
		char pad_0374[2540]; //0x0374
};