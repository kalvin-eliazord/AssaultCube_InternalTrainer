#pragma once

struct Vector3 { float x, y, z; };

class Player
{
	public:
		char pad_0000[4]; //0x0000
		Vector3 m_HeadCoords; //0x0004
		char pad_0010[36]; //0x0010
		Vector3 m_Coords; //0x0034
		Vector3 m_Angles; //0x0040
		char pad_004C[172]; //0x004C
		int32_t m_health; //0x00F8
		char pad_00FC[24]; //0x00FC
		int32_t magPistolAmmo; //0x0114
		char pad_0118[16]; //0x0118
		int32_t magRifleAmmo; //0x0128
		char pad_012C[16]; //0x012C
		int32_t pistolAmmo; //0x013C
		char pad_0140[16]; //0x0140
		int32_t assaultRifleAmmo; //0x0150
		char pad_0154[56]; //0x0154
		int32_t nbPistolShot; //0x018C
		char pad_0190[16]; //0x0190
		int32_t nbRifleShot; //0x01A0
		char pad_01A4[392]; //0x01A4
		int32_t teamID; //0x032C
		char pad_0330[1304]; //0x0330
}; //Size: 0x0848
