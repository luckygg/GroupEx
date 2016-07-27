
// FTech_GroupExDlg.h : header file
//

#pragma once

#include "GroupEx.h"

// CFTech_GroupExDlg dialog
class CFTech_GroupExDlg : public CDialogEx
{
// Construction
public:
	CFTech_GroupExDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FTECH_GROUPEX_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public :
	CGroupEx m_grpTest1;
	CGroupEx m_grpTest2;
	CGroupEx m_grpTest3;
	CGroupEx m_grpTest4;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
};
