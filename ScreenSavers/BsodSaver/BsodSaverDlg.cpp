// BsodSaverDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BsodSaver.h"
#include "BsodSaverDlg.h"
#include "changeRes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CLR_DARK_BLUE 0x800000
#define CLR_LIGHT_BLUE 0XF0CAA6
#define CLR_BLACK 0X000000
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
    CAboutDlg();

// Dialog Data
    enum { IDD = IDD_ABOUTBOX };

    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
    DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CBsodSaverDlg dialog




CBsodSaverDlg::CBsodSaverDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CBsodSaverDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

    m_BkColor = COLORREF (0x800000);
    m_BkgrndBrush.CreateSolidBrush (m_BkColor);
    
    m_TimerCount = -1;

    m_ErrorMsgDuration      = AfxGetApp()->GetProfileInt(_T("Settings"), _T("ErrorMsgDuration"), 5);
    m_WindowStartDuration   = AfxGetApp()->GetProfileInt(_T("Settings"), _T("WindowStartDuration"), 5);
    m_PostStartDuration     = AfxGetApp()->GetProfileInt(_T("Settings"), _T("PostStartDuration"), 2);


    m_ErrorMessage = _T("A problem has been detected and windows has been shut down to prevent damage to your computer.\n\
The problem seems to be caused by the following file: SPCMDCON.SYS\n\
\n\
PAGE_FAULT_IN_NONPAGED_AREA\n\
\n\
If this is the first time you've seen this Stop error screen,\
restart your computer. If this screen appears again, follow \
these steps:\n\
\n\
Check to make sure any new hardware or software is properly installed.\n\
If this is a new installation, ask your hardware or software manufacturer \
for any Windows updates you might need.\n\
\n\
If problems continue, disable or remove any newly installed hardware \
or software. Disable BIOS memory options such as caching or shadowing.\n\
If you need to use Safe Mode to remove or disable components, restart \
your computer, press F8 to select Advanced Startup Options, and then \
select Safe Mode.\n\
\n\
Technical information:\n\
\n\
*** STOP: 0x00000050 (0xFD3094C2, 0x00000001, 0xFBEE7617, 0X00000000)\n\
\n\
\n\
***  SPCMDCON.SYS - Address FBFE7617 base at FBFE5000, DateStamp 3d6dd67c");

}

void CBsodSaverDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_BLUE_TEXT, m_BlueText);
    DDX_Control(pDX, IDC_IMAGE_BOX, m_WindowsLogo);
    DDX_Control(pDX, IDC_SCROLLBAR_BOX, m_ScrollbarBox);
}

BEGIN_MESSAGE_MAP(CBsodSaverDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_WM_CTLCOLOR_REFLECT()
    ON_WM_TIMER()
END_MESSAGE_MAP()


// CBsodSaverDlg message handlers

BOOL CBsodSaverDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // IDM_ABOUTBOX must be in the system command range.
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }



    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);            // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon

    ShowCursor (FALSE);             //Hide Mouse Cursor.

    RepositionControls ();
    m_ScrollbarBox.StartTimer ();
    
    m_TimerCount = -1;
    SetTimer (1, 1000, NULL);
    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBsodSaverDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
    if ((nID & 0xFFF0) == IDM_ABOUTBOX)
    {
        CAboutDlg dlgAbout;
        dlgAbout.DoModal();
    }
    else
    {
        CDialog::OnSysCommand(nID, lParam);
    }
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBsodSaverDlg::OnPaint()
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
        CDialog::OnPaint();
    }
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CBsodSaverDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}


