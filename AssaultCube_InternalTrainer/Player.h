#pragma once

struct Vector3 { float x, y, z; };

class Player
{
	public:
		char pad_0000[4]; //0x0000
		Vector3 N00000054; //0x0004
		char pad_0010[36]; //0x0010
		Vector3 N0000005E; //0x0034
		Vector3 m_angles; //0x0040
		char pad_004C[172]; //0x004C
		int32_t m_health; //0x00F8
		char pad_00FC[64]; //0x00FC
		int32_t m_ammoGun; //0x013C
		char pad_0140[16]; //0x0140
		int32_t m_ammoRifle; //0x0150
		char pad_0154[3844]; //0x0154
};