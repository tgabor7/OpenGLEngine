#include "Quaternion.h"


Quaternion::Quaternion()
{
}
Quaternion::Quaternion(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
	normalize();
}
void Quaternion::normalize() {
	float mag = (float)sqrt(w * w + x * x + y * y + z * z);
	this->w /= mag;
	this->x /= mag;
	this->y /= mag;
	this->z /= mag;
}
mat4x4 Quaternion::toRotationMatrix() {
	mat4x4 matrix(1.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		1.0f,
		0.0f,
		0.0f,
		0.0f,
		0.0f,
		1.0f);
	float xy = x * y;
	float xz = x * z;
	float xw = x * w;
	float yz = y * z;
	float yw = y * w;
	float zw = z * w;
	float xSquared = x * x;
	float ySquared = y * y;
	float zSquared = z * z;
	matrix[0][0] = 1 - 2 * (ySquared + zSquared);
	matrix[0][1] = 2 * (xy - zw);
	matrix[0][2] = 2 * (xz + yw);
	matrix[0][3] = 0;
	matrix[1][0] = 2 * (xy + zw);
	matrix[1][1] = 1 - 2 * (xSquared + zSquared);
	matrix[1][2] = 2 * (yz - xw);
	matrix[1][3] = 0;
	matrix[2][0] = 2 * (xz - yw);
	matrix[2][1] = 2 * (yz + xw);
	matrix[2][2] = 1 - 2 * (xSquared + ySquared);
	matrix[2][3] = 0;
	matrix[3][0] = 0;
	matrix[3][1] = 0;
	matrix[3][2] = 0;
	matrix[3][3] = 1;
	return matrix;
}

Quaternion::~Quaternion()
{
}
