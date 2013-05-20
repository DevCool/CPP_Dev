// MyStatic.cpp : implementation file
//

#include "stdafx.h"
#include "MyStatic.h"


// CMyStatic

IMPLEMENT_DYNAMIC(CMyStatic, CStatic)

CMyStatic::CMyStatic()
{
    m_BkColor = GetSysColor (CTLCOLOR_DLG);

	m_BkgrndBrush.CreateSysColorBrush (COLOR_WINDOW);
    
    m_FgColor = COLORREF (0X000000);

	m_hCursor = LoadCursor(NULL, MAKEINTRESOURCE (IDC_ARROW));
}


CMyStatic::~CMyStatic()
{
}



BEGIN_MESSAGE_MAP(CMyStatic, CStatic)
    ON_WM_CTLCOLOR()
    ON_WM_CTLCOLOR_REFLECT()
	ON_WM_SETCURSOR()

END_MESSAGE_MAP()

void CMyStatic::SetForeGroundColor(COLORREF clr)
{
    m_FgColor = clr;
    RedrawWindow();
}

void CMyStatic::SetBackGroundColor(COLORREF clr)
{
    m_BkColor = clr;
    m_BkgrndBrush.DeleteObject();
    m_BkgrndBrush.CreateSolidBrush(clr);
    RedrawWindow();
}


void CMyStatic::SetNewFont (int size, CString FontName)
{
    CFont TextFont;
    TextFont.CreatePointFont (size, FontName);
    SetFont (&TextFont);
    TextFont.Detach ();
}


// CMyStatic message handlers


HBRUSH CMyStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
    HBRUSH hbr = (HBRUSH)m_BkgrndBrush; 

    pDC->SetBkColor(m_BkColor);
    pDC->SetTextColor(m_FgColor);

    return hbr;
}

void CMyStatic::SetHandCursor ()
{
	m_hCursor = LoadCursor(NULL, MAKEINTRESOURCE (IDC_HAND));
}

BOOL CMyStatic::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
    if (m_hCursor)
    {
        ::SetCursor(m_hCursor);
        return TRUE;
    }
    return FALSE;
}

