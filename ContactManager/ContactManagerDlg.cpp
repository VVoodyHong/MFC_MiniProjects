
// ContactManagerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ContactManager.h"
#include "ContactManagerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CContactManagerDlg 대화 상자



CContactManagerDlg::CContactManagerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONTACTMANAGER_DIALOG, pParent)
	, m_strName(_T(""))
	, m_strMobileTel(_T(""))
	, m_strOfficeTel(_T(""))
	, m_strHomeTel(_T(""))
	, m_strEmail(_T(""))
	, m_strBirth(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CContactManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_strName);
	DDX_Text(pDX, IDC_EDIT2, m_strMobileTel);
	DDX_Text(pDX, IDC_EDIT3, m_strOfficeTel);
	DDX_Text(pDX, IDC_EDIT4, m_strHomeTel);
	DDX_Text(pDX, IDC_EDIT5, m_strEmail);
	DDX_Text(pDX, IDC_EDIT6, m_strBirth);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
}

BEGIN_MESSAGE_MAP(CContactManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_DATALOAD, &CContactManagerDlg::OnBnClickedDataload)
	ON_BN_CLICKED(ID_DATAINSERT, &CContactManagerDlg::OnBnClickedDatainsert)
	ON_BN_CLICKED(ID_DATADELETE, &CContactManagerDlg::OnBnClickedDatadelete)
	ON_BN_CLICKED(ID_DATAMODIFY, &CContactManagerDlg::OnBnClickedDatamodify)
	ON_BN_CLICKED(ID_DATASAVE, &CContactManagerDlg::OnBnClickedDatasave)
	ON_BN_CLICKED(IDCANCEL, &CContactManagerDlg::OnBnClickedCancel)
	ON_LBN_SELCHANGE(IDC_LIST1, &CContactManagerDlg::OnSelchangeList1)
END_MESSAGE_MAP()


// CContactManagerDlg 메시지 처리기

BOOL CContactManagerDlg::OnInitDialog()
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

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CContactManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CContactManagerDlg::OnPaint()
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
HCURSOR CContactManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CContactManagerDlg::tockenstring(CStringArray& arr, CString& str)
{
	CString t = "";
	for (int i = 0; i < str.GetLength(); i++)
	{
		char s = str.GetAt(i);
		if (s == ',')
		{
			arr.Add(t);
			t = "";
			continue;
		}
		t += s;
	}
	arr.Add(t);
}

void CContactManagerDlg::OnBnClickedDataload()
{
	FILE* fp;
	errno_t err = fopen_s(&fp, "contact.txt", "rt");
	if (err != 0)
	{
		AfxMessageBox("Fail to open file!");
		return;
	}

	char fpln[64];
	while (fgets(fpln, 64, fp) != NULL)
	{
		size_t len = strlen(fpln);
		if (fpln[len - 1] == '\n')
			fpln[len - 1] = '\0';
		m_ctrlList.AddString(fpln);
	}
	fclose(fp);
}


void CContactManagerDlg::OnBnClickedDatainsert()
{
	UpdateData(TRUE);

	CString str;
	for (int i = 0; i < m_ctrlList.GetCount(); i++)
	{
		m_ctrlList.GetText(i, str);

		CStringArray arr;
		tockenstring(arr, str);

		if (arr.GetAt(0) == m_strName)
		{
			AfxMessageBox("같은 이름이 존재합니다.");
			return;
		}
	}
	m_ctrlList.AddString(m_strName + "," + m_strMobileTel + "," + m_strOfficeTel + "," + m_strHomeTel + "," + m_strEmail + "," + m_strBirth);
}


void CContactManagerDlg::OnBnClickedDatadelete()
{
	int nSel = m_ctrlList.GetCurSel();
	if (nSel == LB_ERR)
	{
		AfxMessageBox("선택된 데이터가 없습니다.");;
		return;
	}

	m_ctrlList.DeleteString(nSel);
}


void CContactManagerDlg::OnBnClickedDatamodify()
{
	UpdateData(TRUE);

	CString str;
	for (int i = 0; i < m_ctrlList.GetCount(); i++)
	{
		m_ctrlList.GetText(i, str);

		CStringArray arr;
		tockenstring(arr, str);

		if (arr.GetAt(0) == m_strName)
		{
			str =  m_strName + "," + m_strMobileTel + "," + m_strOfficeTel + "," + m_strHomeTel + "," + m_strEmail + "," + m_strBirth;
			m_ctrlList.InsertString(i, str);
			m_ctrlList.DeleteString(i+1);
			return;
		}
	}
	AfxMessageBox("이름이 발견되지 않습니다.");
}


void CContactManagerDlg::OnBnClickedDatasave()
{
	FILE* fp;
	errno_t err = fopen_s(&fp, "contact_new.txt", "wt");
	if (err != 0)
	{
		AfxMessageBox("Fail to open file!");
		return;
	}

	CString str;
	for (int i = 0 ; i < m_ctrlList.GetCount() ; i++)
	{
		m_ctrlList.GetText(i, str);
		fprintf(fp, "%s\n", (LPCTSTR)str);
	}
	fclose(fp);

	AfxMessageBox("저장되었습니다.");
}


void CContactManagerDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

void CContactManagerDlg::OnSelchangeList1()
{
	int nSel = m_ctrlList.GetCurSel();
	if (nSel == LB_ERR)	return;

	CString str;
	m_ctrlList.GetText(nSel, str);

	CStringArray arr;
	tockenstring(arr, str);

	m_strName		= arr.GetAt(0);
	m_strMobileTel	= arr.GetAt(1);
	m_strOfficeTel	= arr.GetAt(2);
	m_strHomeTel	= arr.GetAt(3);
	m_strEmail		= arr.GetAt(4);
	m_strBirth		= arr.GetAt(5);

	UpdateData(FALSE);
}
