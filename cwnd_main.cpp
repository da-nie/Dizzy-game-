//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cwnd_main.h"

//****************************************************************************************************
//глобальные переменные
//****************************************************************************************************

extern HINSTANCE hProjectInstance;
extern CWnd_Main cWnd_Main;

//****************************************************************************************************
//константы
//****************************************************************************************************

//****************************************************************************************************
//макроопределения
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//зарегистировать класс окна
//----------------------------------------------------------------------------------------------------
void CWnd_Main::Register(void)
{
 WNDCLASS wc;
 wc.style=CS_HREDRAW|CS_VREDRAW;
 wc.cbClsExtra=0;
 wc.cbWndExtra=0;
 wc.hInstance=hProjectInstance;
 wc.hIcon=LoadIcon(NULL,IDI_APPLICATION);
 wc.hCursor=LoadCursor(NULL,IDC_ARROW);
 wc.hbrBackground=(HBRUSH)(COLOR_WINDOW);
 wc.lpszMenuName=NULL;
 wc.lpszClassName="Dizzy";
 wc.lpfnWndProc=(WNDPROC)WNDProc;
 RegisterClass(&wc);
}
//----------------------------------------------------------------------------------------------------
//функция обратного вызова окна
//----------------------------------------------------------------------------------------------------
long WINAPI CWnd_Main::WNDProc(HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam)
{
 switch(msg)
 {
  case WM_CREATE:
  {
   cWnd_Main.Create(hWnd,wParam,lParam);
   return(0);
  }
  case WM_DESTROY:
  {
   cWnd_Main.Destroy(hWnd,wParam,lParam);
   PostQuitMessage(0);
   return(0);
  }
  case WM_PAINT:
  {
   cWnd_Main.Paint(hWnd,wParam,lParam);
   return(0);
  }
  case WM_ERASEBKGND:
  {
   return(0);
  }
 }
 return(DefWindowProc(hWnd,msg,wParam,lParam));
}

//****************************************************************************************************
//конструктор и деструктор
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CWnd_Main::CWnd_Main(void)
{ 
 Active=false;

 iVideo_Ptr.reset(IVideo::CreateNewCVideoSoftware(CGame::SCREEN_WIDTH,CGame::SCREEN_HEIGHT));
 iVideo_Ptr->Init();

 cGame_Ptr.reset(new CGame()); 

 Enabled=false;
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CWnd_Main::~CWnd_Main()
{
}

//****************************************************************************************************
//закрытые функции
//****************************************************************************************************


//****************************************************************************************************
//открытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//создание окна
//----------------------------------------------------------------------------------------------------
void CWnd_Main::Create(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 hWnd=hWnds;
 Active=true;

 //определим размер окна по заданной клиентской области
 RECT rect;
 rect.left=0;
 rect.right=CGame::SCREEN_WIDTH*2;
 rect.top=0;
 rect.bottom=CGame::SCREEN_HEIGHT*2;
 AdjustWindowRect(&rect,WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,FALSE);
 
 RECT w_rect;
 GetWindowRect(hWnd,&w_rect);
 w_rect.right=rect.right-rect.left;
 w_rect.bottom=rect.bottom-rect.top;

 MoveWindow(hWnd,w_rect.left,w_rect.top,w_rect.right,w_rect.bottom,TRUE);

 Enabled=cGame_Ptr->Init(iVideo_Ptr.get());
}
//----------------------------------------------------------------------------------------------------
//уничтожения окна
//----------------------------------------------------------------------------------------------------
void CWnd_Main::Destroy(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 Active=false; 
}
//----------------------------------------------------------------------------------------------------
//рисование окна
//----------------------------------------------------------------------------------------------------
void CWnd_Main::Paint(HWND hWnds,WPARAM wParam,LPARAM lParam)
{ 
 if (Active==false) return;
 PAINTSTRUCT ps;
 HDC hdc=BeginPaint(hWnd,&ps);

 //вызываем отрисовку
 uint32_t width;
 uint32_t height;
 iVideo_Ptr->GetScreenSize(width,height);
 void *vptr;
 iVideo_Ptr->GetVideoPointer(vptr);
 uint32_t linesize;
 iVideo_Ptr->GetLineSize(linesize);

 BITMAPINFOHEADER bmih;
 bmih.biSize=sizeof(BITMAPINFOHEADER);
 bmih.biWidth=width;
 bmih.biHeight=-static_cast<long>(height);
 bmih.biPlanes=1;
 bmih.biBitCount=32;
 bmih.biCompression=BI_RGB;
 bmih.biSizeImage=0;
 bmih.biXPelsPerMeter=300;
 bmih.biYPelsPerMeter=300;
 bmih.biClrUsed=0;
 bmih.biClrImportant=0;
 RGBQUAD rgbq;
 BITMAPINFO info;
 rgbq.rgbBlue=1;
 rgbq.rgbGreen=0;
 rgbq.rgbRed=0;
 rgbq.rgbReserved=0;
 info.bmiHeader=bmih;
 info.bmiColors[0]=rgbq;
 StretchDIBits(hdc,0,0,width*2,height*2,0,0,width,height,vptr,&info,DIB_RGB_COLORS,SRCCOPY);
 
 EndPaint(hWnd,&ps);
}

//----------------------------------------------------------------------------------------------------
//создание кадра изображения
//----------------------------------------------------------------------------------------------------
void CWnd_Main::Processing(void)
{
 if (Active==false) return;
 if (Enabled==false) return;

 bool left=false;
 bool right=false;
 bool up=false;
 bool down=false;
 bool fire=false; 
 if (GetAsyncKeyState(VK_LEFT)&32768) left=true;
 if (GetAsyncKeyState(VK_RIGHT)&32768) right=true;
 if (GetAsyncKeyState(VK_UP)&32768) up=true;
 if (GetAsyncKeyState(VK_DOWN)&32768) down=true;
 if (GetAsyncKeyState(VK_SPACE)&32768) fire=true;
 if (GetAsyncKeyState(VK_RETURN)&32768) fire=true;
 if (GetAsyncKeyState(VK_LCONTROL)&32768) fire=true;
 if (GetAsyncKeyState(VK_RCONTROL)&32768) fire=true;
 
 cGame_Ptr->OnTimer(left,right,up,down,fire,iVideo_Ptr.get());
 InvalidateRect(hWnd,NULL,FALSE);
}