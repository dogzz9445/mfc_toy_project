#pragma once

class CWebcam
{
public:
  CWebcam();
  virtual ~CWebcam();

  cv::Mat mFrame;
  CImage mImage;
protected:
  cv::VideoCapture *mCapture;
  BITMAPINFO *mBitInfo;
  
  CImage* CreateImage(cv::Mat& frame);

public:
  BOOL Init(cv::Size);
  BOOL Resize(cv::Size);
  BOOL Read(HDC);
  BOOL Draw(HDC);

  cv::Mat getFrame(); // return clone of frame;
};

