#include "ImageGrid.h"
#include "operatii.h"
#include <QApplication.h>
#include "histogram.h"
#include <Filter.h>


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ImageGrid *grid = new ImageGrid("Prelucrarea imaginilor");

	QString imageDir = "Images/";
	QString imageFile(imageDir + "lena512.bmp");

	int w, h;
	unsigned char* img = Tools::readImageGray8(imageFile, w, h);
	
	grid->addImage(img, w, h, 0, 0, "Original");
	grid->addHistogram(calculateHistogram(img, w, h), 256, 1, 0, "histo_0");

	//filtru 1
	Filter f(3, 3, new double[3 * 3] {	0,   0.2,  0,
										0.2, 0.2, 0.2,
										0,   0.2,   0 });
	unsigned char* filter_1 = f.applyMaskAndGenerateImg(img, w, h);
	//f.printMask(2, 5);
	grid->addImage(filter_1, w, h, 0, 1, "Filtru 1");
	grid->addHistogram(calculateHistogram(filter_1, w, h), 256, 1, 1, "histo_1");

	//filtru 2
	f.changeMask(5, new double[5 * 5]{	0, 0, 1, 0, 0,
											0, 1, 1, 1, 0,
											1, 1, 1, 1, 1, 
											0, 1, 1, 1, 0, 
											0, 0, 1, 0, 0, });
	unsigned char* filter_2 = f.applyMaskAndGenerateImg(img, w, h);
	grid->addImage(filter_2, w, h, 0, 2, "Filtru 2");
	grid->addHistogram(calculateHistogram(filter_2, w, h), 256, 1, 2, "histo_2");
	//f.printMask();

	//filtru 3
	f.changeMask(9);
	unsigned char* filter_3 = f.applyMaskAndGenerateImg(img, w, h);
	grid->addImage(filter_3, w, h, 0, 3, "Filtru Eye");
	grid->addHistogram(calculateHistogram(filter_3, w, h), 256, 1, 3, "histo_3");
	//f.printMask();

	f.changeMask(11, Filter::FilterType::UNIFORM);
	unsigned char* filter_4 = f.applyMaskAndGenerateImg(img, w, h);
	grid->addImage(filter_4, w, h, 0, 4, "Filtru Uniform");
	grid->addHistogram(calculateHistogram(filter_4, w, h), 256, 1, 4, "histo_4");
	//f.printMask();

	f.changeMask(11, Filter::FilterType::GAUSS);
	unsigned char* filter_5 = f.applyMaskAndGenerateImg(img, w, h);
	grid->addImage(filter_5, w, h, 0, 5, "Filtru Gauss");
	grid->addHistogram(calculateHistogram(filter_5, w, h), 256, 1, 5, "histo_5");
	f.printMask();

	grid->show();
	return a.exec();
}

