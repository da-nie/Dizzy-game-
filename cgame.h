#ifndef C_GAME_H
#define C_GAME_H

//****************************************************************************************************
//����� ����
//****************************************************************************************************

//****************************************************************************************************
//������������ ����������
//****************************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>

#include "ivideo.h"
#include "cfontprinter.h"
#include "csprite.h"
#include "ipart.h"
#include "iconditionalexpression.h"
#include "cgamestate.h"

//****************************************************************************************************
//����������������
//****************************************************************************************************

//****************************************************************************************************
//���������
//****************************************************************************************************

//****************************************************************************************************
//��������������� ����������
//****************************************************************************************************

//****************************************************************************************************
//����� ����
//****************************************************************************************************
class CGame
{
 public:
  //-������������---------------------------------------------------------------------------------------
  //-���������------------------------------------------------------------------------------------------
  //-���������------------------------------------------------------------------------------------------
  static const int32_t DIZZY_WIDTH=25;
  static const int32_t DIZZY_HEIGHT=22;
    
  static const int32_t SCREEN_WIDTH=320;
  static const int32_t SCREEN_HEIGHT=240;

  static const int32_t TILE_WIDTH=16;//������ �����
  static const int32_t TILE_HEIGHT=16;//������ �����
  static const int32_t TILE_BORDER_WIDTH=1;//������ �����
  static const int32_t TILE_BORDER_HEIGHT=1;//������ �����  
  static const int32_t TILE_WITH_BORDER_WIDTH=TILE_WIDTH+TILE_BORDER_WIDTH+TILE_BORDER_WIDTH;//������ ����� � ������
  static const int32_t TILE_WITH_BORDER_HEIGHT=TILE_HEIGHT+TILE_BORDER_HEIGHT+TILE_BORDER_HEIGHT;//������ ����� � ������

  static const int32_t USE_DELAY_COUNTER_MAX_VALUE=10;//������������ ��������� �������� �������� �� ���������� ������� ������ "������������"
 private:
  //-����������-----------------------------------------------------------------------------------------

  //�����  

  int32_t Map_X;//���������� ������ �������� ���� �����
  int32_t Map_Y;

  CSprite cSprite_Dizzy;//������ �����
  CSprite cSprite_Frame;//�����

  CSprite cSprite_Tiles;//�����
  CSprite cSprite_TilesBarrier;//��������������� ������
  
  int32_t X;//����������
  int32_t Y;

  int32_t dX;//��������
  int32_t dY;

  int32_t FrameFall;
  int32_t FrameJumpUp;
  int32_t FrameJumpLeft;
  int32_t FrameJumpRight;

  //������ ��������
  enum MOVE
  {
   MOVE_STOP,
   MOVE_LEFT,
   MOVE_RIGHT,
   MOVE_JUMP,
   MOVE_JUMP_LEFT,
   MOVE_JUMP_RIGHT,
  };

  bool MoveControl;//��������� �� Dizzy

  struct SFrame
  {   
   MOVE Move;//����� ��������
   int32_t ImageFrame;//����� ����� � �����������
   SFrame *sFrame_Next_Ptr;//��������� �� ��������� ����
   bool EndFrame;//�������� �� ���� ��������� ������
   
   SFrame(int32_t image_frame,MOVE move,bool end_frame=false,SFrame *next_ptr=NULL)
   { 
    Move=move;
	ImageFrame=image_frame;
	sFrame_Next_Ptr=next_ptr;
	EndFrame=end_frame;
   }
  };
  
  SFrame *sFrame_Stop_Ptr;
  SFrame *sFrame_MoveLeft_Ptr;
  SFrame *sFrame_MoveRight_Ptr;
  SFrame *sFrame_Jump_Ptr;
  SFrame *sFrame_JumpLeft_Ptr;
  SFrame *sFrame_JumpRight_Ptr;

  SFrame *sFrame_Ptr;

  std::vector<SFrame> sFrame_Array;//����� ������ ��� ��������

  int32_t SmallTickCounter;//������� ������ �����
  
  std::vector<std::shared_ptr<IConditionalExpression> > ConditionalExpression;//����� �������� ��������� ������� ������
  std::shared_ptr<CFontPrinter> cFontPrinter_Ptr;//��������� �� ����� ������ �� ��������

  CGameState cGameState;//��������� ����

  uint32_t UseDelayCounter;//������� �� ���������� ������� ������ "������������"
 public:
  //-�����������----------------------------------------------------------------------------------------
  CGame(void);
  //-����������-----------------------------------------------------------------------------------------
  ~CGame();
 public:
  //-�������� �������-----------------------------------------------------------------------------------
  void OnTimer(bool left,bool right,bool up,bool down,bool fire,IVideo *iVideo_Ptr);//��������� �������  
 private:
  //-�������� �������-----------------------------------------------------------------------------------  
  void OnPaint(IVideo *iVideo_Ptr);//���������� ��������  
  void KeyboardControl(bool left,bool right,bool up,bool down,bool fire);//���������� �� ����������
  void PressUse(void);//������ ������ "������������"
  void Processing(IVideo *iVideo_Ptr);//��������� �������� ����
  bool IsCollizionLegs(IVideo *iVideo_Ptr,int32_t xp,int32_t yp);//��������� ������������ � ������� ��� �����
  bool IsCollizionBody(IVideo *iVideo_Ptr,int32_t xp,int32_t yp);//��������� ������������ � ������� ������� �����
  bool LoadMap(const std::string &file_name);//��������� �����
  void DrawBarrier(IVideo *iVideo_Ptr);//���������� ��������
  void DrawMap(IVideo *iVideo_Ptr);//���������� �����
  void DrawFirstPlaneMap(IVideo *iVideo_Ptr);//���������� ����� ��������� �����
  void DrawItemMap(IVideo *iVideo_Ptr);//���������� ����� ���������
  void ClearScreen(IVideo *iVideo_Ptr,uint32_t color);//�������� �����
  void CreateConditionalExpression(void);//������� �������� ���������
  void PutMessage(CGameState::SMessage &sMessage,IVideo *iVideo_Ptr);//����� ���������
};

#endif