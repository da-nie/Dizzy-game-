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
  static const uint32_t BLACK_COLOR=(0<<24)|(0<<16)|(0<<8)|(0<<0);//������ ����
  static const uint32_t YELLOW_COLOR=(0<<24)|(255<<16)|(255<<8)|(0<<0);//����� ���� ����

  static const uint32_t SKY_COLOR=(0<<24)|(81<<16)|(162<<8)|(243<<0);//���� ����
  static const uint32_t BLEND_COLOR=(00<<24)|(81<<16)|(162<<8)|(243<<0);//���������� ����
  static const uint8_t BLEND_COLOR_R=81;//���������� ����, ��������� R
  static const uint8_t BLEND_COLOR_G=162;//���������� ����, ��������� G
  static const uint8_t BLEND_COLOR_B=243;//���������� ����, ��������� B

  static const uint32_t NO_BARRIER_COLOR=(0x00<<24)|(0x00<<16)|(0x00<<8)|(0x00<<0);//���� ���������� �����������
  static const uint8_t NO_BARRIER_COLOR_R=0;//���� ���������� �����������, ��������� R
  static const uint8_t NO_BARRIER_COLOR_G=0;//���� ���������� �����������, ��������� G
  static const uint8_t NO_BARRIER_COLOR_B=0;//���� ���������� �����������, ��������� B

  static const int32_t TILES_ANIMATION_TICK_COUNTER_DIVIDER=7;//�������� ����� �������� ������
  static const int32_t DIZZY_ANIMATION_TICK_COUNTER_DIVIDER=3;//�������� ����� �������� �����
  static const int32_t MOVE_TICK_COUNTER_DIVIDER=7;//�������� ����� ����������� �����
  
  static const int32_t DIZZY_WIDTH=25;//������ ������� �����
  static const int32_t DIZZY_HEIGHT=22;//������ ������� �����
    
  static const int32_t SCREEN_WIDTH=320;//������ ������
  static const int32_t SCREEN_HEIGHT=240;//������ ������

  static const int32_t TILE_WIDTH=16;//������ �����
  static const int32_t TILE_HEIGHT=16;//������ �����
  static const int32_t TILE_BORDER_WIDTH=1;//������ �����
  static const int32_t TILE_BORDER_HEIGHT=1;//������ �����  
  static const int32_t TILE_WITH_BORDER_WIDTH=TILE_WIDTH+TILE_BORDER_WIDTH+TILE_BORDER_WIDTH;//������ ����� � ������
  static const int32_t TILE_WITH_BORDER_HEIGHT=TILE_HEIGHT+TILE_BORDER_HEIGHT+TILE_BORDER_HEIGHT;//������ ����� � ������

  static const int32_t USE_DELAY_COUNTER_MAX_VALUE=5;//������������ ��������� �������� �������� �� ���������� ������� ������ "������������"

  static const int32_t MAX_INVENTORY_SIZE=3;//������������ ���������� ��������� � ���������

  static const int32_t SPEED_X=2;//�������� ����� �� X
  static const int32_t SPEED_Y=2;//�������� ����� �� Y
 private:
  //-����������-----------------------------------------------------------------------------------------
	   
  int32_t Map_X;//���������� ������ �������� ���� �����
  int32_t Map_Y;

  CSprite cSprite_Dizzy;//������ �����
  CSprite cSprite_Frame;//�����

  CSprite cSprite_Tiles;//�����
  CSprite cSprite_TilesBarrier;//��������������� ������
  
  int32_t X;//���������� ����� �� ������
  int32_t Y;

  int32_t dX;//�������� �����
  int32_t dY;

  //������ �������� �����
  enum MOVE
  {
   MOVE_STOP,
   MOVE_LEFT,
   MOVE_RIGHT,
   MOVE_JUMP,
   MOVE_JUMP_LEFT,
   MOVE_JUMP_RIGHT,
  };

  bool MoveControl;//��������� �� Dizzy �������

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
  
  SFrame *sFrame_Stop_Ptr;//��������� �� ������������������ �������� "����� �����"
  SFrame *sFrame_MoveLeft_Ptr;//��������� �� ������������������ �������� "����� ��� �����"
  SFrame *sFrame_MoveRight_Ptr;//��������� �� ������������������ �������� "����� ��� ������"
  SFrame *sFrame_Jump_Ptr;//��������� �� ������������������ �������� "����� ������� �� �����"
  SFrame *sFrame_JumpLeft_Ptr;//��������� �� ������������������ �������� "����� ������� �����"
  SFrame *sFrame_JumpRight_Ptr;//��������� �� ������������������ �������� "����� ������� ������"

  SFrame *sFrame_Ptr;//��������� �� ������� ���� ��������

  std::vector<SFrame> sFrame_Array;//����� ������ ��� �������� �����

  int32_t TilesAnimationTickCounter;//������� �������� ������
  int32_t DizzyAnimationTickCounter;//������� �������� �����
  int32_t FlashTickCounter;//������� ������� ������� � ���������
  int32_t MoveTickCounter;//������� ����������� �����
  
  std::shared_ptr<CFontPrinter> cFontPrinter_Ptr;//��������� �� ����� ������ �� ��������

  CGameState cGameState;//��������� ����

  uint32_t UseDelayCounter;//������� �� ���������� ������� ������ "������������"
  
  bool InventoryMode;//����� ������ � ���������
  int32_t InventorySelectedIndex;//��������� ������� � ���������
 public:
  //-�����������----------------------------------------------------------------------------------------
  CGame(void);
  //-����������-----------------------------------------------------------------------------------------
  ~CGame();
 public:
  //-�������� �������-----------------------------------------------------------------------------------
  void OnTimer(bool left,bool right,bool up,bool down,bool fire,IVideo *iVideo_Ptr);//��������� �������  
  bool Init(IVideo *iVideo_Ptr);//�������������
 private:
  //-�������� �������-----------------------------------------------------------------------------------  
  void OnPaint(IVideo *iVideo_Ptr);//���������� ��������  
  void KeyboardControl(bool left,bool right,bool up,bool down,bool fire);//���������� �� ����������
  void PressUse(void);//������ ������ "������������"
  void DizzyAnimation(void);//��������� �������� �����
  void DizzyMoveProcessing(IVideo *iVideo_Ptr);//��������� �������� �����
  void TilesAnimation(void);//�������� ���� ������
  void ConditionalProcessing(void);//��������� ��������� �������
  void Processing(IVideo *iVideo_Ptr);//��������� �������� ����
  bool IsCollizionLegs(IVideo *iVideo_Ptr,int32_t xp,int32_t yp);//��������� ������������ � ������� ��� �����
  bool IsCollizionBody(IVideo *iVideo_Ptr,int32_t xp,int32_t yp);//��������� ������������ � ������� ������� �����
  bool LoadMap(const std::string &file_name);//��������� �����
  void DrawBarrier(IVideo *iVideo_Ptr);//���������� ��������
  void DrawMap(IVideo *iVideo_Ptr);//���������� �����
  void DrawFirstPlaneMap(IVideo *iVideo_Ptr);//���������� ����� ��������� �����
  void DrawItemMap(IVideo *iVideo_Ptr);//���������� ����� ���������
  void PutMessage(CGameState::SMessage &sMessage,IVideo *iVideo_Ptr);//����� ���������
  void PutFrame(int32_t x,int32_t y,int32_t text_width,int32_t text_height,IVideo *iVideo_Ptr);//���������� ����� � �������� ���������� ����� ��� ������ (x,y,text_width,text_height - ���� ������ ������)
  void PutInventory(IVideo *iVideo_Ptr);//������� ���������
  void SetDescription(const std::string &name,const std::string &description);//������ ��������
  void PushInventory(std::shared_ptr<IPart> iPart_Ptr);//�������� � ���������
  std::shared_ptr<IPart> PopInventory(size_t index);//������ �� ���������
  bool LoadConditional(const std::string &path,std::vector<std::string> &log);//��������� ������� ����
  bool LoadConditionalFile(const std::string &file_name,std::vector<std::string> &log);//��������� ���� ������� ����
};

#endif