#pragma once
#include <ostream>

namespace bplr
{
	namespace math
	{
		struct vec2
		{
			float x, y;

			vec2();
			vec2(float scalar);
			vec2(float x, float y);

			vec2& add(const vec2& other);
			vec2& subtract(const vec2& other);
			vec2& multiply(const vec2& other);
			vec2& divide(const vec2& other);

			vec2& add(float value);
			vec2& subtract(float value);
			vec2& multiply(float value);
			vec2& divide(float value);

			friend vec2 operator+(vec2 left, const vec2& right);
			friend vec2 operator-(vec2 left, const vec2& right);
			friend vec2 operator*(vec2 left, const vec2& right);
			friend vec2 operator/(vec2 left, const vec2& right);

			friend vec2 operator+(vec2 left, float value);
			friend vec2 operator-(vec2 left, float value);
			friend vec2 operator*(vec2 left, float value);
			friend vec2 operator/(vec2 left, float value);

			friend vec2 operator-(vec2 right);

			bool operator==(const vec2& other) const;
			bool operator!=(const vec2& other) const;

			vec2& operator+=(const vec2& other);
			vec2& operator-=(const vec2& other);
			vec2& operator*=(const vec2& other);
			vec2& operator/=(const vec2& other);

			vec2& operator+=(float value);
			vec2& operator-=(float value);
			vec2& operator*=(float value);
			vec2& operator/=(float value);

			bool operator<(const vec2& other) const;
			bool operator<=(const vec2& other) const;
			bool operator>(const vec2& other) const;
			bool operator>=(const vec2& other) const;

			vec2 normalise() const;
			float magnatude() const;
			float dot(const vec2& other) const;

			std::string toString() const;
			friend std::ostream& operator<<(std::ostream& stream, const vec2& vector);

		};
	}
}