void CBsodSaverDlg::RepositionControls()
{
    //Get Old resolution and save it in m_OldResolution
    int nHorizRes = ::GetDeviceCaps (GetDesktopWindow ()->GetDC ()->m_hDC, HORZRES);
    int nVertRes = ::GetDeviceCaps (GetDesktopWindow ()->GetDC ()->m_hDC, VERTRES);
    m_OldResolution = CPoint (nHorizRes, nVertRes);
    
    //Change current resolution to 640 X 480
    CChangeRes::setResolution (640, 480);
    
    CRect rect640x480 (0, 0, 640, 480);

    
    TCHAR szPath[MAX_PATH];

    if( !GetModuleFileName( NULL, szPath, MAX_PATH ) )
    {
        TRACE(_T("Cannot install service (%d)\n"), GetLastError());
        return;
    }
    
    CString ErrorMsgFileName = szPath;
    int nFileNamePos = ErrorMsgFileName.ReverseFind('\\');
    ErrorMsgFileName = ErrorMsgFileName.Left(nFileNamePos);
    ErrorMsgFileName += _T("\\ErrorMessage.txt");

    CFile file;
    if (file.Open (ErrorMsgFileName, CFile::modeRead))
    {
        ULONG FileSize = file.GetLength ();
        TCHAR *pChar = new TCHAR[FileSize + 1];
        memset (pChar, 0, (FileSize + 1) * sizeof(TCHAR));

        file.Read (pChar, FileSize);
        file.Close  ();
        
        m_ErrorMessage = CString (pChar).Left(FileSize);
        delete [] pChar;
    }


    m_BlueText.SetNewFont (100, _T("Lucida Console"));
    m_BlueText.SetBackGroundColor (CLR_DARK_BLUE );
    m_BlueText.SetForeGroundColor (0xFFFFFF);
    m_BlueText.SetWindowText (m_ErrorMessage);

    this->MoveWindow (rect640x480);//Resize Parent Dialog Box

    //m_WindowsLogo.ShowWindow (SW_SHOW);
    m_WindowsLogo.MoveWindow (rect640x480);
    m_ScrollbarBox.MoveWindow (258, 354, 120, 9);
    
    rect640x480.left += 10;
    rect640x480.top += 10;
    m_BlueText.MoveWindow (rect640x480);
}

void CBsodSaverDlg::PostNcDestroy()
{
    CChangeRes::setResolution (m_OldResolution.x, m_OldResolution.y);
    CDialog::PostNcDestroy();
}


HBRUSH CBsodSaverDlg::CtlColor(CDC* pDC, UINT nCtlColor) 
{
    HBRUSH hbr = (HBRUSH)m_BkgrndBrush; 
    pDC->SetBkColor(m_BkColor);
   
    return hbr;
}



void CBsodSaverDlg::OnTimer(UINT_PTR nIDEvent)
{
    m_TimerCount++;

    if (m_TimerCount == 0)
    {
        ShowErrorMessage();
    }
    else if (m_TimerCount ==  m_ErrorMsgDuration)
    {
        ShowStartupScreen();
    }
    else if (m_TimerCount == (m_ErrorMsgDuration + m_WindowStartDuration))
    {
        HideAll();
    }
    else if (m_TimerCount == (m_ErrorMsgDuration + m_WindowStartDuration + m_PostStartDuration))
    {
        m_TimerCount = -1;
    }
    
    CDialog::OnTimer(nIDEvent);
}


void CBsodSaverDlg::ShowErrorMessage()
{
    //Set the dialog color to blue.
    m_BkgrndBrush.DeleteObject();
    m_BkgrndBrush.CreateSolidBrush(CLR_DARK_BLUE);
    Invalidate();

    ShowCursor (FALSE);

    m_WindowsLogo.ShowWindow (SW_HIDE);
    m_ScrollbarBox.ShowWindow (SW_HIDE);

    m_BlueText.ShowWindow (SW_SHOW);
}


void CBsodSaverDlg::ShowStartupScreen()
{
    //Set the dialog color to black.
    m_BkgrndBrush.DeleteObject();
    m_BkgrndBrush.CreateSolidBrush (CLR_BLACK);
    Invalidate();
    
    ShowCursor (FALSE);

    m_WindowsLogo.ShowWindow (SW_SHOW);
    m_ScrollbarBox.ShowWindow (SW_SHOW);

    m_BlueText.ShowWindow (SW_HIDE);
}

void CBsodSaverDlg::HideAll()
{
    //Set the dialog color to light blue.
    m_BkgrndBrush.DeleteObject();
    m_BkgrndBrush.CreateSolidBrush (CLR_LIGHT_BLUE);
    Invalidate();

    while (ShowCursor (TRUE) < 0);

    SetCursorPos(320, 240);

    m_WindowsLogo.ShowWindow (SW_HIDE);
    m_ScrollbarBox.ShowWindow (SW_HIDE);

    m_BlueText.ShowWindow (SW_HIDE);
}
