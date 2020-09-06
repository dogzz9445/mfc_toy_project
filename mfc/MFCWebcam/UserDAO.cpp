#include "stdafx.h"
#include "UserDAO.h"

// 아래 소스 참고
// https://m.blog.naver.com/PostView.nhn?blogId=tipsware&logNo=221337692149&proxyReferer=https:%2F%2Fwww.google.com%2F

std::vector<CUser> UserDAO::SelectAll()
{
  std::vector<CUser> users;
  Connect(_T(SQLCON_DSN), _T(SQLCON_ID), _T(SQLCON_PW));

  // 환경 설정
  SQLSetStmtAttr(hStmt, SQL_ATTR_QUERY_TIMEOUT, (SQLPOINTER)15, SQL_IS_UINTEGER);

  SQLBindCol(hStmt, 1, SQL_C_SHORT, &user_id, sizeof(user_id), &uid);
  SQLBindCol(hStmt, 2, SQL_WCHAR, user_name, 30, &una);
  SQLBindCol(hStmt, 3, SQL_WCHAR, user_imgurl, 500, &uiu);
  SQLBindCol(hStmt, 4, SQL_C_ULONG, &user_imgsize, sizeof(user_imgsize), &uis);

  ExecuteStatementDirect((SQLWCHAR*)L"SELECT * FROM user");

  do {
    mRet = SQLFetch(hStmt);
    CUser user;
    user.setId(user_id);
    user.setName(CString(user_name));
    user.setImgUrl(CString(user_imgurl));
    user.setImgSize(user_imgsize);
    users.push_back(user);
  } while (mRet != SQL_NO_DATA);
  users.pop_back();

  Disconnect();
  return users;
}

CUser UserDAO::AddUser(CUser& user)
{
  Connect(_T(SQLCON_DSN), _T(SQLCON_ID), _T(SQLCON_PW));

  CString query;
  query.Format(L"INSERT INTO user (name, imgurl, imgsize) VALUES ('%s', '%s', '%d')",
    user.getName(), user.getImgUrl(), user.getImgSize());
  PrepareStatement((SQLWCHAR*)query.GetString());

  ExecuteStatement();

  ExecuteStatementDirect((SQLWCHAR*)L"SELECT LAST_INSERT_ID();");

  SQLBindCol(hStmt, 1, SQL_C_SHORT, &user_id, sizeof(user_id), &uid);
  SQLBindCol(hStmt, 2, SQL_WCHAR, user_name, 30, &una);
  SQLBindCol(hStmt, 3, SQL_WCHAR, user_imgurl, 500, &uiu);
  SQLBindCol(hStmt, 4, SQL_C_ULONG, &user_imgsize, sizeof(user_imgsize), &uis);

  mRet = SQLFetch(hStmt);
  CUser cuser;
  cuser.setId(user_id);
  cuser.setName(CString(user_name));
  cuser.setImgUrl(CString(user_imgurl));
  cuser.setImgSize(user_imgsize);

  Disconnect();
  return cuser;
}
