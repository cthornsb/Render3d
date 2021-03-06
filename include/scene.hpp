#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <cstddef>
#include <chrono>

#include "lightSource.hpp"

class sdlWindow;
class sdlKeyEvent;
class sdlMouseEvent;

class object;
class camera;
class lightSource;
class triangle;

// Make a typedef for clarity when working with chrono.
typedef std::chrono::system_clock sclock;

/** @class scene
  * @brief 
  * @author Cory R. Thornsberry
  * @date September 5, 2019
  */

class scene{
public:
	/** Supported drawing modes
	  */
	enum drawMode {WIREFRAME, ///< Draw outlines of triangles with no backface culling
	               MESH,      ///< Draw outlines of triangles with backface culling
	               SOLID,     ///< Draw filled triangles with wireframe outline overlayed
	               RENDER     ///< Draw filled triangles with light shading
	};

	/** @class pixelTriplet
	  * @brief Simple holder for the pixel coordinates of a 2d projection of a 3d triangle
	  * @author Cory R. Thornsberry
	  * @date September 5, 2019
	  */
	class pixelTriplet{
	public:
		triangle *tri; ///< Pointer to the real triangle

		int pX[3]; ///< The horizontal pixel coordinates for the three vertices
		int pY[3]; ///< The vertical pixel coordinates for the three vertices

		bool draw[3]; ///< Flag for each vertex indicating that it is on the screen

		/** Default constructor
		  */
		pixelTriplet() { }
		
		/** Constructor taking a pointer to a 3d triangle
		  */
		pixelTriplet(triangle *t) : tri(t) { }

		/** Return true if at least one of the vertices is on the screen and return false otherwise
		  */
		bool goodToDraw() const { return (draw[0] || draw[1] || draw[2]); }
	};

	/** Default constructor
	  */
	scene();
	
	/** Constructor taking a pointer to a camera
	  */
	scene(camera *cam_);

	/** Destructor
	  */
	~scene();

	/** Opening the SDL window
	  */
	void initialize();

	/** Return true if the window is still open, and return false otherwise
	  */
	bool getStatus() const { return isRunning; }

	/** Get the width of the screen (in pixels)
	  */
	int getScreenWidth() const { return screenWidthPixels; }

	/** Get the height of the screen (in pixels)
	  */	
	int getScreenHeight() const { return screenHeightPixels; }
	
	/** Get a pointer to the main camera
	  */
	camera *getCamera(){ return cam; }

	/** Get a pointer to the world light source
	  */
	lightSource *getWorldLight(){ return &worldLight; }

	/** Get the total time elapsed since the scene was initialized (in seconds)
	  */
	double getTimeElapsed() const { return timeElapsed; }

	/** Get the time taken for the most recent render (in seconds)
	  */
	double getRenderTime() const { return renderTime; }
	
	/** Get the average amount of time for each render (in seconds)
	  */
	double getAverageRenderTime() const { return (totalRenderTime/updateCount); }

	/** Get the instantaneous framerate of the most recent render (in Hz)
	  */
	double getFramerate() const { return framerate; }
	
	/** Get the average framerate (in Hz)
	  */	
	double getAverageFramerate() const { return (updateCount/timeElapsed); }

	/** Get a pointer to the last user keypress event
	  */
	sdlKeyEvent* getKeypress();
	
	/** Get a pointer to the last user mouse event
	  */
	sdlMouseEvent* getMouse();

	/** Set the width of the screen (in pixels)
	  */
	void setScreenWidth(const int &width){ screenWidthPixels = width; }
	
	/** Set the height of the screen (in pixels)
	  */
	void setScreenHeight(const int &height){ screenHeightPixels = height; }
	
	/** Set the main camera for rendering and update its aspect ratio
	  */
	void setCamera(camera *cam_);

	/** Enable or disable the drawing of triangle normals
	  */
	void setDrawNormals(const bool &enable=true){ drawNorm = enable; }

	/** Enable or disable the drawing of the X, Y, and Z axes at the origin
	  */
	void setDrawOrigin(const bool &enable=true){ drawOrigin = enable; }

	/** Set the target maximum framerate for rendering (in Hz)
	  */
	void setFramerateCap(const double &cap){ framerateCap = cap; }

	/** Add an object to the list of objects to be rendered
	  */
	void addObject(object *obj){ objects.push_back(obj); }
	
	/** Add a light to the list of lights to be rendered
	  */
	void addLight(const lightSource &light){ lights.push_back(light); }

	/** Render a 3d object
	  * @param obj Pointer to the object to draw
	  */
	void render(object* obj);

