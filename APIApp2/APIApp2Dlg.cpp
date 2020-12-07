
// APIApp2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "APIApp2.h"
#include "APIApp2Dlg.h"
#include "afxdialogex.h"
#include "mysql.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(lib, "libmysql.lib")

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CAPIApp2Dlg 대화 상자



CAPIApp2Dlg::CAPIApp2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_APIAPP2_DIALOG, pParent)
	, m_strPasswd(_T(""))
	, m_strUserID(_T("woody"))
	, m_strSearch(_T(""))
	, m_dSearch(0)
	, m_strMessage(_T(""))
	, m_strCombo1(_T(""))
	, m_strCombo2(_T(""))
	, m_strCombo3(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAPIApp2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ctrlListCtrl);
	DDX_Text(pDX, IDC_PASSWD, m_strPasswd);
	DDX_Text(pDX, IDC_USERID, m_strUserID);
	DDX_Text(pDX, IDC_SEARCHSTR1, m_strSearch);
	DDX_Text(pDX, IDC_SEARCHSTR2, m_dSearch);
	DDX_Text(pDX, IDC_MESSAGE, m_strMessage);
	DDX_CBString(pDX, IDC_COMBO1, m_strCombo1);
	DDX_CBString(pDX, IDC_COMBO2, m_strCombo2);
	DDX_CBString(pDX, IDC_COMBO3, m_strCombo3);
}

BEGIN_MESSAGE_MAP(CAPIApp2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CAPIApp2Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN1, &CAPIApp2Dlg::OnBnClickedBtn1)
	ON_BN_CLICKED(IDC_BTN2, &CAPIApp2Dlg::OnBnClickedBtn2)
END_MESSAGE_MAP()


// CAPIApp2Dlg 메시지 처리기

BOOL CAPIApp2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	//-------------------------------------------------------------------------------------
	// ListCtrl Title Setting
	LV_COLUMN lvcolumn;
	lvcolumn.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH | LVCF_FMT;

	m_ctrlListCtrl.SetExtendedStyle(m_ctrlListCtrl.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CString titlearr[7] = { _T("#"), _T("Code"), _T("Name"), _T("Region"), _T("SurfaceArea"), _T("Population"), _T("GNP") };
	UINT titlewdt[7] = { 40, 50, 250, 180, 100, 100, 100 };
	UINT titlefmt[7] = { LVCFMT_LEFT, LVCFMT_CENTER, LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_RIGHT, LVCFMT_RIGHT };

	for (int i = 0; i < 7; i++)
	{
		lvcolumn.pszText = (LPTSTR)(LPCTSTR)titlearr[i];
		lvcolumn.iSubItem = i;
		lvcolumn.cx = titlewdt[i];
		lvcolumn.fmt = titlefmt[i];

		m_ctrlListCtrl.InsertColumn(i, &lvcolumn);
	}
	//-------------------------------------------------------------------------------------
	// ComboBox Setting
	CComboBox* pCbo = (CComboBox*)GetDlgItem(IDC_COMBO1);
	pCbo->AddString(_T("Name"));
	pCbo->AddString(_T("Region"));
	pCbo->SetCurSel(0);

	pCbo = (CComboBox*)GetDlgItem(IDC_COMBO2);
	pCbo->AddString(_T("SurfaceArea"));
	pCbo->AddString(_T("Population"));
	pCbo->AddString(_T("GNP"));
	pCbo->SetCurSel(0);

	pCbo = (CComboBox*)GetDlgItem(IDC_COMBO3);
	pCbo->AddString(_T(">="));
	pCbo->AddString(_T("="));
	pCbo->AddString(_T("<="));
	pCbo->SetCurSel(0);
	//-------------------------------------------------------------------------------------

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CAPIApp2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CAPIApp2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CAPIApp2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// 검색전에 Validation 점검
BOOL CAPIApp2Dlg::validCheck(int type)
{
	if (m_strUserID.IsEmpty())
	{
		AfxMessageBox("You need a UserID");
		return FALSE;
	}
	if (m_strPasswd.IsEmpty())
	{
		AfxMessageBox("You need a Password");
		return FALSE;
	}

	// 문자열 검색 validation
	if (type == 1 && m_strSearch.IsEmpty())
	{
		AfxMessageBox("You need a Search String");
		return FALSE;
	}

	return TRUE;
}

int CAPIApp2Dlg::setDataToList(CString& strUserID, CString& strPasswd, CString strFilter, CString& sqlstr)
{
	MYSQL mysql;

	if (!mysql_init(&mysql))
	{
		AfxMessageBox(_T("fail to mysql_init()"));
		return -1;
	}

	if (mysql_real_connect(&mysql, "localhost", strUserID, strPasswd, "world", 0, NULL, 0) == FALSE)
	{
		AfxMessageBox(mysql_error(&mysql));
		return -1;
	}

	if (!strFilter.IsEmpty())	sqlstr = _T("select Code,Name,Region,SurfaceArea,Population,GNP from country where ") + strFilter;
	else						sqlstr = _T("select Code,Name,Region,SurfaceArea,Population,GNP from country");

	mysql_query(&mysql, sqlstr);

	MYSQL_RES* result = mysql_store_result(&mysql);
	if (!result)
	{
		AfxMessageBox(mysql_error(&mysql));
		mysql_close(&mysql);
		return -1;
	}

	int idx = 0;
	CString valstr;
	MYSQL_ROW row;
	while (row = mysql_fetch_row(result))
	{
		valstr.Format("%d", idx + 1);
		m_ctrlListCtrl.InsertItem(idx, valstr);

		for (int i = 0; i < 6; i++)
			m_ctrlListCtrl.SetItemText(idx, i + 1, row[i]);

		idx++;
	}
	mysql_free_result(result);

	mysql_close(&mysql);

	return idx;
}

void CAPIApp2Dlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	if (validCheck() == FALSE)	return;

	m_ctrlListCtrl.DeleteAllItems();

	CString sqlstr;
	int rec = setDataToList(m_strUserID, m_strPasswd, _T(""), sqlstr);

	m_strMessage = _T("");
	if (0 <= rec)	m_strMessage.Format(_T("[%d]%s"), rec, sqlstr);

	UpdateData(FALSE);
}

void CAPIApp2Dlg::OnBnClickedBtn1()	// 문자열 검색
{
	UpdateData(TRUE);

	if (validCheck(1) == FALSE)	return;

	m_ctrlListCtrl.DeleteAllItems();

	CString strFilter = m_strCombo1 + _T(" like '%") + m_strSearch + _T("%'");

	CString sqlstr;
	int rec = setDataToList(m_strUserID, m_strPasswd, strFilter, sqlstr);

	m_strMessage = _T("");
	if (0 <= rec)		m_strMessage.Format(_T("[%d]%s"), rec, sqlstr);

	UpdateData(FALSE);
}

void CAPIApp2Dlg::OnBnClickedBtn2()	// 수치 검색
{
	UpdateData(TRUE);

	if (validCheck() == FALSE)	return;

	m_ctrlListCtrl.DeleteAllItems();

	CString val;
	if (m_strCombo2 == _T("Population"))	val.Format(_T("%d"), (int)m_dSearch);
	else									val.Format(_T("%.2f"), m_dSearch);

	CString strFilter = m_strCombo2 + m_strCombo3 + val;

	CString sqlstr;
	int rec = setDataToList(m_strUserID, m_strPasswd, strFilter, sqlstr);

	m_strMessage = _T("");
	if (0 <= rec)		m_strMessage.Format(_T("[%d]%s"), rec, sqlstr);

	UpdateData(FALSE);
}
