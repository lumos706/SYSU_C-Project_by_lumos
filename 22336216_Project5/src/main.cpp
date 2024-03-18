#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>

using namespace cv;
using namespace std;

string fileName;
string compressfile;
Mat compressimage;
Mat originalImage;

//vector<pair<int, uchar>> runLengthEncode(const Mat& image) {
//    vector<pair<int, uchar>> encodedData;
//    int count = 1;
//    for (int i = 1; i < image.rows; ++i) {
//        for (int j = 0; j < image.cols; ++j) {
//            if (image.at<uchar>(i, j) == image.at<uchar>(i - 1, j)) {
//                ++count;
//            } else {
//                encodedData.push_back({count, image.at<uchar>(i - 1, j)});
//                count = 1;
//            }
//        }
//    }
//    // 处理最后一行
//    encodedData.push_back({count, image.at<uchar>(image.rows - 1, 0)});
//    return encodedData;
//}
//
//// 将压缩数据写入文件
//void writeEncodedDataToFile(const vector<pair<int, uchar>>& encodedData, const string& fileName) {
//    ofstream outFile(fileName, ios::binary);
//    if (!outFile.is_open()) {
//        cout << "Error: Unable to open the file for writing." << endl;
//        return;
//    }
//
//    for (const auto& run : encodedData) {
//        // 写入重复次数
//        outFile.write(reinterpret_cast<const char*>(&run.first), sizeof(int));
//        // 写入像素值
//        outFile.write(reinterpret_cast<const char*>(&run.second), sizeof(uchar));
//    }
//
//    outFile.close();
//    cout << "Encoded data written to " << fileName << "." << endl;
//}
//vector<pair<int, uchar>> readEncodedDataFromFile(const string& fileName) {
//    ifstream inFile(fileName, ios::binary);
//    if (!inFile.is_open()) {
//        cout << "Error: Unable to open the file for reading." << endl;
//        return {};
//    }
//
//    vector<pair<int, uchar>> encodedData;
//    int count;
//    uchar pixelValue;
//
//    while (inFile.read(reinterpret_cast<char*>(&count), sizeof(int)) &&
//           inFile.read(reinterpret_cast<char*>(&pixelValue), sizeof(uchar))) {
//        encodedData.push_back({count, pixelValue});
//    }
//
//    inFile.close();
//    return encodedData;
//}
//
//// 游走编码解压函数
//Mat runLengthDecode(const vector<pair<int, uchar>>& encodedData, int imageWidth, int imageHeight) {
//    Mat decompressedImage(imageHeight, imageWidth, CV_8UC1, Scalar(0));
//
//    int rowIndex = 0;
//    int colIndex = 0;
//
//    for (const auto& run : encodedData) {
//        for (int i = 0; i < run.first; ++i) {
//            decompressedImage.at<uchar>(rowIndex, colIndex) = run.second;
//            ++colIndex;
//            if (colIndex == imageWidth) {
//                colIndex = 0;
//                ++rowIndex;
//            }
//        }
//    }
//
//    return decompressedImage;
//}


// (1) 图像数据的读取与写入存储，并通过第三方库调用 UI 窗口展示图片
void displayImage(const Mat& image, const string& windowName = "Image") {
    namedWindow(windowName, WINDOW_AUTOSIZE);
    imshow(windowName, image);
    waitKey(0);
    destroyAllWindows();
}

// (2) 实现图像数据的压缩存储
vector<uchar> compressImage(const Mat& image) {
    vector<uchar> compressedData;
    imencode(".ppm", image, compressedData);
    return compressedData;
}

// (3) 彩色图像转变为灰度图像
Mat convertToGray(const Mat& colorImage) {
    Mat grayImage;
    cvtColor(colorImage, grayImage, COLOR_BGR2GRAY);
    return grayImage;
}

// (4) 实现图像尺寸的缩放
Mat resizeImage(const Mat& originalImage, int width, int height) {
    Mat resizedImage;
    resize(originalImage, resizedImage, Size(width, height));
    return resizedImage;
}

// (5) 实现图像数据的解压缩
Mat decompressImage(const vector<uchar>& compressedData) {
    Mat decompressedImage = imdecode(compressedData, IMREAD_COLOR);
    return decompressedImage;
}

