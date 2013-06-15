#include <StdAfx.h>
#include "ini.h"


#define UNMATCH_STRING      "<INI_DEFAULT_UNMATCH_STRING>"
#define EMPTY_STRING        ""


CIni::CIni(const char *pchFileName)
{
    ZeroBuffer();
    if (NULL != pchFileName)
    {
        strncpy(m_achFile, pchFileName, FILE_NAME_LEHGTH_MAX);
    }
}

BOOL CIni::CheckExist(const char *pchIndex, const char *pchItem)
{
    ZeroBuffer();
    GetPrivateProfileString(pchIndex, pchItem, UNMATCH_STRING,
        m_achBuffer, BUFFER_LENGTH, m_achFile);
    return CheckBufferValid();
}

int CIni::ReadInt(const char *pchIndex, const char *pchItem)
{
    return GetPrivateProfileInt(pchIndex, pchItem, 0, m_achFile);
}

char* CIni::ReadText(const char *pchIndex, const char *pchItem)
{
    if (CheckExist(pchIndex, pchItem))
    {
        return m_achBuffer;
    }
    else
    {
        return EMPTY_STRING;
    }
}

BOOL CIni::Write(const char *pchIndex, const char *pchItem,
                 const int iValue)
{
    itoa(iValue, m_achBuffer, 10);
    return WritePrivateProfileString(pchIndex, pchItem,
        m_achBuffer, m_achFile);
}

BOOL CIni::Write(const char *pchIndex, const char *pchItem,
                 const char *pchString)
{
    return WritePrivateProfileString(pchIndex, pchItem,
        pchString, m_achFile);
}

void CIni::ZeroBuffer()
{
    memset(m_achBuffer, 0x0, BUFFER_LENGTH);
}

BOOL CIni::CheckBufferValid()
{
    return (0 != strncmp(m_achBuffer, UNMATCH_STRING, BUFFER_LENGTH));
}
