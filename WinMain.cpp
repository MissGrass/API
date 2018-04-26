/* Visual studio 2017 �汾������ */ 

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <stdexcept>

using namespace std;

//�ص�����ԭ������,���س����εĽ����,CALLBACK�Ǳ�ʾstdcall����
LRESULT CALLBACK WinProc(
	HWND hwnd,      // handle to window
	UINT uMsg,      // message identifier
	WPARAM wParam,  // first message parameter
	LPARAM lParam   // second message parameter
);

// WinMain����,������ڵ㺯��
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	//���һ��������,�ô��ڽṹ��
	WNDCLASS wnd;
	wnd.cbClsExtra = 0;//��Ķ����ڴ�
	wnd.cbWndExtra = 0;//���ڵĶ����ڴ�
	wnd.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);//��������ɫ��ˢ��ǿ��ת����
	wnd.hCursor = LoadCursor(NULL, IDC_APPSTARTING);//��꣬��׼��ͷ��Сɳ©
	wnd.hIcon = LoadIcon(NULL, IDI_APPLICATION);//ͼ��,��׼Ӧ�ó���ͼ��
	wnd.hInstance = hInstance;//ʵ�������ֵΪ��������ϵͳ����ľ��ֵ
	wnd.lpfnWndProc = WinProc;//��Ϣ��Ӧ����
	wnd.lpszClassName = _T("huoche");//�����������,��ע��ʱ��ʹ�õ�
	wnd.lpszMenuName = NULL;//Ĭ��ΪNULLû�б�����
	wnd.style = CS_HREDRAW | CS_VREDRAW;//����Ϊˮƽ�ʹ�ֱ�ػ�

	RegisterClass(&wnd);//ע��һ��������

	//����һ������
	HWND hwnd;//���洴�����ں�����ɴ��ھ��������ʾ
			  //����Ƕ��ĵ�����,�����һ������lParam����ָ��һ��CLIENTCREATESTRUCT�ṹ��
	hwnd = CreateWindow(_T("huoche"), _T("�𳵶�Ʊϵͳ"), WS_OVERLAPPEDWINDOW, 0, 0, 600, 400, NULL, NULL, hInstance, NULL);//ָ��������һ������Ӱ�ı߽�

	ShowWindow(hwnd, SW_SHOWDEFAULT);//��ʾ����
	UpdateWindow(hwnd);//����һ������


	MSG msg;//��Ϣ�ṹ��
			//�����Ϣ����,����ֵ��-1,��GetMessage����Ϣ������ȡ����WM_QUIT��Ϣʱ,����ֵ��0
			//Ҳ����ʹ��PeekMessage��������Ϣ������ȡ����Ϣ

	BOOL bSet;
	while ((bSet = GetMessage(&msg, NULL, 0, 0)) != 0) {
		if (-1 == bSet) {
			return -1;
		}
		else {
			TranslateMessage(&msg);//ת��
			DispatchMessage(&msg);
		}
	}
	return 0;
}


//��Ϣѭ���жԲ�ͬ����Ϣ������в�ͬ����Ӧ
LRESULT CALLBACK WinProc(
	HWND hwnd,      // handle to window
	UINT uMsg,      // message identifier
	WPARAM wParam,  // first message parameter
	LPARAM lParam   // second message parameter
) {
	switch (uMsg) {
	case WM_CHAR://�ַ���Ϣ
		char szChar[20];
		sprintf_s(szChar, "char is %d;", wParam);//��ʽ������,stdio.h
		MessageBoxA(hwnd, szChar, "abc", 0);//�������windows.h��
		break;
	case WM_LBUTTONDOWN://��������Ϣ
		MessageBox(hwnd, _T("mouse clicked"), _T("���"), 0);
		HDC hdc;
		hdc = GetDC(hwnd);//��ȡ�豸�����ľ��,�����������
						  //��x=0,y=50(����)�ĵط��������
		TextOut(hdc, 0, 50, _T("��ӭ����𳵶�Ʊϵͳ"), 10);
		ReleaseDC(hwnd, hdc);//��ʹ����DC��һ��Ҫע���ͷ�
		break;
	case WM_PAINT://�����ػ�
		HDC hDc;
		PAINTSTRUCT ps;

		hDc = BeginPaint(hwnd, &ps);
		TextOut(hDc, 0, 0, _T("�𳵶�Ʊ"),4);
		EndPaint(hwnd, &ps);
		break;
	case WM_CLOSE://�ر���Ϣ
		if (IDYES == MessageBox(hwnd, _T("�Ƿ���Ľ�����"), _T("��Ʊ1"), MB_YESNO)) {
			DestroyWindow(hwnd);//���ٴ���
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);//����Ӧ��Ϣ��,Ͷ��һ���˳�����Ϣʹ�ó���ȫ�˳�
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);//����ȱʡ����Ϣ������̺���
	}
	return 0;
}

