#pragma once

unsigned char negateImage(unsigned char charpixel);
class binarizeImage {
	unsigned char m_threshold;
public:
	binarizeImage(unsigned char threshold) : m_threshold(threshold) {}
	unsigned char operator()(unsigned char pixel);
};

class enlightImage {
	short m_value;
public:
	enlightImage(short value) : m_value(value) {}
	unsigned char operator()(unsigned char pixel);
};

class contrastImage {
	unsigned char a, b, sa, sb;
	double m, n, p;
public:
	contrastImage(unsigned char a, unsigned char  b, unsigned char sa, unsigned char sb);
	unsigned char operator()(unsigned char pixel);
};

class gammaCorectionImage {
	double c, lambda;
public:
	gammaCorectionImage(double c, double lambda) : c(c), lambda(lambda) {}
	unsigned char operator()(unsigned char pixel);
};

class contrastCompressImage {
	double c;
public:
	contrastCompressImage(double c) : c(c) {}
	unsigned char operator()(unsigned char pixel);
};

class bitSlicingImage {
	int n;
public:
	bitSlicingImage(int n) : n(n%8) {}
	unsigned char operator()(unsigned char pixel);
};

class windowOperationImage {
	unsigned char operation, a, b;
public:
	windowOperationImage(unsigned char n, unsigned char a, unsigned char b);
	unsigned char operator()(unsigned char pixel);
};

template <typename Operation>
inline unsigned char* applyOperation(unsigned char* img, int w, int h, Operation operation)
{
	unsigned char* result = new unsigned char[w * h];
	for (int i = 0; i < h * w; i++) {
		result[i] = operation(img[i]);
	}
	return result;
}
