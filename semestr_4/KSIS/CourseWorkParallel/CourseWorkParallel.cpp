#include <iostream>
#include <opencv2/opencv.hpp>
#include <mpi.h>
#include <opencv2/core/utils/logger.hpp>

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

int main(int argc, char** argv) {
    cv::utils::logging::setLogLevel(cv::utils::logging::LOG_LEVEL_SILENT);
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    cv::Mat image = cv::imread("input.png", cv::IMREAD_GRAYSCALE), result;
    if (image.empty()) {
        std::cerr << "Error: Unable to read image file." << std::endl;
        return -1;
    }

    std::clock_t timer = std::clock();
    int width = image.cols, height = image.rows;
    cv::Mat imagePart = image.clone()(cv::Rect(rank * (width / size), 0, width / size, height));

    imagePart = imageProcessing(imagePart);
    if (rank == 0) {
        result = imagePart.clone();
        for (int i = 1; i < size; i++) {
            MPI_Recv(imagePart.data, width * height * 3, MPI_UNSIGNED_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            cv::hconcat(result, imagePart, result);
        }

        timer = std::clock() - timer;
        std::cout << timer << " ms" << std::endl;
        cv::imwrite("output.png", result);
    }
    else {
        MPI_Send(imagePart.data, width * height * 3, MPI_UNSIGNED_CHAR, 0, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}