//****************************************************************************************************
//������������ ����������
//****************************************************************************************************
#include <windows.h>
#include <stdint.h>
#include <mmsystem.h>
#include "cwnd_main.h"

//****************************************************************************************************
//���������� ����������
//****************************************************************************************************
static const double FPS=60;//������� ������

HINSTANCE hProjectInstance;
CWnd_Main cWnd_Main;

LARGE_INTEGER start_time;

//****************************************************************************************************
//��������� �������
//****************************************************************************************************
void CALLBACK TimerEvent(UINT uTimerID,UINT uMsg,DWORD_PTR dwUser,DWORD_PTR dw1,DWORD_PTR dw2);//������� ��������������� �������

//****************************************************************************************************
//���������� �������
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//������� ������� ���������
//----------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevstance,LPSTR lpstrCmdLine,int nCmdShow)
{
 hProjectInstance=hInstance;
 MSG msg;
 CWnd_Main::Register();

 HWND hWnd=GetDesktopWindow();
 RECT rect;
 rect.left=0;
 rect.right=CGame::SCREEN_WIDTH*2;
 rect.bottom=CGame::SCREEN_HEIGHT*2;
 rect.top=0;

 while(ShowCursor(FALSE)==FALSE);

// HWND hWndS=CreateWindow("Dizzy","���� ��� Dizzy",WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_VISIBLE,rect.left,rect.top,rect.right,rect.bottom,hWnd,0,hProjectInstance,NULL);
 HWND hWndS=CreateWindow("Dizzy","���� ��� Dizzy",WS_POPUP|WS_VISIBLE,rect.left,rect.top,rect.right,rect.bottom,hWnd,0,hProjectInstance,NULL);
 SetWindowPos(hWndS,HWND_TOPMOST,0,0,0,SWP_NOMOVE|SWP_NOREDRAW,SWP_NOSIZE);

 timeBeginPeriod(1);
 MMRESULT res=timeSetEvent(static_cast<UINT>(1000/FPS),1,TimerEvent,0,TIME_PERIODIC);
 if (res!=NULL)
 {
  while(GetMessage(&msg,NULL,0,0))
  {
   TranslateMessage(&msg);
   DispatchMessage(&msg);
  }
  timeKillEvent(res);
 }
 else MessageBox(NULL,"�� ������� ������� �������������� ������!","������",MB_OK);
 timeEndPeriod(1);
 while(ShowCursor(TRUE)==FALSE);
 return(msg.wParam);
}

//----------------------------------------------------------------------------------------------------
//������� ��������������� �������
//----------------------------------------------------------------------------------------------------
void CALLBACK TimerEvent(UINT uTimerID,UINT uMsg,DWORD_PTR dwUser,DWORD_PTR dw1,DWORD_PTR dw2)
{
 LARGE_INTEGER current_time;
 QueryPerformanceCounter(&current_time);
 cWnd_Main.Processing();
 start_time=current_time;
}
