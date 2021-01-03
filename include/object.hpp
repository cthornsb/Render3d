#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <vector>

#include "scene.hpp"
#include "matrix3.hpp"
#include "triangle.hpp"
#include "Vertex.hpp"
#include "WrappedValue.hpp"
#include "VertexContainer.hpp"
#include "PolygonContainer.hpp"

class camera;
class Shader;

/// <summary>
/// 3d object geometry class
/// </summary>
class object{
public:
	/** Default constructor
	  */
	object();

	/** Object position constructor
	  */	
	object(const vector3& pos_);
	
	/** Get a pointer to the vector of polygons which comprise this 3d object
	  */
	std::vector<triangle>* getPolygons() { return polys.getPolygons(); }

	/** Get the position offset of the object
	  */
	vector3 getPosition() const { return pos; }

	/** Get the position of the center of the object
	  */
	vector3 getCenter() const { return (center + pos); }

	/** Get the size of the object along the x-axis
	  */
	float getSizeX() const { return (maxSize[0] - minSize[0]); }

	/** Get the size of the object along the y-axis
	  */
	float getSizeY() const { return (maxSize[1] - minSize[1]); }

	/** Get the size of the object along the z-axis
	  */
	float getSizeZ() const { return (maxSize[2] - minSize[2]); }

	/** Get the current pitch angle (angle about the x-axis) (in radians)
	  */
	float getPitchAngle() const { return pitchAngle.get(); }

	/** Get the current roll angle (angle about the z-axis) (in radians)
	  */
	float getRollAngle() const { return rollAngle.get(); }

	/** Get the current yaw angle (angle about the y-axis) (in radians)
	  */
	float getYawAngle() const { return yawAngle.get(); }

	/** Get a const pointer to the position vector
	  */
	const vector3* getConstPositionPointer() const { return (const vector3*)&pos; }

	/** Get a const pointer to the position vector
	  */
	vector3* getPositionPointer() { return &pos; }

	/** Get a const pointer to the rotation matrix
	  */
	const matrix3* getConstRotationMatrix() const { return (const matrix3*)&rot; }

	/** Get a pointer to the rotation matrix
	  */
	matrix3* getRotationMatrix() { return &rot; }

	/** Get the number of unique vertices
	  */
	size_t getNumberOfVertices() const { return vertices.size(); }
	
	/** Get the number of unique polygons
	  */
	size_t getNumberOfPolygons() const { return polys.size(); }

	/** Get the number of expected vertices
	  */
	size_t getNumberOfReservedVertices() const { return reservedVertices; }

	/** Get the number of expected polygons
	  */
	size_t getNumberOfReservedPolygons() const { return reservedPolygons; }

	/** Get a const pointer to this object's parent
	  * @return Pointer to this object's parent object, or (this) if object has no parent
	  */
	const object* getParent() const { return (parent ? parent : this); }

	/** Get a const pointer to the shader used to render the object
	  */
	const Shader* getShader() const { return shader; }

	/** Get a pointer to the vertex container object
	  */
	const VertexContainer* getVertices() const { return &vertices; }

	/** Get a pointer to the polygon container object
	  */
	const PolygonContainer* getPolygons() const { return &polys; }

	/** Get the array of raw vertex position data
	  */
	const float* getRawVertexData() const { return polys.getConstVertexData(); }

	/** Get OpenGL VBO id number corresponding to object vertices
	  */
	unsigned int getVertexVBO() const { return polys.getVertexVBO(); }

	/** Get OpenGL VBO id number corresponding to object vertex indicies
	  */
	unsigned int getIndexVBO() const { return polys.getIndexVBO(); }

	/** Return true if this object has a parent object and return false otherwise
	  */
	bool isChild() const { return (parent != 0x0); }

	/** Return true if this object has child objects and return false otherwise
	  */
	bool hasChildren() const { return !children.empty(); }

	/** Get const iterator at the start of the child objects vector
	  */
	std::vector<object*>::const_iterator beginChildren() const { return children.cbegin(); }

	/** Get const iterator at the end of the child objects vector
	  */
	std::vector<object*>::const_iterator endChildren() const { return children.cend(); }

	/** Rotate the object by a given amount about the X, Y, and Z, axes (all in radians)
	  * @note This method will rotate vertices from their current position. Use setRotation() to specify the rotation explicitly
	  */
	void rotate(const float& theta, const float& phi, const float& psi);

	/** Move the position of the object
	  * @note This method moves the object relative to its current position. Use setPosition() to specify the position explicitly
	  */
	void move(const vector3 &offset);

	/** Rotate the object to specified angles about the X, Y, and Z, axes (all in radians)
	  */
	void setRotation(const float& theta, const float& phi, const float& psi);

	/** Set the position of the object
	  */
	void setPosition(const vector3 &position);

