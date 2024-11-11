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

const string fileExtention = ".gia";
string tempPath;

enum Extention {
	EXT_BMP,
	EXT_GIA,
	NULLL
};
Extention extention = NULLL;

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

//1, 4, 5, 6, 8, 11, 12
typedef struct tFILEHEADER {
	WORD gfType;           // (1) Идентификатор типа файла (2 байта)
	DWORD gfRasterSize;    // (4) Размер растра в байтах (4 байта)
	WORD gfRasterOffset;   // (5) Смещение растровых данных от начала файла в байтах (2 байта)
	DWORD gfWidth;         // (6) Ширина изображения в пикселях (4 байта)
	DWORD gfImageSize;     // (8) Размер изображения в пикселях (4 байта)
	char comment[16];      // (11) Комментарий (16 байт)
	WORD gfVersion;        // (12) Версия файла (2 байта)
} giaFileHead;

giaFileHead giaHead;

//Пиксель
struct Color {
	BYTE blue;
	BYTE green;
	BYTE red;
};

//Размер 1-го пикселя
int pixel_size = sizeof(Color);


//1 - BMP, 2 - GIA
int img_type = 0;

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

//Вывести заголовок GIA файла
void ShowGIAHeaders(giaFileHead fh) {
	cout << "File Type: " << (CHAR)fh.gfType << endl;
	cout << "Comment: " << fh.comment << endl;
	cout << "Version: " << fh.gfVersion << endl;
	cout << "Raster Size: " << fh.gfRasterSize << " bytes" << endl;
	cout << "Image Size: " << fh.gfImageSize << " pixels" << endl;
	cout << "Offset: " << fh.gfRasterOffset << " bytes" << endl;
	cout << "Width: " << fh.gfWidth << " pixels" << endl;
}

Extention getFileExtention(string path) {
	size_t dotPosition = path.rfind('.');

	if (dotPosition != string::npos || dotPosition != path.length() - 1) {
		if (path.substr(dotPosition) == ".bmp") {
			return Extention::EXT_BMP;
		}
		else if (path.substr(dotPosition) == ".gia") {
			return Extention::EXT_GIA;
		}
	}
	return Extention::NULLL;
}

//Функция для загрузки изображения
bool OpenImage(string path) {
	ifstream img_file;
	Color temp;
	char buf[3];

	//Открыть файл на чтение
	img_file.open(path.c_str(), ios::in | ios::binary);
	if (!img_file) {
		cout << "File isn`t open!" << endl;
		return false;
	}

	if (getFileExtention(path) == Extention::EXT_BMP) { //if bmp
		//Считать заголовки BMP
		img_file.read((char*)&FileHead, sizeof(FileHead));
		img_file.read((char*)&InfoHead, sizeof(InfoHead));

		img_type = 1;
		width = InfoHead.biWidth;
		height = InfoHead.biHeight;

		src_image = new Color[width * height];

		int i, j;
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				img_file.read((char*)&temp, pixel_size);
				src_image[i * width + j] = temp;
			}
			//Дочитать биты используемые для выравнивания до двойного слова
			img_file.read((char*)buf, j % 4);
		}
		img_file.close();
	}
	else {
		//Считать заголовок GIA
		img_file.read((char*)&giaHead, sizeof(giaHead));

		img_type = 2;

		width = giaHead.gfWidth;
		height = giaHead.gfImageSize / width;

		src_image = new Color[width * height]; //height ???

		int i, j;
		for (i = 0; i < height; i++) {
			for (j = 0; j < width; j++) {
				img_file.read((char*)&temp, pixel_size);
				src_image[i * width + j] = temp;
			}
		}
		img_file.close();
	}
	return true;
}

