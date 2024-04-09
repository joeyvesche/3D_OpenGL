// CThicknessDlg.cpp : implementation file
//

#include "pch.h"
#include "Step2.h"
#include "afxdialogex.h"
#include "CThicknessDlg.h"


// CThicknessDlg dialog

IMPLEMENT_DYNAMIC(CThicknessDlg, CDialog)

CThicknessDlg::CThicknessDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, m_thickness(0)
{

}

CThicknessDlg::~CThicknessDlg()
{
}

void CThicknessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_thickness);
}


BEGIN_MESSAGE_MAP(CThicknessDlg, CDialog)
END_MESSAGE_MAP()


// CThicknessDlg message handlers
