// BsodSaver.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "BsodSaver.h"
#include "BsodSaverDlg.h"
#include "ConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBsodSaverApp

BEGIN_MESSAGE_MAP(CBsodSaverApp, CWinApp)
    ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CBsodSaverApp construction

CBsodSaverApp::CBsodSaverApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}


// The one and only CBsodSaverApp object

CBsodSaverApp theApp;


// CBsodSaverApp initialization

BOOL CBsodSaverApp::InitInstance()
{
    // InitCommonControlsEx() is required on Windows XP if an application
    // manifest specifies use of ComCtl32.dll version 6 or later to enable
    // visual styles.  Otherwise, any window creation will fail.
    INITCOMMONCONTROLSEX InitCtrls;
    InitCtrls.dwSize = sizeof(InitCtrls);
    // Set this to include all the common control classes you want to use
    // in your application.
    InitCtrls.dwICC = ICC_WIN95_CLASSES;
    InitCommonControlsEx(&InitCtrls);

    CWinApp::InitInstance();

    AfxEnableControlContainer();

    // Standard initialization
    // If you are not using these features and wish to reduce the size
    // of your final executable, you should remove from the following
    // the specific initialization routines you do not need
    // Change the registry key under which our settings are stored
    // TODO: You should modify this string to be something appropriate
    // such as the name of your company or organization
    SetRegistryKey(_T("BSOD_SAVER"));


    //When Windows runs your screensaver, it launches it with one of three command line options:
    //
    ///s – Start the screensaver in full-screen mode. 
    ///c – Show the configuration settings dialog box. 
    ///p #### – Display a preview of the screensaver using the specified window handle.
    //The screensaver sample handles these arguments in the Program.cs source file; however, the /p argument is not implemented.

    CString CmdLine = GetCommandLine();
    //AfxMessageBox (CmdLine);

    CString strOption = CmdLine.Right (CmdLine.GetLength() - CmdLine.ReverseFind('/') - 1);
    
    switch(strOption[0])
    {
    case 'c':
    case 'C':
        {
            CConfigDlg dlg;
            m_pMainWnd = &dlg;
            INT_PTR nResponse = dlg.DoModal();
        }
        break;

    case 'p':
    case 'P':
        {
            //Code to create a new preview window and show the output in that window
        }
        break;

    case 's':
    case 'S':
    default://Launch the application in full screen mode otherwise.
        {
            CBsodSaverDlg dlg;
            m_pMainWnd = &dlg;
            INT_PTR nResponse = dlg.DoModal();
        }
    }
    return FALSE;
}
