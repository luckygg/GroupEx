// GroupEx.cpp : implementation file
//

#include "stdafx.h"
#include "FTech_GroupEx.h"
#include "GroupEx.h"


// CGroupEx

IMPLEMENT_DYNAMIC(CGroupEx, CWnd)

CGroupEx::CGroupEx()
{
	m_clrBkg	= Color(255,128,128,128);
	m_clrText	= Color(255,  0,  0,  0);
	m_clrTextBkg= Color(255,100,100,100);
	m_clrBorder = Color(255,255,  0,  0);

	m_bEnable		= true;
	m_bIsStandard	= true;
	m_bDrawTextBkg  = false;

	m_fSizeBorder	= 2;
	m_fSizeText		= 20;
	m_nOffsetTextX	= 0;
	m_nOffsetTextY	= 0;
	m_nOffsetImageX = 0;
	m_nOffsetImageY = 0;
	m_nTextAlign1	= 0;
	m_nTextAlign2	= 0;
	m_nOffsetSplitter = 0;
	m_nOffsetLeft	= 0;
	m_nOffsetRight	= 0;

	m_pBmpImage = NULL;

	m_rcImage = Rect(0,0,0,0);
	m_rcCaption = Rect(0,0,0,0);
}

CGroupEx::~CGroupEx()
{
	if (m_pBmpImage != NULL)
	{
		delete m_pBmpImage;
		m_pBmpImage = NULL;
	}
}


BEGIN_MESSAGE_MAP(CGroupEx, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()



// CGroupEx message handlers




void CGroupEx::PreSubclassWindow()
{
	CRect rect;
	GetClientRect(&rect);

	m_rcImage = Rect(rect.left, rect.top, rect.Width(), rect.Height());

	CWnd::PreSubclassWindow();
}


void CGroupEx::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CRect rect;
	GetClientRect(&rect);

	Graphics mainG (dc.GetSafeHdc());

	// 메모리 생성
	Bitmap memBmp(rect.Width(), rect.Height());

	Graphics memG(&memBmp);

	//----- 메모리상에 그리는 부분 -----//
	if (m_bIsStandard == true)
		DrawBorder(&memG);
	else
		DrawBkg(&memG);

	DrawImage(&memG);
	DrawText(&memG);
	//---------------------------------//

	if (m_bEnable == true)
	{
		// 그려진 메모리를 최종 출력
		mainG.DrawImage(&memBmp,0,0);
	}
	else
	{
		ColorMatrix GrayMat = {	
			0.30f, 0.30f, 0.30f, 0.00f, 0.00f,
			0.59f, 0.59f, 0.59f, 0.00f, 0.00f,
			0.11f, 0.11f, 0.11f, 0.00f, 0.00f,
			0.00f, 0.00f, 0.00f, 1.00f, 0.00f,
			0.00f, 0.00f, 0.00f, 0.00f, 1.00f	};

			ImageAttributes ia;
			ia.SetColorMatrix(&GrayMat);

			RectF grect; grect.X=0, grect.Y=0; grect.Width = (float)rect.Width(); grect.Height = (float)rect.Height();
			mainG.DrawImage(&memBmp, grect, 0, 0, (float)rect.Width(), (float)rect.Height(), UnitPixel, &ia);
	}
}


BOOL CGroupEx::OnEraseBkgnd(CDC* pDC)
{
	//Avoid Flicker.
	//return CWnd::OnEraseBkgnd(pDC);
	return TRUE;
}

