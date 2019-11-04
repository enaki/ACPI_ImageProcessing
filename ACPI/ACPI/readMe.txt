
Scroll wheel - zoom in/out

Left button drag - deplasare in imagine cand aceasta este mai mare decat fereastra

Ctrl+A - activeaza / dezactiveaza ajustarea automata a dimensiunii imaginii 
		 pe care se afla cursorul mouse-ului

Shift+A - activeaza / dezactiveaza ajustarea automata a dimensiunii 
		  tuturor imaginilor

Ctrl+R - reseteaza imaginea curenta la dimensiunile sale initiale

Shift+R - reseteaza toate imaginile la dimensiunile lor initiale


//--------------------------All operations-------------------------------------//

	grid->addImage(img, w, h, 0, 0, "Original");

	unsigned char* negated = applyOperation(img, w, h, negateImage);
	grid->addImage(negated, w, h, 0, 1, "Negate Image");
	
	unsigned char* binarized_1 = applyOperation(img, w, h, binarizeImage{80});
	grid->addImage(binarized_1, w, h, 0, 2, "Binarized Image threshold=80");

	unsigned char* binarized_2 = applyOperation(img, w, h, binarizeImage{ 90 });
	grid->addImage(binarized_2, w, h, 0, 3, "Binarized Image threshold=90");

	unsigned char* lighted_1 = applyOperation(img, w, h, enlightImage{ 35 });
	grid->addImage(lighted_1, w, h, 0, 4, "Lighted Image d=35");

	unsigned char* lighted_2 = applyOperation(img, w, h, enlightImage{ -30 });
	grid->addImage(lighted_2, w, h, 1, 0, "Lighted Image d=-30");

	unsigned char* contrast = applyOperation(img, w, h, contrastImage{ 60, 195, 25, 225 });
	grid->addImage(contrast, w, h, 1, 1, "Contrast Image ");

	unsigned char* gamma_1 = applyOperation(img, w, h, gammaCorectionImage{ 1, 1.2 });
	grid->addImage(gamma_1, w, h, 1, 2, "Gamma Correction Image 120%");
	
	unsigned char* gamma_2 = applyOperation(img, w, h, gammaCorectionImage{ 1, 0.8 });
	grid->addImage(gamma_2, w, h, 1, 3, "Gamma Correction Image 80%");

	unsigned char* contrast_compress = applyOperation(img, w, h, contrastCompressImage{ 25 });
	grid->addImage(contrast_compress, w, h, 1, 4, "Contrast Compress");
	
	
	
	for (int i = 0; i < 8; i++) {
		unsigned char* slicing_image = applyOperation(img, w, h, bitSlicingImage{ i });
		QString title = "Bit Slicing ";
		title.append('0'+i);
		grid->addImage(slicing_image, w, h, i / 5, i % 5, title);
	}

	unsigned char* window_1 = applyOperation(img, w, h, windowOperationImage{ 1, 140, 180 });
	grid->addImage(window_1, w, h, 1, 3, "Window Operation 1 (140 - 180)p");

	unsigned char* window_2 = applyOperation(img, w, h, windowOperationImage{ 0, 140, 180 });
	grid->addImage(window_2, w, h, 1, 4, "Window Operation 2 (140 - 180)p");


//-------------------------------------histogram test---------------------------------------------------//

	grid->addImage(img, w, h, 0, 0, "Original");
	grid->addHistogram(calculateHistogram(img, w, h), 256, 1, 0, "histo_1");


	unsigned char* equalizer = equalizeHistogram(img, w, h);
	grid->addImage(equalizer, w, h, 0, 1, "Equalized");
	grid->addHistogram(calculateHistogram(equalizer, w, h), 256, 1, 1, "histo_2");

	unsigned char* negated = applyOperation(img, w, h, negateImage);
	grid->addImage(negated, w, h, 0, 1, "Negate Image");
	grid->addHistogram(calculateHistogram(negated, w, h), 256, 1, 1, "histo_2");

	unsigned char* binarized_1 = applyOperation(img, w, h, binarizeImage{ 80 });
	grid->addImage(binarized_1, w, h, 0, 2, "Binarized Image threshold=80");
	grid->addHistogram(calculateHistogram(binarized_1, w, h), 256, 1, 2, "histo_3");

	unsigned char* contrast_compress = applyOperation(img, w, h, contrastCompressImage{ 25 });
	grid->addImage(contrast_compress, w, h, 0, 3, "Contrast Compress");
	grid->addHistogram(calculateHistogram(contrast_compress, w, h), 256, 1, 3, "histo_4");


//-------------------------------------histogram test equalizer---------------------------------------------------//
	unsigned char* equalizer = equalizeHistogram(img, w, h);
	grid->addImage(equalizer, w, h, 0, 1, "Equalized");
	grid->addHistogram(calculateHistogram(equalizer, w, h), 256, 1, 1, "histo_2");
	
	unsigned char* equalizer_addaptive = adaptiveEqualizeHistogram(img, w, h, 101);
	grid->addImage(equalizer_addaptive, w, h, 0, 2, "Adaptive Equalized");
	grid->addHistogram(calculateHistogram(equalizer_addaptive, w, h), 256, 1, 2, "histo_3");