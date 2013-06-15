// RelaxReminder.h : main header file for the RELAXREMINDER application
//

#if !defined(AFX_RELAXREMINDER_H__8E1FBEE0_8DD6_4129_AD63_4ED9A8167E02__INCLUDED_)
#define AFX_RELAXREMINDER_H__8E1FBEE0_8DD6_4129_AD63_4ED9A8167E02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"        // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRelaxReminderApp:
// See RelaxReminder.cpp for the implementation of this class
//

class CRelaxReminderApp : public CWinApp
{
public:
    CRelaxReminderApp();

// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CRelaxReminderApp)
    public:
    virtual BOOL InitInstance();
    //}}AFX_VIRTUAL

// Implementation

    //{{AFX_MSG(CRelaxReminderApp)
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RELAXREMINDER_H__8E1FBEE0_8DD6_4129_AD63_4ED9A8167E02__INCLUDED_)
