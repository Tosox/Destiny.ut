#pragma once

struct ViewMatrix_t
{
	float matrix[4][4];

	inline float at(int i, int j) const { return matrix[i][j]; }
};
