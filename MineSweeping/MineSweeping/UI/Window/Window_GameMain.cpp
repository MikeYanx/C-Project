#include "Window_GameMain.h"
#include "../../Controller/GameController.h"
#include "../../Utils/Log.h"

char logbuffer[32];

/*ʹ��˫���弼��,���ƹ��̹��ڸ���,��ֹ������ٶȲ��㵼�µĴ���������˸
 *����ԭ��: ����һ���־û���DC,
 *
 *
 */

/*��̨�����豸������*/
//static HDC backgroundDC = NULL;
/*��ΪbackgroundDC����ѡ����*/
//static HBITMAP backgroundBitmap = NULL;
/*������DC���ش�С,��Ҫ������Ϸ��ʼ���ݽ��и���*/
static int cxClientPix, cyClientPix;
static HBITMAP bufferBmp;
static HDC bufferDC = NULL, drawDC = NULL;
static GameController localGameController;

static int mpx = 0;
static int mpy = 0;

static int ldpx = 0;
static int ldpy = 0;

static int rdpx = 0;
static int rdpy = 0;

static int lupx = 0;
static int lupy = 0;

static int rupx = 0;
static int rupy = 0;

static bool lbs = 0;
static bool rbs = 0;

static TCHAR numbuf[20] = { 0 };

