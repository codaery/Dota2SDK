#pragma once

#include "../utils/vector.h"

namespace math {
	void inline sin_cos(float radians, float* sine, float* cosine);
	void angle_vectors(const QAngle& angles, Vector& forward);
	void angle_vectors(const QAngle& angles, Vector* forward, Vector* right, Vector* up);
	void normalize_angles(QAngle& angle);
	void clamp_angles(QAngle& angle);
	float get_fov(const QAngle& viewAngle, const QAngle& aimAngle);
	float dot_product(const Vector& v1, const float* v2);
	void vector_angles(const Vector& forward, QAngle& angles);
	void vector_transform(const Vector& in1, const matrix3x4_t& in2, Vector& out);
	QAngle calc_angle(const Vector& src, const Vector& dst);
	bool cmpf(float a, float b, float epsilon = 0.01f);
}