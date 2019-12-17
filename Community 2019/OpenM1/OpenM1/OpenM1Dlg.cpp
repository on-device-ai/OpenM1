
// OpenM1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "OpenM1.h"
#include "OpenM1Dlg.h"
#include "afxdialogex.h"

#include "MyButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// COpenM1Dlg dialog



COpenM1Dlg::COpenM1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_OPENM1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COpenM1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COpenM1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &COpenM1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &COpenM1Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_EXIT, &COpenM1Dlg::OnBnClickedExit)
	ON_BN_CLICKED(IDC_NEW_PROC, &COpenM1Dlg::OnBnClickedNewProc)
	ON_BN_CLICKED(IDC_DEL_PROC, &COpenM1Dlg::OnBnClickedDelProc)
	ON_BN_CLICKED(IDC_SAVE_PROCS, &COpenM1Dlg::OnBnClickedSaveProcs)
	ON_BN_CLICKED(IDC_LOAD_PROCS, &COpenM1Dlg::OnBnClickedLoadProcs)
	ON_BN_CLICKED(IDC_RUN_PROCS, &COpenM1Dlg::OnBnClickedRunProcs)
	ON_BN_CLICKED(IDC_CLEAR_PROCS, &COpenM1Dlg::OnBnClickedClearProcs)
END_MESSAGE_MAP()


// COpenM1Dlg message handlers

BOOL COpenM1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	initListCtrl();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COpenM1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COpenM1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COpenM1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COpenM1Dlg::initListCtrl()
{
	CRect rcListCtrl;
	CWnd* pRect = GetDlgItem(IDC_STATIC_LIST);
	if (NULL == pRect)
	{
		return;
	}
	pRect->GetWindowRect(&rcListCtrl);
	ScreenToClient(&rcListCtrl);

	m_pListCtrl = new CListCtrlCustom();
	m_pListCtrl->Create(WS_VISIBLE | WS_BORDER, rcListCtrl, this, IDC_STATIC_LIST + 1);

	DWORD dwExStyle = LVS_EX_FULLROWSELECT;
	m_pListCtrl->SetExtendedStyle(dwExStyle);
	m_pListCtrl->SetRowHeight(25);
	m_pListCtrl->ShowWindow(SW_SHOW);

	m_pListCtrl->InsertColumn(0, _T("No."), LVCFMT_CENTER, 50);
	m_pListCtrl->InsertColumn(1, _T("Procedure"), LVCFMT_CENTER, 325);
}

void COpenM1Dlg::OnBnClickedOk()
{
	
}


void COpenM1Dlg::OnBnClickedCancel()
{

}


void COpenM1Dlg::OnBnClickedExit()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void COpenM1Dlg::OnBnClickedNewProc()
{
	int item_count = m_pListCtrl->GetItemCount();
	CString str_item_count;

	str_item_count.Format(_T("%4d"), item_count+1);

	m_pListCtrl->InsertItem(item_count, str_item_count);
	CMyButton* btn = new CMyButton();
	
	btn->open_procdeure_dialog();
	
	btn->Create(btn->get_desc(), WS_CHILD | WS_VISIBLE, CRect(0, 0, 80, 20),this, m_pListCtrl->GetDlgCtrlID() + 0);
	
	m_pListCtrl->SetItemEx(item_count, 1, btn);
}


void COpenM1Dlg::OnBnClickedDelProc()
{
	POSITION pos = m_pListCtrl->GetFirstSelectedItemPosition();

	int nItem = m_pListCtrl->GetNextSelectedItem(pos);

	m_pListCtrl->DeleteItem(nItem);
}


#define IN_LINE_SIZE	2048

