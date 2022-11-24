#include "math.hpp"
#include "../settings/globals.hpp"
#include "../sdk/Structs.hpp"
#include "../helpers/utils.hpp"

#define M_PI 3.14159265358979323846f

Vector2 math::CalculateAngle(Vector3 src, Vector3 dest)
{
	Vector3 deltaVec = src.to(dest);
	Vector2 angles{};

	angles.x = -std::asin(deltaVec.z / deltaVec.mag()) * (180.f / M_PI);
	angles.y = std::atan2(deltaVec.y, deltaVec.x) * (180.f / M_PI);

	return angles;
}

bool math::WorldToScreen(Vector3 pos, Vector2& screen)
{
	const SIZE windowSize = utils::getTargetSize();
	ViewMatrix_t matrix = g_Client.getViewMatrix();

	Vector4 clipCoords{};
	clipCoords.x = pos.x * matrix.at(0, 0) + pos.y * matrix.at(0, 1) + pos.z * matrix.at(0, 2) + matrix.at(0, 3);
	clipCoords.y = pos.x * matrix.at(1, 0) + pos.y * matrix.at(1, 1) + pos.z * matrix.at(1, 2) + matrix.at(1, 3);
	clipCoords.z = pos.x * matrix.at(2, 0) + pos.y * matrix.at(2, 1) + pos.z * matrix.at(2, 2) + matrix.at(2, 3);
	clipCoords.w = pos.x * matrix.at(3, 0) + pos.y * matrix.at(3, 1) + pos.z * matrix.at(3, 2) + matrix.at(3, 3);

	if (clipCoords.w < 0.1f)
		return false;

	Vector3 normalized{};
	normalized.x = clipCoords.x / clipCoords.w;
	normalized.y = clipCoords.y / clipCoords.w;
	normalized.z = clipCoords.z / clipCoords.w;

	screen.x = (windowSize.cx / 2.f * normalized.x) + (normalized.x + windowSize.cx / 2.f);
	screen.y = -(windowSize.cy / 2.f * normalized.y) + (normalized.y + windowSize.cy / 2.f);

	return true;
}


