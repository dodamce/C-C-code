#include<Windows.h>
#include"resource.h"

/*
* ģ̬�Ի���
*/

HINSTANCE G_hInstance;//ȫ�ִ��ھ����Ϊ����ģ̬���ڴ�����Ҳ���Խ��ܵ�ʵ�����

//��������¼���ڴ�����
BOOL CALLBACK Register(HWND hWnd, UINT uMeg, WPARAM wParam, LPARAM lParam)
{
	switch (uMeg)
	{
		case WM_CLOSE://���ڹر���Ϊû����Ϣѭ�������Բ���Ҫ��WM_DESTORY��дPostQuitText��������ѭ��
		{
			EndDialog(hWnd, 0);//����ģ̬�Ի���
			return TRUE;//���������
		}
		case WM_COMMAND:
		{

			int wID = LOWORD(wParam);
			switch (wID)
			{
			case IDOK:
				//��ȡ�û���������,�����ʼ�û�Ϊdodamce ����Ϊ123
				TCHAR UserName[150];
				TCHAR UserPassword[150];
				GetDlgItemText(hWnd, IDC_EDIT1, UserName, 150);
				GetDlgItemText(hWnd, IDC_EDIT2, UserPassword, 150);
				if (wcscmp(UserName, L"dodamce") == 0 && wcscmp(UserPassword, L"123") == 0)//���ַ����ȽϺ���
				{
					//�رյ�¼����,�˳�����Ϊ1
					EndDialog(hWnd, 1);
				}
				else
				{
					MessageBox(hWnd, L"�û���������������", L"����", MB_OK);
					return TRUE;
				}
				break;
			case IDCANCEL:
				//�˳�����
				EndDialog(hWnd, 0);//�����˳���Ϣ��0�����˳�ʱ�����������е�DialogBox���˳��룬��1����DialogBox
				break;
			}
		}
	}
	return FALSE;
}

//�ڶ�����Ϣ���ڴ�����
BOOL CALLBACK MesDel(HWND hWnd, UINT uMeg, WPARAM wParam, LPARAM lParam)
{
	switch (uMeg)
	{
		case WM_CLOSE://���ڹر���Ϊû����Ϣѭ�������Բ���Ҫ��WM_DESTORY��дPostQuitText��������ѭ��
		{
			EndDialog(hWnd, 0);//����ģ̬�Ի���
			return TRUE;//���������
		}
	}
	return FALSE;//ϵͳ������Ϣ
}

BOOL CALLBACK DiglogProc(HWND hWnd, UINT uMeg, WPARAM wParam, LPARAM lParam)
{
	switch (uMeg)
	{
		case WM_INITDIALOG://�Ի����ʼ����Ϣ,��ʱ�Ի���û��ʾ����
		{
			//���ش���ͼ��
			HICON Hicon=LoadIcon(G_hInstance,MAKEINTRESOURCE(IDI_ICON1));

			//�������ô���ͼ�����Ϣ
			SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)Hicon);//���ô�ͼ��
			SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)Hicon);//����Сͼ��

			SetWindowText(hWnd,L"20040441-dodamce");//���ô��ڱ�����

			//���ô���͸����
			SetLayeredWindowAttributes(hWnd, RGB(0, 0, 0), 125, LWA_ALPHA);//0��ȫ͸����255Ϊ��͸��,LWA_ALPHA�Ǵ���͸��

			break;
		}
		case WM_CLOSE://���ڹر���Ϊû����Ϣѭ�������Բ���Ҫ��WM_DESTORY��дPostQuitText��������ѭ��
		{
			int ret=MessageBox(hWnd, L"ȷ���˳���", L"��ʾ", MB_YESNO);
			if (IDNO == ret)
				return TRUE;//�����Ѿ�����������Ϣ��
			else
			{
				EndDialog(hWnd, 0);//����ģ̬�Ի���
				break;
			}
		}
		case WM_DESTROY://��WM_CLOSE֮��ᷢ�������Ϣ
		{
			MessageBox(NULL, L"�˳��ɹ�", L"��ʾ", MB_OK);//ȫ����Ϣ����
		}
		case WM_COMMAND://������Ϣ,�����ϵİ�ť
		{
			int wID = LOWORD(wParam);
			switch (wID)
			{
			case IDOK:
				MessageBox(hWnd, L"ȷ��OK", L"��ʾ", MB_OK);
				break;
			case IDCANCEL:
				//�˳�����
				EndDialog(hWnd, 0);//�����˳���Ϣ��0�����˳�ʱ�����������е�DialogBox���˳��룬��1����DialogBox
				break;
			case IDC_BUTTON_MEG://�Զ�����Ϣ��ť
			{
				DialogBox(G_hInstance, MAKEINTRESOURCE(IDD_MES),hWnd,MesDel);
				break;
			}
			default:
				break;
			}
			break;
		}
		case WM_DROPFILES://��ק�ļ���Ϣ
		{
			HDROP hDrop = (HDROP)wParam;//��ק�ļ����
			//DragQueryFile(����0xFFFFFFFF�����ļ�����,�����0���ļ�����-1����ļ�·�����浽������������lpszFile�������У����ĸ�����
			//�洢��ק�ļ����ƻ������Ĵ�С����lpszFileָ����ָ���������ַ�����)
			int cout = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
			TCHAR szPath[MAX_PATH] = { 0 };//�����ļ���·��
			for (int i = 0; i < cout; i++)
			{
				DragQueryFile(hDrop, i, szPath, MAX_PATH);
				MessageBox(hWnd, szPath, L"�ļ�·��", MB_OK);
			}
			break;
		}
	}
	//�������ʾ�Լ������������Ĭ�ϴ�����Ϣ�����ؼٱ�ʾ��Ϣ�Լ�������ϵͳĬ�ϴ���
	return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmpShow)
{
	G_hInstance = hInstance;
	//������¼����
	int resule=DialogBox(hInstance, MAKEINTRESOURCE(IDD_RESISTER), NULL, Register);
	if (resule == 0)//��¼���ȡ��
	{
		return 2;
	}
	else
	{
		//������
		DialogBox(hInstance, MAKEINTRESOURCE(IDD_MYDIALOG), NULL, DiglogProc);//����ģ̬�Ի���,�������Dialogģ��ǿ��ת��Ϊ�ַ�������
	}
	return 0;
}