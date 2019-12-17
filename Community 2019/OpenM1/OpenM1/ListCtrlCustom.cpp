#include "pch.h"
#include "ListCtrlCustom.h"

IMPLEMENT_DYNAMIC(CListCtrlCustom, CListCtrl)

CListCtrlCustom::CListCtrlCustom(void)
	: m_pfnResizeExCtrl(NULL)
{
}

CListCtrlCustom::~CListCtrlCustom(void)
{
	_clearExCtrls();
	m_lstImgForRowHeight.DeleteImageList();
}

BEGIN_MESSAGE_MAP(CListCtrlCustom, CListCtrl)
	//{{AFX_MSG_MAP(SDCtrlComboboxListctrl)
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

LRESULT CListCtrlCustom::DefWindowProc( UINT message, WPARAM wParam, LPARAM lParam )
{
	LRESULT lRet = CListCtrl::DefWindowProc(message, wParam, lParam);
	LVITEM *pItem = (LVITEM *)lParam;

	switch (message)
	{
	case LVM_INSERTITEM:
		{
			int nCurRow = (int)lRet;
			LP_COLUMN_INFO pArrColumnCreatedCtrls = new COLUMN_INFO;
			int nColumnCount = GetHeaderCtrl()->GetItemCount();
			for (int i=0; i<nColumnCount; ++i)
			{
				pArrColumnCreatedCtrls->Add(NULL);
			}
			m_arrExCtrls.InsertAt(nCurRow, pArrColumnCreatedCtrls);
			if (NULL!=pArrColumnCreatedCtrls)
			{
				_updateExCtrlsPos();
			}
		}
		break;

	case LVM_DELETEITEM:
		{
			int nCurRow = (int)wParam;

			LP_COLUMN_INFO pColInfo = m_arrExCtrls[nCurRow];
			if (NULL==pColInfo)
			{
				break;
			}
			int nCtrls = (int)pColInfo->GetCount();
			for (int i=0; i<nCtrls; ++i)
			{
				CWnd *pCtrl = pColInfo->GetAt(i);
				if (NULL==pCtrl)
				{
					continue;
				}

				pCtrl->DestroyWindow();
				delete (pCtrl);
			}
			delete pColInfo;
			m_arrExCtrls.RemoveAt(nCurRow);

			_updateExCtrlsPos();
		}
		break;

	case LVM_DELETEALLITEMS:
		{
			_clearExCtrls();
		}
		break;

	case LVM_INSERTCOLUMN:
		{
			int nInsertColumn = (int)wParam;
			int nRowCount = (int)m_arrExCtrls.GetCount();
			for (int i=0; i<nRowCount; ++i)
			{
				LP_COLUMN_INFO pColInfo = m_arrExCtrls[i];
				if (NULL == pColInfo)
				{
					continue;
				}

				pColInfo->InsertAt(nInsertColumn, (CWnd *)NULL);
			}

			_updateExCtrlsPos();
		}
		break;

	case LVM_DELETECOLUMN:
		{
			int nRemoveColumn = (int)wParam;
			int nRowCount = (int)m_arrExCtrls.GetCount();
			for (int i=0; i<nRowCount; ++i)
			{
				LP_COLUMN_INFO pColInfo = m_arrExCtrls[i];
				if (NULL == pColInfo)
				{
					continue;
				}
				if (nRemoveColumn < pColInfo->GetCount())
				{
					CWnd *pCtrl = pColInfo->GetAt(nRemoveColumn);
					if (NULL!=pCtrl)
					{
						pCtrl->DestroyWindow();
						delete (pCtrl);
					}
					pColInfo->RemoveAt(nRemoveColumn);
				}
			}

			_updateExCtrlsPos();
		}
		break;
	}

	return lRet;
}

BOOL CListCtrlCustom::OnNotify( WPARAM wParam, LPARAM lParam, LRESULT* pResult )
{
	NMHDR *pNMHDR = (NMHDR *)lParam;
	switch (pNMHDR->code)
	{
	case HDN_BEGINTRACK:
	case HDN_ENDTRACK:
	case HDN_DIVIDERDBLCLICK:
		{
			*pResult = TRUE;
			return TRUE;
		}
		break;
	}

	return CListCtrl::OnNotify(wParam, lParam, pResult);
}

void CListCtrlCustom::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);
	_updateExCtrlsPos();
}

void CListCtrlCustom::_updateExCtrlsPos()
{
	int nTopRowIndex = GetTopIndex();
	int nRowCount = GetItemCount();

	int nRows = (int)m_arrExCtrls.GetCount();
	for (int i=0; i<nRows; ++i)
	{
		LP_COLUMN_INFO pColInfo = m_arrExCtrls[i];
		if (NULL==pColInfo)
		{
			continue;
		}
		int nCtrls = (int)pColInfo->GetCount();
		for (int i=0; i<nCtrls; ++i)
		{
			CWnd *pCtrl = pColInfo->GetAt(i);
			if (NULL==pCtrl)
			{
				continue;
			}

			pCtrl->ShowWindow(SW_HIDE);
		}
	}

	CRect rectWin;
	GetWindowRect(&rectWin);
	ScreenToClient(&rectWin);

	bool bExit = false;
	int nRowMove=nTopRowIndex;
	for (; nRowMove<nRowCount; ++nRowMove)
	{
		LP_COLUMN_INFO pColInfo = m_arrExCtrls[nRowMove];
		if (NULL==pColInfo)
		{
			continue;
		}
		int nCtrls = (int)pColInfo->GetCount();
		for (int nColumn=0; nColumn<nCtrls; ++nColumn)
		{
			CWnd *pCtrl = pColInfo->GetAt(nColumn);
			if (NULL==pCtrl)
			{
				continue;
			}

			CRect rectColumn;
			_getGridRect(nRowMove, nColumn, rectColumn);
			if (rectColumn.top>rectWin.bottom)
			{
				bExit = true;
				break;
			}

			pCtrl->ShowWindow(SW_SHOW);
			if (NULL==m_pfnResizeExCtrl 
				|| m_pfnResizeExCtrl(this, pCtrl, rectColumn)==FALSE)
			{
				pCtrl->MoveWindow(&rectColumn);	
			}
		}

		if (bExit)
		{
			break;
		}
	}
}

