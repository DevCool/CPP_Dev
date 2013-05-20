#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "MyStatic.h"

// CConfigDlg dialog

class CConfigDlg : public CDialog
{
	DECLARE_DYNAMIC(CConfigDlg)

public:
	CConfigDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConfigDlg();

// Dialog Data
	enum { IDD = IDD_CONF_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CSliderCtrl m_ErrorMsgSlider;
	CSliderCtrl m_WindowStartSlider;
	CSliderCtrl m_PostStartSlider;
	afx_msg void OnStnClickedStatic1();

	CMyStatic m_NishantBugalia;
};
