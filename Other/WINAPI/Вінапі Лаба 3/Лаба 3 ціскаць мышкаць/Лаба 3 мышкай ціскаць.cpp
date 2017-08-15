#undef UNICODE
#include <windows.h>
#include <string>
#include <wingdi.h>
#include <winuser.h>
#include <vector>

using namespace std;

struct Infa
{
	int cx;
	int cy;
	int rad;
	Infa(int x1, int y1, int rad=80): cx(x1), cy(y1), rad(rad){}
};

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
BOOL InitApplication(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

LPCSTR szClassName = "WinAPI";
LPCSTR szTitle =     "������ �������";

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
	static int x, y;
	static HDC hDC;
	static vector<Infa> infa;
	static int x1, y1, z1;

 switch(message)
  {
  case WM_LBUTTONDOWN:
	  {
	  x=LOWORD(lParam);
	  y=HIWORD(lParam);
	  int count=0;
	  if(infa.size()!=0)
	  {
		  for (int t=0; t<infa.size(); t++)
		  {	
			  HRGN round=CreateEllipticRgn(infa[t].cx-infa[t].rad, infa[t].cy-infa[t].rad, infa[t].cx+infa[t].rad, infa[t].cy+infa[t].rad);
			  if (PtInRegion(round, x, y))
			  {	
				  infa[t].rad+=20;
				  count++;
			  }
		  }
	  }
	  if (count==0)
			infa.push_back(Infa(x, y));
	  InvalidateRect (hwnd, NULL, true);
	  break;
 }
  case WM_PAINT:
	  hDC = BeginPaint(hwnd, &ps);
	   for (int j=0; j<infa.size(); j++)
	   {
		HBRUSH hbrush=CreateSolidBrush(RGB(x1, y1, z1));
		HBRUSH hbrush2=(HBRUSH)SelectObject(hDC, hbrush);
		Ellipse (hDC, infa[j].cx-infa[j].rad, infa[j].cy-infa[j].rad, infa[j].cx+infa[j].rad, infa[j].cy+infa[j].rad);
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
