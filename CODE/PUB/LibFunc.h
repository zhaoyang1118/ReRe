#ifndef _LIB_FUNC_H
#define _LIB_FUNC_H


// 只允许运行一个实例
BOOL CALLBACK   EnumWndProc(HWND hwnd,LPARAM lParam);

// 将秒数转化为时间的显示格式(12:34:56)
typedef enum {
    TWINKLING_COLON = 0,
    FIXED_COLON,
} TimeFormat;

BOOL            Seconds2Time(UINT nSeconds, char *pchTime, TimeFormat eFormat);

// 判断一个字符串是否全是数字
BOOL            IsNumber(CString str);

// 计算两点之间的距离(街区距离)
UINT            MakeDistance(POINTS a, POINTS b);

// 锁定鼠标键盘
void            LockKeyboard(BOOL bValue);
void            LockMouse(BOOL bValue);
void            LockKeyBoardAndMouse(BOOL bValue);

// 查询程序开机启动
BOOL GetAppAutoStartWithSystem(void);
// 设置程序开机启动
BOOL SetAppAutoStartWithSystem(BOOL bSetStart, const char *pchAppPath);

// 全屏模式检测
BOOL FullscreenModeDectect(void);

#endif