#pragma once

class Filter {
	double* mask;
	unsigned int _lines;
	unsigned int _columns;
public:
	enum FilterType {
		EYE = 0, UNIFORM, GAUSS
	};
	Filter(unsigned int n);
	Filter(unsigned int n, double* v);
	Filter(unsigned int n, unsigned int m, double* v);
	~Filter();
	void printMask(int precision = 0, int space = 4);
	void changeMask(unsigned int n, double* v);
	void changeMask(unsigned int n, unsigned m, double* v);
	void changeMask(int size, FilterType type = EYE);
	unsigned char applyMaskToPixel(unsigned char* img, int w, int h, int index);
	unsigned char* applyMaskAndGenerateImg(unsigned char* img, int w, int h);
};