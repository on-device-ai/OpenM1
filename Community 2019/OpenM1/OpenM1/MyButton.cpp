#include "pch.h"
#include "MyButton.h"

IMPLEMENT_DYNAMIC(CMyButton, CButton)

CMyButton::CMyButton(void) : m_bBatchCall(false)
{
}

CMyButton::~CMyButton(void)
{
}

BEGIN_MESSAGE_MAP(CMyButton, CButton)
	//{{AFX_MSG_MAP(SDCtrlComboboxListctrl)
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CMyButton::OnLButtonUp( UINT nFlags, CPoint point )
{
	open_procdeure_dialog();
	this->SetWindowTextW(m_strDesc);
}

void CMyButton::open_procdeure_dialog()
{
	CProcedure dlg;

	dlg.m_strDesc    = m_strDesc;
	dlg.m_strCmd     = m_strCmd;
	dlg.m_bBatchCall = m_bBatchCall;

	if (dlg.DoModal() == IDOK) {
		m_strDesc    = dlg.m_strDesc;
		m_strCmd     = dlg.m_strCmd;
		m_bBatchCall = dlg.m_bBatchCall;
	}
}