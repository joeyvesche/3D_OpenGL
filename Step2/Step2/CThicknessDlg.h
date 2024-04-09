#pragma once
#include "afxdialogex.h"


// CThicknessDlg dialog

class CThicknessDlg : public CDialog
{
	DECLARE_DYNAMIC(CThicknessDlg)

public:
	CThicknessDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CThicknessDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	double m_thickness;
};
