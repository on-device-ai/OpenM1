			
#pragma once

class CListCtrlCustom;

typedef BOOL (CALLBACK *LPFUNC_SETTING_RECT)(CListCtrlCustom *pListCtrl, CWnd *pCtrl, CRect &rcGrid);

class CListCtrlCustom :
	public CListCtrl
{
	DECLARE_DYNAMIC(CListCtrlCustom)

public:
	CListCtrlCustom(void);
	virtual ~CListCtrlCustom(void);

	// Generic creator
	BOOL Create(_In_ DWORD dwStyle, _In_ const RECT& rect, _In_ CWnd* pParentWnd, _In_ UINT nID);
	// Generic creator allowing extended style bits
	BOOL CreateEx(_In_ DWORD dwExStyle, _In_ DWORD dwStyle, _In_ const RECT& rect,
		_In_ CWnd* pParentWnd, _In_ UINT nID);

public:

	CWnd *GetCtrl(int nRow, int nCol);
	
	CString GetText(int nRow, int nCol);

	BOOL SetItemEx(int nItem, int nSubItem, CWnd *pExCtrl);
	
	BOOL SetRowHeight(int nHeight);

public:
	
	void RegOnSettingRect(LPFUNC_SETTING_RECT pfnResizeExCtrl)
		{ m_pfnResizeExCtrl = pfnResizeExCtrl; }

protected:
	
	void _updateExCtrlsPos();
	
	void _clearExCtrls();
	
	BOOL _getGridRect(int nRow, int nCol, CRect &rect);

protected:
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	DECLARE_MESSAGE_MAP()

protected:
	
	typedef CArray<CWnd *> COLUMN_INFO;
	typedef COLUMN_INFO *LP_COLUMN_INFO;
	typedef CArray<LP_COLUMN_INFO> ROW_EX_CTRL_INFO;
	ROW_EX_CTRL_INFO m_arrExCtrls;

	LPFUNC_SETTING_RECT m_pfnResizeExCtrl;
	
	CImageList m_lstImgForRowHeight;

};

