#include "imagetransform.h"

void ImageTansform::GetTransformation(cv::Mat &src, cv::Mat &dst, cv::Point2d src_vertices[4], cv::Point2d dst_vertices[4])
{
    TransformationMatrix(src_vertices, dst_vertices);
    clock_t start_1 = clock();
    GetDstimage(src, dst);
    clock_t end_1 = clock();
    //add linux test
    cout << "Running Time get transform: " << (double)(end_1 - start_1) / CLOCKS_PER_SEC << endl;
}

int ImageTansform::TransformationMatrix(cv::Point2d src_vertices[4], cv::Point2d dst_vertices[4])
{
    cv::Mat M(3, 3, CV_64F), X(8, 1, CV_64F, M.ptr());
    double a[8][8], b[8];
    cv::Mat A(8, 8, CV_64F, a), B(8, 1, CV_64F, b);
    for (int i = 0; i < 4; ++i)
    {
        a[i][0] = a[i + 4][3] = src_vertices[i].x;
        a[i][1] = a[i + 4][4] = src_vertices[i].y;
        a[i][2] = a[i + 4][5] = 1;
        a[i][3] = a[i][4] = a[i][5] =
            a[i + 4][0] = a[i + 4][1] = a[i + 4][2] = 0;
        a[i][6] = -src_vertices[i].x*dst_vertices[i].x;
        a[i][7] = -src_vertices[i].y*dst_vertices[i].x;
        a[i + 4][6] = -src_vertices[i].x*dst_vertices[i].y;
        a[i + 4][7] = -src_vertices[i].y*dst_vertices[i].y;
        b[i] = dst_vertices[i].x;
        b[i + 4] = dst_vertices[i].y;
    }
    cv::solve(A, B, X, cv::DECOMP_SVD);
    M.ptr<double>()[8] = 1.;     //c22=1
    cv::invert(M, M);
    transformation_matrix_ = M.clone();
    //Get each element of H matrix
    for (size_t i = 0; i < 3; i++)
        for (size_t j = 0; j < 3; j++)
        {
            trans_member[i][j] = M.at<double>(i, j);
        }
    return 0;
}

cv::Point2d ImageTansform::CoordinatTtransformation(cv::Point dst_point, cv::Mat trans_matrix)
{
    cv::Point2d source_point;
    if (0 == determinant(trans_matrix))
    {
        std::cout << "determinant is equal to zero";
    }
    double denominator_index = (dst_point.x*trans_member[2][0] + dst_point.y*trans_member[2][1] + trans_member[2][2]);
    source_point.x = (dst_point.x*trans_member[0][0] + dst_point.y*trans_member[0][1] + trans_member[0][2]) / denominator_index;
    source_point.y = (dst_point.x*trans_member[1][0] + dst_point.y*trans_member[1][1] + trans_member[1][2]) / denominator_index;
    return source_point;

}

int ImageTansform::GetDstimage(cv::Mat src_, cv::Mat dst_)
{
    if (src_.empty())
    {
        return -1;
    }
    for (int row = 0; row < dst_.rows; row++)
    {
        uchar* dst_ptr = dst_.ptr(row);
        for (int col = 0; col < dst_.cols; col++)
        {
            cv::Vec3b temp = Interpolation(src_, cv::Point(col, row), Bilinear);
            dst_ptr[3 * col] = temp[0];
            dst_ptr[3 * col + 1] = temp[1];
            dst_ptr[3 * col + 2] = temp[2];
        }
    }
    return 0;
}

cv::Vec3b ImageTansform::Interpolation(cv::Mat src_, cv::Point dst_point, Interpolation_mode mode)
{
    //add switch to select the different interpolation function
    cv::Vec3b pixel;
    cv::Point2d src_point = CoordinatTtransformation(dst_point, transformation_matrix_);

    int x0 = floor(src_point.x);
    int y0 = floor(src_point.y);
    int x1 = ceil(src_point.x);
    int y1 = ceil(src_point.y);
    uchar *data_up = src_.ptr<uchar>(y0);
    uchar *data_down = src_.ptr<uchar>(y1);
    if (x1 > src_.cols || y1 > src_.rows)
    {
        cout << "the range is out " << endl;
    }
    int chs = src_.channels();
    for (int channel = 0; channel < chs; channel++)
    {
        uchar X0Y0 = data_up[chs*x0 + channel];
        uchar X0Y1 = data_down[chs*x0 + channel];
        uchar X1Y0 = data_up[chs*x1 + channel];
        uchar X1Y1 = data_down[chs*x1 + channel];
        double u_x = src_point.x - x0;
        double u_x1 = 1 - src_point.x + x0;
        double v_y = (src_point.y - y0);
        double v_y1 = 1 - v_y;
        double temp = (X0Y0*v_y1 + X0Y1*v_y)*u_x1 + ((X1Y0*v_y1 + X1Y1*v_y)*u_x);
        pixel[channel] = static_cast<uchar> (temp);
    }
    return pixel;
}




void ImageTansform::VisitMatPixel(cv::Mat visit_mat)
{
    for (size_t rows = 0; rows < visit_mat.rows; rows++)
    {
        std::cout << "\n";
        for (size_t cols = 0; cols < visit_mat.cols; cols++)
        {
            std::cout << visit_mat.at<double>(rows, cols) << "  ";
        }
    }
    std::cout << "\n";

}










