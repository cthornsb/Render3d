#ifndef PRIMITIVES_HPP
#define PRIMITIVES_HPP

#include "object.hpp"

namespace Primitives {
	class Plane : public object {
	public:
		Plane() :
			object(),
			dX(0.5),
			dY(0.5)
		{
		}

		Plane(const Vector3& pos_) :
			object(pos_),
			dX(0.5),
			dY(0.5)
		{
		}

		Plane(const Vector3& pos_, const float& X, const float& Y) :
			object(pos_),
			dX(X/2),
			dY(Y/2)
		{
		}

		/** Build this object by adding polygons to the vector of polygons
			*/
		virtual void userBuild();

	protected:
		float dX; ///< Half width of plane along the x-axis
		float dY; ///< Half height of plane along the y-axis
	};

	class Cube : public Plane {
	public:
		Cube() :
			Plane(),
			dZ(0.5)
		{
		}

		Cube(const Vector3& pos_) :
			Plane(pos_),
			dZ(0.5)
		{
		}

		Cube(const Vector3& pos_, const float& X, const float& Y, const float& Z) :
			Plane(pos_, X, Y),
			dZ(Z/2)
		{
		}

		/** Build this object by adding polygons to the vector of polygons
		 */
		virtual void userBuild();

	protected:
		float dZ; ///< Half depth of cube along the z-axis
	};

	class Circle : public object {
	public:
		Circle() :
			object(),
			dR(0.5),
			nVertices(6)
		{
		}

		Circle(const Vector3& pos_) :
			object(pos_),
			dR(0.5),
			nVertices(6)
		{
		}

		Circle(const Vector3& pos_, const float& R, const int& sides) :
			object(pos_),
			dR(R),
			nVertices(sides)
		{
		}

		/** Build this object by adding polygons to the vector of polygons
		 */
		virtual void userBuild();

	protected:
		float dR; ///< Radius of the circle

		int nVertices; ///< Number of vertices used to approximate the circumference of the circle (not counting the central vertex)

		void approximate(const float& zoffset=0);
	};

	class Cylinder : public Circle {
	public:
		Cylinder() :
			Circle(),
			dZ(0.5)
		{
		}

		Cylinder(const Vector3& pos_) :
			Circle(pos_),
			dZ(0.5)
		{
		}

		Cylinder(const Vector3& pos_, const float& R, const float& Z, const int& sides) :
			Circle(pos_, R, sides),
			dZ(Z/2)
		{
		}

		/** Build this object by adding polygons to the vector of polygons
		 */
		virtual void userBuild();

	protected:
		float dZ; ///< Half depth of the cylinder along the x-axis
	};

	class Cone : public Circle {
	public:
		Cone() :
			Circle(),
			dZ(0.5)
		{
		}

		Cone(const Vector3& pos_) :
			Circle(pos_),
			dZ(0.5)
		{
		}

		Cone(const Vector3& pos_, const float& R, const float& Z, const int& sides) :
			Circle(pos_, R, sides),
			dZ(Z / 2)
		{
		}

		/** Build this object by adding polygons to the vector of polygons
		 */
		virtual void userBuild();

	private:
		float dZ; ///< Half height of the cylinder along the z-axis
	};

	class Sphere : public object {
	public:
		Sphere();

		/** Build this object by adding polygons to the vector of polygons
		 */
		virtual void userBuild();

	protected:
		float dR;
	};

} // namespace primitives

#endif // ifndef PRIMITIVES_HPP