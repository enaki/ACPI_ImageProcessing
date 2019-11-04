#include "Filter.h"
#include <stdio.h>

Filter::Filter(unsigned int n) : _lines(n), _columns(n)
{
	mask = new double[_lines * _columns];
	for (size_t i = 0; i < _lines * _columns; i++) {
		mask[i] = 1;
	}
}

Filter::Filter(unsigned int n, double *v) : _lines(n), _columns(n)
{
	mask = new double[n * n];
	mask = v;
}

Filter::Filter(unsigned int n, unsigned int m, double* v) : _lines(n), _columns(m)
{
	mask = new double[n * m];
	mask = v;
}

void Filter::changeMask(unsigned int n, unsigned m, double* v)
{
	if (mask) {
		delete[] mask;
	}
	this->_columns = m;
	this->_lines = n;
	mask = new double[n * m];
	mask = v;
}

Filter::~Filter()
{
	if (mask) {
		delete[]mask;
	}
}

void Filter::printMask(int precision, int space)
{
	for (size_t i = 0; i <  _lines * _columns; i++) {
		if (i % _columns == 0) {
			printf("\n");
		}
		printf("%*.*lf ", space, precision, mask[i]);
	}
}

void Filter::changeMask(unsigned int n, double* v)
{
	if (mask) {
		delete[]mask;
	}
	this->_columns = this->_lines = n;

	mask = new double[n * n];
	mask = v;
}


void Filter::changeMask(int size, FilterType type)
{
	int temp;
	if (mask) {
		delete[]mask;
	}
	mask = nullptr;
	this->_columns = this->_lines = size;
	mask = new double[_columns * _lines];
	switch (type) {
	case EYE:
		for (int i = 0; i < _lines; i++) {
			for (int j = 0; j < _columns; j++) {
				mask[i * _columns + j] = (i == j) ? 1 : 0;
			}
		}
		break;
	case UNIFORM:
		for (int i = 0; i < _lines; i++) {
			for (int j = 0; j < _columns; j++) {
				mask[i * _columns + j] = 1;
			}
		}
		break;
	case GAUSS:
		mask[0]= 1;
		for (int i = 1; i < size / 2 + 1; i++) {
			mask[i] = mask[i - 1] * 2;
		}
		for (int i = 1; i < size / 2 + 1; i++) {
			for (int j = 0; j < size/ 2 + 1; j++) {
				mask[i * size + j] = mask[(i - 1) * size + j] * 2;
			}
		}
		temp = 2;
		for (int i = size / 2 + 1; i < size; i++) {
			for (int j = 0; j < size / 2 + 1; j++) {
				mask[i * size + j] = mask[(i - temp)*size + j];
			}
			temp+=2;
		}
		for (int i = 0; i < size; i++) {
			temp = 2;
			for (int j = size / 2 + 1; j < size;  j++) {
				mask[i * size + j] = mask[i * size + j-temp];
				temp+=2;
			}
		}
		break;
	default:
		break;
	}
}

unsigned char Filter::applyMaskToPixel(unsigned char* img, int w, int h, int index)
{
	double result = 0;
	double sum = 0;
	index -= (_lines / 2) * w + _columns / 2;
	index = (index + w * h) % (w * h);
	int column_index = index % w;
	int line_index = index / w;
	for (int i = 0; i < _lines * _columns; i++) {
		result += mask[i] * img[(line_index + i/_columns) % h * w + (column_index + i% _columns) % w ];
		sum += mask[i];
	}
	return result / sum;
	
}

unsigned char* Filter::applyMaskAndGenerateImg(unsigned char* img, int w, int h)
{
	unsigned char* result = new unsigned char[w * h];
	//int starting_position = _lines / 2 * (w + 1);

	for (int i = 0; i < w; i++) {
		int start_index = w * i;
		for (int j = 0; j < h; j++) {
			int index = start_index + j;
			/*if (i < _lines/2 || i > w-1-_lines/2 || j < _columns/2 || j > w-1- _columns /2) {
				result[index] = 0;
			}*/
			result[index] = applyMaskToPixel(img, w, h, index);
		}
	}
	return result;
}
