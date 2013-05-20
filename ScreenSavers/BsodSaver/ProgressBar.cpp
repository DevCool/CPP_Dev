// ProgressBar.cpp : implementation file
//

#include "stdafx.h"
#include "ProgressBar.h"
#include "Resource.h"

// CProgressBar
#define SCROLL_BAR_WIDTH 22
#define SCROLL_BAR_HEIGHT 9
#define SCROLLING_SPEED 40
#define SCROLL_JUMP 4
#define BACKGROUND_COLOR 0x000000

IMPLEMENT_DYNAMIC(CProgressBar, CStatic)

CProgressBar::CProgressBar()
{
    m_x = 0;
    m_y = 0;
    
	//Set in OnSize function
    m_width = 0;
    m_height = 0;
}

CProgressBar::~CProgressBar()
{
}


BEGIN_MESSAGE_MAP(CProgressBar, CStatic)
    ON_WM_TIMER()
    ON_WM_PAINT()
    ON_WM_SIZE()
END_MESSAGE_MAP()



// CProgressBar message handlers

void CProgressBar::StartTimer ()
{
    m_x = -SCROLL_BAR_WIDTH;
    SetTimer (2, SCROLLING_SPEED, NULL);
}

void CProgressBar::OnTimer(UINT_PTR nIDEvent)
{
    m_x += SCROLL_JUMP;
    if (m_x >= m_width)
    {
        m_x = -SCROLL_BAR_WIDTH;
    }
    
    Invalidate ();

    CStatic::OnTimer(nIDEvent);
}

void CProgressBar::OnPaint()
{
    CPaintDC dc(this); // device context for painting

    CRect boudingBox;
    GetWindowRect (&boudingBox);
    this->ScreenToClient (&boudingBox);
    dc.FillSolidRect (boudingBox, BACKGROUND_COLOR);
    
    CBitmap scrollBMP;
    scrollBMP.LoadBitmap (IDB_SCROLLBAR_BITMAP);

    BITMAP bm;
    scrollBMP.GetBitmap (&bm);
    CPoint size (bm.bmWidth, bm.bmHeight);

    CDC dcMem;
    dcMem.CreateCompatibleDC (&dc);
    CBitmap* pOldBitmap = dcMem.SelectObject (&scrollBMP);

    int ClipLeft = m_x < 0 ? m_x : 0;
    
    int ClipRight = m_x > (m_width - SCROLL_BAR_WIDTH)? bm.bmWidth - m_x + (m_width - SCROLL_BAR_WIDTH): bm.bmWidth;
    
    dc.BitBlt (m_x - ClipLeft, m_y, ClipRight, size.y, &dcMem, -1 * ClipLeft, 0, SRCCOPY);
    
    dcMem.SelectObject (pOldBitmap);
}

void CProgressBar::OnSize(UINT nType, int cx, int cy)
{
    CStatic::OnSize(nType, cx, cy);

    m_width = cx;
    m_height = cy;
}