void CGroupEx::DrawBorder(Graphics *pG)
{
	CRect rect;
	GetClientRect(&rect);
	
	CString text = L"";
	GetWindowText(text);

	FontFamily fontptroll(L"Arial");
	Gdiplus::Font font(&fontptroll, m_fSizeText, FontStyleRegular, UnitPixel);

	StringFormat formatAlign;
	formatAlign.SetAlignment((Gdiplus::StringAlignment)m_nTextAlign1);		// Left / Center / Right
	formatAlign.SetLineAlignment((Gdiplus::StringAlignment)m_nTextAlign2);	// Top / Middle / Bottom

	RectF rc((float)rect.left+m_nOffsetTextX, (float)rect.top+m_nOffsetTextY, (float)rect.Width(),(float)rect.Height());
	RectF rcDrawn(0,0,0,0);
	pG->MeasureString(text,text.GetLength(),&font,rc,&formatAlign,&rcDrawn);

	if (m_nTextAlign2 == 0)
	{
		REAL margin = (rcDrawn.GetBottom()-rcDrawn.GetTop())/2;
		Pen pen(m_clrBorder,m_fSizeBorder);
		pG->DrawLine(&pen,rcDrawn.GetLeft()+m_nOffsetLeft,rcDrawn.GetTop()+margin,(REAL)rect.left,(REAL)rect.top+margin);
		pG->DrawLine(&pen,(REAL)rect.left,(REAL)rect.top+margin,(REAL)rect.left,(REAL)rect.bottom);
		pG->DrawLine(&pen,(REAL)rect.left,(REAL)rect.bottom,(REAL)rect.right,(REAL)rect.bottom);
		pG->DrawLine(&pen,(REAL)rect.right,(REAL)rect.bottom,(REAL)rect.right,(REAL)rect.top+margin);
		pG->DrawLine(&pen,(REAL)rect.right,(REAL)rect.top+margin,rcDrawn.GetRight()+m_nOffsetRight,rcDrawn.GetTop()+margin);
	}
	else
	{
		REAL margin = (rcDrawn.GetBottom()-rcDrawn.GetTop())/2;
		Pen pen(m_clrBorder,m_fSizeBorder);
		pG->DrawLine(&pen,(REAL)rect.left, (REAL)rect.top, (REAL)rect.left, (REAL)rect.bottom-margin);
		pG->DrawLine(&pen,(REAL)rect.left, (REAL)rect.bottom-margin, rcDrawn.GetLeft()+m_nOffsetLeft, rcDrawn.GetBottom()-margin);
		pG->DrawLine(&pen,rcDrawn.GetRight()+m_nOffsetRight, rcDrawn.GetBottom()-margin, (REAL)rect.right, (REAL)rect.bottom-margin);
		pG->DrawLine(&pen,(REAL)rect.right, (REAL)rect.bottom-margin, (REAL)rect.right, (REAL)rect.top);
		pG->DrawLine(&pen,(REAL)rect.right, (REAL)rect.top, (REAL)rect.left, (REAL)rect.top);
	}
}

void CGroupEx::DrawBkg(Graphics *pG)
{
	CRect rect;
	GetClientRect(&rect);

	if (m_bDrawTextBkg == true)
	{
		CString text = L"";
		GetWindowText(text);

		FontFamily fontptroll(L"굴림");
		Gdiplus::Font font(&fontptroll, m_fSizeText, FontStyleRegular, UnitPixel);

		StringFormat formatAlign;
		formatAlign.SetAlignment((Gdiplus::StringAlignment)m_nTextAlign1);		// Left / Center / Right
		formatAlign.SetLineAlignment((Gdiplus::StringAlignment)m_nTextAlign2);	// Top / Middle / Bottom

		RectF rc((float)rect.left+m_nOffsetTextX, (float)rect.top+m_nOffsetTextY, (float)rect.Width(),(float)rect.Height());
		RectF rcDrawn(0,0,0,0);
		pG->MeasureString(text,text.GetLength(),&font,rc,&formatAlign,&rcDrawn);

		if (m_nTextAlign2 == 0)
		{
			SolidBrush brs1(m_clrTextBkg);
			pG->FillRectangle(&brs1,rect.left,rect.top,rect.right,(INT)rcDrawn.GetBottom()+m_nOffsetSplitter);

			SolidBrush brs2(m_clrBkg);
			pG->FillRectangle(&brs2,rect.left,(INT)rcDrawn.GetBottom()+m_nOffsetSplitter,rect.right,rect.bottom);
		}
		else
		{
			SolidBrush brs1(m_clrBkg);
			pG->FillRectangle(&brs1,rect.left,rect.top,rect.right,(INT)rcDrawn.GetTop()+m_nOffsetSplitter);

			SolidBrush brs2(m_clrTextBkg);
			pG->FillRectangle(&brs2,rect.left,(INT)rcDrawn.GetTop()+m_nOffsetSplitter,rect.right,rect.bottom);
		}
	}
	else
	{
		SolidBrush brs(m_clrBkg);
		pG->FillRectangle(&brs,rect.left,rect.top,rect.right,rect.bottom);
	}
}

void CGroupEx::DrawImage(Graphics *pG)
{
	CRect rect;
	GetClientRect(&rect);

	if (m_pBmpImage == NULL) return;

	CString text = L"";
	GetWindowText(text);

	FontFamily fontptroll(L"Arial");
	Gdiplus::Font font(&fontptroll, m_fSizeText, FontStyleRegular, UnitPixel);

	StringFormat formatAlign;
	formatAlign.SetAlignment((Gdiplus::StringAlignment)m_nTextAlign1);		// Left / Center / Right
	formatAlign.SetLineAlignment((Gdiplus::StringAlignment)m_nTextAlign2);	// Top / Middle / Bottom

	RectF rc((float)rect.left+m_nOffsetTextX, (float)rect.top+m_nOffsetTextY, (float)rect.Width(),(float)rect.Height());
	RectF rcDrawn(0,0,0,0);
	pG->MeasureString(text,text.GetLength(),&font,rc,&formatAlign,&rcDrawn);

	SizeF size(0,0);
	rcDrawn.GetSize(&size);

	if (m_nTextAlign2 == 0)
	{
		m_rcImage = Rect(m_rcImage.GetLeft()+m_nOffsetImageX, (INT)rcDrawn.GetTop()+m_nOffsetImageY, (INT)size.Height, (INT)size.Height);
	}
	else
	{
		m_rcImage = Rect(m_rcImage.GetLeft()+m_nOffsetImageX, (INT)rcDrawn.GetTop()+m_nOffsetImageY, (INT)size.Height, (INT)size.Height);
	}

	pG->DrawImage(m_pBmpImage, m_rcImage, 0,0, m_pBmpImage->GetWidth(), m_pBmpImage->GetHeight(), UnitPixel);
}

