// TesNumDlg.h : header file
//

#if !defined(AFX_TESNUMDLG_H__2AC54E1C_E198_4F69_B41A_BC02F920C2A8__INCLUDED_)
#define AFX_TESNUMDLG_H__2AC54E1C_E198_4F69_B41A_BC02F920C2A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTesNumDlg dialog

class CTesNumDlg : public CDialog
{
// Construction
public:
	CTesNumDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTesNumDlg)
	enum { IDD = IDD_TESNUM_DIALOG };
	CString	m_sSS;
	CString	m_sRR;
	int		m_iLgn;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTesNumDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTesNumDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESNUMDLG_H__2AC54E1C_E198_4F69_B41A_BC02F920C2A8__INCLUDED_)
