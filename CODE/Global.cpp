#include "StdAfx.h"
#include "Global.h"

// 只运行一个程序实例的全局变量
char g_szPropName[40] = "RelaxReminder.RunOneInstance"; //自己定义一个属性名
HANDLE  g_hValue = (HANDLE)1;                           //自己定义一个属性值