void CGroupEx::DrawText(Graphics *pG)
{
	CRect rect;
	GetClientRect(&rect);

	CString text = L"";
	GetWindowText(text);

	FontFamily fontptroll(L"Arial");
	Gdiplus::Font font(&fontptroll, m_fSizeText, FontStyleRegular, UnitPixel);

	StringFormat formatAlign;
	formatAlign.SetAlignment((Gdiplus::StringAlignment)m_nTextAlign1);		// Left / Center / Right
	formatAlign.SetLineAlignment((Gdiplus::StringAlignment)m_nTextAlign2);	// Top / Middle / Bottom
	
	SolidBrush brs(m_clrText);
	
	RectF rc((float)rect.left+m_nOffsetTextX, (float)rect.top+m_nOffsetTextY, (float)rect.Width(),(float)rect.Height());

	pG->DrawString(text,text.GetLength(),&font,rc,&formatAlign,&brs);

	RectF rcDrawn(0,0,0,0);
	pG->MeasureString(text,text.GetLength(),&font,rc,&formatAlign,&rcDrawn);
}


bool CGroupEx::LoadImageFromFile(CString strPath)
{
	if (IsFileExist(strPath) == false) return false;

	if (m_pBmpImage != NULL)
	{
		delete m_pBmpImage;
		m_pBmpImage = NULL;
	}

	m_pBmpImage = (Bitmap*)Image::FromFile(strPath);

	if (m_pBmpImage->GetLastStatus() != Gdiplus::Ok)
		return false;

	Invalidate();

	return true;
}

bool CGroupEx::LoadImageFromResource(UINT ID, bool bPNG)
{
	if (m_pBmpImage != NULL)
	{
		delete m_pBmpImage;
		m_pBmpImage = NULL;
	}

	if (bPNG == false)
	{
		m_pBmpImage = Bitmap::FromResource(AfxGetInstanceHandle(),(WCHAR*)MAKEINTRESOURCE(ID));
	}
	else
	{
		// PNG 리소스는 Bitmap 리소스를 불러오는 것보다 복잡하다.
		HRSRC hResource = ::FindResource(AfxGetApp()->m_hInstance, (WCHAR*)MAKEINTRESOURCEW(ID), L"PNG");	// 3번째 인자는 실제 리소스가 분류되는 문자열이 전달되어야 한다.
		if (!hResource) return false;

		DWORD imageSize = ::SizeofResource(AfxGetApp()->m_hInstance, hResource);
		if (!imageSize) return false;

		const void* pResourceData = ::LockResource(::LoadResource(AfxGetApp()->m_hInstance, hResource));
		if (!pResourceData) return false;

		HGLOBAL hBuffer  = ::GlobalAlloc(GMEM_MOVEABLE, imageSize);
		if (hBuffer)
		{
			void* pBuffer = ::GlobalLock(hBuffer);
			if (pBuffer)
			{
				CopyMemory(pBuffer, pResourceData, imageSize);

				IStream* pStream = NULL;
				if (::CreateStreamOnHGlobal(hBuffer, FALSE, &pStream) == S_OK)
				{
					m_pBmpImage = Gdiplus::Bitmap::FromStream(pStream);
					pStream->Release();

					if (m_pBmpImage)
					{
						if (m_pBmpImage->GetLastStatus() != Gdiplus::Ok)
						{
							delete m_pBmpImage;
							m_pBmpImage = NULL;
						}
					}
				}
			}
			::GlobalUnlock(hBuffer);
			::GlobalFree(hBuffer);
		}
	}

	if (m_pBmpImage->GetLastStatus() != Gdiplus::Ok)
		return false;

	Invalidate();

	return true;
}

bool CGroupEx::IsFileExist(CString strPath)
{
	HANDLE hFind;
	WIN32_FIND_DATA fd;
	if ((hFind = ::FindFirstFile(strPath, &fd)) == INVALID_HANDLE_VALUE) 
	{
		FindClose(hFind);
		return false;
	}

	return true;
}