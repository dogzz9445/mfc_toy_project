#pragma once

#include <windows.h>
#include <sql.h>
#include <sqlext.h>

// �Ʒ� �ڵ� ��� �� ����
// https://docs.microsoft.com/ko-kr/sql/connect/odbc/cpp-code-example-app-connect-access-sql-db?view=sql-server-ver15#b-odbcsqlcpp-code
// http://jjseol.blogspot.com/2017/03/c-odbc-dbms-how-to-connect-to-dbms-with.html

/*******************************************/
/* Macro to call ODBC functions and        */
/* report an error on failure.             */
/* Takes handle, handle type, and stmt     */
/*******************************************/

#define TRYODBC(h, ht, x)   {   mRet = x;\
                                if (mRet != SQL_SUCCESS) \
                                { \
                                    HandleDiagnosticRecord (h, ht, mRet); \
                                } \
                                if (mRet == SQL_ERROR) \
                                { \
                                    MessageBox(_T("Error in  " L#x "\n")); \
                                    return;  \
                                }  \
                            }

// FIXME: 
// �޼����ڽ� ���� ���ؼ� CDialogEx�� ��� ������
// �ƴϸ� CWnd�� ������ �ִ� handler�ε� ���ư�����
// �ƴϸ� ��Ӿ��� handler�� ���޹޾Ƽ� õ�� ��������
class MODBC : public CWnd
{
protected:
  SQLHENV hEnv;
  SQLHDBC hDbc;
  SQLHSTMT hStmt;
  RETCODE mRet;

  // Connection
  void AllocateHandles();
  void ConnectDataSource(const wchar_t* dsn, const wchar_t* id,
                         const wchar_t* password);
  void DisconnectDataSource();

  // Query
  void ExecuteStatementDirect(SQLWCHAR* sql);
  void PrepareStatement(SQLWCHAR* sql);
  void ExecuteStatement();

public:
  MODBC() {}
  virtual ~MODBC();

  void Connect(const wchar_t* dsn, const wchar_t* id,
               const wchar_t* password);
  void Disconnect();

protected:
  void HandleDiagnosticRecord(SQLHANDLE      hHandle,
    SQLSMALLINT    hType,
    RETCODE        RetCode);
};

