#include "histogram.h"
#include <math.h>
#include <algorithm>

int* calculateHistogram(unsigned char* img, int w, int h, unsigned int L)
{
	int* histo = new int[L];
	for (int i = 0; i < L; i++) {
		histo[i] = 0;
	}
	for (int i = 0; i < w*h; i++) {
		histo[img[i]]++;
	}
	return histo;
}

int* calculateCummulativeHistogram(unsigned char* img, int w, int h, unsigned int L)
{
	int* histogram_values = calculateHistogram(img, w, h);
	int* cummulative_histogram_values = new int[L];

	cummulative_histogram_values[0] = histogram_values[0];
	for (int i = 1; i < L; i++) {
		cummulative_histogram_values[i] = cummulative_histogram_values[i - 1] + histogram_values[i];
	}
	return cummulative_histogram_values;
}


unsigned char* equalizeHistogram(unsigned char* img, int w, int h, unsigned int L) {
	unsigned char* result = new unsigned char[w * h];
	int* cummulative_histogram_values = calculateCummulativeHistogram(img, w, h);

	for (int i = 0; i < w * h; i++) {
		result[i] = floor((double)cummulative_histogram_values[img[i]] / (w * h) * (L - 1));
	}
	return result;
}

unsigned char* extractImageSubregion(unsigned char* img, int w, int h, unsigned int &n, int index) {
	unsigned int semi_n = n / 2;
	int linie = index / w;
	int coloana = index % w;
	unsigned char* result ;
	if (linie >= semi_n && coloana >= semi_n) {
		result = new unsigned char[n * n];
		index -= (w + 1) * semi_n;
		for (int k = 0; k < n * n; k++) {
			result[k] = img[index + k / n * w + k % n];
		}
	}
	else {
		n = 2 * std::min(linie, coloana) + 1;
		result = extractImageSubregion(img, w, h, n, index);
	}
	return result;
}

unsigned char* adaptiveEqualizeHistogram(unsigned char* img, int w, int h, unsigned int n, unsigned int L)
{
	unsigned char* result = new unsigned char[w * h];
	for (int i = 0; i < w*h; i++) {
		unsigned int n_temp = n;
		unsigned char* img_temp = extractImageSubregion(img, w, h, n_temp, i);
		int* cummulative_histogram_values = calculateCummulativeHistogram(img_temp, n_temp, n_temp);
		result[i] = floor((double)cummulative_histogram_values[img[i]] / (n_temp * n_temp) * (L - 1));
		delete[]img_temp;
	}
	return result;
}
