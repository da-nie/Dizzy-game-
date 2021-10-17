//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include <windows.h>
#include <stdint.h>
#include <mmsystem.h>
#include "cwnd_main.h"

//****************************************************************************************************
//глобальные переменные
//****************************************************************************************************
static const double FPS=33;//частота кадров

HINSTANCE hProjectInstance;
CWnd_Main cWnd_Main;

LARGE_INTEGER start_time;

//****************************************************************************************************
//прототипы функций
//****************************************************************************************************
void CALLBACK TimerEvent(UINT uTimerID,UINT uMsg,DWORD_PTR dwUser,DWORD_PTR dw1,DWORD_PTR dw2);//функция мультимедийного таймера

//****************************************************************************************************
//реализация функций
//****************************************************************************************************

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

 timeBeginPeriod(1);
 MMRESULT res=timeSetEvent(1000/FPS,1,TimerEvent,0,TIME_PERIODIC);
 if (res!=NULL)
 {
  while(GetMessage(&msg,NULL,0,0))
  {
   TranslateMessage(&msg);
   DispatchMessage(&msg);
  }
  timeKillEvent(res);
 }
 else MessageBox(NULL,"Не удалось создать мультимедийный таймер!","Ошибка",MB_OK);
 /*
 DWORD start_time=GetTickCount();
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
   DWORD current_time=GetTickCount();
   int32_t delta_time=current_time-start_time;
   if (delta_time<0)
   {
    start_time=current_time;
    continue;
   }
   if (delta_time*FPS<1000) continue;
   break;
  }
  start_time=GetTickCount();
  cWnd_Main.Processing();
 }
 */
 timeEndPeriod(1);

 /*
 
 //timeBeginPeriod(1);
 while(GetMessage(&msg,NULL,0,0))
 {
  TranslateMessage(&msg);
  DispatchMessage(&msg);
 }
 //timeEndPeriod(1);
 return(msg.wParam);
 */

 //while(ShowCursor(FALSE)==FALSE);

 /*
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
 */
 //while(ShowCursor(TRUE)==FALSE);
 return(msg.wParam);
}

//----------------------------------------------------------------------------------------------------
//функция мультимедийного таймера
//----------------------------------------------------------------------------------------------------
void CALLBACK TimerEvent(UINT uTimerID,UINT uMsg,DWORD_PTR dwUser,DWORD_PTR dw1,DWORD_PTR dw2)
{
 LARGE_INTEGER current_time;
 QueryPerformanceCounter(&current_time);
 cWnd_Main.Processing();

 /*
 LARGE_INTEGER CounterFrequency;
 QueryPerformanceFrequency(&CounterFrequency);
 double d_CounterFrequency=(double)CounterFrequency.QuadPart;
 double delta_time=(double)(current_time.QuadPart-start_time.QuadPart);
 delta_time/=d_CounterFrequency;
 delta_time*=1000.0;

 static int time_array[256];
 static int pos=0;

 time_array[pos]=delta_time;
 pos++;

 if (pos==256)
 {
  FILE *file=fopen("time.txt","ab");
  for(size_t n=0;n<pos;n++)
  {
   fprintf(file,"delta:%i\r\n",time_array[n]);
  }
  fclose(file);
  pos=0;
 }
 */
 start_time=current_time;
}
