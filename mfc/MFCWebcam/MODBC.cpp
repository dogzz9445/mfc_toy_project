#include "stdafx.h"
#include "MODBC.h"

MODBC::~MODBC()
{
  Disconnect();
}

void MODBC::Connect(const wchar_t* dsn, const wchar_t* id,
                    const wchar_t* password)
{
  Disconnect();
  AllocateHandles();
  ConnectDataSource(dsn, id, password);
}

void MODBC::Disconnect()
{
  DisconnectDataSource();
}

void MODBC::AllocateHandles()
{
  mRet = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
  if (mRet == SQL_ERROR)
  {
    MessageBox(_T("Unable to allocate an environmnet handle\n"));
    return;
  }

  TRYODBC(hEnv,
      SQL_HANDLE_ENV,
      SQLSetEnvAttr(hEnv,
        SQL_ATTR_ODBC_VERSION,
        (SQLPOINTER)SQL_OV_ODBC3,
        0));

  // Allocate a connection
  TRYODBC(hEnv,
    SQL_HANDLE_ENV,
    SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc));
}

void MODBC::ConnectDataSource(const wchar_t* dsn, const wchar_t* id,
                              const wchar_t* password)
{
  TRYODBC(hDbc,
      SQL_HANDLE_DBC,
      SQLConnect(hDbc,
        (SQLWCHAR*)dsn, SQL_NTS,   // DSN, length
        (SQLWCHAR*)id,  SQL_NTS,   // ID,  length
        (SQLWCHAR*)password,  SQL_NTS)); // PW,  length

  TRYODBC(hDbc,
    SQL_HANDLE_DBC,
    SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt));
}

void MODBC::ExecuteStatementDirect(SQLWCHAR* sql)
{
  if (!(mRet == SQL_SUCCESS || mRet == SQL_SUCCESS_WITH_INFO))
  {
    MessageBox(_T("DB 연결 실패\n"));
    return;
  }

  mRet = SQLExecDirect(hStmt, (SQLWCHAR*)sql, SQL_NTS);

  switch (mRet)
  {
  case SQL_SUCCESS_WITH_INFO:
    HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, mRet);
  case SQL_SUCCESS:
    MessageBox(_T("쿼리 성공\n"));

    // TODO:
    // id 값 가져오기
    break;
  case SQL_ERROR:
    HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, mRet);
    break;
  default:
    MessageBox(_T("실패"));
  };
}

void MODBC::PrepareStatement(SQLWCHAR * sql)
{
  if (!(mRet == SQL_SUCCESS || mRet == SQL_SUCCESS_WITH_INFO))
  {
    MessageBox(_T("DB 연결 실패\n"));
    return;
  }

  mRet = SQLPrepare(hStmt, (SQLWCHAR*)sql, SQL_NTS);

  switch (mRet)
  {
  case SQL_SUCCESS_WITH_INFO:
    HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, mRet);
  case SQL_SUCCESS:
    //MessageBox(_T("쿼리 준비 성공\n"));
    break;
  case SQL_ERROR:
    HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, mRet);
    break;
  default:
    break;
  };
}

void MODBC::ExecuteStatement()
{
  mRet = SQLExecute(hStmt);

  switch (mRet)
  {
  case SQL_SUCCESS_WITH_INFO:
    HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, mRet);
  case SQL_SUCCESS:
    MessageBox(_T("쿼리 성공\n"));

    // id 값 가져오기
    break;
  case SQL_ERROR:
    HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, mRet);
    break;
  default:
    MessageBox(_T("실패"));
  };
}

void MODBC::DisconnectDataSource()
{
  if (hStmt)
  {
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
  }

  if (hDbc)
  {
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
  }

  if (hEnv)
  {
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
  }

  // cout << "disconnected";
}

void MODBC::HandleDiagnosticRecord(SQLHANDLE hHandle,
  SQLSMALLINT    hType,
  RETCODE        RetCode)
{
  SQLSMALLINT iRec = 0;
  SQLINTEGER  iError;
  WCHAR       wszMessage[1000];
  WCHAR       wszState[SQL_SQLSTATE_SIZE + 1];


  if (RetCode == SQL_INVALID_HANDLE)
  {
    MessageBox(L"Invalid handle!\n");
    return;
  }

  while (SQLGetDiagRec(hType,
    hHandle,
    ++iRec,
    wszState,
    &iError,
    wszMessage,
    (SQLSMALLINT)(sizeof(wszMessage) / sizeof(WCHAR)),
    (SQLSMALLINT *)NULL) == SQL_SUCCESS)
  {
    // Hide data truncated..
    if (wcsncmp(wszState, L"01004", 5))
    {
      CString str;
      str.Format(L"[%5.5s] %s (%d)\n", wszState, wszMessage, iError);
      MessageBox(str);
    }
  }
}