#pragma once

int* calculateHistogram(unsigned char* img, int w, int h, unsigned int L = 256);
int* calculateCummulativeHistogram(unsigned char* img, int w, int h, unsigned int L = 256);
unsigned char* equalizeHistogram(unsigned char* img, int w, int h, unsigned int L = 256);
unsigned char* extractImageSubregion(unsigned char* img, int w, int h, unsigned int &n, int index);
unsigned char* adaptiveEqualizeHistogram(unsigned char* img, int w, int h, unsigned int n, unsigned int L = 256);
