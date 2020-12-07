
// APIApp2Dlg.h: 헤더 파일
//

#pragma once

// CAPIApp2Dlg 대화 상자
class CAPIApp2Dlg : public CDialogEx
{
// 생성입니다.
public:
	CAPIApp2Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	BOOL validCheck(int type = 0);
	int setDataToList(CString& strUserID, CString& strPasswd, CString strFilter, CString& sqlstr);


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_APIAPP2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CListCtrl m_ctrlListCtrl;
	CString m_strPasswd;
	CString m_strUserID;
	CString m_strSearch;
	double m_dSearch;
	afx_msg void OnBnClickedBtn1();
	afx_msg void OnBnClickedBtn2();
	CString m_strMessage;
	CString m_strCombo1;
	CString m_strCombo2;
	CString m_strCombo3;
};
