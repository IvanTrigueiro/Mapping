#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;

int main() {
  // Ler e assegurar que a imagem esta em escala de cinza
  cv::Mat imageGray = cv::imread("./static/mapa.png", cv::IMREAD_GRAYSCALE);

  if (imageGray.empty()) {
    cout << "could not open the image" << endl;
    cin.get();
    return -1;
  }

  // Desse jeito branco representa lugares vagos e preto representa lugares
  // ocupados.
  cv::imshow("Map (PNG)", imageGray);

  // cv::bitwise_not(imageGray, imageGray); //Inverter os valores, pois 0
  // (preto) representa lugares vagos e 1 lugares ocupados.

  cv::Mat imageBW;  // Imagem Binaria

  // Depois do treshold, todos os valores sao 0 ou 255.
  cv::threshold(imageGray, imageBW, 0, 255.0, cv::THRESH_BINARY);

  // cv::normalize(imageGray, imageBW, 0, 255, cv::NORM_MINMAX, CV_32FC1);

  // Divide os valores por 255, para binarizar a imagem.
  cv::Mat imageGrid = imageBW / 255;

  // cv::imshow("imageGrid", imageGrid);

  cv::imwrite("./static/imageGrid.pgm", imageGrid);  // Salvando a imagem.

  // imageGrid.convertTo(imageGrid, CV_8UC1);

  // Escrevendo o resultado.
  cv::FileStorage file("./output/map.yaml", cv::FileStorage::WRITE);

  file << "grid " << imageGrid;
  file.release();

  cv::waitKey(0);

  cv::destroyAllWindows();
  return 0;
}