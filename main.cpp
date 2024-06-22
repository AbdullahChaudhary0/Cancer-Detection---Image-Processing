#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <time.h>
using namespace std;
using namespace cv;

template<typename T>
void smallest(T array[], int row, int col) {
    int check[4] = { 0 };
    check[0] = array[row][col - 1];
    check[1] = array[row - 1][col - 1];
    check[2] = array[row - 1][col];
    check[3] = array[row - 1][col + 1];

    int temp = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = i + 1; j < 4; j++)
        {
            if (check[i] > check[j])
            {
                temp = check[i];
                check[i] = check[j];
                check[j] = temp;
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        if (check[i] != 0) {
            array[row][col] = check[i];
            break;
        }
    }
}

int main() {

    Mat img = imread("C:/Users/PC/Desktop/Data Structure/Segmented Outputs/mIMD091.bmp");
    Mat imgtrue = imread("C:/Users/PC/Desktop/Data Structure/Ground Truths/IMD002_lesion.bmp");
    namedWindow("First OpenCV Application", WINDOW_AUTOSIZE);
    moveWindow("First OpenCV Application", 0, 45);

    int row = img.rows;
    int col = img.cols;


    int** data = new int* [row];
    for (int i = 0; i < row; i++) {
        data[i] = new int[col];
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            data[i][j] = img.at<Vec3b>(i, j)[0];
        }
    }

    int** dataRe = new int* [row];
    for (int i = 0; i < row; i++) {
        dataRe[i] = new int[col];
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            dataRe[i][j] = data[i][j];
        }
    }

    int count = 0;
    int x = 1;

    int array[1000] = { 0 };
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (dataRe[i][j] == 255) {

                if (dataRe[i][j - 1] == 0 && dataRe[i - 1][j - 1] == 0 && dataRe[i - 1][j] == 0 && dataRe[i - 1][j + 1] == 0) {
                    dataRe[i][j] = x;
                    array[x] = x;
                    x++;

                }
                else
                    smallest(dataRe, i, j);
            }
        }
    }


    int parent = 0;

    for (int i = 1; i < row; i++) {
        for (int j = 0; j < col - 2; j++) {
            if (dataRe[i][j] != 0) {
                // Two Element Check
                if (dataRe[i][j - 1] != 0 && dataRe[i - 1][j - 1] != 0) {
                    if (dataRe[i][j - 1] < dataRe[i - 1][j - 1]) {
                        parent = dataRe[i - 1][j - 1];
                        array[parent] = dataRe[i][j - 1];

                    }
                    else if (dataRe[i][j - 1] > dataRe[i - 1][j - 1]) {
                        parent = dataRe[i][j - 1];
                        array[parent] = dataRe[i - 1][j - 1];
                    }
                }
                //
                if (dataRe[i][j - 1] != 0 && dataRe[i - 1][j] != 0) {
                    if (dataRe[i][j - 1] < dataRe[i - 1][j]) {
                        parent = dataRe[i - 1][j];
                        array[parent] = dataRe[i][j - 1];
                    }
                    else if (dataRe[i][j - 1] > dataRe[i - 1][j]) {
                        parent = dataRe[i][j - 1];
                        array[parent] = dataRe[i - 1][j];
                    }
                }
                //
                if (dataRe[i][j - 1] != 0 && dataRe[i - 1][j + 1] != 0) {
                    if (dataRe[i][j - 1] < dataRe[i - 1][j + 1]) {
                        parent = dataRe[i - 1][j + 1];
                        array[parent] = dataRe[i][j - 1];
                    }
                    else if (dataRe[i][j - 1] > dataRe[i - 1][j + 1]) {
                        parent = dataRe[i][j - 1];
                        array[parent] = dataRe[i - 1][j + 1];
                    }
                }
                //
                if (dataRe[i - 1][j - 1] != 0 && dataRe[i - 1][j] != 0) {
                    if (dataRe[i - 1][j - 1] < dataRe[i - 1][j]) {
                        parent = dataRe[i - 1][j];
                        array[parent] = dataRe[i - 1][j - 1];
                    }
                    else if (dataRe[i - 1][j - 1] > dataRe[i - 1][j]) {
                        parent = dataRe[i - 1][j - 1];
                        array[parent] = dataRe[i - 1][j];
                    }
                }
                //
                if (dataRe[i - 1][j - 1] != 0 && dataRe[i - 1][j + 1] != 0) {
                    if (dataRe[i - 1][j - 1] < dataRe[i - 1][j + 1]) {
                        parent = dataRe[i - 1][j + 1];
                        array[parent] = dataRe[i - 1][j - 1];
                    }
                    else if (dataRe[i - 1][j - 1] > dataRe[i - 1][j + 1]) {
                        parent = dataRe[i - 1][j - 1];
                        array[parent] = dataRe[i - 1][j + 1];
                    }
                }
                //
                if (dataRe[i - 1][j] != 0 && dataRe[i - 1][j + 1] != 0) {
                    if (dataRe[i - 1][j] < dataRe[i - 1][j + 1]) {
                        parent = dataRe[i - 1][j + 1];
                        array[parent] = dataRe[i - 1][j];
                    }
                    else if (dataRe[i - 1][j] > dataRe[i - 1][j + 1]) {
                        parent = dataRe[i - 1][j];
                        array[parent] = dataRe[i - 1][j + 1];
                    }
                }
                // Three elements check
                if (dataRe[i][j - 1] != 0 && dataRe[i - 1][j - 1] != 0 && dataRe[i - 1][j] != 0) {
                    if (dataRe[i][j - 1] < dataRe[i - 1][j - 1] && dataRe[i][j - 1] < dataRe[i - 1][j]) {
                        parent = dataRe[i - 1][j - 1];
                        array[parent] = dataRe[i][j - 1];
                        parent = dataRe[i - 1][j];
                        array[parent] = dataRe[i][j - 1];
                    }
                    else if (dataRe[i - 1][j - 1] < dataRe[i][j - 1] && dataRe[i - 1][j - 1] < dataRe[i - 1][j]) {
                        parent = dataRe[i][j - 1];
                        array[parent] = dataRe[i - 1][j - 1];
                        parent = dataRe[i - 1][j];
                        array[parent] = dataRe[i - 1][j - 1];
                    }
                    else {
                        parent = dataRe[i][j - 1];
                        array[parent] = dataRe[i - 1][j];
                        parent = dataRe[i - 1][j - 1];
                        array[parent] = dataRe[i - 1][j];
                    }
                }
                //
                if (dataRe[i][j - 1] != 0 && dataRe[i - 1][j - 1] != 0 && dataRe[i - 1][j + 1] != 0) {
                    if (dataRe[i][j - 1] < dataRe[i - 1][j - 1] && dataRe[i][j - 1] < dataRe[i - 1][j + 1]) {
                        parent = dataRe[i - 1][j - 1];
                        array[parent] = dataRe[i][j - 1];
                        parent = dataRe[i - 1][j + 1];
                        array[parent] = dataRe[i][j - 1];
                    }
                    else if (dataRe[i - 1][j - 1] < dataRe[i][j - 1] && dataRe[i - 1][j - 1] < dataRe[i - 1][j + 1]) {
                        parent = dataRe[i][j - 1];
                        array[parent] = dataRe[i - 1][j - 1];
                        parent = dataRe[i - 1][j + 1];
                        array[parent] = dataRe[i - 1][j - 1];
                    }
                    else {
                        parent = dataRe[i][j - 1];
                        array[parent] = dataRe[i - 1][j + 1];
                        parent = dataRe[i - 1][j - 1];
                        array[parent] = dataRe[i - 1][j + 1];
                    }
                }
                //
                if (dataRe[i][j - 1] != 0 && dataRe[i - 1][j] != 0 && dataRe[i - 1][j + 1] != 0) {
                    if (dataRe[i][j - 1] < dataRe[i - 1][j] && dataRe[i][j - 1] < dataRe[i - 1][j + 1]) {
                        parent = dataRe[i - 1][j];
                        array[parent] = dataRe[i][j - 1];
                        parent = dataRe[i - 1][j + 1];
                        array[parent] = dataRe[i][j - 1];
                    }
                    else if (dataRe[i - 1][j] < dataRe[i][j - 1] && dataRe[i - 1][j] < dataRe[i - 1][j + 1]) {
                        parent = dataRe[i][j - 1];
                        array[parent] = dataRe[i - 1][j];
                        parent = dataRe[i - 1][j + 1];
                        array[parent] = dataRe[i - 1][j];
                    }
                    else {
                        parent = dataRe[i][j - 1];
                        array[parent] = dataRe[i - 1][j + 1];
                        parent = dataRe[i - 1][j];
                        array[parent] = dataRe[i - 1][j + 1];
                    }
                }
                //
                if (dataRe[i - 1][j - 1] != 0 && dataRe[i - 1][j] != 0 && dataRe[i - 1][j + 1] != 0) {
                    if (dataRe[i - 1][j - 1] < dataRe[i - 1][j] && dataRe[i - 1][j - 1] < dataRe[i - 1][j + 1]) {
                        parent = dataRe[i - 1][j];
                        array[parent] = dataRe[i - 1][j - 1];
                        parent = dataRe[i - 1][j + 1];
                        array[parent] = dataRe[i - 1][j - 1];
                    }
                    else if (dataRe[i - 1][j] < dataRe[i - 1][j - 1] && dataRe[i - 1][j] < dataRe[i - 1][j + 1]) {
                        parent = dataRe[i - 1][j - 1];
                        array[parent] = dataRe[i - 1][j];
                        parent = dataRe[i - 1][j + 1];
                        array[parent] = dataRe[i - 1][j];
                    }
                    else {
                        parent = dataRe[i - 1][j - 1];
                        array[parent] = dataRe[i - 1][j + 1];
                        parent = dataRe[i - 1][j];
                        array[parent] = dataRe[i - 1][j + 1];
                    }
                }
                //Four elements check
                if (dataRe[i][j - 1] != 0 && dataRe[i - 1][j - 1] != 0 && dataRe[i - 1][j] != 0 && dataRe[i - 1][j + 1] != 0) {
                    if (dataRe[i][j - 1] < dataRe[i - 1][j - 1] && dataRe[i][j - 1] < dataRe[i - 1][j] && dataRe[i][j - 1] < dataRe[i - 1][j + 1]) {
                        parent = dataRe[i - 1][j - 1];
                        array[parent] = dataRe[i][j - 1];
                        parent = dataRe[i - 1][j];
                        array[parent] = dataRe[i][j - 1];
                        parent = dataRe[i - 1][j + 1];
                        array[parent] = dataRe[i][j - 1];
                    }
                    else if (dataRe[i - 1][j - 1] < dataRe[i][j - 1] && dataRe[i - 1][j - 1] < dataRe[i - 1][j] && dataRe[i - 1][j - 1] < dataRe[i - 1][j + 1]) {
                        parent = dataRe[i][j - 1];
                        array[parent] = dataRe[i - 1][j - 1];
                        parent = dataRe[i - 1][j];
                        array[parent] = dataRe[i - 1][j - 1];
                        parent = dataRe[i - 1][j + 1];
                        array[parent] = dataRe[i - 1][j - 1];
                    }
                    else if (dataRe[i - 1][j] < dataRe[i][j - 1] && dataRe[i - 1][j] < dataRe[i - 1][j - 1] && dataRe[i - 1][j] < dataRe[i - 1][j + 1]) {
                        parent = dataRe[i][j - 1];
                        array[parent] = dataRe[i - 1][j];
                        parent = dataRe[i - 1][j - 1];
                        array[parent] = dataRe[i - 1][j];
                        parent = dataRe[i - 1][j + 1];
                        array[parent] = dataRe[i - 1][j];
                    }
                    else {
                        parent = dataRe[i][j - 1];
                        array[parent] = dataRe[i - 1][j + 1];
                        parent = dataRe[i - 1][j - 1];
                        array[parent] = dataRe[i - 1][j + 1];
                        parent = dataRe[i - 1][j];
                        array[parent] = dataRe[i - 1][j + 1];
                    }
                }
            }
        }
    }

    int maxVal = 0;

    for (int i = 1; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (dataRe[i][j] > maxVal)
                maxVal = dataRe[i][j];
        }
    }


    int temp = 0;
    for (int i = 1; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (dataRe[i][j] != 0) {
                temp = dataRe[i][j];
                dataRe[i][j] = array[temp];
            }
        }
    }

    int maxLabel = 0;
    int counter = 0;
    int check = 0;

    for (int k = 1; k < maxVal; k++) {
        counter = 0;
        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                if (k == dataRe[i][j])
                    counter++;
            }
        }
        if (counter > check) {
            check = counter;
            maxLabel = k;

        }

    }


    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (dataRe[i][j] == maxLabel) {
                img.at<Vec3b>(i, j)[0] = 255;
                img.at<Vec3b>(i, j)[1] = 255;
                img.at<Vec3b>(i, j)[2] = 255;

            }
            else {
                img.at<Vec3b>(i, j)[0] = 0;
                img.at<Vec3b>(i, j)[1] = 0;
                img.at<Vec3b>(i, j)[2] = 0;
            }

       }
    }

    float truePositive = 0;
    float falseNegative = 0;
    float falsepositive = 0;
    for (int i = 0; i < imgtrue.rows; i++)
    {
        for (int j = 0; j < imgtrue.cols; j++)
        {

            if ((imgtrue.at<Vec3b>(i, j)[0] == img.at<Vec3b>(i, j)[0]) && (imgtrue.at<Vec3b>(i, j)[1] == img.at<Vec3b>(i, j)[1]) && (imgtrue.at<Vec3b>(i, j)[2] == img.at<Vec3b>(i, j)[2]))
            {
                truePositive++;
            }
            else if ((imgtrue.at<Vec3b>(i, j)[0] == 255 && img.at<Vec3b>(i, j)[0] == 0) && (imgtrue.at<Vec3b>(i, j)[1] == 255 && img.at<Vec3b>(i, j)[1] == 0)
                && (imgtrue.at<Vec3b>(i, j)[2] == 255 && img.at<Vec3b>(i, j)[2] == 0))
            {
                falseNegative++;
            }
            else if ((imgtrue.at<Vec3b>(i, j)[0] == 0 && img.at<Vec3b>(i, j)[0] == 255) && (imgtrue.at<Vec3b>(i, j)[1] == 0 && img.at<Vec3b>(i, j)[1] == 255)
                && (imgtrue.at<Vec3b>(i, j)[2] == 0 && img.at<Vec3b>(i, j)[2] == 255))
            {
                falsepositive++;
            }
        }
    }
    float diceCoefficient = float((2.0 * truePositive) / (falseNegative + (2.0 * truePositive) + falsepositive));
    cout << "Dice Coefficient with segmented image: " << diceCoefficient << endl;



    /////////////////////////////////////////////////////////////////////////////////////Task2////////////////////////////////////////////////////////////////////////////////////////////
    Mat image = imread("C:/Users/PC/Desktop/Data Structure/Original Images/IMD002.bmp");
    Mat imagetrue = imread("C:/Users/PC/Desktop/Data Structure/Ground Truths/IMD002_lesion.bmp");
    namedWindow("First OpenCV Application", WINDOW_AUTOSIZE);
    moveWindow("First OpenCV Application", 0, 45);

    int row2 = image.rows;
    int col2 = image.cols;


    int** data2 = new int* [row2];
    for (int i = 0; i < row2; i++) {
        data2[i] = new int[col2];
    }

    for (int i = 0; i < row2; i++) {
        for (int j = 0; j < col2; j++) {
            data2[i][j] = image.at<Vec3b>(i, j)[0];
        }
    }
    
    int* cluster1 = new int[440000];
    int* cluster2 = new int[440000];
   
    srand(time(0));
    int centroid1 = rand() % 45;
    int centroid2 = rand() % 70 + 185;

    int diff1 = 0;
    int diff2 = 0;

    int counter1 = 0;
    int counter2 = 0;

    int count1 = 0;
    int count2 = 0;
    while (1) {
        counter1 = 0;
        counter2 = 0;
        for (int i = 0; i < row2; i++) {
            for (int j = 0; j < col2; j++) {

                if (centroid1 > data2[i][j])
                    diff1 = centroid1 - data2[i][j];
                else
                    diff1 = data2[i][j] - centroid1;

                if (centroid2 > data2[i][j])
                    diff2 = centroid2 - data2[i][j];
                else
                    diff2 = data2[i][j] - centroid2;

                if (diff1 < diff2) {
                    cluster1[counter1] = data2[i][j];
                    counter1++;
                }
                else if (diff2 < diff1) {
                    cluster2[counter2] = data2[i][j];
                    counter2++;
                }
                if (diff1 == diff2) {
                    cluster1[counter1] = data2[i][j];
                    counter1++;
                    cluster2[counter2] = data2[i][j];
                    counter2++;
                }
            }
        }

        if (count1 == counter1 && count2 == counter2)
            break;

        for (int i = 0; i < counter1; i++) {
            count1++;
        }

        for (int i = 0; i < counter2; i++) {
            count2++;
        }

        int sum = 0;
        int sum2 = 0;

        for (int i = 0; i < counter1; i++) {
            sum += cluster1[i];
        }

        for (int i = 0; i < counter2; i++) {
            sum2 += cluster2[i];
        }

        centroid1 = sum / counter1;
        centroid2 = sum2 / counter2;

        count1 = counter1;
        count2 = counter2;
    }

    if (count1 > count2){
        for (int i = 0; i < row2; i++) {
            for (int j = 0; j < col2; j++) {

                for (int k = 0; k < 255; k++) {
                    if (data2[i][j] == cluster1[k]){
                        data2[i][j] = 1;
                        break;
                    }
                }
            }
        }
    }
    else if (count2 > count1) {
        for (int i = 0; i < row2; i++) {
            for (int j = 0; j < col2; j++) {

                for (int k = 0; k < count2; k++) {
                    if (data2[i][j] == cluster2[k]){
                        data2[i][j] = 1;
                        break;
                    }   
                }
            }
        }
    }

    for (int i = 0; i < row2; i++) {
        for (int j = 0; j < col2; j++) {
            if (data2[i][j] == 1){
                image.at<Vec3b>(i, j)[0] = 0;
                image.at<Vec3b>(i, j)[1] = 0;
                image.at<Vec3b>(i, j)[2] = 0;
            }
            else {
                image.at<Vec3b>(i, j)[0] = 255;
                image.at<Vec3b>(i, j)[1] = 255;
                image.at<Vec3b>(i, j)[2] = 255;
            }

        }
    }
    
    truePositive = 0;
    falseNegative = 0;
    falsepositive = 0;
    for (int i = 0; i < imagetrue.rows; i++)
    {
        for (int j = 0; j < imagetrue.cols; j++)
        {

            if ((imagetrue.at<Vec3b>(i, j)[0] == image.at<Vec3b>(i, j)[0]) && (imagetrue.at<Vec3b>(i, j)[1] == image.at<Vec3b>(i, j)[1]) && (imagetrue.at<Vec3b>(i, j)[2] == image.at<Vec3b>(i, j)[2]))
            {
                truePositive++;
            }
            else if ((imagetrue.at<Vec3b>(i, j)[0] == 255 && image.at<Vec3b>(i, j)[0] == 0) && (imagetrue.at<Vec3b>(i, j)[1] == 255 && image.at<Vec3b>(i, j)[1] == 0)
                && (imagetrue.at<Vec3b>(i, j)[2] == 255 && image.at<Vec3b>(i, j)[2] == 0))
            {
                falseNegative++;
            }
            else if ((imagetrue.at<Vec3b>(i, j)[0] == 0 && image.at<Vec3b>(i, j)[0] == 255) && (imagetrue.at<Vec3b>(i, j)[1] == 0 && image.at<Vec3b>(i, j)[1] == 255)
                && (imagetrue.at<Vec3b>(i, j)[2] == 0 && image.at<Vec3b>(i, j)[2] == 255))
            {
                falsepositive++;
            }
        }
    }
    diceCoefficient = float((2.0 * truePositive) / (falseNegative + (2.0 * truePositive) + falsepositive));
    cout << "Dice Coefficient with real image: " << diceCoefficient << endl;
     
    delete[] cluster1;
    delete[] cluster2;
     
    /*imshow("First OpenCV Application", image);
    waitKey(0);
    destroyAllWindows();*/
    return 0;
}