	/** Clear the screen by filling it with a color (black by default)
	  */
	void clear(const sdlColor &color=Colors::BLACK);
	
	/** Update the screen
	  * @note This method should be called once per iteration of the main loop
	  * @return True if the update was successful and return false if the user closed the window
	  */
	bool update();
	
	/** Wait until the user closes the screen, and then return
	  * @note Only useful for testing
	  */
	void wait();

private:
	double timeElapsed; ///< The time since the program was started
	double totalRenderTime; ///< The running total time of all render events
	double renderTime; ///< The time taken to perform the last render
	double framerate; ///< The instantaneous framerate of the last render

	unsigned short framerateCap; ///< The target render framerate (in Hz)
	
	unsigned long long updateCount; ///< The number of times the user has called update()

	bool drawNorm; ///< Flag indicating that normal vectors will be drawn on each triangle
	bool drawOrigin; ///< Flag indicating that the X, Y, and Z axes will be drawn at the origin
	bool isRunning; ///< Flag indicating that the window is still open and active

	int screenWidthPixels; ///< Width of the viewing window (in pixels)
	int screenHeightPixels; ///< Height of the viewing window (in pixels)

	int minPixelsX;
	int minPixelsY;
	
	int maxPixelsX;
	int maxPixelsY;

	sclock::time_point timeOfInitialization; ///< The time that the scene was initialized
	sclock::time_point timeOfLastUpdate; ///< The last time that update() was called by the user

	camera *cam;
	
	sdlWindow *window; ///< Pointer to the main renderer window
	
	directionalLight worldLight; ///< Global light source
	
	std::vector<object*> objects;
	
	std::vector<lightSource> lights;

	std::vector<pixelTriplet> polygonsToDraw;

	/** 
	  */
	void processObject(object *obj);

	/**
	  */
	bool checkScreenSpace(const double &x, const double &y);

	/** Convert screen-space coordinates [-1, 1] to pixel-space
	  * @note The origin of pixel-space is the upper-left corner of the screen with the positive x-direction
	  *       being toward the right side of the screen and the positive y-direction being toward the bottom
	  * @param x The horizontal component of the screen-space coordinate
	  * @param y The vertical component of the screen-space coordinate
	  * @param px The horizontal pixel corresponding to the input x-coordinate
	  * @param py The vertical pixel corresponding to the input y-coordinate
	  * @return True if the point is on the screen and return false otherwise
	  */
	bool convertToPixelSpace(const double &x, const double &y, int &px, int &py);

	/** Convert screen-space coordinates [-1, 1] to pixel-space
	  * @note The origin of pixel-space is the upper-left corner of the screen with the positive x-direction
	  *       being toward the right side of the screen and the positive y-direction being toward the bottom
	  * @param x Array of horizontal components of the screen-space coordinates (must contain at least 3 elements)
	  * @param y Array of vertical components of the screen-space coordinates (must contain at least 3 elements)
	  * @param coords The pixel coordinate holder for the three vertex projections
	  * @return True if at least one of the vertices is on the screen and return false otherwise
	  */
	bool convertToPixelSpace(const double *x, const double *y, pixelTriplet &coords);

	/** Draw a point to the screen
	  * @param point The point in 3d space to draw
	  * @param color The color of the point
	  */
	void drawPoint(const vector3 &point, const sdlColor &color);

	/** Draw a vector to the screen
	  * @param start The start point of the vector to draw
	  * @param direction The direction of the vector to draw
	  * @param color The color of the vector
	  * @param length The total length to draw
	  */	
	void drawVector(const vector3 &start, const vector3 &direction, const sdlColor &color, const double &length=1);
	
	/** Draw a ray to the screen
	  * @param proj The 3d ray to draw
	  * @param color The color of the ray
	  * @param length The total length to draw
	  */
	void drawRay(const ray &proj, const sdlColor &color, const double &length=1);
	
	/** Draw the outline of a triangle to the screen
	  * @param coords The pixel coordinate holder for the three vertex projections
	  * @param color The line color of the triangle
	  * @note There must be AT LEAST three elements in each array
	  */
	void drawTriangle(const pixelTriplet &coords, const sdlColor &color);
	
	/** Draw a filled triangle to the screen
	  * @param coords The pixel coordinate holder for the three vertex projections
	  * @param color The fill color of the triangle
	  * @note There must be AT LEAST three elements in each array
	  */
	void drawFilledTriangle(const pixelTriplet &coords, const sdlColor &color);
};

#endif
