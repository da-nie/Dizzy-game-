#include "stdafx.h"
//------------------------------------------------------------------------------
#include "cwnd_main.h"
//------------------------------------------------------------------------------
class CWinApp_Main:public CWinApp
{
 protected:
  //-���������� ������-------------------------------------------------------
  //-������� ������----------------------------------------------------------
  //-������------------------------------------------------------------------
 public:
  //-����������� ������------------------------------------------------------
  CWinApp_Main(void);
  //-���������� ������-------------------------------------------------------
  ~CWinApp_Main();
  //-���������� ������-------------------------------------------------------
  //-���������� ������� ������-----------------------------------------------
  BOOL InitInstance(void);
  //-����� ������� ������----------------------------------------------------
  //-������� ��������� ��������� ������--------------------------------------
  //-����� ������� ������----------------------------------------------------
  //-������------------------------------------------------------------------
};
//-����������� ������--------------------------------------------------------
CWinApp_Main::CWinApp_Main(void)
{
}
//-���������� ������---------------------------------------------------------
CWinApp_Main::~CWinApp_Main()
{
}
//-���������� ������� ������-------------------------------------------------
BOOL CWinApp_Main::InitInstance(void)
{
 CWnd_Main *cWnd_Main=new CWnd_Main;
 HCURSOR hCursor=LoadStandardCursor(IDC_ARROW);
 HICON hIcon=LoadStandardIcon(IDI_APPLICATION);
 HBRUSH hBrush=(HBRUSH)COLOR_WINDOW;
 LPCSTR ClassName=AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW,hCursor,hBrush,hIcon);
 //��������� ������ ���� �� �������� ���������� �������
 RECT Rect;
 Rect.left=0;
 Rect.right=320;
 Rect.top=0;
 Rect.bottom=240;
 AdjustWindowRect(&Rect,WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,FALSE);
 cWnd_Main->CreateEx(0,ClassName,"Dizzy",WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,0,0,Rect.right-Rect.left,Rect.bottom-Rect.top,NULL,NULL);
 cWnd_Main->ShowWindow(m_nCmdShow);
 m_pMainWnd=cWnd_Main;
 return TRUE;
}
//-����� ������� ������------------------------------------------------------
//-������� ��������� ��������� ������----------------------------------------
//-����� ������� ������------------------------------------------------------
//-������--------------------------------------------------------------------
CWinApp_Main cWinApp_Main;


