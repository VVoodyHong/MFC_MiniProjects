
// PMStringDlg.h: 헤더 파일
//

#pragma once

#include <vector>

class PatternMatch
{
public:
	virtual int patternmatch(const char* pText, const char* pPtrn) = 0;
	virtual int getType() = 0;
};

class Brute_Force : public PatternMatch
{
public:
	int patternmatch(const char* pText, const char* pPtrn)
	{
		int lenText = (int)strlen(pText);
		int lenPtrn = (int)strlen(pPtrn);

		int m;	// m_strText의 index
		int n;	// m_strPattern의 index
		for (int i = 0; i < lenText; i++)
		{
			m = i;
			n = 0;
			while (pText[m] == pPtrn[n])
			{
				m++;
				n++;
				if (n == lenPtrn)
					return i;

				if (lenPtrn < n)
					break;
			}
		}
		return -1;
	}
	int getType() { return 0; }
};

class Boyer_Moore : public PatternMatch
{
public:
	std::vector<int> buildLastFunction(const char* pPtrn)
	{
		int lenPtrn = (int)strlen(pPtrn);

		const int N_ASCII = 128;				// number of ASCII characters
		std::vector<int> last(N_ASCII);			// assume ASCII character set
		for (int i = 0; i < N_ASCII; i++)		// initialize array
			last[i] = -1;
		for (int i = 0; i < lenPtrn; i++)
		{
			last[pPtrn[i]] = i;					// (implicit cast to ASCII code)
		}
		return last;
	}

	int patternmatch(const char* pText, const char* pPtrn)
	{
		int lenText = (int)strlen(pText);
		int lenPtrn = (int)strlen(pPtrn);

		std::vector<int> last = buildLastFunction(pPtrn);
		int i = lenPtrn - 1;
		if (lenText - 1 < i)				// pattern longer than text?
			return-1;						// ...then no match

		int j = lenPtrn - 1;
		do {
			if (pPtrn[j] == pText[i])
				if (j == 0) return i;		// found a match
				else {						// looking-glass heuristic
					i--; j--;				// proceed right-to-left
				}
			else {							// character-jump heuristic
				i = i + lenPtrn - min(j, 1 + last[pText[i]]);
				j = lenPtrn - 1;
			}
		} while (i <= lenText - 1);
		return -1;

	}
	int getType() { return 1; }
};

// CPMStringDlg 대화 상자
class CPMStringDlg : public CDialogEx
{
// 생성입니다.
public:
	CPMStringDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PMSTRING_DIALOG };
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
	CString m_strText;
	CString m_strPattern;
	CListBox m_ctrlList;
	BOOL m_nType;
	afx_msg void OnClickedBtnsearch();
};
