#pragma once


// CProcedure dialog

class CProcedure : public CDialogEx
{
	DECLARE_DYNAMIC(CProcedure)

public:
	CProcedure(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CProcedure();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SET_PROC_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strDesc;
	CString m_strCmd;
	BOOL m_bBatchCall;
};
