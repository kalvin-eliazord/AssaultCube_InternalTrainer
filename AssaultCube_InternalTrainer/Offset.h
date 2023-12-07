#pragma once
namespace Offset
{
	const     static uintptr_t ModBaseAddr     { (uintptr_t) GetModuleHandleW(L"ac_client.exe")};
	constexpr static uintptr_t DecAmmo         { 0x637E9 };
	constexpr static uintptr_t DecHp           { 0x29D1F };
	constexpr static uintptr_t LocalPlayer     { 0x10f4f4 };
	constexpr static uintptr_t NbPlayer        { 0x10f500 };
	constexpr static uintptr_t EntityList      { 0x10f4f8 };
	constexpr static uintptr_t EntityNotLoaded { 0x4E1A04 };
};