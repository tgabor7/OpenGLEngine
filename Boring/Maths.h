#pragma once
#include <glm\vec3.hpp>
#include <glm\mat4x4.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "DataTypes.h"
#include <math.h>
#include "State.h"

using namespace glm;

namespace functions {
	static mat4x4 createTransformationMatrix(vec3 translation, vec3 rotation, vec3 dimensions) {
		mat4 res;
		res = translate(res, translation);
		res = rotate(res, rotation.x, glm::vec3(1, 0, 0));
		res = rotate(res, rotation.y, glm::vec3(0, 1, 0));
		res = rotate(res, rotation.z, glm::vec3(0, 0, 1));
		res = scale(res, dimensions);
		return res;
	}
	static mat4x4 lookAtP(vec3 eye, vec3 center, vec3 up, mat4x4 dest) {
		vec3 forward(0, 0, 0);


		forward = center - eye;
		forward = normalize(forward);

		vec3 side(0, 0, 0);
		side = glm::cross(forward, up);
		side = normalize(side);


		up = cross(side, forward);


		mat4x4 matrix = mat4x4(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
		matrix[0][0] = side.x;
		matrix[0][1] = side.y;
		matrix[0][2] = side.z;
		matrix[1][0] = up.x;
		matrix[1][1] = up.y;
		matrix[1][2] = up.z;
		matrix[2][0] = -forward.x;
		matrix[2][1] = -forward.y;
		matrix[2][2] = -forward.z;

		matrix = inverse(matrix);


		return matrix;
	}
	static mat4x4 createViewMatrix(Camera camera) {

		mat4x4 view = mat4x4();
		view = lookAtP(camera.position, camera.pointToLookAt, vec3(0, 1, 0), view);
		view = glm::translate(view, -camera.position);

		return view;
	}
	static mat4x4 createProjectionMatrix(float FOV, float NEAR_PLANE, float FAR_PLANE) {

		float aspectRatio = (float)State::WIDTH / (float)State::HEIGHT;
		float y_scale = (float)((1.0f / tan(((FOV / 2.0f) / 360)*3.14f)) * aspectRatio);
		float x_scale = y_scale / aspectRatio;
		float frustum_length = FAR_PLANE - NEAR_PLANE;

		mat4x4 projectionMatrix = mat4x4();
		projectionMatrix[0][0] = x_scale;
		projectionMatrix[1][1] = y_scale;
		projectionMatrix[2][2] = -((FAR_PLANE + NEAR_PLANE) / frustum_length);
		projectionMatrix[2][3] = -1;
		projectionMatrix[3][2] = -((2 * NEAR_PLANE * FAR_PLANE) / frustum_length);
		projectionMatrix[3][3] = 0;

		return projectionMatrix;


	}

	static vec2 cross(float r, vec2 v) {
		return vec2(r * v.y, -r * v.x);
	}
	static float cross(vec2 v1, vec2 v2) {
		return v1.x * v2.y - v1.y * v2.x;
	}
	static float dot(vec2 v1, vec2 v2) {
		return v1.x*v2.x + v1.y*v2.y;
	}
	static vec2 tripleProduct(vec2 a, vec2 b, vec2 c) {
		vec2 r;

		float ac = dot(a, c);
		float bc = dot(b, c);


		r.x = b.x * ac - a.x * bc;
		r.y = b.y * ac - a.y * bc;
		return r;
	}
}
