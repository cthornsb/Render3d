#include <iostream>

#include "ColorRGB.hpp"

#ifdef USE_SDL_RENDERER
	ColorRGB::ColorRGB(const float& value){
		r = toUChar(value);
		g = r;
		b = r;
	}

	ColorRGB::ColorRGB(const float& red, const float& green, const float& blue){
		r = toUChar(red);
		g = toUChar(green);
		b = toUChar(blue);
	}

	ColorRGB ColorRGB::invert() const {
		return ColorRGB(255-r, 255-g, 255-b);
	}

	void ColorRGB::toGrayscale(){
		// Based on the sRGB convention
		r = ((unsigned char)(0.2126*r));
		g = ((unsigned char)(0.7152*g));
		b = ((unsigned char)(0.0722*b));
	}
#else
	ColorRGB::ColorRGB(const float& value, const float& alpha/*=1*/){
		r = value;
		g = r;
		b = r;
		a = alpha;
	}

	ColorRGB::ColorRGB(const float& red, const float& green, const float& blue, const float& alpha/*=1*/){
		r = red;
		g = green;
		b = blue;
		a = alpha;
	}

	ColorRGB ColorRGB::invert() const {
		return ColorRGB(1-r, 1-g, 1-b);
	}

	void ColorRGB::toGrayscale(){
		// Based on the sRGB convention
		float prime = r * 0.2126f + g * 0.7152f + b * 0.0722f;
		r = prime;
		g = prime;
		b = prime;
	}
#endif

float ColorRGB::operator [] (const size_t& index) {
	switch (index) {
	case 0:
		return r;
	case 1:
		return g;
	case 2:
		return b;
	case 3:
		return a;
	default:
		break;
	}
	return -1;
}

ColorRGB ColorRGB::operator + (const ColorRGB& rhs) const {
	float rprime = (r + rhs.r);// / 255.0f;
	float gprime = (g + rhs.g);// / 255.0f;
	float bprime = (b + rhs.b);// / 255.0f;
	return ColorRGB((rprime <= 1 ? rprime : 1), (gprime <= 1 ? gprime : 1), (bprime <= 1 ? bprime : 1));
}

ColorRGB ColorRGB::operator - (const ColorRGB& rhs) const {
	float rprime = (r - rhs.r);// / 255.0f;
	float gprime = (g - rhs.g);// / 255.0f;
	float bprime = (b - rhs.b);// / 255.0f;
	return ColorRGB((rprime > 0 ? rprime : 0), (gprime > 1 ? gprime : 0), (bprime > 1 ? bprime : 0));
}

#ifndef USE_SDL_RENDERER
ColorRGB ColorRGB::operator * (const float& rhs) const {
	return ColorRGB(r*rhs, g*rhs, b*rhs);
}

ColorRGB ColorRGB::operator / (const float& rhs) const {
	return ColorRGB(r/rhs, g/rhs, b/rhs);
}
#else
ColorRGB ColorRGB::operator * (const float& rhs) const {
	return ColorRGB(toFloat(r) * rhs, toFloat(g) * rhs, toFloat(b) * rhs);
}

ColorRGB ColorRGB::operator / (const float& rhs) const {
	return ColorRGB(toFloat(r) / rhs, toFloat(g) / rhs, toFloat(b) / rhs);
}
#endif

ColorRGB& ColorRGB::operator += (const ColorRGB& rhs){
	return ((*this) = (*this) + rhs);
}

ColorRGB& ColorRGB::operator -= (const ColorRGB& rhs){
	return ((*this) = (*this) - rhs);
}

ColorRGB& ColorRGB::operator *= (const float& rhs){
	return ((*this) = (*this) * rhs);
}

ColorRGB& ColorRGB::operator /= (const float& rhs){
	return ((*this) = (*this) / rhs);
}

void ColorRGB::dump() const {
	std::cout << "r=" << (int)r << ", g=" << (int)g << ", b=" << (int)b << std::endl;
}

ColorRGB ColorRGB::heatMap(const float& x, const float& xmax, const float& xmin/*=0*/) {
	float rgb;
	if (x < xmin)
		rgb = 0.f;
	else if (x > xmax)
		rgb = 1.f;
	else
		rgb = 1.0f - x / (xmax - xmin);
	return ColorRGB(rgb, rgb, rgb);
}