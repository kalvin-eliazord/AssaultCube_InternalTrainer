#pragma once
namespace PagePatcher
{
	void PatchingPage(uintptr_t* dst, uintptr_t* src, int size);
	void NopPage(uintptr_t* dst, int size);
};