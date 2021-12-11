#include<Windows.h>
#include<time.h>

#define TIME_ID  5  //时间定时器

#define DOD_UMTEST (WM_USER+1)   //1024之前都是系统定义的，自己定义要在1024之后即WM_USER之后

/*
	消息分类：
	1.进队列消息：会从消息队列中取出消息，大部分用户输入的消息都是进队消息
	2.不进队列消息：不会从消息队列取消息，eg:WM_CREATE  WM_PAINT
*/

/*类型
UINT 无符号整形
WPAPAM  无符号整形
LPARAM 长整型
LONG long
TCHAR 宽字符
LPCTSTR const w_char_t*
ATOM 字 unsigned short
DWORD 双字 unsigned long
*/

/* 
	SetMessage:执行完函数后返回，阻塞式等待返回,返回一个消息的处理结果
	PostMessage:只负责将消息投递出去，成功返回1失败0，不关心消息处理结果
	如果跨进程最好用PostMessage
*/

/*
	用户自定义消息

*/

//uMeg消息编号,返回函数指针
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMeg, WPARAM wParam, LPARAM lParam)
{
	switch (uMeg)
	{
		case DOD_UMTEST://用户自定义消息，取消定时器
		{
			KillTimer(hWnd, TIME_ID);

			//设置标题
			SetWindowText(hWnd, L"dodamce");
		}
		case WM_CREATE://创建窗口消息
		{
			CREATESTRUCT* ipcs = (CREATESTRUCT*)lParam;//CREATESTRUCT结构体，保存的是注册窗口的信息
			MessageBox(hWnd, L"WM_CREAT消息", L"提示", MB_OK);
			SetTimer(hWnd, TIME_ID, 1000, NULL);//NULL表示1000毫秒系统处理一次时间消息
			break;
		}
		case WM_CLOSE://关闭窗口消息
		{
			int result = MessageBox(hWnd, L"确定退出?", L"提示", MB_YESNO);
			if (result == IDYES)
			{
				break;
			}
			else//否则最小化
			{
				ShowWindow(hWnd, SW_MINIMIZE);
				return 1;//不用系统默认处理,return1表示已经处理过了。
			}
		}
		case WM_DESTROY://窗口销毁消息，窗口退出时收到，主要做清理窗口数据的工作，窗口已经被销毁，无法在执行窗口操作
			PostQuitMessage(0);//发送进程退出消息，退出进程。
			break;
		case WM_LBUTTONDOWN://鼠标左键按下消息
		{
			//获取鼠标坐标
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			TCHAR chInfo[256] = { 0 };
			wsprintf(chInfo, L"鼠标左键按下，x=%d y=%d", x, y);//将宽字符写到缓冲区中

			if (wParam & MK_CONTROL)//如果为真说明按下Ctrl键
			{
				wcscat(chInfo, L"按下ctrl键");//宽字符连接
			}
			if (wParam & MK_MBUTTON)
			{
				wcscat(chInfo, L"按下中键");//宽字符连接
			}
			//....

			//设置窗口标题
			SetWindowText(hWnd, chInfo);
			break;
		}
		case WM_LBUTTONUP:
		{
			//获取鼠标坐标
			int x = LOWORD(lParam);//获取lparam低16位数字
			int y = HIWORD(lParam);////获取lparam高16位数字

			TCHAR chInfo[256] = { 0 };
			wsprintf(chInfo, L"鼠标左键抬起，x=%d y=%d", x, y);//将宽字符写到缓冲区中
			SetWindowText(hWnd, chInfo);
			break;
		}
		case WM_RBUTTONDOWN://右键退出
		{
			int res = MessageBox(hWnd, L"右键退出吗?", L"提示", MB_YESNO);
			if (IDYES == res)
			{
				PostQuitMessage(0);//发送进程退出消息，退出进程。
			}
			break;
		}
		case WM_LBUTTONDBLCLK://左键双击
			MessageBox(hWnd, L"双击", L"提示", MB_OK);
			break;
		case WM_MOUSEMOVE://鼠标移动消息
		{
			//获取鼠标坐标
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			TCHAR chInfo[256] = { 0 };
			wsprintf(chInfo, L"x=%d y=%d", x, y);//将宽字符写到缓冲区中
			SetWindowText(hWnd, chInfo);
			break;
		}
		case WM_KEYDOWN://键盘按下消息
		{
			//此时wparam保存的是虚拟键盘值
			switch (wParam)
			{
				case VK_SPACE://空格,模拟鼠标按键
				{
					int x = 50; int y = 150;
					//将坐标合成4字，a是低位b是高位
					SendMessage(hWnd, WM_LBUTTONDOWN, 0, MAKELONG(x, y));
					break;
				}
				case VK_SHIFT://按下SHIFT向指定窗口(记事本)发送信号
				{
					HWND hWndNotPead = FindWindow(L"Notepad", NULL);//向记事本窗口类发送消息
					if (hWndNotPead == NULL)
					{
						MessageBox(hWnd, L"找不到记事本", L"提示", MB_OK);
						return 1;
					}
					PostMessage(hWndNotPead, WM_CLOSE, 0, 0);//WM_CLOSE消息不用传信息
					break;
				}
				case VK_ESCAPE:
				{
					break;
				}
				case VK_RETURN://回车键发送自定义消息
				{
					MessageBox(hWnd, L"取消时间", L"提示", MB_OK);
					PostMessage(hWnd, DOD_UMTEST, 0, 0);
				}
				//.....
				case VK_LEFT://左键
				{//...
					break;
				}
				case 0x30://正上方数字0
				{
					MessageBox(hWnd, L"0", L"提示", MB_OK);
					break;
				}
				case VK_NUMPAD0://小键盘的0
					break;
				case 0x41://A字符
				{
					MessageBox(hWnd, L"A", L"提示", MB_OK);//不分大小写
					break;
				}
			}

			break;
		}
		case WM_KEYUP://键盘抬起消息
			break;
		case WM_CHAR://字符消息,由一次按下消息和抬起消息组合起来的，在虚拟键转化为字符消息中转化
		{
			TCHAR Ch = (TCHAR)wParam;
			TCHAR Buff[256] = { 0 };
			wsprintf(Buff, L"字符：%c", Ch);
			SetWindowText(hWnd, Buff);
			break;
		}
		case WM_PAINT://绘图消息，窗口显示时会发出此消息
		{
			PAINTSTRUCT ps;//画图结构体
			HDC hDC = BeginPaint(hWnd, &ps);//初始化画图结构体

			//画椭圆
			Ellipse(hDC, 10, 10, 200, 100);

			EndPaint(hWnd,&ps);//停止画图
			break;
		}
		case WM_TIMER://定时器消息
		{
			int TimeID = wParam;//从wParam获取定时器ID
			switch (TimeID)
			{
			case TIME_ID://获取到这个ID显示时间
				//获取当前时间
			{
				time_t hour = time(NULL);
				tm* year = localtime(&hour);//转化时间戳,tm是结构体，年月日
				TCHAR Buff[256] = { 0 };
				wsprintf(Buff, L"当前时间：%d-%d-%d %d:%d:%d", year->tm_year + 1900, year->tm_mon + 1, year->tm_mday
					, year->tm_hour, year->tm_min, year->tm_sec);
				SetWindowText(hWnd, Buff);
			}
			//.....
			default:
				break;
			}
		}
	}
	return DefWindowProc(hWnd, uMeg, wParam, lParam);//窗口默认处理函数
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPereInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//设计窗口类
	WNDCLASS Box = { 0 };
	Box.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;//窗口属性，移动时水平竖直重绘，响应双击
	Box.lpfnWndProc = WindowsProc;//消息处理函数指针
	Box.cbClsExtra = 0;//不需要额外字节
	Box.cbWndExtra = 0;//不需要额外空间
	Box.hInstance = hInstance;//当前应用程序的实例句柄
	Box.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);//默认可执行程序图标
	Box.hCursor = LoadCursor(NULL, IDC_HAND);//系统自带双手图标
	Box.hbrBackground = CreateSolidBrush(RGB(255, 255, 0));//黄色背景
	Box.lpszMenuName = NULL;//无菜单
	Box.lpszClassName = L"dodamce";//窗口类名

	//注册窗口类
	if (RegisterClass(&Box) == 0)
	{
		MessageBox(NULL, L"此程序不能运行在Windows NT上",L"提示",MB_OK|MB_ICONWARNING);//图标变成系统默认警告图标
		return -1;
	}
	
	//创建窗口
	HWND hwnd=CreateWindow(L"dodamce", L"20050441", WS_SYSMENU|WS_BORDER | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
		300, 200, 800, 600,NULL,NULL,hInstance,NULL);//返回窗口句柄
	//窗口风格：带系统菜单，边框，标题栏，最大化，最小化
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