	/** Set the shader to use for rendering
	  */
	void setShader(const Shader* shdr) { shader = shdr; }

	/** Reset the offset position of the object to its original location
	  */
	void resetPosition();

	/** Project all vertices onto the view-plane
	  */
	void renderAllVertices(camera* cam);

	/** Add a child to this object
	  * @note An object with multiple parents may cause undefined behavior
	  * @param child Pointer to the child object
	  * @param offset Position offset inside the parent object
	  */
	void addChild(object* child, const vector3& offset = zeroVector);

	/** Remove a child from this object
	  * @param child Pointer to the child object
	  * @param offset Position offset inside the parent object
	  */
	void removeChild(object* child);

	/** Call the user build function for this class
	  */
	void build();

	/** Build this object by adding polygons to the vector of polygons
	  */
	virtual void userBuild() = 0;
	
protected:
	bool built; ///< Flag indicating that the geometry has been constructed

	size_t reservedVertices; ///< The number of expected vertices
	size_t reservedPolygons; ///< The number of expected polygons which will be built

	vector3 pos; ///< The position offset of the object (not necessarily the center)
	vector3 pos0; ///< The original position offset of the object
	
	matrix3 rot; ///< The rotation of the object about the offset position

	vector3 center; ///< Center of the box which bounds the model

	WrappedValue pitchAngle; ///< Angle of camera tilt up or down (i.e. about the horizontal axis)
	WrappedValue rollAngle; ///< Angle of camera roll cw or ccw (i.e. about the depth axis)
	WrappedValue yawAngle; ///< Angle of camera turn left or right (i.e. about the vertical axis

	float maxSize[3]; ///< Maximum extent along the x, y, and z-axes
	float minSize[3]; ///< Minimum extent along the x, y, and z-axes

	VertexContainer vertices; ///< Vector of all unique vertices
	
	std::vector<Vertex*> verticesToDraw; ///< List of vertices which will be drawn

	PolygonContainer polys; ///< Vector of all unique polygons which make up this 3d object

	std::vector<object*> children; ///< Vector of pointers to child objects

	vector3 parentOffset; ///< Offset of this object within its parent

	const object* parent; ///< Pointer to parent object

	const Shader* shader; ///< Pointer to an OpenGL shader to use for rendering

	/** Update the physical size of the object along the x-axis
	  * @note The size is only for informational purposes and does not change the scale of the object
	  */
	void setSizeX(const float& min_, const float& max_);

	/** Update the physical size of the object along the x-axis
	  * @note The size is only for informational purposes and does not change the scale of the object
	  */
	void setSizeY(const float& min_, const float& max_);

	/** Update the physical size of the object along the x-axis
	  * @note The size is only for informational purposes and does not change the scale of the object
	  */
	void setSizeZ(const float& min_, const float& max_);

	/** Set this object's parent
	  * @return True if this object had no parent, and return false if otherwise
	  */
	bool setParent(const object* obj);

	/** Update the position of all child objects to the parent position
	  */
	void updatePosition();

	/** Update the position based on new parent position
	  */
	void updatePositionForParent(const vector3& position);

	/** Update the rotation of all child objects to that of the parent
	  */
	void updateRotation();

	/** Update the rotation based on new parent rotation
	  */
	void updateRotationForParent(const matrix3* rotation);

	/** Reserve space in the geometry vectors so that they will not resize when being filled
	  * @param nVert Number of expected vertices
	  * @param nPoly Number of expected polygons. If equal to zero, use the number of vertices
	  */
	void reserve(const size_t& nVert, const size_t& nPoly=0);

	/** Rotate all vertices using the object's internal rotation matrix
	  */
	void transform(const matrix3* mat);
	
	/** Add a unique vertex to the vector of vertices
	  * @return Pointer to the vertex vector
	  */
	Vertex* addVertex(const float &x, const float&y, const float&z);

	/** Add a unique vertex to the vector of vertices
	  * @return Pointer to the vertex vector
	  */
	Vertex* addVertex(const vector3& vec);

	/** Add a unique polygon to the vector of polygons
	  */
	void addTriangle(const unsigned short &i0, const unsigned short &i1, const unsigned short &i2);

	/** Add two unique polygons (representing a quadrilateral) to the vector of polygons
	  */
	void addQuad(const unsigned short& i0, const unsigned short& i1, const unsigned short& i2, const unsigned short& i3);

	/** Add a unique static triangle to the vector of polygons
	  * @note Static triangles cannot be moved or rotated
	  */
	void addStaticTriangle(const unsigned short& i0, const unsigned short& i1, const unsigned short& i2);

	/** Add two unique static triangles (representing a quadrilateral) to the vector of polygons
	  * @note Static triangles cannot be moved or rotated
	  */
	void addStaticQuad(const unsigned short& i0, const unsigned short& i1, const unsigned short& i2, const unsigned short& i3);
};

#endif
