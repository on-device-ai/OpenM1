// Procedure.cpp : implementation file
//

#include "pch.h"
#include "OpenM1.h"
#include "Procedure.h"
#include "afxdialogex.h"


// CProcedure dialog

IMPLEMENT_DYNAMIC(CProcedure, CDialogEx)

CProcedure::CProcedure(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SET_PROC_DIALOG, pParent)
	, m_strDesc(_T(""))
	, m_strCmd(_T(""))
	, m_bBatchCall(FALSE)
{

}

CProcedure::~CProcedure()
{
}

void CProcedure::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_DESC, m_strDesc);
	DDX_Text(pDX, IDC_CMD, m_strCmd);
	DDX_Check(pDX, IDC_BATCH_CALL, m_bBatchCall);
}


BEGIN_MESSAGE_MAP(CProcedure, CDialogEx)
END_MESSAGE_MAP()


// CProcedure message handlers