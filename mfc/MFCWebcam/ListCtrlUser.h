#pragma once

#include "User.h"
// CListCtrlUser

class CListCtrlUser : public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlUser)

public:
	CListCtrlUser();
	virtual ~CListCtrlUser();

  void CreateHead();
  void CreateBody(std::vector<CUser>& users);

protected:
	DECLARE_MESSAGE_MAP()
};