void showMousePointerInfo(HDC hdc) {
	SetTextColor(hdc, RGB(255, 255, 255));
	SetBkColor(hdc, RGB(0, 0, 0));
	SetBkMode(hdc, OPAQUE);

	TextOut(hdc, 10, 10, L"MousePosi", lstrlen(L"MousePosi"));
	wsprintf(numbuf, L"X: %4d    ", mpx);
	TextOut(hdc, 10, 30, numbuf, lstrlen(numbuf));
	wsprintf(numbuf, L"Y: %4d    ", mpy);
	TextOut(hdc, 10, 50, numbuf, lstrlen(numbuf));

	TextOut(hdc, 130, 10, L"LastLBDPosi", lstrlen(L"LastLBDPosi"));
	wsprintf(numbuf, L"X: %4d    ", ldpx);
	TextOut(hdc, 130, 30, numbuf, lstrlen(numbuf));
	wsprintf(numbuf, L"Y: %4d    ", ldpy);
	TextOut(hdc, 130, 50, numbuf, lstrlen(numbuf));

	TextOut(hdc, 250, 10, L"LastRBDPosi", lstrlen(L"LastRBDPosi"));
	wsprintf(numbuf, L"X: %4d    ", rdpx);
	TextOut(hdc, 250, 30, numbuf, lstrlen(numbuf));
	wsprintf(numbuf, L"Y: %4d    ", rdpy);
	TextOut(hdc, 250, 50, numbuf, lstrlen(numbuf));

	TextOut(hdc, 370, 10, L"LastLBUPosi", lstrlen(L"LastLBUPosi"));
	wsprintf(numbuf, L"X: %4d    ", lupx);
	TextOut(hdc, 370, 30, numbuf, lstrlen(numbuf));
	wsprintf(numbuf, L"Y: %4d    ", lupy);
	TextOut(hdc, 370, 50, numbuf, lstrlen(numbuf));

	TextOut(hdc, 490, 10, L"LastRBUPosi", lstrlen(L"LastRBUPosi"));
	wsprintf(numbuf, L"X: %4d    ", rupx);
	TextOut(hdc, 490, 30, numbuf, lstrlen(numbuf));
	wsprintf(numbuf, L"Y: %4d    ", rupy);
	TextOut(hdc, 490, 50, numbuf, lstrlen(numbuf));

	TextOut(hdc, 610, 10, L"PointerStatus", lstrlen(L"PointerStatus"));
	wsprintf(numbuf, L"Left : %d ", lbs);
	TextOut(hdc, 610, 30, numbuf, lstrlen(numbuf));
	wsprintf(numbuf, L"Right: %d ", rbs);
	TextOut(hdc, 610, 50, numbuf, lstrlen(numbuf));


}
// ���ڴ�����Ϣ����(�ص�����)
LRESULT CALLBACK WindowProc_GameMain(HWND phwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//CreateCompatibleBitmap()
	switch (msg)
	{

		/*
		WM_CREATE �ڴ�������(����CreateWindow����)ʱ������ֻ����һ�Ρ�
		WM_PAINT����Ҫ�ػ�(����UpdateWindow����)ʱ���ã�����δ�����
		WM_CREATE����WM_PAINT
		*/
	case WM_CREATE:
	{
		/*����һ�����ڻ�ȡ������Ϣ*/
		GameInfo gi;
		gi.boardLength = 40;
		gi.boardHeight = 30;
		gi.mineNum = 39;
		gi.playerName = L"TestPlayer";
		gi.gameModel = new MineSweepingGame(40, 30, 39);
		/**/

		cxClientPix = 0;
		cyClientPix = 0;
		hwnd[2] = phwnd;
		/*��ʼ��Canve*/
		localGameController.initialize(&gi, phwnd, hInstance[2],&cxClientPix, &cyClientPix);

		HDC hdc = GetDC(phwnd); //��ȡ�豸

		bufferDC = CreateCompatibleDC(hdc); //���豸����һ���ڴ�ռ�

		drawDC = CreateCompatibleDC(hdc);

		bufferBmp = CreateCompatibleBitmap(hdc, cxClientPix, cyClientPix); //����һ��cxClient, cyClient��С������ӦDC�豸������λͼ

		ReleaseDC(phwnd, hdc);

		SelectObject(bufferDC, bufferBmp);

		inflog("GameCanveSize: w:",itoa(cxClientPix, logbuffer, 10),"px | h:", itoa(cyClientPix, logbuffer, 10),"px.");
		/*��һ�λ���*/
		//localGameController.draw(phwnd);
		

		//set_window_size(phwnd, 900, 600);
		/*
		HDC hdc = GetDC(phwnd);
		HDC backgroundDC = CreateCompatibleDC(hdc);
		HBITMAP backgroundBitmap = CreateCompatibleBitmap(hdc, cxClientPix, cyClientPix);
		ReleaseDC(phwnd, hdc);
		SelectObject(backgroundDC, backgroundBitmap);
		*/

		//onDraw2();
		/*
		break������Ҫ!!!
		break������Ҫ!!!
		break������Ҫ!!!
		��Ҫ�Ļ�˵����
		*/
		break;
	}
	// ���ڻ�����Ϣ
	/*ʹ��WS_EX_LAYERED��񴰿ڲ���� WM_PAINT ��Ϣ������Ӧ,��ͼ������WM_CREATE״̬�µ�UpdateLayeredWindow()��������*/
	case WM_PAINT: {
		PAINTSTRUCT ps;
		/*��ӦWM_PAINTʱ����������������BeginPaint��EndPaint,����WM_PAINT�ᵼ����Ч����ı���������;����������HDC��ͼ������*/
		HDC hdc = BeginPaint(hwnd[2], &ps);
		localGameController.draw(hdc, bufferDC, drawDC, bufferBmp);
		showMousePointerInfo(hdc);
		/*
		HBITMAP hBitmap_num3 = (HBITMAP)LoadImage(hInstance[2], L"res\\bitmap\\msg-num3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);//LoadBitmap(hInstance[2], L"res\\bitmap\\msg-num3.bmp");
		SelectObject(drawDC, hBitmap_num3);
		BitBlt(bufferDC, 50, 50, 16, 16, drawDC, 0, 0, SRCCOPY);
		BitBlt(hdc, 0, 0, cxClientPix, cyClientPix, bufferDC, 0, 0, SRCCOPY);
		BitmapHelper te(L"res\\bitmap\\msg-num2.bmp");
		te.ShowOnDevice(hdc,200,200);
		*/
		/*
		* ���ݻ���
		*/
		//bitmap_num5.ShowOnDevice(hdc,100,100);

		/*������ͼ,�ͷŻ�ͼ��*/
		EndPaint(hwnd[2], &ps);
		break;
	}
				   /*
	case WM_SIZE: {
		HDC hdc = GetDC(phwnd);
		bufferBmp = CreateCompatibleBitmap(hdc, cxClientPix, cyClientPix);
		ReleaseDC(phwnd, hdc);
	}
	*/

	case WM_MOUSEMOVE: {
		memset(numbuf, 0, sizeof(TCHAR) * 20);
		mpx = (int)LOWORD(lParam);
		mpy = (int)HIWORD(lParam);
		HDC hdc = GetDC(phwnd);
		showMousePointerInfo(hdc);
		ReleaseDC(phwnd, hdc);
		break;
	}
	case WM_LBUTTONDOWN: {
		lbs = 1;
		ldpx = mpx;
		ldpy = mpy;
		HDC hdc = GetDC(phwnd);
		showMousePointerInfo(hdc);
		ReleaseDC(phwnd, hdc);
		break;
	}
	case WM_RBUTTONDOWN: {
		rbs = 1;
		rdpx = mpx;
		rdpy = mpy;
		HDC hdc = GetDC(phwnd);
		showMousePointerInfo(hdc);
		ReleaseDC(phwnd, hdc);
		break;
	}
	case WM_LBUTTONUP: {
		lbs = 0;
		lupx = mpx;
		lupy = mpy;
		HDC hdc = GetDC(phwnd);
		showMousePointerInfo(hdc);
		ReleaseDC(phwnd, hdc);
		break;
	}
	case WM_RBUTTONUP: {
		rbs = 0;
		rupx = mpx;
		rupy = mpy;
		HDC hdc = GetDC(phwnd);
		showMousePointerInfo(hdc);
		ReleaseDC(phwnd, hdc);
		break;
	}
	case WM_COMMAND:
	{

		switch (wParam) {
		
		}

		break;
	}
	// ���ڹر���Ϣ
	case WM_CLOSE:
		DestroyWindow(hwnd[2]);
		break;
		// ����������Ϣ
	case WM_DESTROY:
		PostQuitMessage(0); // �����뿪��Ϣ��ϵͳ
		break;
		//case WM_SIZE:
		//{
		//	break;
		//}
		//set_window_size(hwnd, 1000, 625);
		// ������Ϣ
	default:
		// pass ��ϵͳ���۲���
		return DefWindowProc(phwnd, msg, wParam, lParam);
	}
	//return DefWindowProc(phwnd, msg, wParam, lParam);
	return 0;
}


void RegisterWindow_GameMain(HINSTANCE hInstance) {
	WNDCLASSEX wc;
	// 1)���ô�������
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc_GameMain; // ���õ��Ĳ��Ĵ��ڹ��̻ص�����
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;//(HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = regClassName[2];
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	// 2)ע��
	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"����ע��ʧ��!", L"����", MB_ICONEXCLAMATION | MB_OK);
		exit(0); // �����˳�
	}
}
HWND CreateWindow_GameMain(HINSTANCE hInstance, int nCmdShow) {
	hwnd[2] = CreateWindow(
		regClassName[2],
		wndTitle[2],
		WS_OVERLAPPEDWINDOW,
		wga[2].X, wga[2].Y, wga[2].nWidth, wga[2].nHeight, // �������� x,y,���� �߶� 
		NULL, NULL, hInstance, NULL);
	if (hwnd[2] == NULL)
	{
		MessageBox(NULL, L"���ڴ���ʧ��!", L"����", MB_ICONEXCLAMATION | MB_OK);
		exit(0); // �����˳�
	}
	// ��ʾ����
	ShowWindow(hwnd[2], SW_SHOW);
	UpdateWindow(hwnd[2]);
	return hwnd[2];
}