#include <opencv2/opencv.hpp>
#include <Windows.h>

class Pixel
{
private:
public:
	HWND hwnd;
	int width;
	int height;
};

class ImageSearcher
{
public:
	ImageSearcher(const std::string &window_title, const std::string &image_path) : window_title_(window_title), image_(cv::imread(image_path))
	{
		// Get the dimensions of the background window
		RECT rect;
		GetClientRect(hwnd_, &rect);
		width_ = rect.right - rect.left;
		height_ = rect.bottom - rect.top;
	}

	cv::Point search() const
	{
		// Capture a screenshot of the background window
		HDC hdcScreen = GetDC(NULL);
		HDC hdcWindow = GetDC(hwnd_);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdcScreen, width_, height_);
		HGDIOBJ old_obj = SelectObject(hdcWindow, hBitmap);
		BitBlt(hdcWindow, 0, 0, width_, height_, hdcScreen, 0, 0, SRCCOPY);
		cv::Mat screen(height_, width_, CV_8UC4);
		GetBitmapBits(hBitmap, width_ * height_ * 4, screen.data);
		SelectObject(hdcWindow, old_obj);
		DeleteObject(hBitmap);
		ReleaseDC(NULL, hdcScreen);
		ReleaseDC(hwnd_, hdcWindow);

		// Create a result matrix to hold the match scores
		cv::Mat result;
		int result_cols = screen.cols - image_.cols + 1;
		int result_rows = screen.rows - image_.rows + 1;
		result.create(result_rows, result_cols, CV_32FC1);

		// Match the template using normalized cross-correlation
		cv::matchTemplate(screen, image_, result, cv::TM_CCORR_NORMED);

		// Find the maximum match score
		double minVal, maxVal;
		cv::Point minLoc, maxLoc;
		cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

		// Output the location of the match
		return maxLoc;
	}

private:
	HWND hwnd_;
	int width_;
	int height_;
	std::string window_title_;
	cv::Mat image_;
};