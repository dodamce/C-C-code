#include<Windows.h>
#include<time.h>

#define TIME_ID  5  //ʱ�䶨ʱ��

#define DOD_UMTEST (WM_USER+1)   //1024֮ǰ����ϵͳ����ģ��Լ�����Ҫ��1024֮��WM_USER֮��

/*
	��Ϣ���ࣺ
	1.��������Ϣ�������Ϣ������ȡ����Ϣ���󲿷��û��������Ϣ���ǽ�����Ϣ
	2.����������Ϣ���������Ϣ����ȡ��Ϣ��eg:WM_CREATE  WM_PAINT
*/

/*����
UINT �޷�������
WPAPAM  �޷�������
LPARAM ������
LONG long
TCHAR ���ַ�
LPCTSTR const w_char_t*
ATOM �� unsigned short
DWORD ˫�� unsigned long
*/

/* 
	SetMessage:ִ���꺯���󷵻أ�����ʽ�ȴ�����,����һ����Ϣ�Ĵ�����
	PostMessage:ֻ������ϢͶ�ݳ�ȥ���ɹ�����1ʧ��0����������Ϣ������
	�������������PostMessage
*/

/*
	�û��Զ�����Ϣ

*/

//uMeg��Ϣ���,���غ���ָ��
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMeg, WPARAM wParam, LPARAM lParam)
{
	switch (uMeg)
	{
		case DOD_UMTEST://�û��Զ�����Ϣ��ȡ����ʱ��
		{
			KillTimer(hWnd, TIME_ID);

			//���ñ���
			SetWindowText(hWnd, L"dodamce");
		}
		case WM_CREATE://����������Ϣ
		{
			CREATESTRUCT* ipcs = (CREATESTRUCT*)lParam;//CREATESTRUCT�ṹ�壬�������ע�ᴰ�ڵ���Ϣ
			MessageBox(hWnd, L"WM_CREAT��Ϣ", L"��ʾ", MB_OK);
			SetTimer(hWnd, TIME_ID, 1000, NULL);//NULL��ʾ1000����ϵͳ����һ��ʱ����Ϣ
			break;
		}
		case WM_CLOSE://�رմ�����Ϣ
		{
			int result = MessageBox(hWnd, L"ȷ���˳�?", L"��ʾ", MB_YESNO);
			if (result == IDYES)
			{
				break;
			}
			else//������С��
			{
				ShowWindow(hWnd, SW_MINIMIZE);
				return 1;//����ϵͳĬ�ϴ���,return1��ʾ�Ѿ�������ˡ�
			}
		}
		case WM_DESTROY://����������Ϣ�������˳�ʱ�յ�����Ҫ�����������ݵĹ����������Ѿ������٣��޷���ִ�д��ڲ���
			PostQuitMessage(0);//���ͽ����˳���Ϣ���˳����̡�
			break;
		case WM_LBUTTONDOWN://������������Ϣ
		{
			//��ȡ�������
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			TCHAR chInfo[256] = { 0 };
			wsprintf(chInfo, L"���������£�x=%d y=%d", x, y);//�����ַ�д����������

			if (wParam & MK_CONTROL)//���Ϊ��˵������Ctrl��
			{
				wcscat(chInfo, L"����ctrl��");//���ַ�����
			}
			if (wParam & MK_MBUTTON)
			{
				wcscat(chInfo, L"�����м�");//���ַ�����
			}
			//....

			//���ô��ڱ���
			SetWindowText(hWnd, chInfo);
			break;
		}
		case WM_LBUTTONUP:
		{
			//��ȡ�������
			int x = LOWORD(lParam);//��ȡlparam��16λ����
			int y = HIWORD(lParam);////��ȡlparam��16λ����

			TCHAR chInfo[256] = { 0 };
			wsprintf(chInfo, L"������̧��x=%d y=%d", x, y);//�����ַ�д����������
			SetWindowText(hWnd, chInfo);
			break;
		}
		case WM_RBUTTONDOWN://�Ҽ��˳�
		{
			int res = MessageBox(hWnd, L"�Ҽ��˳���?", L"��ʾ", MB_YESNO);
			if (IDYES == res)
			{
				PostQuitMessage(0);//���ͽ����˳���Ϣ���˳����̡�
			}
			break;
		}
		case WM_LBUTTONDBLCLK://���˫��
			MessageBox(hWnd, L"˫��", L"��ʾ", MB_OK);
			break;
		case WM_MOUSEMOVE://����ƶ���Ϣ
		{
			//��ȡ�������
			int x = LOWORD(lParam);
			int y = HIWORD(lParam);

			TCHAR chInfo[256] = { 0 };
			wsprintf(chInfo, L"x=%d y=%d", x, y);//�����ַ�д����������
			SetWindowText(hWnd, chInfo);
			break;
		}
		case WM_KEYDOWN://���̰�����Ϣ
		{
			//��ʱwparam��������������ֵ
			switch (wParam)
			{
				case VK_SPACE://�ո�,ģ����갴��
				{
					int x = 50; int y = 150;
					//������ϳ�4�֣�a�ǵ�λb�Ǹ�λ
					SendMessage(hWnd, WM_LBUTTONDOWN, 0, MAKELONG(x, y));
					break;
				}
				case VK_SHIFT://����SHIFT��ָ������(���±�)�����ź�
				{
					HWND hWndNotPead = FindWindow(L"Notepad", NULL);//����±������෢����Ϣ
					if (hWndNotPead == NULL)
					{
						MessageBox(hWnd, L"�Ҳ������±�", L"��ʾ", MB_OK);
						return 1;
					}
					PostMessage(hWndNotPead, WM_CLOSE, 0, 0);//WM_CLOSE��Ϣ���ô���Ϣ
					break;
				}
				case VK_ESCAPE:
				{
					break;
				}
				case VK_RETURN://�س��������Զ�����Ϣ
				{
					MessageBox(hWnd, L"ȡ��ʱ��", L"��ʾ", MB_OK);
					PostMessage(hWnd, DOD_UMTEST, 0, 0);
				}
				//.....
				case VK_LEFT://���
				{//...
					break;
				}
				case 0x30://���Ϸ�����0
				{
					MessageBox(hWnd, L"0", L"��ʾ", MB_OK);
					break;
				}
				case VK_NUMPAD0://С���̵�0
					break;
				case 0x41://A�ַ�
				{
					MessageBox(hWnd, L"A", L"��ʾ", MB_OK);//���ִ�Сд
					break;
				}
			}

			break;
		}
		case WM_KEYUP://����̧����Ϣ
			break;
		case WM_CHAR://�ַ���Ϣ,��һ�ΰ�����Ϣ��̧����Ϣ��������ģ��������ת��Ϊ�ַ���Ϣ��ת��
		{
			TCHAR Ch = (TCHAR)wParam;
			TCHAR Buff[256] = { 0 };
			wsprintf(Buff, L"�ַ���%c", Ch);
			SetWindowText(hWnd, Buff);
			break;
		}
		case WM_PAINT://��ͼ��Ϣ��������ʾʱ�ᷢ������Ϣ
		{
			PAINTSTRUCT ps;//��ͼ�ṹ��
			HDC hDC = BeginPaint(hWnd, &ps);//��ʼ����ͼ�ṹ��

			//����Բ
			Ellipse(hDC, 10, 10, 200, 100);

			EndPaint(hWnd,&ps);//ֹͣ��ͼ
			break;
		}
		case WM_TIMER://��ʱ����Ϣ
		{
			int TimeID = wParam;//��wParam��ȡ��ʱ��ID
			switch (TimeID)
			{
			case TIME_ID://��ȡ�����ID��ʾʱ��
				//��ȡ��ǰʱ��
			{
				time_t hour = time(NULL);
				tm* year = localtime(&hour);//ת��ʱ���,tm�ǽṹ�壬������
				TCHAR Buff[256] = { 0 };
				wsprintf(Buff, L"��ǰʱ�䣺%d-%d-%d %d:%d:%d", year->tm_year + 1900, year->tm_mon + 1, year->tm_mday
					, year->tm_hour, year->tm_min, year->tm_sec);
				SetWindowText(hWnd, Buff);
			}
			//.....
			default:
				break;
			}
		}
	}
	return DefWindowProc(hWnd, uMeg, wParam, lParam);//����Ĭ�ϴ�����
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPereInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//��ƴ�����
	WNDCLASS Box = { 0 };
	Box.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;//�������ԣ��ƶ�ʱˮƽ��ֱ�ػ棬��Ӧ˫��
	Box.lpfnWndProc = WindowsProc;//��Ϣ������ָ��
	Box.cbClsExtra = 0;//����Ҫ�����ֽ�
	Box.cbWndExtra = 0;//����Ҫ����ռ�
	Box.hInstance = hInstance;//��ǰӦ�ó����ʵ�����
	Box.hIcon = LoadIcon(NULL, IDI_EXCLAMATION);//Ĭ�Ͽ�ִ�г���ͼ��
	Box.hCursor = LoadCursor(NULL, IDC_HAND);//ϵͳ�Դ�˫��ͼ��
	Box.hbrBackground = CreateSolidBrush(RGB(255, 255, 0));//��ɫ����
	Box.lpszMenuName = NULL;//�޲˵�
	Box.lpszClassName = L"dodamce";//��������

	//ע�ᴰ����
	if (RegisterClass(&Box) == 0)
	{
		MessageBox(NULL, L"�˳�����������Windows NT��",L"��ʾ",MB_OK|MB_ICONWARNING);//ͼ����ϵͳĬ�Ͼ���ͼ��
		return -1;
	}
	
	//��������
	HWND hwnd=CreateWindow(L"dodamce", L"20050441", WS_SYSMENU|WS_BORDER | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
		300, 200, 800, 600,NULL,NULL,hInstance,NULL);//���ش��ھ��
	//���ڷ�񣺴�ϵͳ�˵����߿򣬱���������󻯣���С��
	if (hwnd == NULL)
	{
		MessageBox(NULL, L"���ڴ���ʧ��", L"��ʾ", MB_OK);
		return -2;
	}

	//��ʾ����
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	//��Ϣѭ��
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))//������Ϣ������
	{
		//���������Ϣת��Ϊ�ַ���Ϣ
		TranslateMessage(&msg);
		//�ַ���Ϣ
		DispatchMessage(&msg);
	}
	return 0;
}