#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/gapi/imgproc.hpp>
#include <tuple>
#include <vector>

using namespace std;

int main() {

	cv::Mat img = cv::imread("D:/Documents/UFPB/Robótica/Práticas C++/Mapping/OccupancyGrid/mapa.bmp"/*, cv::IMREAD_GRAYSCALE*/); //Ler e assegurar que a imagem está em escala de cinza
	cv::Mat imageGray;
	cv::cvtColor(img, imageGray, cv::COLOR_BGR2GRAY);

	/*cout << imageGray.type() << endl;*/

	if (imageGray.empty()) {
		cout << "Não pôde abrir imagem." <<endl;
		cin.get();
		return -1;
	}

	//cv::bitwise_not(imageGray, imageGray); //Inverter os valores, pois 0 (preto) representa lugares vagos e 1 lugares ocupados.

	cv::Mat imageBinary; //Imagem Binária

	cv::threshold(imageGray, imageBinary, 0, 255.0, cv::THRESH_BINARY); // Depois do treshold, todos os valores são 0 ou 255.

	cv::imshow("imageBinary", imageBinary);
	
	cv::Mat imageGrid = imageBinary / 255; // Divide os valores por 255, para binarizar a imagem.

	//cout << "Matrix Type: " << imageGrid.type() << endl;

	cv::imshow("imageGrid", imageGrid);

	cv::imwrite("imageGrid.pgm", imageGrid); // Salvando a imagem.

	int resolucaoMapa = 50;
	int resolucaoAstar = 5;

	cout << "Grid Width: " << imageGrid.cols << endl;
	cout << "Grid Height: " << imageGrid.rows << endl;

	cv::Mat imageCellDivision = cv::Mat::zeros(imageGrid.rows/resolucaoAstar, imageGrid.cols/resolucaoAstar, CV_8UC1);

	//cout << imageCellDivision << endl;
	
	cout << "Primeiro valor: " << (int)imageGrid.at<uchar>(0, 0) << endl;

	for (int i = 0, m = 0; i < imageGrid.cols || m < (imageGrid.cols /resolucaoAstar); i += 5, m++){
		for (int j = 0, n = 0; j < imageGrid.rows || n < (imageGrid.rows / resolucaoAstar); j += 5, n++) {
			imageCellDivision.at<uchar>(n, m) = imageGrid.at<uchar>(j, i);
		}
	}

	cout << "Cell Image Width: " << imageCellDivision.cols << endl;
	cout << "Cell Image Height: " << imageCellDivision.rows << endl;

	//imageCellDivision = imageCellDivision * 255;
	//cv::imwrite("imageCellDivision.bmp", imageCellDivision); // Salvando a imagem.

	//cv::FileStorage file("output.yaml", cv::FileStorage::WRITE); // Escrevendo o resultado.
	//file << "grid " << imageGrid;
	//file.release();

	/*cv::bitwise_not(imageCellDivision, imageCellDivision);
	cv::imwrite("imageCellDivisionInverted2.bmp", imageCellDivision);*/

	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}