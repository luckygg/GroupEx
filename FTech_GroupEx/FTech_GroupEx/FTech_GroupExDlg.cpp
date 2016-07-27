
// FTech_GroupExDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FTech_GroupEx.h"
#include "FTech_GroupExDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFTech_GroupExDlg dialog




CFTech_GroupExDlg::CFTech_GroupExDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFTech_GroupExDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFTech_GroupExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GRP_TEST, m_grpTest1);
	DDX_Control(pDX, IDC_GRP_TEST2, m_grpTest2);
	DDX_Control(pDX, IDC_GRP_TEST3, m_grpTest3);
	DDX_Control(pDX, IDC_GRP_TEST4, m_grpTest4);
}

BEGIN_MESSAGE_MAP(CFTech_GroupExDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CFTech_GroupExDlg message handlers

BOOL CFTech_GroupExDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_grpTest1.SetText(L"Image File");
	m_grpTest1.LoadImageFromFile(L"1.png");
	m_grpTest1.SetOffsetImage(70,0);
	m_grpTest1.SetOffsetBorder(-25,0);
	m_grpTest1.SetAlignTextCT();

	m_grpTest2.SetText(L"Disable");
	m_grpTest2.SetEnable(false);

	m_grpTest3.SetStandardMode(false);
	m_grpTest3.SetDrawTextBkg(true);
	m_grpTest3.SetColorTextBkg(255,44,44,44);
	m_grpTest3.SetColorBkg(255,61,61,61);
	m_grpTest3.SetColorText(255,255,255,255);
	m_grpTest3.LoadImageFromResource(IDB_PNG1,true);
	m_grpTest3.SetAlignTextCB();
	m_grpTest3.SetOffsetImage(80,0);

	m_grpTest4.SetStandardMode(false);
	m_grpTest4.SetColorBkg(255,61,61,61);
	m_grpTest4.SetColorText(255,255,255,255);
	m_grpTest4.SetAlignTextLT();
	m_grpTest4.SetOffsetText(5,5);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFTech_GroupExDlg::OnPaint()
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
HCURSOR CFTech_GroupExDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

