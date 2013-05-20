// BsodSaverDlg.h : header file
//

#pragma once
#include "MyStatic.h"
#include "ProgressBar.h"


// CBsodSaverDlg dialog
class CBsodSaverDlg : public CDialog
{
// Construction
public:
    CBsodSaverDlg(CWnd* pParent = NULL);    // standard constructor

// Dialog Data
    enum { IDD = IDD_BSODSAVER_DIALOG };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


// Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()

public:
    afx_msg void RepositionControls();
    HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    afx_msg void OnTimer(UINT_PTR nIDEvent);

    void ShowErrorMessage();
    void ShowStartupScreen();
    void HideAll();

protected:
    virtual void PostNcDestroy();
    
private:
    CMyStatic    m_BlueText;            //Static box to display Error Message.
    CBrush       m_BkgrndBrush;         //Solid Brush to change the dialog color to m_BkColor.
    COLORREF     m_BkColor;             //Dialog background color.
    CStatic      m_WindowsLogo;         //Static Box (Image Type) to show the Windows Logo.
    CProgressBar m_ScrollbarBox;        //Windows XP startup progressbar.
    CPoint       m_OldResolution;       //Initial desktop resolution.
    
    int          m_TimerCount;          //Keeps a count for error/startup & light blue desktop
    CString      m_ErrorMessage;        //Default Error Message.

    UINT         m_ErrorMsgDuration;    //Time taken to show the error message (in seconds).
    UINT         m_WindowStartDuration; //Time taken to show Windows Startup Logo(in seconds).
    UINT         m_PostStartDuration;   //Time taken to show the Initial desktop (light blue) (in seconds).
};
