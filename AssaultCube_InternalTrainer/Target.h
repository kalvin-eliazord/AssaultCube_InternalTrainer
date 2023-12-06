#pragma once
struct Target
{
	const Vector3 calculatedAngles;
	const Vector3 calculatedDistance;

	Target(Vector3 pCalcAngles, Vector3 pCalcDist)
		: calculatedAngles{pCalcAngles}
		, calculatedDistance{pCalcDist}
	{}
};