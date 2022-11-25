#pragma once

#include "../sdk/sdk.hpp"

namespace math
{
	Vector2 CalculateAngle(Vector3 src, Vector3 dest);
	bool WorldToScreen(Vector3 pos, Vector2& screen);
}
