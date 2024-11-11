#include <iostream>
#include "stdafx.h"
#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

#include <Windows.h> // For BYTE definition
#include <cstdlib>   // For rand() and srand()
#include <ctime>     
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

void addAdditiveNoise(int noiseLevel) {
	srand((time(0)));

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int noiseRed = (rand() % (2 * noiseLevel + 1)) - noiseLevel;
			int noiseGreen = (rand() % (2 * noiseLevel + 1)) - noiseLevel;
			int noiseBlue = (rand() % (2 * noiseLevel + 1)) - noiseLevel;

			int newRed = src_image[x + y * width].red + noiseRed;
			newRed < 0 ? newRed = 0 : false;
			newRed > 255 ? newRed = 255 : false;
			src_image[x + y * width].red = static_cast<BYTE>(newRed);

			int newGreen = src_image[x + y * width].green + noiseGreen;
			newGreen < 0 ? newGreen = 0 : false;
			newGreen > 255 ? newGreen = 255 : false;
			src_image[x + y * width].green = static_cast<BYTE>(newGreen);

			int newBlue = src_image[x + y * width].blue + noiseBlue;
			newBlue < 0 ? newBlue = 0 : false;
			newBlue > 255 ? newBlue = 255 : false;
			src_image[x + y * width].blue = static_cast<BYTE>(newBlue);
		}
	}
}

void lowPassFiltering() {
	for (int y = 1; y < height - 1; y++) {
		for (int x = 1; x < width - 1; x++) {
			int maxRed = src_image[(x - 1) + (y - 1) * width].red +
				src_image[(x - 1) + y * width].red +
				src_image[(x - 1) + (y + 1) * width].red +
				src_image[x + (y - 1) * width].red +
				src_image[x + y * width].red +
				src_image[x + (y + 1) * width].red +
				src_image[(x + 1) + (y - 1) * width].red +
				src_image[(x + 1) + y * width].red +
				src_image[(x + 1) + (y + 1) * width].red;
			double res = maxRed / 9;
			src_image[x + y * width].red = static_cast<BYTE>(res);

			int maxGreen = src_image[(x - 1) + (y - 1) * width].green +
				src_image[(x - 1) + y * width].green +
				src_image[(x - 1) + (y + 1) * width].green +
				src_image[x + (y - 1) * width].green +
				src_image[x + y * width].green +
				src_image[x + (y + 1) * width].green +
				src_image[(x + 1) + (y - 1) * width].green +
				src_image[(x + 1) + y * width].green +
				src_image[(x + 1) + (y + 1) * width].green;
			res = maxGreen / 9;
			src_image[x + y * width].green = static_cast<BYTE>(res);

			int maxBlue = src_image[(x - 1) + (y - 1) * width].blue +
				src_image[(x - 1) + y * width].blue +
				src_image[(x - 1) + (y + 1) * width].blue +
				src_image[x + (y - 1) * width].blue +
				src_image[x + y * width].blue +
				src_image[x + (y + 1) * width].blue +
				src_image[(x + 1) + (y - 1) * width].blue +
				src_image[(x + 1) + y * width].blue +
				src_image[(x + 1) + (y + 1) * width].blue;
			res = maxBlue / 9;
			src_image[x + y * width].blue = static_cast<BYTE>(res);
		}
	}
}

int main(int argc, char* argv[]) {
	srand((unsigned)time(NULL));

	string path_to_image, temp;

	ReadPath(path_to_image);
	OpenImage(path_to_image);
	cout << "Whaat do? 1.Add noise 2.remove noise\n";
	int result;
	cin >> result;
	if (result == 1) {
		addAdditiveNoise(10);
	}
	else {
		lowPassFiltering();
	}
	SaveImage("result.bmp");
	ClearMemory();
	cout << "END!" << endl;
	return 0;
}