//Функция для сохранения изображения
bool Save(string path, Extention outputExtention) {
	ofstream img_file;
	char buf[3];

	if (img_type == 1) {
		switch (outputExtention) {
		case EXT_BMP:
			tempPath = "result.bmp";
			img_file.open(tempPath, ios::out | ios::binary);
			img_file.write((char*)&FileHead, sizeof(FileHead));
			img_file.write((char*)&InfoHead, sizeof(InfoHead));
			break;
		case EXT_GIA:
			tempPath = "result.gia";
			img_file.open(tempPath, ios::out | ios::binary);
			giaHead.gfType = FileHead.bfType; // (1)
			giaHead.gfWidth = InfoHead.biWidth; // (6)
			giaHead.gfImageSize = InfoHead.biHeight * InfoHead.biWidth; // (8)
			giaHead.gfRasterSize = giaHead.gfImageSize * 8 / InfoHead.biBitCount; // (4) размер изображения в пикселях * 8 / глубина цвета
			strncpy_s(giaHead.comment, "Hello, World!", sizeof(giaHead.comment) - 1); // (11)
			giaHead.comment[sizeof(giaHead.comment) - 1] = '\0';
			giaHead.gfVersion = 1; // (12)
			giaHead.gfRasterOffset = sizeof(giaHead) + 1; // (5)
			img_file.write((char*)&giaHead, sizeof(giaHead));
			img_type = 2;
			break;
		default:
			break;
		}
	}
	else if (img_type == 2) {
		int padding_size, image_size;
		switch (outputExtention) {
		case EXT_BMP:
			tempPath = "result.bmp";
			img_file.open(tempPath, ios::out | ios::binary);
			padding_size = (4 - width % 4) % 4;
			image_size = (width + padding_size) * height * pixel_size;

			FileHead.bfType = giaHead.gfType;
			FileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + image_size;
			FileHead.bfReserved1 = 0;
			FileHead.bfReserved2 = 0;
			FileHead.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

			InfoHead.biSize = sizeof(BITMAPINFOHEADER);
			InfoHead.biWidth = width;
			InfoHead.biHeight = height;
			InfoHead.biPlanes = 1;
			InfoHead.biBitCount = 24;
			InfoHead.biCompression = 0;
			InfoHead.biSizeImage = image_size;
			InfoHead.biXPelsPerMeter = 0;
			InfoHead.biYPelsPerMeter = 0;
			InfoHead.biClrUsed = 0;
			InfoHead.biClrImportant = 0;

			img_file.write((char*)&FileHead, sizeof(FileHead));
			img_file.write((char*)&InfoHead, sizeof(InfoHead));

			img_type = 1;
			break;
		case EXT_GIA:
			tempPath = "result.gia";
			img_file.open(tempPath, ios::out | ios::binary);
			img_file.write((char*)&giaHead, sizeof(giaHead));
			break;
		}
	}

	int i, j;
	if (dst_image == 0) {
		dst_image = new Color[width * height];
		memcpy(dst_image, src_image, width * height * sizeof(Color));
	}

	for (i = 0; i < height; i++) {
		for (j = 0; j < width; j++) {
			img_file.write((char*)&dst_image[i * width + j], pixel_size);
		}
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
	switch (img_type) {
	case 1:
		ShowBMPHeaders(FileHead, InfoHead);
		system(path.c_str());
		break;
	case 2:
		ShowGIAHeaders(giaHead);
		break;
	default:
		cout << "Incorrect image type" << endl;
		break;
	}
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

void BlackVignette() {
	int xCenter = width / 2;
	int yCenter = height / 2;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int distance = sqrt((x - xCenter)*(x - xCenter) + (y - yCenter)*(y - yCenter));
			double normalized_distance = distance / sqrt(xCenter * xCenter + yCenter * yCenter);
			double vignette_factor = 1 - normalized_distance * normalized_distance;
			src_image[x + y * width].red *= vignette_factor;
			src_image[x + y * width].green *= vignette_factor;
			src_image[x + y * width].blue *= vignette_factor;
		}
	}
}

void WhiteVignette() {
	int xCenter = width / 2;
	int yCenter = height / 2;

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int distance = sqrt((x - xCenter) * (x - xCenter) + (y - yCenter) * (y - yCenter));
			double normalized_distance = distance / sqrt(xCenter * xCenter + yCenter * yCenter);
			double vignette_factor = normalized_distance * normalized_distance;
			src_image[x + y * width].red = src_image[x + y * width].red + (255 - src_image[x + y * width].red) * vignette_factor;
			src_image[x + y * width].green = src_image[x + y * width].green + (255 - src_image[x + y * width].green) * vignette_factor;
			src_image[x + y * width].blue = src_image[x + y * width].blue + (255 - src_image[x + y * width].blue) * vignette_factor;
		}
	}
}

void SelectConversion() {
	int result;
	cout << "\nWhat conversion to apply?\n1.Black vignette\n2.White vignette\n3.Save without conversion\nYour choise: ";
	cin >> result;
	switch (result) {
	case 1:
		BlackVignette();
		break;
	case 2:
		WhiteVignette();
		break;
	case 3:
		break;
	default:
		cout << "\nInput error";
		break;
	}
}

void SelectFormatForSaving(Extention& formatForSaving) {
	int result;
	cout << "What format to save in?\n1.bmp\n2.gia\nYour choise: ";
	cin >> result;

	switch (result) {
	case 1:
		formatForSaving = Extention::EXT_BMP;
		break;
	case 2:
		formatForSaving = Extention::EXT_GIA;
		break;
	default:
		formatForSaving = Extention::NULLL;
		cout << "\nInput error";
		break;
	}
}

int main(int argc, char* argv[]) {
	srand((unsigned)time(NULL));

	//Путь к текущему изображению
	string path_to_image, temp;
	Extention formatForSaving = Extention::NULLL;

	ReadPath(path_to_image);
	OpenImage(path_to_image);
	SelectConversion();
	SelectFormatForSaving(formatForSaving);
	Save(path_to_image, formatForSaving);

	ShowImage(tempPath);
	ClearMemory();
	cout << "END!" << endl;
	return 0;
}
