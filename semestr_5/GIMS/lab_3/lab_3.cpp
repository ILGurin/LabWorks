#include <iostream>
#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;
#pragma pack(2)

string tempPath;

//Заголовок файла BMP 
typedef struct tBITMAPFILEHEADER {
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
}sFileHead;

//Заголовок BitMap's
typedef struct tBITMAPINFOHEADER {
	DWORD biSize;
	LONG biWidth;
	LONG biHeight;
	WORD biPlanes;
	WORD biBitCount;
	DWORD biCompression;
	DWORD biSizeImage;
	LONG biXPelsPerMeter;
	LONG biYPelsPerMeter;
	DWORD biClrUsed;
	DWORD biClrImportant;
}sInfoHead;

sFileHead FileHead;
sInfoHead InfoHead;

//Пиксель
struct Color {
	BYTE blue;
	BYTE green;
	BYTE red;
};

//Размер 1-го пикселя
int pixel_size = sizeof(Color);


//1 - BMP, 2 - GIA
//int img_type = 0;

//Исходное изображение
Color* src_image = 0;
//Результативное изображение
Color* dst_image = 0;

//Размер изображения
int width = 0;
int height = 0;

//Вывести заголовок BMP файла
void ShowBMPHeaders(tBITMAPFILEHEADER fh, tBITMAPINFOHEADER ih) {
	cout << "Type: " << (CHAR)fh.bfType << endl;
	cout << "Size: " << fh.bfSize << endl;
	cout << "Shift of bits: " << fh.bfOffBits << endl;
	cout << "Width: " << ih.biWidth << endl;
	cout << "Height: " << ih.biHeight << endl;
	cout << "Planes: " << ih.biPlanes << endl;
	cout << "BitCount: " << ih.biBitCount << endl;
	cout << "Compression: " << ih.biCompression << endl;
}

//Функция для загрузки изображения
bool OpenImage(string path) {
	ifstream img_file;
	Color temp;
	char buf[3];

	//Открыть файл на чтение
	img_file.open(path.c_str(), ios::in | ios::binary);
	if (!img_file)
	{
		cout << "File isn`t open!" << endl;
		return false;
	}

	//Считать заголовки BMP
	img_file.read((char*)&FileHead, sizeof(FileHead));
	img_file.read((char*)&InfoHead, sizeof(InfoHead));

	/*img_type = 1;*/
	ShowBMPHeaders(FileHead, InfoHead);
	width = InfoHead.biWidth;
	height = InfoHead.biHeight;


	src_image = new Color[width * height];

	int i, j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			img_file.read((char*)&temp, pixel_size);
			src_image[i * width + j] = temp;
		}
		//Дочитать биты используемые для выравнивания до двойного слова
		img_file.read((char*)buf, j % 4);
	}
	img_file.close();

	return true;
}

//Функция для сохранения изображения
bool SaveImage(string path) {
	ofstream img_file;
	char buf[3];

	img_file.open(path.c_str(), ios::out | ios::binary);
	if (!img_file)
	{
		return false;
	}

	img_file.write((char*)&FileHead, sizeof(FileHead));
	img_file.write((char*)&InfoHead, sizeof(InfoHead));

	dst_image = new Color[width * height];
	memcpy(dst_image, src_image, width * height * sizeof(Color));


	int i, j;
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			img_file.write((char*)&dst_image[i * width + j], pixel_size);
		}
		img_file.write((char*)buf, j % 4);
	}
	img_file.close();

	return true;
}

//Скопировать содержимое результируещего изображения в начальное
void CopyDstToSrc() {
	if (dst_image != 0) {
		memcpy(src_image, dst_image, width * height * sizeof(Color));
	}
}

//Отобразить текущее изображение с помощью вызова стандартного просмотрщика
void ShowImage(string path) {
	ShowBMPHeaders(FileHead, InfoHead);
	system(path.c_str());
}
//Считать путь к изображению
void ReadPath(string& str) {
	str.clear();
	cout << "Enter path to image" << endl;
	cin >> str;
}

void ClearMemory(void) {
	//Освободить память исходного изображения
	if (src_image != 0) {
		delete[] src_image;
	}
	//Освободить память результрующего изображения
	if (dst_image != 0) {
		delete[] dst_image;
	}
}

void applyRobertsCross(vector<vector<int>> matrix) {
	vector<vector<int>> newMatrix(height, vector<int>(width));
	vector<int> vec;
	vector<int> allvec;
	for (int y = 0; y < height - 1; ++y) {
		for (int x = 0; x < width - 1; ++x) {
			newMatrix[y][x] = abs(matrix[y][x] - matrix[y + 1][x + 1]) + abs(matrix[y][x+1] - matrix[y+1][x]);

			allvec.push_back(newMatrix[y][x]);
			auto it = std::find(vec.begin(), vec.end(), newMatrix[y][x]);
			if (it != vec.end()) {
			}
			else {
				vec.push_back(newMatrix[y][x]);
			}

		}
	}
	sort(vec.begin(), vec.end());
	sort(allvec.begin(), allvec.end());
	for (size_t i = 0; i < vec.size(); ++i) {
		std::cout << vec[i] << " ";
	}
	int avg = vec[(vec.size()/2/2/2)];
	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			if (newMatrix[y][x] < avg) {
				src_image[y * width + x].red = 255;
				src_image[y * width + x].green = 255;
				src_image[y * width + x].blue = 255;
			}
			else {
				src_image[y * width + x].red = 0;
				src_image[y * width + x].green = 0;
				src_image[y * width + x].blue = 0;
			}
		}
	}

}

vector<vector<int>> conversionToLuminanceMatrix() {
	vector<vector<int>> brightnessMatrix(height, vector<int>(width));
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int red = src_image[y * width + x].red;
			int green = src_image[y * width + x].green;
			int blue = src_image[y * width + x].blue;

			int brightness = static_cast<int>(0.3 * red + 0.6 * green + 0.1 * blue);
			brightnessMatrix[y][x] = brightness;
		}
	}
	return brightnessMatrix;
}

int main(int argc, char* argv[]) {
	srand((unsigned)time(NULL));

	string path_to_image1, temp;
	path_to_image1 = "H.bmp";
	OpenImage(path_to_image1);
	applyRobertsCross(conversionToLuminanceMatrix());
	SaveImage("result.bmp");
	ClearMemory();
	cout << "END!" << endl;
	return 0;
}