BOOL CListCtrlCustom::Create( _In_ DWORD dwStyle, _In_ const RECT& rect, _In_ CWnd* pParentWnd, _In_ UINT nID )
{
	BOOL bRet = CListCtrl::Create(dwStyle, rect, pParentWnd, nID);

	LONG lStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);
	lStyle |= LVS_REPORT;
	SetWindowLong(GetSafeHwnd(), GWL_STYLE, lStyle);

	return bRet;
}

BOOL CListCtrlCustom::CreateEx( _In_ DWORD dwExStyle, _In_ DWORD dwStyle, _In_ const RECT& rect, _In_ CWnd* pParentWnd, _In_ UINT nID )
{
	BOOL bRet = CListCtrl::CreateEx(dwExStyle, dwStyle, rect, pParentWnd, nID);

	LONG lStyle = GetWindowLong(GetSafeHwnd(), GWL_STYLE);
	lStyle |= LVS_REPORT;
	SetWindowLong(GetSafeHwnd(), GWL_STYLE, lStyle);

	return bRet;
}

void CListCtrlCustom::_clearExCtrls()
{
	int nRows = (int)m_arrExCtrls.GetCount();
	for (int i=0; i<nRows; ++i)
	{
		LP_COLUMN_INFO pColInfo = m_arrExCtrls[i];
		if (NULL==pColInfo)
		{
			continue;
		}
		int nCtrls = (int)pColInfo->GetCount();
		for (int i=0; i<nCtrls; ++i)
		{
			CWnd *pCtrl = pColInfo->GetAt(i);
			if (NULL==pCtrl)
			{
				continue;
			}

			pCtrl->DestroyWindow();
			delete (pCtrl);
		}
		delete pColInfo;
	}
	m_arrExCtrls.RemoveAll();
}

CWnd * CListCtrlCustom::GetCtrl( int nRow, int nCol )
{
	LP_COLUMN_INFO pColumnInfo = m_arrExCtrls[nRow];
	if (NULL == pColumnInfo)
	{
		return NULL;
	}

	if (nCol < pColumnInfo->GetCount())
	{
		return pColumnInfo->GetAt(nCol);
	}

	return NULL;
}

BOOL CListCtrlCustom::_getGridRect( int nRow, int nCol, CRect &rect )
{
	BOOL bRet = GetSubItemRect(nRow, nCol, LVIR_BOUNDS, rect);
	
	if (TRUE==bRet &&  0==nCol)
	{
		int nWidth0 = GetColumnWidth(0);
		rect.right = rect.left + nWidth0;
	}
	return bRet;
}

CString CListCtrlCustom::GetText( int nRow, int nCol )
{
	CWnd *pCtrl = GetCtrl(nRow, nCol);
	if (NULL == pCtrl)
	{
		return GetItemText(nRow, nCol);
	}

	CString sText;
	pCtrl->GetWindowText(sText);
	return sText;
}

BOOL CListCtrlCustom::SetItemEx( int nItem, int nSubItem, CWnd *pExCtrl )
{
	int nColumnCount = GetHeaderCtrl()->GetItemCount();
	if (nItem >= GetItemCount()
		|| nSubItem >= nColumnCount
		)
	{
		return FALSE;
	}

	LP_COLUMN_INFO &pColumnInfo = m_arrExCtrls[nItem];
	if (NULL == pColumnInfo)
	{
		pColumnInfo = new COLUMN_INFO;
		for (int i=0; i<nColumnCount; ++i)
		{
			pColumnInfo->Add(NULL);	
		}
	}
	else
	{
		if (pColumnInfo->GetCount() > nSubItem)
		{
			CWnd *pCtrlOld = pColumnInfo->GetAt(nSubItem);
			if (NULL != pCtrlOld)
			{
				delete pCtrlOld;
			}
		}
	}

	pColumnInfo->SetAt(nSubItem, pExCtrl);

	pExCtrl->SetParent(this);

	_updateExCtrlsPos();

	return TRUE;
}

BOOL CListCtrlCustom::SetRowHeight( int nHeight )
{
	m_lstImgForRowHeight.DeleteImageList();
	m_lstImgForRowHeight.Create(1, nHeight, ILC_COLOR32, 1, 0);
	if (SetImageList(&m_lstImgForRowHeight, LVSIL_SMALL) == NULL)
	{
		return FALSE;
	}

	_updateExCtrlsPos();

	DeleteItem(InsertItem(0, _T("")));

	return TRUE;
}

