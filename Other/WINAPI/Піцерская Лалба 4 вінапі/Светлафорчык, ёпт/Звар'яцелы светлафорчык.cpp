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
LPCSTR szTitle =     "������������ ����'���";

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
    600,       // ������ ����
    600,       // ������ ����
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
	HBRUSH hbr, hbrye[2], hbrgr[2], hbrre[2]; 
	HDC hDC;
 switch(message)
  {
  case WM_SIZE:
	  sx=LOWORD(lParam);
	  sy=HIWORD(lParam);  
	  break;
  case WM_CREATE:
	  SetTimer(hwnd, 1, 1000, NULL);
	  break;
  case WM_TIMER:
	  time++;
	  InvalidateRect(hwnd, NULL, true);
	  break;
  case WM_PAINT:
	  hDC = BeginPaint(hwnd, &ps);
	  hbr=CreateSolidBrush(RGB(0,0,0));
	  SelectObject(hDC, hbr);
	  Rectangle (hDC, sx/3, 0, 2*sx/3, sy);
	  hbrre[0]=CreateSolidBrush(RGB(128,0,0));
	  SelectObject(hDC, hbrre[0]);
	  Ellipse (hDC, sx/2-sy/8, sy/6-sy/8, sx/2+sy/8, sy/6+sy/8);
	  hbrye[0]=CreateSolidBrush(RGB(255,165,0));
	  SelectObject(hDC, hbrye[0]);
	  Ellipse (hDC, sx/2-sy/8, 3*sy/6-sy/8, sx/2+sy/8, 3*sy/6+sy/8);
	  hbrgr[0]=CreateSolidBrush(RGB(0,100,0));
	  SelectObject(hDC, hbrgr[0]);
	  Ellipse (hDC, sx/2-sy/8, 5*sy/6-sy/8, sx/2+sy/8, 5*sy/6+sy/8);
	  if(time%3==0)
	  {
			  hbrre[1]=CreateSolidBrush(RGB(255,0,0));
			  SelectObject(hDC, hbrre[1]);
			  Ellipse (hDC, sx/2-sy/8, sy/6-sy/8, sx/2+sy/8, sy/6+sy/8);
	  }
	  if(time%3==1)
	  {
		  hbrye[1]=CreateSolidBrush(RGB(255,255,0));
		  SelectObject(hDC, hbrye[1]);
		  Ellipse (hDC, sx/2-sy/8, 3*sy/6-sy/8, sx/2+sy/8, 3*sy/6+sy/8);
	  }
	  if(time%3==2)
	  {
		  hbrgr[1]=CreateSolidBrush(RGB(0,255,0));
		  SelectObject(hDC, hbrgr[1]);
		  Ellipse (hDC, sx/2-sy/8, 5*sy/6-sy/8, sx/2+sy/8, 5*sy/6+sy/8);
	  }
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
