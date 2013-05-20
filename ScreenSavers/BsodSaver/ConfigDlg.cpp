// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BsodSaver.h"
#include "ConfigDlg.h"


// CConfigDlg dialog

IMPLEMENT_DYNAMIC(CConfigDlg, CDialog)

CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
{

}

CConfigDlg::~CConfigDlg()
{
}

void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_ErrorMsgSlider);
	DDX_Control(pDX, IDC_SLIDER2, m_WindowStartSlider);
	DDX_Control(pDX, IDC_SLIDER3, m_PostStartSlider);
	DDX_Control(pDX, IDC_STATIC1, m_NishantBugalia);
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CConfigDlg::OnBnClickedOk)
	ON_STN_CLICKED(IDC_STATIC1, &CConfigDlg::OnStnClickedStatic1)
END_MESSAGE_MAP()

BOOL CConfigDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

	m_ErrorMsgSlider.SetRange(0,100);
	m_WindowStartSlider.SetRange(0,100);
	m_PostStartSlider.SetRange(0,100);

	m_ErrorMsgSlider.SetPos(AfxGetApp()->GetProfileInt(_T("Settings"), _T("ErrorMsgDuration"), 5));
	m_WindowStartSlider.SetPos(AfxGetApp()->GetProfileInt(_T("Settings"), _T("WindowStartDuration"), 5));
	m_PostStartSlider.SetPos(AfxGetApp()->GetProfileInt(_T("Settings"), _T("PostStartDuration"), 2));

	//m_NishantBugalia.SetBackGroundColor(
	m_NishantBugalia.SetForeGroundColor(COLORREF(0xFF0000));
	m_NishantBugalia.SetHandCursor();


	return TRUE;
}
// CConfigDlg message handlers

void CConfigDlg::OnBnClickedOk()
{
	AfxGetApp()->WriteProfileInt(_T("Settings"), _T("ErrorMsgDuration"), m_ErrorMsgSlider.GetPos());
    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("WindowStartDuration"), m_WindowStartSlider.GetPos());
    AfxGetApp()->WriteProfileInt(_T("Settings"), _T("PostStartDuration"), m_PostStartSlider.GetPos());
	OnOK();
}

void CConfigDlg::OnStnClickedStatic1()
{
	::ShellExecute(NULL, _T("open"), _T("http://niscience.blogspot.com"), NULL, NULL, SW_SHOWNORMAL);
}
