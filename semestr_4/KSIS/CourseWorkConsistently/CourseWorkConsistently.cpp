#include <opencv2/opencv.hpp>
#include <opencv2/core/utils/logger.hpp>
#include <vector>

cv::Mat applyRobertsFilter(const cv::Mat& image) {
    cv::Mat grad_x, grad_y;
    cv::Mat kernel_x = (cv::Mat_<float>(2, 2) <<
        1, 0,
        0, -1);
    cv::Mat kernel_y = (cv::Mat_<float>(2, 2) <<
        0, 1,
        -1, 0);

    cv::filter2D(image, grad_x, CV_32F, kernel_x);
    cv::filter2D(image, grad_y, CV_32F, kernel_y);

    cv::Mat magnitude;
    cv::magnitude(grad_x, grad_y, magnitude);

    cv::Mat result;
    magnitude.convertTo(result, CV_8U);
    return result;
}

cv::Mat resize(const cv::Mat& image) {
    cv::Mat result;
    cv::resize(image, result, cv::Size(), 0.5, 0.5);
    return result;
}

cv::Mat imageProcessing(const cv::Mat& image) {
    return applyRobertsFilter(resize(image));
}

int main() {
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
    cv::Mat image = cv::imread("input.jpg", cv::IMREAD_GRAYSCALE);
    if (image.empty()) {
        std::cerr << "Error: Unable to read image file." << std::endl;
        return -1;
    }

    std::clock_t timer = std::clock();
    image = imageProcessing(image);
    timer = std::clock() - timer;
    std::cout << timer << " ms" << std::endl;
    cv::imwrite("output.jpg", image);
    return 0;
}