#include<Windows.h>
#include"resource.h"

/*
* 模态对话框
*/

HINSTANCE G_hInstance;//全局窗口句柄，为了让模态窗口处理函数也可以接受到实例句柄

//第三个登录窗口处理函数
BOOL CALLBACK Register(HWND hWnd, UINT uMeg, WPARAM wParam, LPARAM lParam)
{
	switch (uMeg)
	{
		case WM_CLOSE://窗口关闭因为没有消息循环，所以不需要在WM_DESTORY中写PostQuitText函数跳出循环
		{
			EndDialog(hWnd, 0);//结束模态对话框
			return TRUE;//代表处理完毕
		}
		case WM_COMMAND:
		{

			int wID = LOWORD(wParam);
			switch (wID)
			{
			case IDOK:
				//获取用户名与密码,假设初始用户为dodamce 密码为123
				TCHAR UserName[150];
				TCHAR UserPassword[150];
				GetDlgItemText(hWnd, IDC_EDIT1, UserName, 150);
				GetDlgItemText(hWnd, IDC_EDIT2, UserPassword, 150);
				if (wcscmp(UserName, L"dodamce") == 0 && wcscmp(UserPassword, L"123") == 0)//长字符串比较函数
				{
					//关闭登录窗口,退出码设为1
					EndDialog(hWnd, 1);
				}
				else
				{
					MessageBox(hWnd, L"用户名或者密码有误", L"警告", MB_OK);
					return TRUE;
				}
				break;
			case IDCANCEL:
				//退出窗口
				EndDialog(hWnd, 0);//发送退出消息，0代表退出时传给主函数中的DialogBox的退出码，传1代表DialogBox
				break;
			}
		}
	}
	return FALSE;
}

//第二个信息窗口处理函数
BOOL CALLBACK MesDel(HWND hWnd, UINT uMeg, WPARAM wParam, LPARAM lParam)
{
	switch (uMeg)
	{
		case WM_CLOSE://窗口关闭因为没有消息循环，所以不需要在WM_DESTORY中写PostQuitText函数跳出循环
		{
			EndDialog(hWnd, 0);//结束模态对话框
			return TRUE;//代表处理完毕
		}
	}
	return FALSE;//系统处理消息
}

BOOL CALLBACK DiglogProc(HWND hWnd, UINT uMeg, WPARAM wParam, LPARAM lParam)
{
	switch (uMeg)
	{
		case WM_INITDIALOG://对话框初始化消息,此时对话框还没显示出来
		{
			//加载窗口图标
			HICON Hicon=LoadIcon(G_hInstance,MAKEINTRESOURCE(IDI_ICON1));

			//发送设置窗口图标的消息
			SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)Hicon);//设置大图标
			SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)Hicon);//设置小图标

			SetWindowText(hWnd,L"20040441-dodamce");//设置窗口标题栏

			//设置窗口透明度
			SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 125, LWA_ALPHA);//0是全透明，255为不透明,LWA_ALPHA是窗口透明

			break;
		}
		case WM_CLOSE://窗口关闭因为没有消息循环，所以不需要在WM_DESTORY中写PostQuitText函数跳出循环
		{
			int ret=MessageBox(hWnd, L"确定退出？", L"提示", MB_YESNO);
			if (IDNO == ret)
				return TRUE;//代表已经处理过这个消息了
			else
			{
				EndDialog(hWnd, 0);//结束模态对话框
				break;
			}
		}
		case WM_DESTROY://在WM_CLOSE之后会发出这个消息
		{
			MessageBox(NULL, L"退出成功", L"提示", MB_OK);//全局消息窗口
		}
		case WM_COMMAND://命令消息,窗口上的按钮
		{
			int wID = LOWORD(wParam);
			switch (wID)
			{
			case IDOK:
				MessageBox(hWnd, L"确认OK", L"提示", MB_OK);
				break;
			case IDCANCEL:
				//退出窗口
				EndDialog(hWnd, 0);//发送退出消息，0代表退出时传给主函数中的DialogBox的退出码，传1代表DialogBox
				break;
			case IDC_BUTTON_MEG://自定义信息按钮
			{
				DialogBox(G_hInstance, MAKEINTRESOURCE(IDD_MES),hWnd,MesDel);
				break;
			}
			default:
				break;
			}
			break;
		}
		case WM_DROPFILES://拖拽文件消息
		{
			HDROP hDrop = (HDROP)wParam;//拖拽文件句柄
			//DragQueryFile(传入0xFFFFFFFF代表文件个数,如果是0到文件个数-1会把文件路径保存到第三个参数中lpszFile缓冲区中，第四个参数
			//存储拖拽文件名称缓冲区的大小，即lpszFile指针所指缓冲区的字符数。)
			int cout = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
			TCHAR szPath[MAX_PATH] = { 0 };//保存文件的路径
			for (int i = 0; i < cout; i++)
			{
				DragQueryFile(hDrop, i, szPath, MAX_PATH);
				MessageBox(hWnd, szPath, L"文件路径", MB_OK);
			}
			break;
		}
	}
	//返回真表示自己处理，不会调用默认处理消息，返回假表示消息自己不处理，系统默认处理
	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmpShow)
{
	G_hInstance = hInstance;
	//弹出登录窗口
	int resule=DialogBox(hInstance, MAKEINTRESOURCE(IDD_RESISTER), NULL, Register);
	if (resule == 0)//登录点击取消
	{
		return 2;
	}
	else
	{
		//主窗口
		DialogBox(hInstance, MAKEINTRESOURCE(IDD_MYDIALOG), NULL, DiglogProc);//创建模态对话框,将导入的Dialog模板强制转化为字符串类型
	}
	return 0;
}