//****************************************************************************************************
//������������ ����������
//****************************************************************************************************
#include "cwnd_main.h"

//****************************************************************************************************
//���������� ����������
//****************************************************************************************************

//****************************************************************************************************
//���������
//****************************************************************************************************

//****************************************************************************************************
//����������������
//****************************************************************************************************


//****************************************************************************************************
//����� ���������
//****************************************************************************************************

BEGIN_MESSAGE_MAP(CWnd_Main,CWnd)
 ON_WM_PAINT()
 ON_WM_CREATE()
 ON_WM_DESTROY()
 ON_WM_TIMER() 
 ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

//****************************************************************************************************
//����������� � ����������
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//�����������
//----------------------------------------------------------------------------------------------------
CWnd_Main::CWnd_Main(void)
{ 
 iVideo_Ptr.reset(IVideo::CreateNewCVideoSoftware(CGame::SCREEN_WIDTH,CGame::SCREEN_HEIGHT));
 iVideo_Ptr->Init();

 cGame_Ptr.reset(new CGame()); 
}
//----------------------------------------------------------------------------------------------------
//����������
//----------------------------------------------------------------------------------------------------
CWnd_Main::~CWnd_Main()
{
}

//****************************************************************************************************
//�������� �������
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************************************
//������� ��������� ���������
//****************************************************************************************************


//****************************************************************************************************
//�������� �������
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//�������� ����
//----------------------------------------------------------------------------------------------------
afx_msg int CWnd_Main::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
 CWnd::OnCreate(lpCreateStruct);

 //��������� ������ ���� �� �������� ���������� �������
 RECT rect;
 rect.left=0;
 rect.right=CGame::SCREEN_WIDTH*2;
 rect.top=0;
 rect.bottom=CGame::SCREEN_HEIGHT*2;
 AdjustWindowRect(&rect,WS_OVERLAPPED|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,FALSE);

 CRect cRect;
 GetWindowRect(&cRect);
 cRect.right=cRect.left+rect.right-rect.left;
 cRect.bottom=cRect.top+rect.bottom-rect.top;
 
 MoveWindow(&cRect,TRUE);
 SetTimer(ID_TIMER_MAIN,30,NULL);
 return(0);
}
//----------------------------------------------------------------------------------------------------
//����������� ����
//----------------------------------------------------------------------------------------------------
afx_msg void CWnd_Main::OnDestroy(void)
{
 KillTimer(ID_TIMER_MAIN);
 CWnd::OnDestroy();
}
//----------------------------------------------------------------------------------------------------
//������� ����������� ����
//----------------------------------------------------------------------------------------------------
afx_msg void CWnd_Main::OnPaint(void)
{ 
 //�������� ���������
 uint32_t width;
 uint32_t height;
 iVideo_Ptr->GetScreenSize(width,height);
 void *vptr;
 iVideo_Ptr->GetVideoPointer(vptr);
 uint32_t linesize;
 iVideo_Ptr->GetLineSize(linesize);

 CPaintDC dc(this);
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
 StretchDIBits(dc.m_hDC,0,0,width*2,height*2,0,0,width,height,vptr,&info,DIB_RGB_COLORS,SRCCOPY);
 CWnd::OnPaint();
}
//----------------------------------------------------------------------------------------------------
//������� �������
//----------------------------------------------------------------------------------------------------
afx_msg void CWnd_Main::OnTimer(UINT nIDEvent)
{
 if (nIDEvent!=ID_TIMER_MAIN) 
 {
  CWnd::OnTimer(nIDEvent);
  return;
 }
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
 InvalidateRect(NULL,FALSE);
}
//----------------------------------------------------------------------------------------------------
//������� ������� ���� ����
//----------------------------------------------------------------------------------------------------
afx_msg BOOL CWnd_Main::OnEraseBkgnd(CDC *pDC)
{
 return(TRUE);
}

