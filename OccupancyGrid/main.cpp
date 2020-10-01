#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {

	cv::Mat imageGray = cv::imread("D:/Documents/UFPB/Robótica/Práticas C++/Mapping/OccupancyGrid/mapa.bmp", cv::IMREAD_GRAYSCALE); //Ler e assegurar que a imagem está em escala de cinza

	if (imageGray.empty()) {
		cout << "Não pôde abrir imagem." <<endl;
		cin.get();
		return -1;
	}

	cv::imshow("Map (PNG)", imageGray); // Desse jeito branco representa lugares vagos e preto representa lugares ocupados.

	//cv::bitwise_not(imageGray, imageGray); //Inverter os valores, pois 0 (preto) representa lugares vagos e 1 lugares ocupados.

	cv::Mat imageBW; //Imagem Binária

	cv::threshold(imageGray, imageBW, 0, 255.0, cv::THRESH_BINARY); // Depois do treshold, todos os valores são 0 ou 255.

	//cv::normalize(imageGray, imageBW, 0, 255, cv::NORM_MINMAX, CV_32FC1); 
	
	cv::Mat imageGrid = imageBW / 255; // Divide os valores por 255, para binarizar a imagem.

	//cv::imshow("imageGrid", imageGrid);

	cv::imwrite("imageGrid.pgm", imageGrid); // Salvando a imagem.

	//imageGrid.convertTo(imageGrid, CV_8UC1);

	cv::FileStorage file("output.yaml", cv::FileStorage::WRITE); // Escrevendo o resultado.
	file << "grid " << imageGrid;
	file.release();

	cv::waitKey(0);

	cv::destroyAllWindows();
	return 0;
}