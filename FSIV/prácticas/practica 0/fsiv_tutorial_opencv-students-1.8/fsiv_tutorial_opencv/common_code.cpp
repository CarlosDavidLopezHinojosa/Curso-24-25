
#include "common_code.hpp"

void 
fsiv_find_min_max_loc_1(cv::Mat const& input,
    std::vector<cv::uint8_t>& min_v, std::vector<cv::uint8_t>& max_v,
    std::vector<cv::Point>& min_loc, std::vector<cv::Point>& max_loc)
{
    CV_Assert(input.depth()==CV_8U);

    //! TODO: do a rows/cols scanning to find the first min/max values. 
    // Hint: use cv::split to get the input image channels.

    std::vector<cv::Mat> channels;
    cv::split(input,channels);

    cv::uint8_t min, max;
    cv::Point min_point, max_point;

    for( auto channel : channels)
    {   
        min = 255;
        max = 0;
        for (size_t row = 0; row < channel.rows; row++)
        {
            for (size_t col = 0; col < channel.cols; col++)
            {
                const u_char pixel = channel.at<uchar>(row,col);

                if (min > pixel)
                {
                    min = pixel;
                    min_point = cv::Point(col,row);
                }

                if (max < pixel)
                {
                    max = pixel;
                    max_point = cv::Point(col,row);
                }
            }
        } 

        min_v.push_back(min);
        max_v.push_back(max);
        min_loc.push_back(min_point);
        max_loc.push_back(max_point);
    }
    //

    CV_Assert(size_t(input.channels())==min_v.size());
    CV_Assert(size_t(input.channels())==max_v.size());
    CV_Assert(size_t(input.channels())==min_loc.size());
    CV_Assert(size_t(input.channels())==max_loc.size());
}

void 
fsiv_find_min_max_loc_2(cv::Mat const& input,
    std::vector<double>& min_v, std::vector<double>& max_v,
    std::vector<cv::Point>& min_loc, std::vector<cv::Point>& max_loc)
{

    //! TODO: Find the first min/max values using cv::minMaxLoc function.    
    // Hint: use cv::split to get the input image channels.
    std::vector<cv::Mat> channels;
    cv::split(input,channels);

    double min, max;
    cv::Point min_point, max_point;

    for( auto channel : channels)
    {           
        cv::minMaxLoc(channel,&min,&max,&min_point,&max_point);

        min_v.push_back(min);
        max_v.push_back(max);
        min_loc.push_back(min_point);
        max_loc.push_back(max_point);
    }

    //

    CV_Assert(size_t(input.channels())==min_v.size());
    CV_Assert(size_t(input.channels())==max_v.size());
    CV_Assert(size_t(input.channels())==min_loc.size());
    CV_Assert(size_t(input.channels())==max_loc.size());

}

