#pragma once
#include <string>

namespace bplr
{
	namespace math
	{
		struct vec2;
		struct mat4;

		struct vec3
		{
			float x, y, z;

			vec3();
			vec3(float scalar);
			vec3(float x, float y, float z);
			vec3(const vec2& xy, float z);
			
			vec3& add(const vec3& other);
			vec3& subtract(const vec3& other);
			vec3& multiply(const vec3& other);
			vec3& divide(const vec3& other);

			vec3& add(float value);
			vec3& subtract(float value);
			vec3& multiply(float value);
			vec3& divide(float value);

			vec3 multiply(const mat4& transform) const;

			friend vec3 operator+(vec3 left, const vec3& right);
			friend vec3 operator-(vec3 left, const vec3& right);
			friend vec3 operator*(vec3 left, const vec3& right);
			friend vec3 operator/(vec3 left, const vec3& right);

			friend vec3 operator+(vec3 left, float value);
			friend vec3 operator-(vec3 left, float value);
			friend vec3 operator*(vec3 left, float value);
			friend vec3 operator/(vec3 left, float value);

			bool operator==(const vec3& other) const;
			bool operator!=(const vec3& other) const;

			vec3& operator+=(const vec3& other);
			vec3& operator-=(const vec3& other);
			vec3& operator*=(const vec3& other);
			vec3& operator/=(const vec3& other);

			vec3& operator+=(float value);
			vec3& operator-=(float value);
			vec3& operator*=(float value);
			vec3& operator/=(float value);

			bool operator<(const vec3& other) const;
			bool operator<=(const vec3& other) const;
			bool operator>(const vec3& other) const;
			bool operator>=(const vec3& other) const;

			vec3 cross(const vec3& other) const;
			float dot(const vec3& other) const;

			float magnitude() const;
			vec3 normalize() const;

			std::string toString() const;
			friend std::ostream& operator<<(std::ostream& stream, const vec3& vector);
		};
	}
}
