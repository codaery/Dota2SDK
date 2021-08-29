#include "math.h"
#include <iostream>

void inline math::sin_cos(float radians, float* sine, float* cosine)
{
	*sine = sin(radians);
	*cosine = cos(radians);
}

void math::angle_vectors(const QAngle& angles, Vector& forward)
{
	float sp, sy, cp, cy;

	math::sin_cos(DEG2RAD(angles[YAW]), &sy, &cy);
	math::sin_cos(DEG2RAD(angles[PITCH]), &sp, &cp);

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;
}

void math::angle_vectors(const QAngle& angles, Vector* forward, Vector* right, Vector* up) {
	float sr, sp, sy, cr, cp, cy;

	sin_cos(DEG2RAD(angles[YAW]), &sy, &cy);
	sin_cos(DEG2RAD(angles[PITCH]), &sp, &cp);
	sin_cos(DEG2RAD(angles[ROLL]), &sr, &cr);

	if (forward) {
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if (right) {
		right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
		right->y = (-1 * sr * sp * sy + -1 * cr * cy);
		right->z = -1 * sr * cp;
	}

	if (up) {
		up->x = (cr * sp * cy + -sr * -sy);
		up->y = (cr * sp * sy + -sr * cy);
		up->z = cr * cp;
	}
}

void math::normalize_angles(QAngle& angle)
{
	while (angle.x > 89.0f)
		angle.x -= 180.f;

	while (angle.x < -89.0f)
		angle.x += 180.f;

	while (angle.y > 180.f)
		angle.y -= 360.f;

	while (angle.y < -180.f)
		angle.y += 360.f;
}

void math::clamp_angles(QAngle& angle)
{
	if (angle.y > 180.0f)
		angle.y = 180.0f;
	else if (angle.y < -180.0f)
		angle.y = -180.0f;

	if (angle.x > 89.0f)
		angle.x = 89.0f;
	else if (angle.x < -89.0f)
		angle.x = -89.0f;

	angle.z = 0;
}

float math::get_fov(const QAngle& viewAngle, const QAngle& aimAngle)
{
	QAngle delta = aimAngle - viewAngle;
	normalize_angles(delta);

	return sqrtf(powf(delta.x, 2.0f) + powf(delta.y, 2.0f));
}

void math::vector_angles(const Vector& forward, QAngle& angles)
{
	if (forward[1] == 0.0f && forward[0] == 0.0f)
	{
		angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f; // Pitch (up/down)
		angles[1] = 0.0f;  //yaw left/right
	}
	else
	{
		angles[0] = atan2(-forward[2], forward.Length2D()) * -180 / M_PI;
		angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI;

		if (angles[1] > 90)
			angles[1] -= 180;
		else if (angles[1] < 90)
			angles[1] += 180;
		else if (angles[1] == 90)
			angles[1] = 0;
	}

	angles[2] = 0.0f;
}

float math::dot_product(const Vector& v1, const float* v2)
{
	return v1.x * v2[0] + v1.y * v2[1] + v1.z * v2[2];
}

void math::vector_transform(const Vector& in1, const matrix3x4_t& in2, Vector& out)
{
	out.x = dot_product(in1, in2[0]) + in2[0][3];
	out.y = dot_product(in1, in2[1]) + in2[1][3];
	out.z = dot_product(in1, in2[2]) + in2[2][3];
}

QAngle math::calc_angle(const Vector& src, const Vector& dst)
{
	QAngle angles;
	Vector delta = src - dst;

	math::vector_angles(delta, angles);

	delta.Normalize();

	return angles;
}

bool math::cmpf(float a, float b, float epsilon) {
	return std::abs(a - b) < epsilon;
}
