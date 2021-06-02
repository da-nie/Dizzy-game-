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
#include "csprite.h"

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
  static const int32_t BlockHeightSize=4;
  static const int32_t BlockWidthSize=4;
  static const int32_t MapWidth=320/BlockWidthSize;
  static const int32_t MapHeight=240/BlockHeightSize;
  static const int32_t DizzyWidth=25;
  static const int32_t DizzyHeight=22;
 private:
  //-����������-----------------------------------------------------------------------------------------

  //�����
  bool Map[MapHeight][MapWidth];//�����

  CSprite cSprite_Dizzy;//������ �����
  
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
   
   SFrame(int32_t image_frame,MOVE move,SFrame *next_ptr=NULL)
   { 
    Move=move;
	ImageFrame=image_frame;
	sFrame_Next_Ptr=next_ptr;
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
 public:
  //-�����������----------------------------------------------------------------------------------------
  CGame(void);
  //-����������-----------------------------------------------------------------------------------------
  ~CGame();
 public:
  //-�������� �������-----------------------------------------------------------------------------------
  void OnPaint(IVideo *iVideo_Ptr);//���������� ��������  
  void OnTimer(IVideo *iVideo_Ptr);//��������� �������  
  void KeyboardControl(bool left,bool right,bool up,bool down,bool fire);//���������� �� ����������
 private:
  //-�������� �������-----------------------------------------------------------------------------------  
  void GetMapCoord(int32_t x,int32_t y,int32_t &map_x,int32_t &map_y);//�������� ���������� �����
  bool IsCollizionDownOneBlock(IVideo *iVideo_Ptr,int32_t xp,int32_t yp);//����������, ��� ������������ ��������� �� ������ ����� � �� ���� ���� (����� ��� ������)
  bool IsCollizion(IVideo *iVideo_Ptr,int32_t xp,int32_t yp);//��������� ������������ � �������
};

#endif