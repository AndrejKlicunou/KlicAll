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
LPCSTR szTitle =     "�������";

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
	PAINTSTRUCT ps;
	static int sx, sy;
	static int time=0;
	HDC hDC;
 switch(message)
  {
  case WM_SIZE:
	  sx=LOWORD(lParam);
	  sy=HIWORD(lParam);  
	  break;
  case WM_CREATE:
	  SetTimer(hwnd, 1, 100, NULL);
  case WM_TIMER:
	  time++;
	  InvalidateRect(hwnd, NULL, true);
  case WM_PAINT:
	  hDC = BeginPaint(hwnd, &ps);
	  MoveToEx(hDC, 0, sy/2, NULL);
	  LineTo(hDC, sx, sy/2);
	  Ellipse(hDC, sx/24+(time*1000)%sx, sy/2-2*sy/15, sx/24+2*sy/15+(time*1000)%sx, sy/2);
	  Ellipse(hDC, 5*sx/24-2*sy/15+(time*1000)%sx, sy/2-2*sy/15, 5*sx/24+(time*1000)%sx, sy/2);
	  Rectangle(hDC, 0+(time*1000)%sx, sy/2-sy/15, sx/6+(time*1000)%sx, sy/2-sy/3);
	  Rectangle(hDC, sx/6+(time*1000)%sx, sy/2-0.9*sy/2, 3*sx/12+(time*1000)%sx, sy/2-sy/15);
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
