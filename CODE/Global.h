#ifndef _GLOBAL_H
#define _GLOBAL_H


class CRelaxReminderApp;


// 程序实例
extern CRelaxReminderApp theApp;

// 只运行一个程序实例的全局变量
extern char     g_szPropName[40];   //自己定义一个属性名
extern HANDLE   g_hValue;           //自己定义一个属性值

#endif