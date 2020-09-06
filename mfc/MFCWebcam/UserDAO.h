#pragma once

#include "User.h"
#include "MODBC.h"

// 테스트용 DSN, ID, PW
#define SQLCON_DSN "JoyUser"
#define SQLCON_ID  "joy"
#define SQLCON_PW  "joy1"

#define IMAGE_URL "C:\\db\\images\\"

class UserDAO : public MODBC
{
private:
  unsigned short user_id;
  wchar_t user_name[30];
  wchar_t user_imgurl[500];
  unsigned long user_imgsize;

  SQLLEN uid, una, uiu, uis;

public:
  UserDAO() {}
  virtual ~UserDAO() {}

  std::vector<CUser> SelectAll();
  CUser              AddUser(CUser& cuser);
};

