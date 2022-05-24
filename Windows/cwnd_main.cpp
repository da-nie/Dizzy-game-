//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cwnd_main.h"

//****************************************************************************************************
//глобальные переменные
//****************************************************************************************************

extern HINSTANCE hProjectInstance;
extern CWnd_Main cWnd_Main;

LPDIRECTDRAW lpdd_old=NULL;
LPDIRECTDRAW7 lpdd=NULL;
DDSURFACEDESC2 ddsd;
LPDIRECTDRAWSURFACE7 lpddsprimary=NULL;
LPDIRECTDRAWSURFACE7 lpddssecondary=NULL;

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
  case WM_ACTIVATE:
  {
   cWnd_Main.Activate(hWnd,wParam,lParam);
   return(0);
  }
  case WM_KEYDOWN:
  {
   cWnd_Main.KeyDown(hWnd,wParam,lParam);
   return(0);
  }
  case WM_ERASEBKGND:
  {
   return(0);
  }
  case WM_TIMER:
  {
   cWnd_Main.Processing();
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
 //инициализируем DirectDraw
 lpdd=NULL;
 lpddsprimary=NULL;
 lpddssecondary=NULL;
 if (FAILED(DirectDrawCreate(NULL,&lpdd_old,NULL)))
 {
  MessageBox(hWnd,"Ошибка инициализации DirectDraw7","ERROR",MB_OK);
  DestroyWindow(hWnd);
  return;
 }
 lpdd_old->QueryInterface(IID_IDirectDraw7,(void **)&lpdd);
 lpdd_old->Release();

 Enabled=cGame_Ptr->Init(iVideo_Ptr.get());
}
//----------------------------------------------------------------------------------------------------
//уничтожения окна
//----------------------------------------------------------------------------------------------------
void CWnd_Main::Destroy(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 if (lpdd!=NULL) lpdd->Release();
 lpdd=NULL;
 if (Active==true)
 {
  if (lpddsprimary!=NULL) lpddsprimary->Release();
 }
 Active=false;
}
//----------------------------------------------------------------------------------------------------
//смена активности окна
//----------------------------------------------------------------------------------------------------
void CWnd_Main::Activate(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 if ((LOWORD(wParam)==WA_ACTIVE || LOWORD(wParam)==WA_CLICKACTIVE) && Active==false) 
 {
  lpdd->SetCooperativeLevel(hWnd,DDSCL_FULLSCREEN|DDSCL_ALLOWMODEX|DDSCL_EXCLUSIVE|DDSCL_ALLOWREBOOT);
  lpdd->SetDisplayMode(CGame::SCREEN_WIDTH*2,CGame::SCREEN_HEIGHT*2,32,0,0);
  memset(&ddsd,0,sizeof(ddsd));
  ddsd.dwSize=sizeof(DDSURFACEDESC2);
  ddsd.dwFlags=DDSD_CAPS|DDSD_BACKBUFFERCOUNT;
  ddsd.dwBackBufferCount=1;
  ddsd.ddsCaps.dwCaps=DDSCAPS_COMPLEX|DDSCAPS_FLIP|DDSCAPS_PRIMARYSURFACE;
  lpdd->CreateSurface(&ddsd,&lpddsprimary,NULL);
  ddsd.ddsCaps.dwCaps=DDSCAPS_BACKBUFFER;
  lpddsprimary->GetAttachedSurface(&ddsd.ddsCaps,&lpddssecondary);
  Active=true;
 }
 if (LOWORD(wParam)==WA_INACTIVE && Active==true) 
 {
  if (lpddsprimary!=NULL) lpddsprimary->Release();
  Active=false;
 }
}
//----------------------------------------------------------------------------------------------------
//обработка нажатия клавиш
//----------------------------------------------------------------------------------------------------
void CWnd_Main::KeyDown(HWND hWnds,WPARAM wParam,LPARAM lParam)
{
 if (GetAsyncKeyState(VK_ESCAPE)&32768) DestroyWindow(hWnd);
}
//----------------------------------------------------------------------------------------------------
//рисование окна
//----------------------------------------------------------------------------------------------------
void CWnd_Main::Paint(HWND hWnds,WPARAM wParam,LPARAM lParam)
{ 
 if (Active==false) return;

 //вызываем отрисовку
 uint32_t width;
 uint32_t height;
 iVideo_Ptr->GetScreenSize(width,height);
 void *iptr;
 iVideo_Ptr->GetVideoPointer(iptr);
 uint32_t linesize;
 iVideo_Ptr->GetLineSize(linesize);

 PAINTSTRUCT ps;
 BeginPaint(hWnd,&ps);
 EndPaint(hWnd,&ps);

 lpddssecondary->Lock(NULL,&ddsd,DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT,NULL);
 UINT* video_buffer=(UINT*)ddsd.lpSurface;
 UINT lPitch32=ddsd.lPitch>>2;
 //рисуем с удвоением
 UINT *vptr=video_buffer;
 UINT *sptr=reinterpret_cast<UINT*>(iptr);
 for(int32_t y=0;y<CGame::SCREEN_HEIGHT;y++,sptr+=linesize)
 {
  UINT *vptrx_1=vptr;
  UINT *vptrx_2=vptr+lPitch32;
  UINT *sptrx=sptr;
  for(int32_t x=0;x<CGame::SCREEN_WIDTH;x++,sptrx++)
  {
   *(vptrx_1)=*(sptrx);
   vptrx_1++;
   *(vptrx_1)=*(sptrx);
   vptrx_1++;

   *(vptrx_2)=*(sptrx);
   vptrx_2++;
   *(vptrx_2)=*(sptrx);
   vptrx_2++;
  }
  vptr+=lPitch32;
  vptr+=lPitch32;
 }
 lpddssecondary->Unlock(NULL);
 lpddsprimary->Flip(NULL,DDFLIP_WAIT);
}

//----------------------------------------------------------------------------------------------------
//создание кадра изображения
//----------------------------------------------------------------------------------------------------
void CWnd_Main::Processing(void)
{ 
 static int32_t tick=0;
 tick++;
 tick%=2;
 if (tick==0)
 {
  Paint(hWnd,0,0);
  return;
 }

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
 //InvalidateRect(hWnd,NULL,FALSE);
 Paint(hWnd,0,0);
}