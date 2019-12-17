			
#pragma once

#include "Procedure.h"

class CMyButton : public CButton
{
	DECLARE_DYNAMIC(CMyButton)

public:
	CMyButton(void);
	virtual ~CMyButton(void);

protected:
	CProcedure m_dlgProc;

	CString m_strDesc;
	CString m_strCmd;
	BOOL m_bBatchCall;

public:
	CString get_desc() { return m_strDesc; }
	CString get_cmd() { return m_strCmd; }
	BOOL is_batch_call() { return m_bBatchCall;  }

	void set_desc(CString desc) { m_strDesc = desc; }
	void set_cmd(CString cmd) { m_strCmd = cmd; }
	void set_batch_call(BOOL batch_call) { m_bBatchCall = batch_call; }

	void open_procdeure_dialog();

protected:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	DECLARE_MESSAGE_MAP()

};

