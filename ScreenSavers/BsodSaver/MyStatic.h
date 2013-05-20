#pragma once


// CMyStatic

class CMyStatic : public CStatic
{
    DECLARE_DYNAMIC(CMyStatic)

public:
    CMyStatic();
    virtual ~CMyStatic();

    void SetForeGroundColor(COLORREF clr);
    void SetBackGroundColor(COLORREF clr);

protected:
    DECLARE_MESSAGE_MAP()

private:
    CBrush      m_BkgrndBrush;
    COLORREF    m_BkColor; 
    COLORREF    m_FgColor;
	
	HCURSOR		m_hCursor;

public:
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    void SetNewFont (int size, CString FontName);

	BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	void SetHandCursor ();
};


