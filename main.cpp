//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include <windows.h>
#include <stdint.h>
#include "cwnd_main.h"

//****************************************************************************************************
//глобальные переменные
//****************************************************************************************************
static const double FPS=30;//частота кадров

HINSTANCE hProjectInstance;
CWnd_Main cWnd_Main;

//----------------------------------------------------------------------------------------------------
//главная функция программы
//----------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevstance,LPSTR lpstrCmdLine,int nCmdShow)
{
 hProjectInstance=hInstance;
 MSG msg;
 CWnd_Main::Register();

 HWND hWnd=GetDesktopWindow();
 RECT rect;
 //GetWindowRect(hWnd,&rect);
 rect.left=0;
 rect.right=320;
 rect.bottom=240;
 rect.top=0;

 
 HWND hWndS=CreateWindow("Dizzy","Игра про Dizzy",WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX|WS_VISIBLE,rect.left,rect.top,rect.right,rect.bottom,hWnd,0,hProjectInstance,NULL);
// HWND hWndS=CreateWindow("Dizzy","Игра про Dizzy",WS_POPUP|WS_VISIBLE,rect.left,rect.top,rect.right,rect.bottom,hWnd,0,hProjectInstance,NULL);
 //SetWindowPos(hWndS,HWND_TOPMOST,0,0,0,SWP_NOMOVE|SWP_NOREDRAW,SWP_NOSIZE);

 //while(ShowCursor(FALSE)==FALSE);

 LARGE_INTEGER start_time;
 LARGE_INTEGER current_time;
 LARGE_INTEGER CounterFrequency;
 QueryPerformanceFrequency(&CounterFrequency);
 double d_CounterFrequency=(double)CounterFrequency.QuadPart;
 QueryPerformanceCounter(&start_time);

 while(1)
 {
  while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
  {
   if (msg.message==WM_QUIT) break;
   TranslateMessage(&msg);
   DispatchMessage(&msg);
  }
  if (msg.message==WM_QUIT) break;
  //делаем синхронизацию по таймеру
  while(1)
  {
   QueryPerformanceCounter(&current_time);
   double delta_time=(double)(current_time.QuadPart-start_time.QuadPart);
   if (delta_time<0) 
   {
    start_time=current_time;
    continue;
   }
   if (delta_time<d_CounterFrequency/FPS) continue;
   break;
  }
  QueryPerformanceCounter(&start_time);
  cWnd_Main.Processing();
 }
 //while(ShowCursor(TRUE)==FALSE);
 return(msg.wParam);
}
