#undef UNICODE
#include <windows.h>
#include <string>
#include <wingdi.h>
#include <winuser.h>

using namespace std;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "���� � ������� � ������";

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
  MSG msg;
  /*���� �������� hPrevInstance � Win32 ������ ����� NULL���������� ��������� ��� �������� */
  if (!hPrevInstance) 
  {  /* �������������� ���������� -  �������������� ������ ������ ���� � ������������ ��� */
    if (!InitApplication(hInstance)) 
      return (FALSE);
  }
   /* ��������� �������� ����� ���������� -     ������� ������� ���� ���������� */
  if (!InitInstance(hInstance, nCmdShow)) 
    return (FALSE);  
  
  /* ���� ��������� ��������� */
  while (GetMessage(&msg, NULL, 0, 0)) 
  {   	TranslateMessage(&msg);
    		DispatchMessage(&msg);
  }
  return (msg.wParam);
}

BOOL InitApplication(HINSTANCE hInstance)
{
  WNDCLASS  wc;
  // ��������� ��������� ������ ���� WNDCLASS
  wc.style         = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc   = (WNDPROC)WndProc;
  wc.cbClsExtra    = 0;
  wc.cbWndExtra    = 0;
  wc.hInstance     = hInstance;
  wc.hIcon         = LoadIcon(NULL, IDI_ASTERISK);
  wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)COLOR_3DSHADOW;
  wc.lpszMenuName  = NULL;
  wc.lpszClassName = szClassName;
  // ������������ ����� ����
  return RegisterClass(&wc);
} 
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  HWND hWnd;
  hWnd = CreateWindow(
    szClassName,         // ��������� �� ������ ������������������� ����� ������
    szTitle,             // ��������� �� ��������� ����
    WS_OVERLAPPEDWINDOW, // ����� ����
    10,       // �������������� ���������� ����
    10,       // ������������ ���������� ����
    1000,       // ������ ����
    500,       // ������ ����
    NULL,                // ���������� ������������� ����
    NULL,                // ���������� ���� ����
    hInstance,           // ���������� ���������� ����������
    NULL);               // ��������� �� �������������� ������ ����

  if (!hWnd)    return (FALSE); 
  ShowWindow(hWnd, nCmdShow);
  UpdateWindow(hWnd);
  return (TRUE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int sy, sx, i=0;
	static HFONT hfont1;
	static string str1="�����, ����� ����� ����� �������"; 
	HDC hDC;
	static LOGFONT lf1;
	lf1.lfHeight=((sx+i)/40)+1;
	lf1.lfWidth=0;
	lf1.lfEscapement=0;
	lf1.lfOrientation=0;
	lf1.lfWeight=900;
	lf1.lfItalic=0;
	lf1.lfUnderline=0;
	lf1.lfStrikeOut=0;
	lf1.lfCharSet=5;
	lf1.lfOutPrecision=5;
	lf1.lfClipPrecision=0;
	lf1.lfQuality=0;
	lf1.lfPitchAndFamily=DEFAULT_PITCH;
  PAINTSTRUCT ps;
  switch(message)
  {
  case WM_SIZE:
	  sx=LOWORD(lParam);
	  sy=HIWORD(lParam);  
	  break;
  case WM_CHAR:
	  switch (wParam)
	  {
	  case '+':
		i+=40;
		str1+=(char)wParam;
		InvalidateRect(hwnd, NULL, TRUE);
	  break;
	  case '-':
		i-=40;
		str1+=(char)wParam;
		InvalidateRect(hwnd, NULL, TRUE);
	  break;
	  }

  case WM_PAINT:
	  hDC = BeginPaint(hwnd, &ps);
	  hfont1 = CreateFontIndirect(&lf1);
	  {
		HFONT holdfont1 = (HFONT)SelectObject(hDC, hfont1);
	  }
	  if (sx+i>=0)
	  TextOut (hDC, (sx-i)/3, (sy-i/10)/2, str1.data(), str1.size());
	  EndPaint(hwnd, &ps);
      break;
  case WM_DESTROY:
	     PostQuitMessage(0);
	  	  break;
    default:
      return DefWindowProc(hwnd, message, wParam, lParam);
  }	
  return  0;
}
