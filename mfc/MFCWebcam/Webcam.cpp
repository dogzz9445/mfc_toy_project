#include "stdafx.h"
#include "Webcam.h"

CWebcam::CWebcam() :
  mBitInfo(nullptr),
  mCapture(nullptr)
{
}

CWebcam::~CWebcam()
{
  mImage.ReleaseDC();
  mImage.Destroy();
  delete mBitInfo;

  mCapture->release();
  delete mCapture;
}

CImage * CWebcam::CreateImage(cv::Mat & frame)
{
  CImage image;
  return &image;
}

BOOL CWebcam::Init(cv::Size winSize)
{
  mCapture = new cv::VideoCapture(0);
  if (!mCapture->isOpened())
  {
    return FALSE;
  }
  mCapture->set(cv::CAP_PROP_FRAME_WIDTH, 320);
  mCapture->set(cv::CAP_PROP_FRAME_HEIGHT, 240);

  mBitInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));
  mBitInfo->bmiHeader.biPlanes = 1;
  mBitInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  mBitInfo->bmiHeader.biCompression = BI_RGB;
  mBitInfo->bmiHeader.biClrImportant = 0;
  mBitInfo->bmiHeader.biClrUsed = 0;
  mBitInfo->bmiHeader.biSizeImage = 0;
  mBitInfo->bmiHeader.biXPelsPerMeter = 0;
  mBitInfo->bmiHeader.biYPelsPerMeter = 0;

  mImage.Create(winSize.width, winSize.height, 24);

  return TRUE;
}

BOOL CWebcam::Resize(cv::Size winSize)
{
  mImage.ReleaseDC();
  mImage.Destroy();

  mImage.Create(winSize.width, winSize.height, 24);
  return TRUE;
}

BOOL CWebcam::Draw(HDC dc)
{
  int bpp = 8 * mFrame.elemSize();
  assert((bpp == 8 || bpp == 24 || bpp == 32));

  int border = 0;

  if (bpp < 32)
  {
    border = 4 - (mFrame.cols % 4);
  }

  cv::Mat tFrame;
  if (border > 0 || mFrame.isContinuous() == false)
  {
    cv::copyMakeBorder(mFrame, tFrame, 0, 0, 0, border, cv::BORDER_CONSTANT, 0);
  }
  else
  {
    tFrame = mFrame;
  }

  mBitInfo->bmiHeader.biBitCount = bpp;
  mBitInfo->bmiHeader.biWidth = tFrame.cols;
  mBitInfo->bmiHeader.biHeight = -tFrame.rows;

  if (tFrame.cols == mImage.GetWidth() && tFrame.rows == mImage.GetHeight())
  {
    // source and destination have same size
    // transfer memory block
    // NOTE: the padding border will be shown here. Anyway it will be max 3px width

    SetDIBitsToDevice(mImage.GetDC(),
      //destination rectangle
      0, 0, mImage.GetWidth(), mImage.GetHeight(),
      0, 0, 0, tFrame.rows,
      tFrame.data, mBitInfo, DIB_RGB_COLORS);
  }
  else
  {
    // destination rectangle
    int destx = 0, desty = 0;
    int destw = mImage.GetWidth();
    int desth = mImage.GetHeight();

    // rectangle defined on source bitmap
    // using imgWidth instead of mat_temp.cols will ignore the padding border
    int imgx = 0, imgy = 0;
    int imgWidth = tFrame.cols - border;
    int imgHeight = tFrame.rows;

    StretchDIBits(mImage.GetDC(),
      destx, desty, destw, desth,
      imgx, imgy, imgWidth, imgHeight,
      tFrame.data, mBitInfo, DIB_RGB_COLORS, SRCCOPY);
  }

  mImage.BitBlt(dc, 0, 0);

  return TRUE;
}

cv::Mat CWebcam::getFrame()
{
  return mFrame.clone();
}

BOOL CWebcam::Read(HDC dc)
{
  if (!mCapture->read(mFrame))
  {
    return FALSE;
  }
  return this->Draw(dc);
}