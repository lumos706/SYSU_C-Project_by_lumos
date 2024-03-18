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
//    // �������һ��
//    encodedData.push_back({count, image.at<uchar>(image.rows - 1, 0)});
//    return encodedData;
//}
//
//// ��ѹ������д���ļ�
//void writeEncodedDataToFile(const vector<pair<int, uchar>>& encodedData, const string& fileName) {
//    ofstream outFile(fileName, ios::binary);
//    if (!outFile.is_open()) {
//        cout << "Error: Unable to open the file for writing." << endl;
//        return;
//    }
//
//    for (const auto& run : encodedData) {
//        // д���ظ�����
//        outFile.write(reinterpret_cast<const char*>(&run.first), sizeof(int));
//        // д������ֵ
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
//// ���߱����ѹ����
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


// (1) ͼ�����ݵĶ�ȡ��д��洢����ͨ������������� UI ����չʾͼƬ
void displayImage(const Mat& image, const string& windowName = "Image") {
    namedWindow(windowName, WINDOW_AUTOSIZE);
    imshow(windowName, image);
    waitKey(0);
    destroyAllWindows();
}

// (2) ʵ��ͼ�����ݵ�ѹ���洢
vector<uchar> compressImage(const Mat& image) {
    vector<uchar> compressedData;
    imencode(".ppm", image, compressedData);
    return compressedData;
}

// (3) ��ɫͼ��ת��Ϊ�Ҷ�ͼ��
Mat convertToGray(const Mat& colorImage) {
    Mat grayImage;
    cvtColor(colorImage, grayImage, COLOR_BGR2GRAY);
    return grayImage;
}

// (4) ʵ��ͼ��ߴ������
Mat resizeImage(const Mat& originalImage, int width, int height) {
    Mat resizedImage;
    resize(originalImage, resizedImage, Size(width, height));
    return resizedImage;
}

// (5) ʵ��ͼ�����ݵĽ�ѹ��
Mat decompressImage(const vector<uchar>& compressedData) {
    Mat decompressedImage = imdecode(compressedData, IMREAD_COLOR);
    return decompressedImage;
}

// ��ѹ������д���ļ�
void writeEncodedDataToFile(const vector<uchar>& compressedData, const string& fileName) {
    ofstream outFile(fileName, ios::binary);
    outFile.write(reinterpret_cast<const char*>(compressedData.data()), compressedData.size());
    cout << "ѹ�����ͼ���Ѿ����浽 " << fileName << "." << endl;
}

// ���ļ��ж�ȡѹ������
vector<uchar> readCompressedDataFromFile(const string& fileName) {
    ifstream inFile(fileName, ios::binary | ios::ate);
    if (!inFile.is_open()) {
        cout << "���󣺶�ȡ�ļ�ʧ��." << endl;
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
        // �û�����ͼ���ļ���
        

        // ��ʾ�û�ѡ����
        cout << "-----------------------------------------------------------------" << endl;
        cout << "ѡ��һ�����ܣ�" << endl;
        cout << "1. ѹ��ͼ��" << endl;
        cout << "2. תΪ��ɫ" << endl;
        cout << "3. ����ͼ��" << endl;
        cout << "4. ��ѹͼ��" << endl;
        cout << "0. �˳�����" << endl;

        int choice;
        cout << "���빦�� (0 to exit): ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "�����ļ��� (���� 'exit' ): ";
            cin >> fileName;
            compressfile = fileName;
            if (fileName == "exit") {
                cout << "�˳�����." << endl;
                break;
            }

            // ��ȡͼ��
            originalImage = imread(fileName);
            compressimage = originalImage;
            // ���ͼ���Ƿ�ɹ���ȡ
            if (originalImage.empty()) {
                cout << "���󣺶�ȡ�ļ�ʧ��." << endl;
                continue;  // �ص�ѭ����ʼ����������ͼ���ļ���
            }

            // ��ʾԭʼͼ��
            displayImage(originalImage, fileName);
            //vector<pair<int, uchar>> encodedData = runLengthEncode(originalImage);
            //// ��ѹ������д���ļ�
            //writeEncodedDataToFile(encodedData, "compressed_data.bin");
            
            vector<uchar> compressedData = compressImage(originalImage);
            writeEncodedDataToFile(compressedData, "compressed_data.bin");
            break;
        }
        case 2: {
            //  ��ɫͼ��ת��Ϊ�Ҷ�ͼ��
            cout << "�����ļ��� (���� 'exit' ): ";
            cin >> fileName;

            if (fileName == "exit") {
                cout << "�˳�����." << endl;
                break;
            }

            // ��ȡͼ��
            originalImage = imread(fileName);

            // ���ͼ���Ƿ�ɹ���ȡ
            if (originalImage.empty()) {
                cout << "���󣺶�ȡ�ļ�ʧ��." << endl;
                continue;  // �ص�ѭ����ʼ����������ͼ���ļ���
            }

            // ��ʾԭʼͼ��
            displayImage(originalImage, fileName);
            Mat grayImage = convertToGray(originalImage);
            imwrite("gray_image.png", grayImage);
            displayImage(grayImage, "Gray Image");
            break;
        }
        case 3: {
            cout << "�����ļ��� (���� 'exit' ): ";
            cin >> fileName;

            if (fileName == "exit") {
                cout << "�˳�����." << endl;
                break;
            }

            // ��ȡͼ��
            Mat originalImage = imread(fileName);

            // ���ͼ���Ƿ�ɹ���ȡ
            if (originalImage.empty()) {
                cout << "���󣺶�ȡ�ļ�ʧ��." << endl;
                continue;  // �ص�ѭ����ʼ����������ͼ���ļ���
            }

            // ��ʾԭʼͼ��
            displayImage(originalImage, fileName);
            //  ʵ��ͼ��ߴ������
            int newWidth, newHeight;
            cout << "�����ȣ� ";
            cin >> newWidth;
            cout << "����߶ȣ� ";
            cin >> newHeight;

            Mat resizedImage = resizeImage(originalImage, newWidth, newHeight);

            imwrite("resized_image.png", resizedImage);
            displayImage(resizedImage, "Resized Image");
            break;
        }
        case 4: {
            //ʵ��ͼ�����ݵĽ�ѹ��
            


            vector<uchar> loadedCompressedData = readCompressedDataFromFile("compressed_data.bin");
            Mat decompressedImage = decompressImage(loadedCompressedData);

            imwrite("decompressed_image.ppm", decompressedImage);
            displayImage(decompressedImage, "Decompressed Image");
            break;
        }
        case 0:
            cout << "�˳�����." << endl;
            return 0;
        default:
            cout << "�Ƿ�����. ������Ϸ�����." << endl;
            break;
        }
    }

    return 0;
}


