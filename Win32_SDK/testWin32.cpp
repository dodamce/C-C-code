#include<Windows.h>

//uMeg��Ϣ���,���غ���ָ��
LRESULT CALLBACK WindowsProc(HWND hWnd, UINT uMeg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, uMeg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPereInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//��ƴ�����
	WNDCLASS Box = { 0 };
	Box.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	Box.lpfnWndProc = WindowsProc;
	Box.cbClsExtra = 0;//����Ҫ�����ֽ�
	Box.hInstance = hInstance;
	Box.hIcon = NULL;
	Box.hCursor = NULL;
	Box.hbrBackground = CreateSolidBrush(RGB(255, 255, 0));//��ɫ����
	Box.lpszMenuName = NULL;//�޲˵�
	Box.lpszClassName = L"dodamce";

	//ע�ᴰ����
	if (RegisterClass(&Box) == 0)
	{
		MessageBox(NULL, L"�˳�����������Windows NT��",L"��ʾ",MB_OK|MB_ICONWARNING);
		return -1;
	}
	
	//��������
	HWND hwnd=CreateWindow(L"dodamce", L"20050441", WS_SYSMENU|WS_BORDER | WS_CAPTION | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
		300, 200, 800, 600,NULL,NULL,hInstance,NULL);//���ش��ھ��
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