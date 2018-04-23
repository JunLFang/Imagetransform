#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv/cv.hpp>
#include "Imagetransform.h"
int main()
{
	ImageTansform transformer;
	cv::Mat src = cv::imread("/home/tony_jun/Git/imagetransform/imagetransform/test.jpg");
	imshow("original mat",src);
	cv::Mat dst = cv::Mat::zeros(480,640, CV_8UC3);
	cv::Point2d src_vertices[4];
	src_vertices[0] = cv::Point2d(264.0, 153.0);
	src_vertices[1] = cv::Point2d(1082.0, 160.0);
	src_vertices[2] = cv::Point2d(146.0, 802.0);
	src_vertices[3] = cv::Point2d(1239.0, 796.0);

	cv::Point2d dst_vertices[4]; 
	dst_vertices[0] = cv::Point2d(0.0, 0.0);
	dst_vertices[1] = cv::Point2d(640.0, 0.0);
	dst_vertices[2] = cv::Point2d(0.0, 480);
	dst_vertices[3] = cv::Point2d(640.0, 480.0);

	clock_t start_=clock();
	transformer.GetTransformation(src, dst, src_vertices, dst_vertices);
	clock_t end_=clock();
	cout << "Running Time : " << (double)(end_ - start_) / CLOCKS_PER_SEC << endl;
	imshow("after trnsformation", dst);
	cv::waitKey(0);

    cv::waitKey(0);
    cv::waitKey(0);
    cv::waitKey(0);

	return 0;
}
