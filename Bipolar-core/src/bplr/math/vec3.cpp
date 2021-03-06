#include <sstream>
#include "vec3.h"
#include "vec2.h"
#include "mat4.h"

namespace bplr
{
	namespace math
	{
		vec3::vec3()
			: x(0.0f), y(0.0f), z(0.0f)
		{
		}

		vec3::vec3(float scalar)
			: x(scalar), y(scalar), z(scalar)
		{
		}

		vec3::vec3(float x, float y, float z)
			: x(x), y(y), z(z)
		{
		}

		vec3::vec3(const vec2& xy, float z)
			: x(xy.x), y(xy.y), z(z)
		{
		}

		vec3& vec3::add(const vec3& other)
		{
			x += other.x;
			y += other.y;
			z += other.z;

			return *this;
		}

		vec3& vec3::subtract(const vec3& other)
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;

			return *this;
		}

		vec3& vec3::multiply(const vec3& other)
		{
			x *= other.x;
			y *= other.y;
			z *= other.z;

			return *this;
		}

		vec3& vec3::divide(const vec3& other)
		{
			x /= other.x;
			y /= other.y;
			z /= other.z;

			return *this;
		}

		vec3& vec3::add(float other)
		{
			x += other;
			y += other;
			z += other;

			return *this;
		}

		vec3& vec3::subtract(float other)
		{
			x -= other;
			y -= other;
			z -= other;

			return *this;
		}

		vec3& vec3::multiply(float other)
		{
			x *= other;
			y *= other;
			z *= other;

			return *this;
		}

		vec3& vec3::divide(float other)
		{
			x /= other;
			y /= other;
			z /= other;

			return *this;
		}

		vec3 vec3::multiply(const mat4& transform) const
		{
			return vec3(
				transform.rows[0].x * x + transform.rows[0].y * y + transform.rows[0].z * z + transform.rows[0].w,
				transform.rows[1].x * x + transform.rows[1].y * y + transform.rows[1].z * z + transform.rows[1].w,
				transform.rows[2].x * x + transform.rows[2].y * y + transform.rows[2].z * z + transform.rows[2].w
			);
		}

		vec3 operator+(vec3 left, const vec3& right)
		{
			return left.add(right);
		}

		vec3 operator-(vec3 left, const vec3& right)
		{
			return left.subtract(right);
		}

		vec3 operator*(vec3 left, const vec3& right)
		{
			return left.multiply(right);
		}

		vec3 operator/(vec3 left, const vec3& right)
		{
			return left.divide(right);
		}

		vec3 operator+(vec3 left, float right)
		{
			return left.add(right);
		}

		vec3 operator-(vec3 left, float right)
		{
			return left.subtract(right);
		}

		vec3 operator*(vec3 left, float right)
		{
			return left.multiply(right);
		}

		vec3 operator/(vec3 left, float right)
		{
			return left.divide(right);
		}

		vec3 operator-(vec3 right)
		{
			return right * -1;
		}

		vec3& vec3::operator+=(const vec3& other)
		{
			return add(other);
		}

		vec3& vec3::operator-=(const vec3& other)
		{
			return subtract(other);
		}

		vec3& vec3::operator*=(const vec3& other)
		{
			return multiply(other);
		}

		vec3& vec3::operator/=(const vec3& other)
		{
			return divide(other);
		}

		vec3& vec3::operator+=(float other)
		{
			return add(other);
		}

		vec3& vec3::operator-=(float other)
		{
			return subtract(other);
		}

		vec3& vec3::operator*=(float other)
		{
			return multiply(other);
		}

		vec3& vec3::operator/=(float other)
		{
			return divide(other);
		}

		bool vec3::operator<(const vec3& other) const
		{
			return x < other.x && y < other.y && z < other.z;
		}

		bool vec3::operator<=(const vec3& other) const
		{
			return x <= other.x && y <= other.y && z <= other.z;
		}

		bool vec3::operator>(const vec3& other) const
		{
			return x > other.x && y > other.y && z > other.z;
		}

		bool vec3::operator>=(const vec3& other) const
		{
			return x >= other.x && y >= other.y && z >= other.z;
		}

		bool vec3::operator==(const vec3& other) const
		{
			return x == other.x && y == other.y && z == other.z;
		}

		bool vec3::operator!=(const vec3& other) const
		{
			return !(*this == other);
		}

		vec3 operator-(const vec3& vector)
		{
			return vec3(-vector.x, -vector.y, -vector.z);
		}

		vec3 vec3::cross(const vec3& other) const
		{
			return vec3(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
		}

		float vec3::dot(const vec3& other) const
		{
			return x * other.x + y * other.y + z * other.z;
		}

		float vec3::magnitude() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		vec3 vec3::normalize() const
		{
			float length = magnitude();
			return vec3(x / length, y / length, z / length);
		}

		std::string vec3::toString() const
		{
			std::stringstream result;
			result << "vec3: (" << x << ", " << y << ", " << z << ")";
			return result.str();
		}

		std::ostream& operator<<(std::ostream& stream, const vec3& vector)
		{
			stream << vector.toString();
			return stream;
		}
	}
}
