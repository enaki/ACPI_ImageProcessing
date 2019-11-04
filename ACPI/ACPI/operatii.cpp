#include "operatii.h"
#include <math.h>

unsigned char clamp(int value, int min = 0, int max = 255) {
	if (value < min) {
		return 0;
	}
	if (value > max) {
		return 255;
	}
	return value;
}

unsigned char negateImage(unsigned char pixel)
{
	return 255 - pixel;
}

unsigned char binarizeImage::operator()(unsigned char pixel)
{
	return (pixel > m_threshold) ? 255 : 0;
}

unsigned char enlightImage::operator()(unsigned char pixel)
{
	return clamp(pixel + m_value);
}

contrastImage::contrastImage(unsigned char a_in, unsigned char b_in, unsigned char sa_in, unsigned char sb_in) 
	: a(a_in), b(b_in), sa(sa_in), sb(sb_in)
{
	m = (double)sa / a;
	n = (double)(sb - sa) / (b - a);
	p = (double)(255 - sb) / (255 - b);
}

unsigned char contrastImage::operator()(unsigned char pixel)
{
	
	if (pixel < a) {
		return m * pixel;
	}
	if (pixel < b) {
		return n * (pixel - a) + sa;
	}
	return p* (255 - b) + sb;
}

unsigned char gammaCorectionImage::operator()(unsigned char pixel)
{
	return clamp(c * pow(pixel, lambda));
}

unsigned char contrastCompressImage::operator()(unsigned char pixel)
{
	return clamp(c * log(1 + pixel));
}

unsigned char bitSlicingImage::operator()(unsigned char pixel)
{
	return (pixel & (1 << n)) ? 255 : 0;
}

windowOperationImage::windowOperationImage(unsigned char n, unsigned char a, unsigned char b)
	: operation(n % 2)
{
	if (a > b) {
		this->b = a;
		this->a = b;
	}
	else {
		this->a = a;
		this->b = b;
	}
}

unsigned char windowOperationImage::operator()(unsigned char pixel)
{
	if (pixel >= a && pixel <= b)
		return 255;
	return operation ? pixel : 0;
}
