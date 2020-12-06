
// ContactManager2Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "ContactManager2.h"
#include "ContactManager2Dlg.h"
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


// CContactManager2Dlg 대화 상자



CContactManager2Dlg::CContactManager2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CONTACTMANAGER2_DIALOG, pParent)
	, m_strName(_T(""))
	, m_strMobileTel(_T(""))
	, m_strOfficeTel(_T(""))
	, m_strHomeTel(_T(""))
	, m_strEmail(_T(""))
	, m_strBirth(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	bucketSize = 10;
	hash = new MyHash(bucketSize);
}

CContactManager2Dlg::~CContactManager2Dlg()
{
	delete hash;
}

void CContactManager2Dlg::DoDataExchange(CDataExchange* pDX)
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

BEGIN_MESSAGE_MAP(CContactManager2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_DATALOAD, &CContactManager2Dlg::OnBnClickedDataload)
	ON_BN_CLICKED(ID_DATAINSERT, &CContactManager2Dlg::OnBnClickedDatainsert)
	ON_BN_CLICKED(ID_DATADELETE, &CContactManager2Dlg::OnBnClickedDatadelete)
	ON_BN_CLICKED(ID_DATAMODIFY, &CContactManager2Dlg::OnBnClickedDatamodify)
	ON_BN_CLICKED(ID_DATASAVE, &CContactManager2Dlg::OnBnClickedDatasave)
	ON_BN_CLICKED(IDCANCEL, &CContactManager2Dlg::OnBnClickedCancel)
	ON_LBN_SELCHANGE(IDC_LIST1, &CContactManager2Dlg::OnSelchangeList1)
END_MESSAGE_MAP()


// CContactManager2Dlg 메시지 처리기

BOOL CContactManager2Dlg::OnInitDialog()
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

void CContactManager2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CContactManager2Dlg::OnPaint()
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
HCURSOR CContactManager2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CContactManager2Dlg::displayHashtoList()
{
	NODE** bucketArray = hash->getBucketArray();

	m_ctrlList.ResetContent();
	for (int i = 0; i < bucketSize; i++)
	{
		NODE* t = bucketArray[i];
		if (t == NULL)	continue;
		while (1)
		{
			string str = t->name + "," + t->mobile_tel + "," + t->office_tel + "," + t->home_tel + "," + t->email + "," + t->birth;

			m_ctrlList.AddString(str.c_str());

			t = t->next;
			if (t == NULL) break;
		}
	}
}

void CContactManager2Dlg::tockenstring(vector<string>& vec, char* pstr, size_t len)
{
	string t = "";
	for (size_t i = 0; i < len; i++)
	{
		if (pstr[i] == ',')
		{
			vec.push_back(t);
			t = "";
			continue;
		}
		t += pstr[i];
	}
	vec.push_back(t);
}

void CContactManager2Dlg::OnBnClickedDataload()
{
	FILE* fp;
	errno_t err = fopen_s(&fp, "contact.txt", "rt");
	if (err != 0)
	{
		AfxMessageBox("Fail to open file!");
		return;
	}

	if (hash) delete hash;
	hash = new MyHash(bucketSize);

	char fpln[64];
	while (fgets(fpln, 64, fp) != NULL)
	{
		vector<string> vec;
		size_t len = strlen(fpln);
		if (fpln[len - 1] == '\n')
			fpln[len - 1] = '\0';

		if (0 < strlen(fpln))
		{
			tockenstring(vec, fpln, len - 1);
			hash->insertNode(vec[0], vec[1], vec[2], vec[3], vec[4], vec[5]);
		}
	}
	fclose(fp);

	displayHashtoList();
}

void CContactManager2Dlg::OnBnClickedDatainsert()
{
	UpdateData(TRUE);
	if (hash->searchNode(m_strName.GetString()) != NULL)
	{
		AfxMessageBox("같은 이름이 존재합니다.");
		return;
	}

	hash->insertNode((LPCTSTR)m_strName, (LPCTSTR)m_strMobileTel, (LPCTSTR)m_strOfficeTel,
		(LPCTSTR)m_strHomeTel, (LPCTSTR)m_strEmail, (LPCTSTR)m_strBirth);
	displayHashtoList();
}


void CContactManager2Dlg::OnBnClickedDatadelete()
{
	UpdateData(TRUE);
	NODE* t = hash->searchNode(m_strName.GetString());
	if (t == NULL)
	{
		AfxMessageBox("선택한 이름이 없습니다.");
		return;
	}

	hash->deleteNode(t->name);
	displayHashtoList();
}


void CContactManager2Dlg::OnBnClickedDatamodify()
{
	UpdateData(TRUE);
	NODE* t = hash->searchNode(m_strName.GetString());
	if (t == NULL)
	{
		AfxMessageBox("선택한 이름이 없습니다.");
		return;
	}
	t->mobile_tel = (LPCSTR)m_strMobileTel;
	t->office_tel = (LPCSTR)m_strOfficeTel;
	t->home_tel = (LPCSTR)m_strHomeTel;
	t->email = (LPCSTR)m_strEmail;
	t->birth = (LPCSTR)m_strBirth;

	displayHashtoList();
}

void CContactManager2Dlg::OnBnClickedDatasave()
{
	NODE** bucketArray = hash->getBucketArray();

	FILE* fp;
	errno_t err = fopen_s(&fp, "contact.txt", "wt");
	if (err != 0)
	{
		AfxMessageBox("Fail to open file!");
		return;
	}

	for (int i = 0; i < bucketSize; i++)
	{
		NODE* t = bucketArray[i];
		if (t == NULL)	continue;
		while (1)
		{
			string str = t->name + "," + t->mobile_tel + "," + t->office_tel + "," + t->home_tel + "," + t->email + "," + t->birth;

			fprintf(fp, "%s\n", str.c_str());

			t = t->next;
			if (t == NULL) break;
		}
	}
	fclose(fp);

	AfxMessageBox("저장되었습니다.");
}

void CContactManager2Dlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

void CContactManager2Dlg::OnSelchangeList1()
{
	int nSel = m_ctrlList.GetCurSel();
	if (nSel == LB_ERR)	return;

	CString str;
	m_ctrlList.GetText(nSel, str);

	vector<string> vec;
	tockenstring(vec, (LPSTR)(LPCSTR)str, str.GetLength());

	m_strName = vec[0].c_str();
	m_strMobileTel = vec[1].c_str();
	m_strOfficeTel = vec[2].c_str();
	m_strHomeTel = vec[3].c_str();
	m_strEmail = vec[4].c_str();
	m_strBirth = vec[5].c_str();

	UpdateData(FALSE);
}
