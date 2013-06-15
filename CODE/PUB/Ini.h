#ifndef _INI_H
#define _INI_H


#define FILE_NAME_LEHGTH_MAX    (256)
#define BUFFER_LENGTH           (32 * 1024)


class CIni
{
public:
    CIni(const char *pchFileName);
    BOOL    CheckExist(const char *pchIndex, const char *pchItem);
    int     ReadInt(const char *pchIndex, const char *pchItem);
    char*   ReadText(const char *pchIndex, const char *pchItem);
    BOOL    Write(const char *pchIndex, const char *pchItem,  const int iValue);
    BOOL    Write(const char *pchIndex, const char *pchItem, const char *pchString);
private:
    char    m_achFile[FILE_NAME_LEHGTH_MAX];
    char    m_achBuffer[BUFFER_LENGTH];
    void    ZeroBuffer();
    BOOL    CheckBufferValid();
};


#endif