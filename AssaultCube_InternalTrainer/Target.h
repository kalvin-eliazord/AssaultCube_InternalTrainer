#pragma once
struct Target
{
	const Vector3 calcAngles;
	const Vector3 calcDistance;

	Target(Vector3 pCalcAngles, Vector3 pCalcDist)
		: calcAngles   {pCalcAngles}
		, calcDistance {pCalcDist}
	{}
};

