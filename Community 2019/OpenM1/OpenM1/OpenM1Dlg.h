
// OpenM1Dlg.h : header file
//

#pragma once

#include "ListCtrlCustom.h"

// COpenM1Dlg dialog
class COpenM1Dlg : public CDialogEx
{
// Construction
public:
	COpenM1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OPENM1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation

private:
	void initListCtrl();

private:
	//ListCtrlCustom
	CListCtrlCustom* m_pListCtrl;

	BOOL COpenM1Dlg::MoveItem(int from, int to);

public:
	CListCtrlCustom* get_list_ctrl() { return m_pListCtrl; }

protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedExit();
	afx_msg void OnBnClickedNewProc();
	afx_msg void OnBnClickedDelProc();
	afx_msg void OnBnClickedSaveProcs();
	afx_msg void OnBnClickedLoadProcs();
	afx_msg void OnBnClickedRunProcs();
	afx_msg void OnBnClickedClearProcs();
	afx_msg void OnBnClickedItemUp();
	afx_msg void OnBnClickedItemDown();
};
