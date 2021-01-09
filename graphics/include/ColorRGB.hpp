#ifndef COLOR_RGB_HPP
#define COLOR_RGB_HPP

class ColorRGB{
public:
#ifndef USE_SDL_RENDERER
		float r; ///< Red component
		float g; ///< Green component
		float b; ///< Blue component
		float a; ///< Alpha channel
#else
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
#endif

	/** Default constructor (black)
	  */
	ColorRGB() : 
		r(0), 
		g(0), 
		b(0), 
		a(1) 
	{ 
	}

	/** Grayscale constructor (0, 1)
	  */
	ColorRGB(const float& value, const float& alpha=1);

	/** RGB constructor (0, 1)
	  */
	ColorRGB(const float& red, const float& green, const float& blue, const float& alpha=1);

	/** Element access operator
	  * @return The color element in range [0,1] or -1 if index is out of range
	  **/
	float operator [] (const size_t& index);

	/** Equality operator
	  */
	bool operator == (const ColorRGB& rhs) const { return (r==rhs.r && g==rhs.g && b==rhs.b); }

	/** Inequality operator
	  */
	bool operator != (const ColorRGB& rhs) const { return (r!=rhs.r || g!=rhs.g || b!=rhs.b); }

	/** Add a color to this color and return the result
	  */
	ColorRGB operator + (const ColorRGB& rhs) const ;

	/** Subtract a color from this color and return the result
	  */
	ColorRGB operator - (const ColorRGB& rhs) const ;

	/** Multiply this color by a constant scaling factor and return the result
	  */
	ColorRGB operator * (const float& rhs) const ;

	/** Divide this color by a constant scaling factor and return the restul
	  */
	ColorRGB operator / (const float& rhs) const ;

	/** Add a color to this color
	  */
	ColorRGB& operator += (const ColorRGB& rhs);

	/** Subtract a color from this color
	  */
	ColorRGB& operator -= (const ColorRGB& rhs);

	/** Multiply this color by a constant scaling factor
	  */
	ColorRGB& operator *= (const float& rhs);
	
	/** Divide this color by a constant scaling factor
	  */
	ColorRGB& operator /= (const float& rhs);

	/** Get the RGB inverse of this color
	  */
	ColorRGB invert() const ;

	/** Conver the color to grayscale using RGB coefficients based on the sRGB convention
	  */
	void toGrayscale();
	
	/** Dump the RGB color components to stdout
	  */
	void dump() const ;
	
	/** Reset color and alpha values
	  */
	void reset() {
		r = 0;
		g = 0;
		b = 0;
		a = 1;
	}

	/** Convert a floating point value in the range [0, 1] to an unsigned char between 0 and 255
	  */
	static unsigned char toUChar(const float& val){ return ((unsigned char)(val*255)); }
	
	/** Convert an unsigned char to a floating point value in the range [0, 1]
	  */
	static float toFloat(const unsigned char& val){ return (float(val)/255); }

	/** 
	  */
	static ColorRGB heatMap(const float& x, const float& xmax, const float& xmin = 0);
};

namespace Colors{
	// Greyscale colors
	const ColorRGB BLACK(0, 0, 0);
	const ColorRGB DKGRAY(2/3.0f, 2/3.0f, 2/3.0f);
	const ColorRGB LTGRAY(1/3.0f, 1/3.0f, 1/3.0f);
	const ColorRGB WHITE(1, 1, 1);
	
	// Primary colors
	const ColorRGB RED(1, 0, 0);
	const ColorRGB GREEN(0, 1, 0);
	const ColorRGB BLUE(0, 0, 1);
	
	// Secondary colors
	const ColorRGB YELLOW(1, 1, 0);
	const ColorRGB MAGENTA(1, 0, 1);
	const ColorRGB CYAN(0, 1, 1);

	// Tertiary colors
	const ColorRGB ORANGE(1.f, 0.5f, 0.f);
	const ColorRGB CHARTREUSE(0.5f, 1.f, 0.f);
	const ColorRGB SPRING(0.f, 1.f, 0.5f);
	const ColorRGB AZURE(0.f, 0.5f, 1.f);
	const ColorRGB VIOLET(0.5f, 0.f, 1.f);
	const ColorRGB ROSE(1.f, 0.f, 0.5f);
}

#endif