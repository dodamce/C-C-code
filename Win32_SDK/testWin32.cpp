#include<Windows.h>

//uMeg消息编号,返回函数指针
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMeg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, uMeg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPereInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//设计窗口类
	WNDCLASS Box = { 0 };
	Box.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	Box.lpfnWndProc = WindowsProc;
	Box.cbClsExtra = 0;//不需要额外字节
	Box.hInstance = hInstance;
	Box.hIcon = NULL;
	Box.hCursor = NULL;
	Box.hbrBackground = CreateSolidBrush(RGB(255, 255, 0));//黄色背景
	Box.lpszMenuName = NULL;//无菜单
	Box.lpszClassName = L"dodamce";

	//注册窗口类
	if (RegisterClass(&Box) == 0)
	{
		MessageBox(NULL, L"此程序不能运行在Windows NT上",L"提示",MB_OK|MB_ICONWARNING);
		return -1;
	}
	
	//创建窗口
	HWND hwnd=CreateWindow(L"dodamce", L"20050441", WS_SYSMENU|WS_BORDER | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
		300, 200, 800, 600,NULL,NULL,hInstance,NULL);//返回窗口句柄
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"窗口创建失败", L"提示", MB_OK);
		return -2;
	}

	//显示窗口
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	//消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))//所有消息都处理
	{
		//将虚拟键消息转化为字符消息
		TranslateMessage(&msg);
		//分发消息
		DispatchMessage(&msg);
	}
	return 0;
}