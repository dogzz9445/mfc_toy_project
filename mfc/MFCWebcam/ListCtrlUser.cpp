// ListCtrlUser.cpp : implementation file
//

#include "stdafx.h"
#include "MFCWebcam.h"
#include "ListCtrlUser.h"

// CListCtrlUser

IMPLEMENT_DYNAMIC(CListCtrlUser, CListCtrl)

CListCtrlUser::CListCtrlUser()
{
}

CListCtrlUser::~CListCtrlUser()
{
}


BEGIN_MESSAGE_MAP(CListCtrlUser, CListCtrl)
END_MESSAGE_MAP()


// CListCtrlUser message handlers
void CListCtrlUser::CreateHead()
{
  CRect rect;
  GetClientRect(&rect);
  WORD listWidth = rect.Width();

  SetRedraw(FALSE);
  DeleteAllItems();

  LPWSTR colNames[4] = { L"ID", L"¿Ã∏ß", L"image url", L"image size" };
  WORD colSizes[4] = { 60, 60, 100, 100 };
  LV_COLUMN lCol;

  lCol.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
  lCol.fmt = LVCFMT_LEFT;

  for (int i = 0; i < 4; i++)
  {
    lCol.pszText = colNames[i];
    lCol.iSubItem = i;
    lCol.cx = colSizes[i];
    InsertColumn(i, &lCol);
  }

  SetRedraw(TRUE);
  Invalidate();
}

void CListCtrlUser::CreateBody(std::vector<CUser>& users)
{
  if (users.empty())
  {
    return;
  }
  SetRedraw(FALSE);
  DeleteAllItems();

  for (auto it = users.begin(); it != users.end(); it++)
  {
    auto user = *it;
    CString format;

    format.Format(L"%d", user.id);
    int nItem = InsertItem(0, (LPCTSTR)format.GetString());
    SetItem(nItem, 1, LVIF_TEXT, user.name, 0, 0, 0, NULL);
    SetItem(nItem, 2, LVIF_TEXT, user.imgurl, 0, 0, 0, NULL);
    format.Format(L"%d", user.imgsize);
    SetItem(nItem, 3, LVIF_TEXT, (LPCTSTR)format.GetString(), 0, 0, 0, NULL);
  }

  SetRedraw(TRUE);
  Invalidate();
}