void COpenM1Dlg::OnBnClickedLoadProcs()
{
	CFileDialog load_procs_filedlg(true, _T("*.prc"), _T("OpenM1.prc"), OFN_FILEMUSTEXIST, _T("Procedure File (*.prc)|*.prc||"));

	if (load_procs_filedlg.DoModal() == IDOK) {
		FILE* fp = NULL;
		_wfopen_s(&fp, (LPCTSTR)load_procs_filedlg.GetPathName(), _T("rt, ccs=UTF-8"));

		if (fp) {
			int        index = 0;
			wchar_t    line_str[IN_LINE_SIZE];
			int        item_count;
			CMyButton* btn = NULL;

			m_pListCtrl->DeleteAllItems();

			while (1) {
				if (fgetws(line_str, IN_LINE_SIZE, fp) != NULL) {
					if ((index == 0) && (line_str[0] == _T('$'))) {
						CString str_item_count;

						item_count = m_pListCtrl->GetItemCount();
						str_item_count.Format(_T("%4d"), item_count + 1);
						m_pListCtrl->InsertItem(item_count, str_item_count);

						btn = new CMyButton();
						
						index += 1;
					} else if (index > 0) {
						switch (index) {
						case 1:
							{
								CString line_cstr = (CString)line_str;
								line_cstr.Replace(_T("\r"), _T("\0")); line_cstr.Replace(_T("\n"), _T("\0"));

								btn->set_desc(line_cstr);
								index += 1;
							}
							break;
						case 2:
							{
								CString line_cstr = (CString)line_str;
								line_cstr.Replace(_T("\r"), _T("\0")); line_cstr.Replace(_T("\n"), _T("\0"));

								btn->set_cmd(line_cstr);
								index += 1;
							}
							break;
						case 3:
							{
								BOOL is_batch_call = _ttoi((CString)line_str);
								btn->set_batch_call(is_batch_call);

								btn->Create(btn->get_desc(), WS_CHILD | WS_VISIBLE, CRect(0, 0, 80, 20), this, m_pListCtrl->GetDlgCtrlID() + 0);

								m_pListCtrl->SetItemEx(item_count, 1, btn);

								btn = NULL;

								index = 0;
							}
							break;
						}
					}
					else {
						if (btn) {
							delete btn;
							btn = NULL;

							index = 0;
						}

					}
				}

				if (feof(fp)) {
					break;
				}
			}

			fclose(fp);
		}
	}

}


void COpenM1Dlg::OnBnClickedSaveProcs()
{
	CFileDialog save_procs_filedlg(false, _T("*.prc"), _T("OpenM1.prc"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Procedure File (*.prc)|*.prc||"));

	if (save_procs_filedlg.DoModal() == IDOK) {
		FILE* fp = NULL;
		_wfopen_s(&fp, (LPCTSTR)save_procs_filedlg.GetPathName(), _T("wt, ccs=UTF-8"));

		if (fp) {

			for (int i = 0; i < m_pListCtrl->GetItemCount(); i++) {
				CMyButton* btn = (CMyButton*)m_pListCtrl->GetCtrl(i, 1);
				
				fwprintf(fp, _T("$%d\n"), i);
				fwprintf(fp, _T("%ls\n"),(LPCTSTR)btn->get_desc());
				fwprintf(fp, _T("%ls\n"),(LPCTSTR)btn->get_cmd());
				fwprintf(fp, _T("%d\n") , btn->is_batch_call());
			}

			fclose(fp);
		}
	}
}

UINT MyThreadProc(LPVOID pParam)
{
	COpenM1Dlg* pObject = (COpenM1Dlg*)pParam;

	FILE* fp = NULL;
	fopen_s(&fp, ".\\tmp\\ExecM1.bat", "w");
	if (fp) {

		CString cmd_line;

		for (int i = 0; i < pObject->get_list_ctrl()->GetItemCount(); i++) {
			CMyButton* btn = (CMyButton*)pObject->get_list_ctrl()->GetCtrl(i, 1);

			if (btn->is_batch_call()) {
				cmd_line  = "call ";
				cmd_line += btn->get_cmd();
			}
			else {
				cmd_line  = btn->get_cmd();
			}

			fwprintf(fp, _T("%ls\n"), (LPCTSTR)cmd_line);
		}

		fputs("pause\n", fp);
		fclose(fp);
	}

	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = _T(".\\tmp\\ExecM1.bat");
	ShExecInfo.lpParameters = _T("");
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOW;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

	DeleteFile(_T(".\\tmp\\ExecM1.bat"));

	return 0;   // thread completed successfully
}

void COpenM1Dlg::OnBnClickedRunProcs()
{
	AfxBeginThread(MyThreadProc, this);
}


void COpenM1Dlg::OnBnClickedClearProcs()
{
	m_pListCtrl->DeleteAllItems();
}
