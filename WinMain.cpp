/* Visual studio 2017 版本下运行 */ 

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdexcept>

using namespace std;

//回调函数原型声明,返回长整形的结果码,CALLBACK是表示stdcall调用
LRESULT CALLBACK WinProc(
	HWND hwnd,      // handle to window
	UINT uMsg,      // message identifier
	WPARAM wParam,  // first message parameter
	LPARAM lParam   // second message parameter
);

// WinMain函数,程序入口点函数
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	//设计一个窗口类,用窗口结构体
	WNDCLASS wnd;
	wnd.cbClsExtra = 0;//类的额外内存
	wnd.cbWndExtra = 0;//窗口的额外内存
	wnd.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);//背景，黑色画刷（强制转换）
	wnd.hCursor = LoadCursor(NULL, IDC_APPSTARTING);//光标，标准箭头和小沙漏
	wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);//图标,标准应用程序图标
	wnd.hInstance = hInstance;//实例句柄赋值为程序启动系统分配的句柄值
	wnd.lpfnWndProc = WinProc;//消息响应函数
	wnd.lpszClassName = _T("huoche");//窗口类的名子,在注册时会使用到
	wnd.lpszMenuName = NULL;//默认为NULL没有标题栏
	wnd.style = CS_HREDRAW | CS_VREDRAW;//定义为水平和垂直重画

	RegisterClass(&wnd);//注册一个窗口类

	//创建一个窗口
	HWND hwnd;//保存创建窗口后的生成窗口句柄用于显示
			  //如果是多文档程序,则最后一个参数lParam必须指向一个CLIENTCREATESTRUCT结构体
	hwnd = CreateWindow(_T("huoche"), _T("火车订票系统"), WS_OVERLAPPEDWINDOW, 0, 0, 600, 400, NULL, NULL, hInstance, NULL);//指定窗口有一个带阴影的边界

	ShowWindow(hwnd, SW_SHOWDEFAULT);//显示窗口
	UpdateWindow(hwnd);//更新一个窗口


	MSG msg;//消息结构体
			//如果消息出错,返回值是-1,当GetMessage从消息队列中取到是WM_QUIT消息时,返回值是0
			//也可以使用PeekMessage函数从消息队列中取出消息

	BOOL bSet;
	while ((bSet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (-1 == bSet) {
			return -1;
		}
		else {
			TranslateMessage(&msg);//转换
			DispatchMessage(&msg);
		}
	}
	return 0;
}


//消息循环中对不同的消息各类进行不同的响应
LRESULT CALLBACK WinProc(
	HWND hwnd,      // handle to window
	UINT uMsg,      // message identifier
	WPARAM wParam,  // first message parameter
	LPARAM lParam   // second message parameter
) {
	switch (uMsg) {
	case WM_CHAR://字符消息
		char szChar[20];
		sprintf_s(szChar, "char is %d;", wParam);//格式化操作,stdio.h
		MessageBoxA(hwnd, szChar, "abc", 0);//输出操作windows.h中
		break;
	case WM_LBUTTONDOWN://鼠标左键消息
		MessageBox(hwnd, _T("mouse clicked"), _T("点击"), 0);
		HDC hdc;
		hdc = GetDC(hwnd);//获取设备上下文句柄,用来输出文字
						  //在x=0,y=50(像素)的地方输出文字
		TextOut(hdc, 0, 50, _T("欢迎进入火车订票系统"), 10);
		ReleaseDC(hwnd, hdc);//在使用完DC后一定要注意释放
		break;
	case WM_PAINT://窗口重绘
		HDC hDc;
		PAINTSTRUCT ps;

		hDc = BeginPaint(hwnd, &ps);
		TextOut(hDc, 0, 0, _T("火车订票"),4);
		EndPaint(hwnd, &ps);
		break;
	case WM_CLOSE://关闭消息
		if (IDYES == MessageBox(hwnd, _T("是否真的结束？"), _T("订票1"), MB_YESNO)) {
			DestroyWindow(hwnd);//销毁窗口
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);//在响应消息后,投递一个退出的消息使用程序安全退出
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//调用缺省的消息处理过程函数
	}
	return 0;
}

