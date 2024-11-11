#include <iostream>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;
using namespace cv;

void addImpulseNoise(Mat& image, int probability, double mean, double stdDev);
void medianFilter(Mat& image);
void kenny(Mat& image);
void verticalReflection(Mat& image);

int main() {
    Mat image = imread("H.bmp", IMREAD_UNCHANGED);
    while (true) {
        int result;
        cout << "What transformation to apply? \n1.Median filter\n2.Kenny\n3.Vertical reflection\n4.Add noice\n";
        cin >> result;
        switch (result) {
        case 1:
            medianFilter(image);;
            break;
        case 2:
            kenny(image);;
            break;
        case 3:
            verticalReflection(image);
            break;
        case 4:
            addImpulseNoise(image, 30, 0, 1.5);
            break;
        }
        imwrite("result.bmp", image);
        system("result.bmp");
    }

    float noiseProbability = 0.5;
}

void addImpulseNoise(Mat& image, int probability, double mean, double stdDev) {
    int width = image.cols;
    int height = image.rows;
    int totalPixels = width * height;
    int noisyPixelsCount = static_cast<int>(totalPixels * probability);

    random_device rd;
    mt19937 gen(rd());
    normal_distribution<double> d(mean, stdDev);
    uniform_int_distribution<int> dist_width(0, width - 1);
    uniform_int_distribution<int> dist_height(0, height - 1);

    for (int i = 0; i < noisyPixelsCount; i++) {
        int x = dist_width(gen);
        int y = dist_height(gen);
        Vec3b color = image.at<Vec3b>(y, x);

        double newBlue = color[0] + d(gen);
        double newGreen = color[1] + d(gen);
        double newRed = color[2] + d(gen);

        color[0] = newBlue < 0 ? 0 : (newBlue > 255 ? 255 : newBlue);
        color[1] = newGreen < 0 ? 0 : (newGreen > 255 ? 255 : newGreen);
        color[2] = newRed < 0 ? 0 : (newRed > 255 ? 255 : newRed);

        image.at<Vec3b>(y, x) = color;
    }
}

void medianFilter(Mat& image) {
    Mat medianImage;
    medianBlur(image, medianImage, 3);
    image = medianImage;
}

void kenny(Mat& image) {
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    cv::Mat thresh;
    cv::threshold(gray, thresh, 127, 255, cv::THRESH_BINARY);

    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;;
    cv::findContours(thresh, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> extContours;
    vector<Vec4i> extHierarchy;
    findContours(thresh, extContours, extHierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    for (const auto& extContour : extContours) {
        contours.erase(std::remove_if(contours.begin(), contours.end(),
            [&extContour](const std::vector<cv::Point>& contour) {
                return contour == extContour;
            }), contours.end());
    }
    cv::Mat drawing = cv::Mat::zeros(thresh.size(), CV_8UC3);
    for (size_t i = 0; i < contours.size(); i++) {
        cv::drawContours(drawing, contours, (int)i, cv::Scalar(0, 255, 0), 2, 8, hierarchy, 0);
    }
    image = drawing;
}

void verticalReflection(Mat& image) {
    Mat transformMatrix = (Mat_<double>(2, 3) << 1, 0, 0, 0, -1, image.rows);;
    warpAffine(image, image, transformMatrix, image.size());
}
