// DialogAboutAbout.cpp : implementation file
//

#include "stdafx.h"
#include "RelaxReminder.h"
#include "PubFunc.h"
#include "Version.h"
#include "StringTable.h"
#include "RelaxTimer.h"
#include "DialogTrayWindow.h"
#include "DialogDarkerScreen.h"
#include "RelaxReminderDlg.h"
#include "DialogAboutAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define HTTP_WEBSITE        "http://rere.appinn.me"
#define EMAIL_ADDRESS       "zhaoyang1118@gmail.com"


/////////////////////////////////////////////////////////////////////////////
// CDialogAboutAbout dialog


CDialogAboutAbout::CDialogAboutAbout(CWnd* pParent /*=NULL*/)
    : CDialog(CDialogAboutAbout::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDialogAboutAbout)
        // NOTE: the ClassWizard will add member initialization here
    //}}AFX_DATA_INIT
}


void CDialogAboutAbout::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CDialogAboutAbout)
        // NOTE: the ClassWizard will add DDX and DDV calls here
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialogAboutAbout, CDialog)
    //{{AFX_MSG_MAP(CDialogAboutAbout)
    ON_WM_CTLCOLOR()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialogAboutAbout message handlers

BOOL CDialogAboutAbout::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    CString strVersion, strCopyRight;
    CString strAppFile = m_pdlgMain->m_strAppFile;
    CStringTable *pst = &(m_pdlgMain->m_str);

    // 设置dedicate文字
    GetDlgItem(IDC_STATIC_DEDICATED)->SetWindowText("Honey Sophie(张江曼)\n");

    // 设置程序文件路径
    GetDlgItem(IDC_EDIT_IMAGE_PATH)->SetWindowText(strAppFile);

    // 设置文件版本号和build号
    strVersion = pst->GetStr(ABOUT_ABOUT_APPINFO_VERSION);
    strVersion += " ";
    strVersion += GetFileVersion(strAppFile);
    strVersion += " (";
    strVersion += GetFileVerInfoItem(strAppFile, "PrivateBuild");
    strVersion += ")";
    GetDlgItem(IDC_STATIC_VERSION)->SetWindowText(strVersion);

    // 设置CopyRight信息
    strCopyRight = GetFileVerInfoItem(strAppFile, "LegalCopyright");
    GetDlgItem(IDC_STATIC_COPYRIGHT)->SetWindowText(strCopyRight);

    // 获取超链接区域
    GetDlgItem(IDC_STATIC_AUTHOR_HOMEPAGE)->GetWindowRect(&m_rectHttp);
    ScreenToClient(&m_rectHttp);
    GetDlgItem(IDC_STATIC_AUTHOR_EMAIL)->GetWindowRect(&m_rectEmail);
    ScreenToClient(&m_rectEmail);

    // 设置超链接字体
    m_fontLink.CreateFont(13,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,  
        ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,  
        DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Tahoma");
    m_fontLinkMouseOn.CreateFont(13,0,0,0,FW_NORMAL,FALSE,TRUE,FALSE,  
        ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,  
        DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,"Tahoma");
    GetDlgItem(IDC_STATIC_AUTHOR_HOMEPAGE)->SetFont(&m_fontLink);

    // 设置超链接显示内容
    SetDlgItemText(IDC_STATIC_AUTHOR_HOMEPAGE, HTTP_WEBSITE);
    SetDlgItemText(IDC_STATIC_AUTHOR_EMAIL, EMAIL_ADDRESS);

    LoadLanguageStrings();

    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

HBRUSH CDialogAboutAbout::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
    HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
    
    // TODO: Change any attributes of the DC here
    if (pWnd->GetDlgCtrlID() == IDC_STATIC_AUTHOR_HOMEPAGE ||
        pWnd->GetDlgCtrlID() == IDC_STATIC_AUTHOR_EMAIL) 
    {
        pDC->SetTextColor(RGB(0, 0, 255));
        pDC->SetBkMode(TRANSPARENT);
    }
    // TODO: Return a different brush if the default is not desired
    return hbr;
}

void CDialogAboutAbout::OnMouseMove(UINT nFlags, CPoint point) 
{
    // TODO: Add your message handler code here and/or call default
    static BOOL sbMouseOnLink = FALSE;
    BOOL        bMouseOnHttpLink = m_rectHttp.PtInRect(point);
    BOOL        bMouseOnEmailLink = m_rectEmail.PtInRect(point);

    if (bMouseOnHttpLink || bMouseOnEmailLink)
    {// 如果鼠标落在HTTP_LINK上
        SetCursor(AfxGetApp()->LoadOEMCursor(OCR_HAND));
        if (sbMouseOnLink == FALSE) 
        {
            CWnd *pwndUnderline = GetDlgItem((bMouseOnHttpLink & !bMouseOnEmailLink) ?
                                             IDC_STATIC_AUTHOR_HOMEPAGE :
                                             IDC_STATIC_AUTHOR_EMAIL);
            pwndUnderline->SetFont(&m_fontLinkMouseOn);
            sbMouseOnLink = TRUE;
        }
    }
    else
    {// 如果鼠标落在HTTP_LINK外
        if (sbMouseOnLink == TRUE) 
        {
            GetDlgItem(IDC_STATIC_AUTHOR_HOMEPAGE)->SetFont(&m_fontLink);
            GetDlgItem(IDC_STATIC_AUTHOR_EMAIL)->SetFont(&m_fontLink);
            sbMouseOnLink = FALSE;
        }
    }
    CDialog::OnMouseMove(nFlags, point);
}

void CDialogAboutAbout::OnLButtonDown(UINT nFlags, CPoint point) 
{
    // TODO: Add your message handler code here and/or call default
    CString strMailto, strHttpLink;
    strHttpLink = HTTP_WEBSITE;
    strMailto = "mailto:";
    strMailto += EMAIL_ADDRESS;

    if (m_rectHttp.PtInRect(point))
    {
        if (nFlags == MK_LBUTTON) 
        {
             ShellExecute(NULL, NULL, strHttpLink, NULL, NULL, SW_NORMAL); 
        }
    }

    if (m_rectEmail.PtInRect(point))
    {
        if (nFlags == MK_LBUTTON) 
        {
            ShellExecute(NULL, NULL, strMailto, NULL, NULL, SW_NORMAL); 
        }
    }
    
    CDialog::OnLButtonDown(nFlags, point);
}

void CDialogAboutAbout::LoadLanguageStrings()
{
    CStringTable *pst;
    
    pst = &(m_pdlgMain->m_str);
    SetDlgItemText(IDC_STATIC_DEDICATE, pst->GetStr(ABOUT_ABOUT_DEDICATE));
    SetDlgItemText(IDC_STATIC_APPINFO, pst->GetStr(ABOUT_ABOUT_APPINFO));
    SetDlgItemText(IDC_STATIC_APPINFO_APPNAME, pst->GetStr(ABOUT_ABOUT_APPINFO_APPNAME));
    // ABOUT_ABOUT_APPINFO_VERSION 在程序中设置
    Invalidate(TRUE);
}
