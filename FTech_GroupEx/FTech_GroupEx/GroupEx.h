#pragma once

//----------------------------------------------------------
// GroupEx Control
//----------------------------------------------------------
// Programmed by William Kim
//----------------------------------------------------------

// CGroupEx

class CGroupEx : public CWnd
{
	DECLARE_DYNAMIC(CGroupEx)

public:
	CGroupEx();
	virtual ~CGroupEx();

public :
	//----- Set Enable & Disable Control -----//
	void SetEnable(bool bEnable) { m_bEnable = bEnable; Invalidate(); }

	//----- Set Draw Mode -----//
	void SetStandardMode	(bool bEnable) { m_bIsStandard	= bEnable; Invalidate(); }
	void SetDrawTextBkg		(bool bEnable) { m_bDrawTextBkg = bEnable; Invalidate(); }

	//----- Set Text -----//
	void SetText(CString strText) { SetWindowText(strText); Invalidate(); }

	//----- Set Offset -----//
	void SetOffsetText		(int nX, int nY)		{ m_nOffsetTextX	= nX;		m_nOffsetTextY	= nY;		Invalidate(); }
	void SetOffsetImage		(int nX, int nY)		{ m_nOffsetImageX	= nX;		m_nOffsetImageY = nY;		Invalidate(); }
	void SetOffsetBorder	(int nLeft, int nRight) { m_nOffsetLeft		= nLeft;	m_nOffsetRight	= nRight;	Invalidate(); }
	void SetOffsetSplitter	(int nY)				{ m_nOffsetSplitter = nY;									Invalidate(); }

	//----- Set Size -----//
	void SetSizeText	(float fSize) { m_fSizeText		= fSize; Invalidate(); }
	void SetSizeBorder	(float fSize) { m_fSizeBorder	= fSize; Invalidate(); }
	void SetSizeImage	(int nLeft, int nTop, int nWidth, int nHeight) { m_rcImage = Rect(nLeft, nTop, nWidth, nHeight); Invalidate(); }

	//----- Set Color -----//
	void SetColorBkg	(int nA, int nR, int nG, int nB) { m_clrBkg		= Color(nA, nR, nG, nB); Invalidate(); }
	void SetColorBorder	(int nA, int nR, int nG, int nB) { m_clrBorder	= Color(nA, nR, nG, nB); Invalidate(); }
	void SetColorText	(int nA, int nR, int nG, int nB) { m_clrText	= Color(nA, nR, nG, nB); Invalidate(); }
	void SetColorTextBkg(int nA, int nR, int nG, int nB) { m_clrTextBkg	= Color(nA, nR, nG, nB); Invalidate(); }

	//----- Set Text Alignment -----//
	void SetAlignTextLT() { m_nTextAlign1 = 0; m_nTextAlign2 = 0; Invalidate(); }
	void SetAlignTextCT() { m_nTextAlign1 = 1; m_nTextAlign2 = 0; Invalidate(); }
	void SetAlignTextRT() { m_nTextAlign1 = 2; m_nTextAlign2 = 0; Invalidate(); }
	void SetAlignTextLB() { m_nTextAlign1 = 0; m_nTextAlign2 = 2; Invalidate(); }
	void SetAlignTextCB() { m_nTextAlign1 = 1; m_nTextAlign2 = 2; Invalidate(); }
	void SetAlignTextRB() { m_nTextAlign1 = 2; m_nTextAlign2 = 2; Invalidate(); }
									 
	//----- Set Image -----//
	bool LoadImageFromFile(CString strPath);
	bool LoadImageFromResource(UINT ID, bool bPNG);

private :
	bool	m_bEnable;
	bool	m_bIsStandard;
	bool	m_bDrawTextBkg;
	int		m_nOffsetTextX;
	int		m_nOffsetTextY;
	int		m_nOffsetImageX;
	int		m_nOffsetImageY;
	int		m_nOffsetSplitter;
	int		m_nOffsetLeft;
	int		m_nOffsetRight;
	int		m_nTextAlign1;
	int		m_nTextAlign2;
	float	m_fSizeText;
	float	m_fSizeBorder;
	Color	m_clrBkg;
	Color	m_clrTextBkg;
	Color	m_clrText;
	Color	m_clrBorder;
	Rect	m_rcImage;
	Rect	m_rcCaption;
	Bitmap* m_pBmpImage;

private :
	void DrawBorder(Graphics *pG);
	void DrawBkg(Graphics *pG);
	void DrawImage(Graphics *pG);
	void DrawText(Graphics *pG);
	bool IsFileExist(CString strPath);
protected:
	DECLARE_MESSAGE_MAP()
	virtual void PreSubclassWindow();
public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