// 将压缩数据写入文件
void writeEncodedDataToFile(const vector<uchar>& compressedData, const string& fileName) {
    ofstream outFile(fileName, ios::binary);
    outFile.write(reinterpret_cast<const char*>(compressedData.data()), compressedData.size());
    cout << "压缩后的图像已经保存到 " << fileName << "." << endl;
}

// 从文件中读取压缩数据
vector<uchar> readCompressedDataFromFile(const string& fileName) {
    ifstream inFile(fileName, ios::binary | ios::ate);
    if (!inFile.is_open()) {
        cout << "错误：读取文件失败." << endl;
        return vector<uchar>();
    }

    streamsize fileSize = inFile.tellg();
    inFile.seekg(0, ios::beg);

    vector<uchar> loadedCompressedData(fileSize);
    inFile.read(reinterpret_cast<char*>(loadedCompressedData.data()), fileSize);

    inFile.close();
    return loadedCompressedData;
}

int main() {
    while (true) {
        // 用户输入图像文件名
        

        // 提示用户选择功能
        cout << "-----------------------------------------------------------------" << endl;
        cout << "选择一个功能：" << endl;
        cout << "1. 压缩图像" << endl;
        cout << "2. 转为灰色" << endl;
        cout << "3. 缩放图像" << endl;
        cout << "4. 解压图像" << endl;
        cout << "0. 退出程序" << endl;

        int choice;
        cout << "输入功能 (0 to exit): ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "输入文件名 (或者 'exit' ): ";
            cin >> fileName;
            compressfile = fileName;
            if (fileName == "exit") {
                cout << "退出程序." << endl;
                break;
            }

            // 读取图像
            originalImage = imread(fileName);
            compressimage = originalImage;
            // 检查图像是否成功读取
            if (originalImage.empty()) {
                cout << "错误：读取文件失败." << endl;
                continue;  // 回到循环开始，重新输入图像文件名
            }

            // 显示原始图像
            displayImage(originalImage, fileName);
            //vector<pair<int, uchar>> encodedData = runLengthEncode(originalImage);
            //// 将压缩数据写入文件
            //writeEncodedDataToFile(encodedData, "compressed_data.bin");
            
            vector<uchar> compressedData = compressImage(originalImage);
            writeEncodedDataToFile(compressedData, "compressed_data.bin");
            break;
        }
        case 2: {
            //  彩色图像转变为灰度图像
            cout << "输入文件名 (或者 'exit' ): ";
            cin >> fileName;

            if (fileName == "exit") {
                cout << "退出程序." << endl;
                break;
            }

            // 读取图像
            originalImage = imread(fileName);

            // 检查图像是否成功读取
            if (originalImage.empty()) {
                cout << "错误：读取文件失败." << endl;
                continue;  // 回到循环开始，重新输入图像文件名
            }

            // 显示原始图像
            displayImage(originalImage, fileName);
            Mat grayImage = convertToGray(originalImage);
            imwrite("gray_image.png", grayImage);
            displayImage(grayImage, "Gray Image");
            break;
        }
        case 3: {
            cout << "输入文件名 (或者 'exit' ): ";
            cin >> fileName;

            if (fileName == "exit") {
                cout << "退出程序." << endl;
                break;
            }

            // 读取图像
            Mat originalImage = imread(fileName);

            // 检查图像是否成功读取
            if (originalImage.empty()) {
                cout << "错误：读取文件失败." << endl;
                continue;  // 回到循环开始，重新输入图像文件名
            }

            // 显示原始图像
            displayImage(originalImage, fileName);
            //  实现图像尺寸的缩放
            int newWidth, newHeight;
            cout << "输入宽度： ";
            cin >> newWidth;
            cout << "输入高度： ";
            cin >> newHeight;

            Mat resizedImage = resizeImage(originalImage, newWidth, newHeight);

            imwrite("resized_image.png", resizedImage);
            displayImage(resizedImage, "Resized Image");
            break;
        }
        case 4: {
            //实现图像数据的解压缩
            


            vector<uchar> loadedCompressedData = readCompressedDataFromFile("compressed_data.bin");
            Mat decompressedImage = decompressImage(loadedCompressedData);

            imwrite("decompressed_image.ppm", decompressedImage);
            displayImage(decompressedImage, "Decompressed Image");
            break;
        }
        case 0:
            cout << "退出程序." << endl;
            return 0;
        default:
            cout << "非法操作. 请输入合法操作." << endl;
            break;
        }
    }

    return 0;
}


