#pragma once
#include <afxwin.h>
#include <sqlext.h>

class CUser
{
public:
  WORD id;
  CString name;
  CString imgurl;
  DWORD imgsize;

public:
  CUser();
  virtual ~CUser();

  WORD getId() { return id; }
  void setId(WORD cid) { id = cid; }
  CString getName() { return name; }
  void setName(CString cname) { name = cname; }
  CString getImgUrl() { return imgurl; }
  void setImgUrl(CString cimgurl) { imgurl = cimgurl; }
  DWORD getImgSize() { return imgsize; }
  void setImgSize(DWORD cimgsize) { imgsize = cimgsize; }
};

