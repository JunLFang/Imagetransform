#pragma once
#ifndef IMAGETRANSFORM_H
#define IMAGETRANSFORM_H
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdlib.h>
#include <iostream>
#include <Eigen/Dense>
#include <time.h>

using namespace std;
enum Interpolation_mode
{
	Linear = 1,
	Bilinear = 2,
	CubicConvolution = 3,
};

class ImageTansform
{ 
public:
	//@brief Image transform interface
	//@param src Source image 
	//@param dst Destination image
	//@param src_vertices The four points of src image
	//@param dst_vertices The four points of dst image
	void GetTransformation(cv::Mat &src, cv::Mat &dst, cv::Point2d src_vertices[4], cv::Point2d dst_vertices[4]);
private:
	//@brief Get H matrix
	//@param src_vertices The four points of src image
	//@param dst_vertices The four points of dst image(it can be the size of dst image)
	int TransformationMatrix(cv::Point2d src_vertices[4], cv::Point2d dst_vertices[4]);
	//@brief Get dst image
	//@param src Source image 
	//@param dst Destination image
	int GetDstimage(cv::Mat src, cv::Mat dst);
	//@brief Interpolation for one dst point 
	//@param src_ Source image
	//@param dst_point_ One dst point 
    //@param mode Different methods of interpolation 
	cv::Vec3b Interpolation(cv::Mat src_, cv::Point dst_point_,Interpolation_mode mode);
	//@brief Get the src point corresponding  with dst point 
	//@param dst_point 
	//@param transformation_matrix 
	cv::Point2d CoordinatTtransformation(cv::Point dst_point, cv::Mat transformation_matrix);
	//@brief Visit the each element of matrix
	//@param visit_mat Visited Mat  
	void VisitMatPixel(cv::Mat visit_mat);
	//@briefGlobal parameter H matrix 
	cv::Mat transformation_matrix_;
	//@briefGlobal parameter H matrix elements
	double trans_member[3][3]{ 0 };
};

#endif

