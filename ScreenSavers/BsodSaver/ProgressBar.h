#pragma once


// CProgressBar

class CProgressBar : public CStatic
{
    DECLARE_DYNAMIC(CProgressBar)

public:
    CProgressBar();
    virtual ~CProgressBar();

protected:
    DECLARE_MESSAGE_MAP()
    
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
    
            void StartTimer ();


private:
    int m_x;
    int m_y;
    
    int m_width;
    int m_height;    
};


