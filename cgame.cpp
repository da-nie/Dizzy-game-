//****************************************************************************************************
//������������ ����������
//****************************************************************************************************
#include "cgame.h"
#include "cpart.h"
#include "csyntaxanalyzer.h"
#include "system.h"
#include <algorithm>
#include <memory>

//****************************************************************************************************
//���������� ����������
//****************************************************************************************************

//****************************************************************************************************
//���������
//****************************************************************************************************
static const char MAP_FILE_NAME[]="map.gam";//��� ����� �����

//****************************************************************************************************
//����������������
//****************************************************************************************************

//****************************************************************************************************
//����������� � ����������
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//�����������
//----------------------------------------------------------------------------------------------------
CGame::CGame(void)
{ 
 cSprite_Dizzy.Load("Sprites\\dizzy.tga");
 cSprite_Dizzy.SetAlpha(0,BLEND_COLOR_R,BLEND_COLOR_G,BLEND_COLOR_B);

 cSprite_Tiles.Load("Tiles\\tiles.tga");
 cSprite_Tiles.SetAlpha(0,BLEND_COLOR_R,BLEND_COLOR_G,BLEND_COLOR_B);

 cSprite_TilesBarrier.Load("Tiles\\tiles_barrier.tga");
 cSprite_TilesBarrier.SetAlpha(0,NO_BARRIER_COLOR_R,NO_BARRIER_COLOR_G,NO_BARRIER_COLOR_B);

 cSprite_Frame.Load("Sprites\\frame.tga");
 cSprite_Frame.SetAlpha(0,BLEND_COLOR_R,BLEND_COLOR_G,BLEND_COLOR_B);

 cSprite_ScreenFrame.Load("Sprites\\screen_frame.tga");
 cSprite_Header.Load("Sprites\\header.tga");

 cFontPrinter_Ptr.reset(new CFontPrinter("Sprites\\font.tga",8,8,BLEND_COLOR_R,BLEND_COLOR_G,BLEND_COLOR_B));

 //Dizzy �����
 sFrame_Array.push_back(SFrame(0,MOVE_STOP,false,NULL));//0 
 sFrame_Array.push_back(SFrame(1,MOVE_STOP,true,NULL));//1
 //Dizzy ��� �����
 sFrame_Array.push_back(SFrame(9,MOVE_LEFT,false,NULL));//2 
 sFrame_Array.push_back(SFrame(10,MOVE_LEFT,false,NULL));//3
 sFrame_Array.push_back(SFrame(11,MOVE_LEFT,false,NULL));//4
 sFrame_Array.push_back(SFrame(12,MOVE_LEFT,false,NULL));//5
 sFrame_Array.push_back(SFrame(13,MOVE_LEFT,false,NULL));//6
 sFrame_Array.push_back(SFrame(14,MOVE_LEFT,false,NULL));//7
 sFrame_Array.push_back(SFrame(15,MOVE_LEFT,false,NULL));//8
 sFrame_Array.push_back(SFrame(16,MOVE_LEFT,true,NULL));//9
 //Dizzy ��� ������
 sFrame_Array.push_back(SFrame(17,MOVE_RIGHT,false,NULL));//10 
 sFrame_Array.push_back(SFrame(18,MOVE_RIGHT,false,NULL));//11
 sFrame_Array.push_back(SFrame(19,MOVE_RIGHT,false,NULL));//12
 sFrame_Array.push_back(SFrame(20,MOVE_RIGHT,false,NULL));//13
 sFrame_Array.push_back(SFrame(21,MOVE_RIGHT,false,NULL));//14
 sFrame_Array.push_back(SFrame(22,MOVE_RIGHT,false,NULL));//15
 sFrame_Array.push_back(SFrame(23,MOVE_RIGHT,false,NULL));//16
 sFrame_Array.push_back(SFrame(24,MOVE_RIGHT,true,NULL));//17
 //Dizzy ������� �� �����
 sFrame_Array.push_back(SFrame(2,MOVE_JUMP,false,NULL));//18 
 sFrame_Array.push_back(SFrame(3,MOVE_JUMP,false,NULL));//19
 sFrame_Array.push_back(SFrame(4,MOVE_JUMP,false,NULL));//20
 sFrame_Array.push_back(SFrame(5,MOVE_JUMP,false,NULL));//21
 sFrame_Array.push_back(SFrame(6,MOVE_JUMP,false,NULL));//22
 sFrame_Array.push_back(SFrame(7,MOVE_JUMP,false,NULL));//23
 sFrame_Array.push_back(SFrame(8,MOVE_JUMP,true,NULL));//24
 //Dizzy ������� �����
 sFrame_Array.push_back(SFrame(25,MOVE_JUMP_LEFT,false,NULL));//25
 sFrame_Array.push_back(SFrame(26,MOVE_JUMP_LEFT,false,NULL));//26
 sFrame_Array.push_back(SFrame(27,MOVE_JUMP_LEFT,false,NULL));//27
 sFrame_Array.push_back(SFrame(28,MOVE_JUMP_LEFT,false,NULL));//28
 sFrame_Array.push_back(SFrame(29,MOVE_JUMP_LEFT,false,NULL));//29
 sFrame_Array.push_back(SFrame(30,MOVE_JUMP_LEFT,false,NULL));//30
 sFrame_Array.push_back(SFrame(31,MOVE_JUMP_LEFT,true,NULL));//31
 //Dizzy ������� ������
 sFrame_Array.push_back(SFrame(32,MOVE_JUMP_RIGHT,false,NULL));//32
 sFrame_Array.push_back(SFrame(33,MOVE_JUMP_RIGHT,false,NULL));//33
 sFrame_Array.push_back(SFrame(34,MOVE_JUMP_RIGHT,false,NULL));//34
 sFrame_Array.push_back(SFrame(35,MOVE_JUMP_RIGHT,false,NULL));//35
 sFrame_Array.push_back(SFrame(36,MOVE_JUMP_RIGHT,false,NULL));//36
 sFrame_Array.push_back(SFrame(37,MOVE_JUMP_RIGHT,false,NULL));//37
 sFrame_Array.push_back(SFrame(38,MOVE_JUMP_RIGHT,true,NULL));//38

 sFrame_Stop_Ptr=&sFrame_Array[0];
 sFrame_MoveLeft_Ptr=&sFrame_Array[2];
 sFrame_MoveRight_Ptr=&sFrame_Array[10];
 sFrame_Jump_Ptr=&sFrame_Array[18];
 sFrame_JumpLeft_Ptr=&sFrame_Array[25];
 sFrame_JumpRight_Ptr=&sFrame_Array[32];
 
 sFrame_Array[0].sFrame_Next_Ptr=&sFrame_Array[1];
 sFrame_Array[1].sFrame_Next_Ptr=&sFrame_Array[0];

 sFrame_Array[2].sFrame_Next_Ptr=&sFrame_Array[3];
 sFrame_Array[3].sFrame_Next_Ptr=&sFrame_Array[4];
 sFrame_Array[4].sFrame_Next_Ptr=&sFrame_Array[5];
 sFrame_Array[5].sFrame_Next_Ptr=&sFrame_Array[6];
 sFrame_Array[6].sFrame_Next_Ptr=&sFrame_Array[7];
 sFrame_Array[7].sFrame_Next_Ptr=&sFrame_Array[8];
 sFrame_Array[8].sFrame_Next_Ptr=&sFrame_Array[9];
 sFrame_Array[9].sFrame_Next_Ptr=&sFrame_Array[2];

 sFrame_Array[10].sFrame_Next_Ptr=&sFrame_Array[11];
 sFrame_Array[11].sFrame_Next_Ptr=&sFrame_Array[12];
 sFrame_Array[12].sFrame_Next_Ptr=&sFrame_Array[13];
 sFrame_Array[13].sFrame_Next_Ptr=&sFrame_Array[14];
 sFrame_Array[14].sFrame_Next_Ptr=&sFrame_Array[15];
 sFrame_Array[15].sFrame_Next_Ptr=&sFrame_Array[16];
 sFrame_Array[16].sFrame_Next_Ptr=&sFrame_Array[17];
 sFrame_Array[17].sFrame_Next_Ptr=&sFrame_Array[10];

 sFrame_Array[18].sFrame_Next_Ptr=&sFrame_Array[19];
 sFrame_Array[19].sFrame_Next_Ptr=&sFrame_Array[20];
 sFrame_Array[20].sFrame_Next_Ptr=&sFrame_Array[21];
 sFrame_Array[21].sFrame_Next_Ptr=&sFrame_Array[22];
 sFrame_Array[22].sFrame_Next_Ptr=&sFrame_Array[23];
 sFrame_Array[23].sFrame_Next_Ptr=&sFrame_Array[24];
 sFrame_Array[24].sFrame_Next_Ptr=&sFrame_Array[18];

 sFrame_Array[25].sFrame_Next_Ptr=&sFrame_Array[26];
 sFrame_Array[26].sFrame_Next_Ptr=&sFrame_Array[27];
 sFrame_Array[27].sFrame_Next_Ptr=&sFrame_Array[28];
 sFrame_Array[28].sFrame_Next_Ptr=&sFrame_Array[29];
 sFrame_Array[29].sFrame_Next_Ptr=&sFrame_Array[30];
 sFrame_Array[30].sFrame_Next_Ptr=&sFrame_Array[31];
 sFrame_Array[31].sFrame_Next_Ptr=&sFrame_Array[25];

 sFrame_Array[32].sFrame_Next_Ptr=&sFrame_Array[33];
 sFrame_Array[33].sFrame_Next_Ptr=&sFrame_Array[34];
 sFrame_Array[34].sFrame_Next_Ptr=&sFrame_Array[35];
 sFrame_Array[35].sFrame_Next_Ptr=&sFrame_Array[36];
 sFrame_Array[36].sFrame_Next_Ptr=&sFrame_Array[37];
 sFrame_Array[37].sFrame_Next_Ptr=&sFrame_Array[38];
 sFrame_Array[38].sFrame_Next_Ptr=&sFrame_Array[32];


 sFrame_Ptr=sFrame_Stop_Ptr;
}
//----------------------------------------------------------------------------------------------------
//����������
//----------------------------------------------------------------------------------------------------
CGame::~CGame()
{
}

//****************************************************************************************************
//�������� �������
//****************************************************************************************************
//----------------------------------------------------------------------------------------------------
//������������ ��������
//----------------------------------------------------------------------------------------------------
void CGame::OnPaint(IVideo *iVideo_Ptr)
{
 //������� ���
 iVideo_Ptr->ClearScreen(SKY_COLOR);
 //������ �����
 DrawMap(iVideo_Ptr);
 //������ ��������
 DrawItemMap(iVideo_Ptr);
 //������ �����
 cSprite_Dizzy.PutSpriteItem(iVideo_Ptr,X,Y,DIZZY_WIDTH*sFrame_Ptr->ImageFrame,0,DIZZY_WIDTH,DIZZY_HEIGHT,true); 
 //������ �������� ��������� �����
 DrawFirstPlaneMap(iVideo_Ptr); 
 //������ ����� ������ ������
 DrawScreenFrame(iVideo_Ptr);
}
//----------------------------------------------------------------------------------------------------
//���������� �� ����������
//----------------------------------------------------------------------------------------------------
void CGame::KeyboardControl(bool left,bool right,bool up,bool down,bool fire)
{
 if (cGameState.InventoryMode==true)
 {
  if (UseDelayCounter==0)
  {
   if (up==true) 
   {
    cGameState.InventorySelectedIndex--;
	UseDelayCounter=USE_DELAY_COUNTER_MAX_VALUE;
   }
   if (down==true)
   {
    cGameState.InventorySelectedIndex++;
    UseDelayCounter=USE_DELAY_COUNTER_MAX_VALUE;
   }
   if (fire==true)
   {
    PressUse();
	UseDelayCounter=USE_DELAY_COUNTER_MAX_VALUE;
	cGameState.InventoryMode=false;
   }
  }
  return;
 }

 if (MoveControl==true)
 {
  if (left==true) dX=-SPEED_X;
  if (right==true) dX=SPEED_X;
  if (left==false && right==false) dX=0;
  if (up==true) 
  {
   MoveTickCounter=0;
   dY=-SPEED_Y;  
   if (dX==0) sFrame_Ptr=sFrame_Jump_Ptr;
  } 
  if (dY<0)
  {
   if (dX>0 && sFrame_Ptr->Move!=MOVE_JUMP_RIGHT) 
   {
    sFrame_Ptr=sFrame_JumpRight_Ptr;
   }
   if (dX<0 && sFrame_Ptr->Move!=MOVE_JUMP_LEFT) 
   {
    sFrame_Ptr=sFrame_JumpLeft_Ptr; 
   }
   if (dX==0 && sFrame_Ptr->Move!=MOVE_JUMP && sFrame_Ptr->Move!=MOVE_JUMP_RIGHT && sFrame_Ptr->Move!=MOVE_JUMP_LEFT)
   {
  	sFrame_Ptr=sFrame_Stop_Ptr;
   }
  }
  else
  {
   if (dX>0 && sFrame_Ptr->Move!=MOVE_RIGHT) sFrame_Ptr=sFrame_MoveRight_Ptr; 
   if (dX<0 && sFrame_Ptr->Move!=MOVE_LEFT) sFrame_Ptr=sFrame_MoveLeft_Ptr;
   if (dX==0 && dY==0 && sFrame_Ptr->Move!=MOVE_STOP) sFrame_Ptr=sFrame_Stop_Ptr;
  }
  if (sFrame_Ptr->Move==MOVE_STOP && fire==true && UseDelayCounter==0)
  {
   //���������� ��������� ��� ������ �������� � ���������
   size_t size=cGameState.ConditionalExpression.size();
   cGameState.Take.clear();   
   for(size_t n=0;n<size;n++) cGameState.ConditionalExpression[n]->Execute(X+Map_X,Y+Map_Y,DIZZY_WIDTH,DIZZY_HEIGHT,TILE_WIDTH,TILE_HEIGHT,true,false,cGameState);
   //���������� ��������� ��� ������ ������� � ���������
   size=cGameState.Take.size();
   for(size_t n=0;n<size;n++)
   {    
    PushInventory(cGameState.Take[n]);
   }  
   cGameState.InventoryMode=true;
   cGameState.InventorySelectedIndex=0;
   UseDelayCounter=USE_DELAY_COUNTER_MAX_VALUE;
  }
 }
}
//----------------------------------------------------------------------------------------------------
//������ ������ "������������"
//----------------------------------------------------------------------------------------------------
void CGame::PressUse(void)
{ 
 if (cGameState.InventorySelectedIndex!=0)//������� "������������"
 {
  size_t size=cGameState.Inventory.size();
  if (cGameState.InventorySelectedIndex>size) return;//��� ������ �������� � ���������
  //�������� ������� �� ���������
  //������������� ��������� ��������, ������ ���� ��� ��������� � ���������.
  //������� ����������� ������� �� ��� ����� ������������� � ����� �����.
  std::shared_ptr<IPart> unit=cGameState.Inventory[cGameState.InventorySelectedIndex-1];  
  //����� �������� ���������� ����� � ��������� ������� ����
  unit->BlockPosX=(X+DIZZY_WIDTH/2)-TILE_WIDTH/2+Map_X;
  unit->BlockPosY=(Y+DIZZY_HEIGHT)-TILE_HEIGHT+Map_Y;
  //���������, ����� ������� �� ����� ������������
  cGameState.UsedObject=unit;
  //��������� ������� �������������
  size_t cond_size=cGameState.ConditionalExpression.size();
  cGameState.Take.clear();  
  for(size_t m=0;m<cond_size;m++) cGameState.ConditionalExpression[m]->Execute(X+Map_X,Y+Map_Y,DIZZY_WIDTH,DIZZY_HEIGHT,TILE_WIDTH,TILE_HEIGHT,true,false,cGameState);
  //����������� ������� �� ���������
  PopInventory(cGameState.InventorySelectedIndex-1);
  //���� UsedObject ��� �����������, ��������� ������ NULL.
  if (cGameState.UsedObject.get()==NULL)//������� ��� �����������
  {
   if (unit->Enabled==true) PushInventory(unit);//������� ����� ������������� �� ��� ����� �� ����, �������, ���������� ��� ������� � ���������
  }
 }
}

//----------------------------------------------------------------------------------------------------
//��������� �������� �����
//----------------------------------------------------------------------------------------------------
void CGame::DizzyAnimation(void)
{ 
 if (DizzyAnimationTickCounter==0)
 {
  if (sFrame_Ptr->sFrame_Next_Ptr!=NULL) sFrame_Ptr=sFrame_Ptr->sFrame_Next_Ptr;
                                    else sFrame_Ptr=sFrame_Stop_Ptr;
 }
 DizzyAnimationTickCounter++;
 DizzyAnimationTickCounter%=DIZZY_ANIMATION_TICK_COUNTER_DIVIDER;
}

//----------------------------------------------------------------------------------------------------
//��������� �������� �����
//----------------------------------------------------------------------------------------------------
void CGame::DizzyMoveProcessing(IVideo *iVideo_Ptr)
{
 //������������ ������ ��������������

 MoveTickCounter++;
 MoveTickCounter%=MOVE_TICK_COUNTER_DIVIDER;

 //������� ���
 uint32_t w;
 uint32_t h;
 iVideo_Ptr->GetScreenSize(w,h);
 int32_t width=w;
 int32_t height=h;
 int32_t offset_y=cSprite_Header.GetHeight();
 height-=offset_y; 

 iVideo_Ptr->ClearScreen(NO_BARRIER_COLOR); 
 //������ ����������� 
 DrawBarrier(iVideo_Ptr);

 int32_t step_x=abs(dX);
 int32_t step_y=abs(dY);
 
 int32_t dx=dX;
 int32_t dy=dY;

 while(step_x>0 || step_y>0)
 {
  if (step_x>0) step_x--;
  if (step_y>0) step_y--;
    
  int32_t last_x=X;
  int32_t last_y=Y;
  
  if (dx>0) X++;
  if (dx<0) X--;

  if (IsCollizionLegs(iVideo_Ptr,X,Y)==true || IsCollizionBody(iVideo_Ptr,X,Y)==true)//������������� ������������
  {
   if (IsCollizionBody(iVideo_Ptr,X,Y)==false)//����������� �� ���� �������
   {
    //��������� ����� �� ������� ��� �����������
    while(IsCollizionLegs(iVideo_Ptr,X,Y)==true) Y--;
   }
   else
   {
    X=last_x;
    dx=0;
	//dX=0;//TODO: ���� ��� �������, ����� �� ������ ���������� ������������� ����� ���� ������.
   }
  }

  if (dy>0) Y++;
  if (dy<0) Y--;
  if (IsCollizionLegs(iVideo_Ptr,X,Y)==true || IsCollizionBody(iVideo_Ptr,X,Y)==true)//������������� ������������
  {
   Y=last_y;
   dy=0;
   dY=0;
  }

  bool redraw_barrier=MoveMap(width,height,offset_y);

  if (redraw_barrier==true)
  {
   iVideo_Ptr->ClearScreen(NO_BARRIER_COLOR); 
   DrawBarrier(iVideo_Ptr);
  }
 }

 if (IsCollizionLegs(iVideo_Ptr,X,Y+1)==false)//����� ������
 {
  if (MoveTickCounter==0)
  {
   if (dY<SPEED_Y) dY++;
  }
  MoveControl=false;
 }
 else
 {
  if (sFrame_Ptr->Move==MOVE_JUMP_RIGHT || sFrame_Ptr->Move==MOVE_JUMP_LEFT)//����� ������ ������ �����������
  {
   if (sFrame_Ptr->EndFrame==true) MoveControl=true;//������������� ���������
  }
  else MoveControl=true;
 }
}

//----------------------------------------------------------------------------------------------------
//�������� ���� ������
//----------------------------------------------------------------------------------------------------
void CGame::TilesAnimation(void)
{
 TilesAnimationTickCounter++;
 TilesAnimationTickCounter%=TILES_ANIMATION_TICK_COUNTER_DIVIDER;

 //��������� ��������
 if (TilesAnimationTickCounter==0)
 { 
  size_t size=cGameState.Map.size();
  for(size_t n=0;n<size;n++) cGameState.Map[n]->AnimationTiles();
 }
}
//----------------------------------------------------------------------------------------------------
//��������� ��������� �������
//----------------------------------------------------------------------------------------------------
void CGame::ConditionalProcessing(void)
{
 size_t size=cGameState.ConditionalExpression.size();
 cGameState.Take.clear(); 
 for(size_t n=0;n<size;n++) cGameState.ConditionalExpression[n]->Execute(X+Map_X,Y+Map_Y,DIZZY_WIDTH,DIZZY_HEIGHT,TILE_WIDTH,TILE_HEIGHT,false,true,cGameState);
}
//----------------------------------------------------------------------------------------------------
//��������� ��������� ������� �����
//----------------------------------------------------------------------------------------------------
void CGame::DizzyEnergyProcessing(IVideo *iVideo_Ptr)
{
 if (cGameState.Energy==0)//����� �����
 {
  cGameState.AddMessage("����� �����!\\�� �������� �����",100,120);
  //���� ��������� ����� ��������������
  float min_distance=0;
  int32_t y=0;
  int32_t x=0;  
  size_t size=cGameState.Map.size();
  bool first=true;
  for(size_t n=0;n<size;n++)
  {
   std::shared_ptr<IPart> iPart_Ptr=cGameState.Map[n];
   if (iPart_Ptr->Name.compare("RESPAWN")!=0) continue;

   float dx=((X+Map_X)-iPart_Ptr->BlockPosX)/TILE_WIDTH;
   float dy=((Y+Map_Y)-iPart_Ptr->BlockPosY)/TILE_HEIGHT;
   float distance=dx*dx+dy*dy;
   if (first==true || min_distance>distance)
   {
    min_distance=distance;
	x=iPart_Ptr->BlockPosX;
	y=iPart_Ptr->BlockPosY;
   }
   first=false;
  }
  cGameState.Energy=100;
  X=x-Map_X;
  Y=y-Map_Y;
  dX=0;
  dY=0;
  sFrame_Ptr=sFrame_Stop_Ptr;
  //���������� �����
  uint32_t w;
  uint32_t h;
  iVideo_Ptr->GetScreenSize(w,h);
  int32_t width=w;
  int32_t height=h;
  int32_t offset_y=cSprite_Header.GetHeight();
  height-=offset_y; 
  while(1) 
  {
   if (MoveMap(width,height,offset_y)==false) break;
  }
 }
}


//----------------------------------------------------------------------------------------------------
//��������� �������� ����
//----------------------------------------------------------------------------------------------------
void CGame::Processing(IVideo *iVideo_Ptr)
{
 DizzyAnimation();//��������� �������� �����
 DizzyMoveProcessing(iVideo_Ptr);//��������� ��������� �������� �����
 TilesAnimation();//��������� �������� ���� ������
 ConditionalProcessing();//��������� ��������� �������
 DizzyEnergyProcessing(iVideo_Ptr);
}

//----------------------------------------------------------------------------------------------------
//��������� ������������ � ������� ��� �����
//----------------------------------------------------------------------------------------------------
bool CGame::IsCollizionLegs(IVideo *iVideo_Ptr,int32_t xp,int32_t yp)
{
 return(cSprite_Dizzy.IsCollizionSpriteItem(iVideo_Ptr,xp,yp,DIZZY_WIDTH*39,0,DIZZY_WIDTH,DIZZY_HEIGHT,true,0,0,0)); 
}
//----------------------------------------------------------------------------------------------------
//��������� ������������ � ������� ������� �����
//----------------------------------------------------------------------------------------------------
bool CGame::IsCollizionBody(IVideo *iVideo_Ptr,int32_t xp,int32_t yp)
{
 return(cSprite_Dizzy.IsCollizionSpriteItem(iVideo_Ptr,xp,yp,DIZZY_WIDTH*40,0,DIZZY_WIDTH,DIZZY_HEIGHT,true,0,0,0)); 
}
//----------------------------------------------------------------------------------------------------
//���������� ��������
//----------------------------------------------------------------------------------------------------
void CGame::DrawBarrier(IVideo *iVideo_Ptr)
{
 //������ ��� � �������������� ���������
 CSprite &tiles=cSprite_TilesBarrier;

 auto drawing_barrier_function=[this,&tiles,&iVideo_Ptr](std::shared_ptr<IPart> iPart_Ptr)
 { 
  if (iPart_Ptr->Barrier==false) return;//��������� ������ ������������� �������
  if (iPart_Ptr->InInventory==true) return;//�������� � ��������� �� ���������
  if (iPart_Ptr->Enabled==false) return;//������� ���������

  int32_t block_x=iPart_Ptr->BlockPosX;
  int32_t block_y=iPart_Ptr->BlockPosY;

  int32_t screen_x=block_x-Map_X;
  int32_t screen_y=block_y-Map_Y;

  size_t tile_index=iPart_Ptr->cTilesSequence.GetCurrentIndex();
  CTile &cTile=iPart_Ptr->cTilesSequence.GetTile(tile_index);

  int32_t tx=cTile.X*TILE_WITH_BORDER_WIDTH+TILE_BORDER_WIDTH;
  int32_t ty=cTile.Y*TILE_WITH_BORDER_HEIGHT+TILE_BORDER_HEIGHT;

  tiles.PutSpriteItem(iVideo_Ptr,screen_x,screen_y,tx,ty,TILE_WIDTH,TILE_HEIGHT,true);
 };
 std::for_each(cGameState.Map.begin(),cGameState.Map.end(),drawing_barrier_function);
}
//----------------------------------------------------------------------------------------------------
//���������� �����
//----------------------------------------------------------------------------------------------------
void CGame::DrawMap(IVideo *iVideo_Ptr)
{
 //������ ���
 CSprite &tiles=cSprite_Tiles;

 auto drawing_function=[this,&tiles,&iVideo_Ptr](std::shared_ptr<IPart> iPart_Ptr)
 { 
  if (iPart_Ptr->FirstPlane==true) return;//�������� ���� ��������� ��������
  if (iPart_Ptr->Item==true) return;//�������� ��������� ��������
  if (iPart_Ptr->InInventory==true) return;//�������� � ��������� �� ���������
  if (iPart_Ptr->Enabled==false) return;//������� ���������

  int32_t block_x=iPart_Ptr->BlockPosX;
  int32_t block_y=iPart_Ptr->BlockPosY;

  int32_t screen_x=block_x-Map_X;
  int32_t screen_y=block_y-Map_Y;

  size_t tile_index=iPart_Ptr->cTilesSequence.GetCurrentIndex();
  CTile &cTile=iPart_Ptr->cTilesSequence.GetTile(tile_index);

  int32_t tx=cTile.X*TILE_WITH_BORDER_WIDTH+TILE_BORDER_WIDTH;
  int32_t ty=cTile.Y*TILE_WITH_BORDER_HEIGHT+TILE_BORDER_HEIGHT;

  tiles.PutSpriteItem(iVideo_Ptr,screen_x,screen_y,tx,ty,TILE_WIDTH,TILE_HEIGHT,true);
 };
 std::for_each(cGameState.Map.begin(),cGameState.Map.end(),drawing_function);
}
//----------------------------------------------------------------------------------------------------
//���������� ����� ��������� �����
//----------------------------------------------------------------------------------------------------
void CGame::DrawFirstPlaneMap(IVideo *iVideo_Ptr)
{
 //������ ���
 CSprite &tiles=cSprite_Tiles;

 auto drawing_function=[this,&tiles,&iVideo_Ptr](std::shared_ptr<IPart> iPart_Ptr)
 { 
  if (iPart_Ptr->FirstPlane==false) return;//����� ��������� ������ �������� ����
  if (iPart_Ptr->InInventory==true) return;//�������� � ��������� �� ���������
  if (iPart_Ptr->Enabled==false) return;//������� ���������

  int32_t block_x=iPart_Ptr->BlockPosX;
  int32_t block_y=iPart_Ptr->BlockPosY;

  int32_t screen_x=block_x-Map_X;
  int32_t screen_y=block_y-Map_Y;

  size_t tile_index=iPart_Ptr->cTilesSequence.GetCurrentIndex();
  CTile &cTile=iPart_Ptr->cTilesSequence.GetTile(tile_index);

  int32_t tx=cTile.X*TILE_WITH_BORDER_WIDTH+TILE_BORDER_WIDTH;
  int32_t ty=cTile.Y*TILE_WITH_BORDER_HEIGHT+TILE_BORDER_HEIGHT;

  tiles.PutSpriteItem(iVideo_Ptr,screen_x,screen_y,tx,ty,TILE_WIDTH,TILE_HEIGHT,true);
 };
 std::for_each(cGameState.Map.begin(),cGameState.Map.end(),drawing_function);
}

//----------------------------------------------------------------------------------------------------
//���������� ����� ���������
//----------------------------------------------------------------------------------------------------
void CGame::DrawItemMap(IVideo *iVideo_Ptr)
{
 //������ ���
 CSprite &tiles=cSprite_Tiles;

 auto drawing_function=[this,&tiles,&iVideo_Ptr](std::shared_ptr<IPart> iPart_Ptr)
 { 
  if (iPart_Ptr->Item==false) return;//����� ��������� ������ ��������
  if (iPart_Ptr->InInventory==true) return;//�������� � ��������� �� ���������
  if (iPart_Ptr->Enabled==false) return;//������� ���������

  int32_t block_x=iPart_Ptr->BlockPosX;
  int32_t block_y=iPart_Ptr->BlockPosY;

  int32_t screen_x=block_x-Map_X;
  int32_t screen_y=block_y-Map_Y;

  size_t tile_index=iPart_Ptr->cTilesSequence.GetCurrentIndex();
  CTile &cTile=iPart_Ptr->cTilesSequence.GetTile(tile_index);

  int32_t tx=cTile.X*TILE_WITH_BORDER_WIDTH+TILE_BORDER_WIDTH;
  int32_t ty=cTile.Y*TILE_WITH_BORDER_HEIGHT+TILE_BORDER_HEIGHT;

  tiles.PutSpriteItem(iVideo_Ptr,screen_x,screen_y,tx,ty,TILE_WIDTH,TILE_HEIGHT,true);
 };
 std::for_each(cGameState.Map.begin(),cGameState.Map.end(),drawing_function);
}

//----------------------------------------------------------------------------------------------------
//����� ���������
//----------------------------------------------------------------------------------------------------
void CGame::PutMessage(CGameState::SMessage &sMessage,IVideo *iVideo_Ptr)
{
 size_t size=sMessage.Message.size();
 int32_t x=sMessage.ScreenX;
 int32_t y=sMessage.ScreenY;

 int32_t symbol_width=cFontPrinter_Ptr->GetFontWidth();
 int32_t symbol_height=cFontPrinter_Ptr->GetFontHeight();

 PutFrame(x,y,sMessage.InSymbolWidth,sMessage.InSymbolHeight,iVideo_Ptr);

 //������� �����
 for(size_t n=0;n<size;n++,y+=symbol_height)
 {
  cFontPrinter_Ptr->PrintAt(x,y,sMessage.Message[n],iVideo_Ptr);
 }
}
//----------------------------------------------------------------------------------------------------
//���������� ����� � �������� ���������� ����� ��� ������ (x,y,text_width,text_height - ���� ������ ������)
//----------------------------------------------------------------------------------------------------
void CGame::PutFrame(int32_t x,int32_t y,int32_t text_width,int32_t text_height,IVideo *iVideo_Ptr)
{
 static const int32_t FRAME_ANGLE_WIDTH=16;
 static const int32_t FRAME_ANGLE_HEIGHT=16;
 static const int32_t FRAME_VERTICAL_WIDTH=8;
 static const int32_t FRAME_VERTICAL_HEIGHT=8;
 static const int32_t FRAME_HORIZONTAL_WIDTH=8;
 static const int32_t FRAME_HORIZONTAL_HEIGHT=8;

 static const int32_t FRAME_VERTICAL_OFFSET_X=0;
 static const int32_t FRAME_VERTICAL_OFFSET_Y=8;

 static const int32_t FRAME_HORIZONTAL_OFFSET_X=0;
 static const int32_t FRAME_HORIZONTAL_OFFSET_Y=0;

 static const int32_t FRAME_ANGLE_LEFT_UP_OFFSET_X=FRAME_HORIZONTAL_OFFSET_X+FRAME_HORIZONTAL_WIDTH;
 static const int32_t FRAME_ANGLE_LEFT_UP_OFFSET_Y=0;

 static const int32_t FRAME_ANGLE_RIGHT_UP_OFFSET_X=FRAME_ANGLE_LEFT_UP_OFFSET_X+FRAME_ANGLE_WIDTH;
 static const int32_t FRAME_ANGLE_RIGHT_UP_OFFSET_Y=0;
 
 static const int32_t FRAME_ANGLE_LEFT_DOWN_OFFSET_X=FRAME_ANGLE_RIGHT_UP_OFFSET_X+FRAME_ANGLE_WIDTH;
 static const int32_t FRAME_ANGLE_LEFT_DOWN_OFFSET_Y=0;

 static const int32_t FRAME_ANGLE_RIGHT_DOWN_OFFSET_X=FRAME_ANGLE_LEFT_DOWN_OFFSET_X+FRAME_ANGLE_WIDTH;
 static const int32_t FRAME_ANGLE_RIGHT_DOWN_OFFSET_Y=0;

 int32_t symbol_width=cFontPrinter_Ptr->GetFontWidth();
 int32_t symbol_height=cFontPrinter_Ptr->GetFontHeight();

 int32_t width=(text_width+2)*symbol_width;
 int32_t height=(text_height+2)*symbol_height;

 int32_t rx1=x-symbol_width;
 int32_t ry1=y-symbol_height;
 int32_t rx2=rx1+width-1;
 int32_t ry2=ry1+height-1;
 //����������� �������������
 iVideo_Ptr->FillRectangle(rx1,ry1,rx2,ry2,0x00000000);
 //������ �����
 //������� ������
 cSprite_Frame.PutSpriteItem(iVideo_Ptr,rx1-FRAME_ANGLE_WIDTH,ry1-FRAME_ANGLE_HEIGHT,FRAME_ANGLE_LEFT_UP_OFFSET_X,FRAME_ANGLE_LEFT_UP_OFFSET_Y,FRAME_ANGLE_WIDTH,FRAME_ANGLE_HEIGHT,true);
 cSprite_Frame.PutSpriteItem(iVideo_Ptr,rx2,ry1-FRAME_ANGLE_HEIGHT,FRAME_ANGLE_RIGHT_UP_OFFSET_X,FRAME_ANGLE_RIGHT_UP_OFFSET_Y,FRAME_ANGLE_WIDTH,FRAME_ANGLE_HEIGHT,true);
 cSprite_Frame.PutSpriteItem(iVideo_Ptr,rx2,ry2,FRAME_ANGLE_RIGHT_DOWN_OFFSET_X,FRAME_ANGLE_RIGHT_DOWN_OFFSET_Y,FRAME_ANGLE_WIDTH,FRAME_ANGLE_HEIGHT,true);
 cSprite_Frame.PutSpriteItem(iVideo_Ptr,rx1-FRAME_ANGLE_WIDTH,ry2,FRAME_ANGLE_LEFT_DOWN_OFFSET_X,FRAME_ANGLE_LEFT_DOWN_OFFSET_Y,FRAME_ANGLE_WIDTH,FRAME_ANGLE_HEIGHT,true);
 //��������� ������������ ����� ��������
 for(int32_t fx=rx1;fx<rx2;fx+=FRAME_HORIZONTAL_WIDTH)
 {
  cSprite_Frame.PutSpriteItem(iVideo_Ptr,fx,ry1-FRAME_HORIZONTAL_HEIGHT,FRAME_HORIZONTAL_OFFSET_X,FRAME_HORIZONTAL_OFFSET_Y,FRAME_HORIZONTAL_WIDTH,FRAME_HORIZONTAL_HEIGHT,true);
  cSprite_Frame.PutSpriteItem(iVideo_Ptr,fx,ry2-1,FRAME_HORIZONTAL_OFFSET_X,FRAME_HORIZONTAL_OFFSET_Y,FRAME_HORIZONTAL_WIDTH,FRAME_HORIZONTAL_HEIGHT,true);  	  
 }
 for(int32_t fy=ry1;fy<ry2;fy+=FRAME_VERTICAL_HEIGHT)
 {
  cSprite_Frame.PutSpriteItem(iVideo_Ptr,rx1-FRAME_VERTICAL_WIDTH,fy,FRAME_VERTICAL_OFFSET_X,FRAME_VERTICAL_OFFSET_Y,FRAME_VERTICAL_WIDTH,FRAME_VERTICAL_HEIGHT,true);
  cSprite_Frame.PutSpriteItem(iVideo_Ptr,rx2-1,fy,FRAME_VERTICAL_OFFSET_X,FRAME_VERTICAL_OFFSET_Y,FRAME_VERTICAL_WIDTH,FRAME_VERTICAL_HEIGHT,true);  	  
 } 
}
//----------------------------------------------------------------------------------------------------
//������� ���������
//----------------------------------------------------------------------------------------------------
void CGame::PutInventory(IVideo *iVideo_Ptr)
{
 static const std::string header("� ������� � �����");
 static const std::string action("����� � �����");
 static const std::string comment("�� ������ ����� ��� ��������");
 static const std::string empty("� � � � �");
 
 int32_t text_width=header.length();
 if (action.length()>text_width) text_width=action.length();
 if (comment.length()>text_width) text_width=comment.length();
 if (empty.length()>text_width) text_width=empty.length();

 int32_t size=cGameState.Inventory.size();
 for(size_t n=0;n<size;n++)
 {
  int32_t l=cGameState.Inventory[n]->Description.length();
  if (text_width<l) text_width=l;
 }
 if (cGameState.InventorySelectedIndex<0) cGameState.InventorySelectedIndex+=(size+1);
 cGameState.InventorySelectedIndex%=(size+1);

 size_t text_height=8+size;
 if (size==0) text_height++;

 int32_t symbol_width=cFontPrinter_Ptr->GetFontWidth();
 int32_t symbol_height=cFontPrinter_Ptr->GetFontHeight();
 
 int32_t x=(SCREEN_WIDTH-text_width*symbol_width)/2;
 int32_t y=(SCREEN_HEIGHT-text_height*symbol_height)/2;

 PutFrame(x,y,text_width,text_height,iVideo_Ptr);

 cFontPrinter_Ptr->PrintAt(x+symbol_width*(text_width-header.length())/2,y+symbol_height*0,header,iVideo_Ptr);

 if (size==0) cFontPrinter_Ptr->PrintAt(x+symbol_width*(text_width-empty.length())/2,y+symbol_height*3,empty,iVideo_Ptr);

 for(size_t n=0;n<size;n++)
 {  
  std::string &name=cGameState.Inventory[n]->Description;
  if ((n+1)!=cGameState.InventorySelectedIndex || FlashTickCounter>=3)
  {
   cFontPrinter_Ptr->PrintAt(x+symbol_width*(text_width-name.length())/2,y+symbol_height*(n+2),name,iVideo_Ptr);
  }
 }
 
 if (cGameState.InventorySelectedIndex!=0 || FlashTickCounter>=3)
 {
  cFontPrinter_Ptr->PrintAt(x+symbol_width*(text_width-action.length())/2,y+symbol_height*(text_height-3),action,iVideo_Ptr);  
 }

 cFontPrinter_Ptr->PrintAt(x+symbol_width*(text_width-comment.length())/2,y+symbol_height*(text_height-1),comment,iVideo_Ptr);
}
//----------------------------------------------------------------------------------------------------
//�������� � ���������
//----------------------------------------------------------------------------------------------------
void CGame::PushInventory(std::shared_ptr<IPart> iPart_Ptr)
{
 if (cGameState.Inventory.size()>=MAX_INVENTORY_SIZE) return;//��������� ��������

 iPart_Ptr->PushInventory();//���������� ������ � ���������
 cGameState.Inventory.push_back(iPart_Ptr);
}
//----------------------------------------------------------------------------------------------------
//������ �� ���������
//----------------------------------------------------------------------------------------------------
std::shared_ptr<IPart> CGame::PopInventory(size_t index)
{
 std::shared_ptr<IPart> iPart_Ptr=cGameState.Inventory[index];
 cGameState.Inventory.erase(cGameState.Inventory.begin()+index);//������� ������� �� ���������
 iPart_Ptr->PopInventory();//����������� ������
 return(iPart_Ptr);
}

//----------------------------------------------------------------------------------------------------
//���������� �������� �����
//----------------------------------------------------------------------------------------------------
void CGame::DrawScreenFrame(IVideo *iVideo_Ptr)
{
 static const int32_t FRAME_WIDTH=8;
 static const int32_t FRAME_HEIGHT=8;

 static const int32_t FRAME_UNIT_OFFSET_X=11;
 static const int32_t FRAME_UNIT_OFFSET_Y=1;

 static const int32_t FRAME_ANGLE_OFFSET_X=1;
 static const int32_t FRAME_ANGLE_OFFSET_Y=1;

 cSprite_Header.Put(iVideo_Ptr,0,0,false);
 int32_t offset_y=cSprite_Header.GetHeight();
 int32_t f_width=SCREEN_WIDTH/FRAME_HEIGHT;
 int32_t f_height=(SCREEN_HEIGHT-offset_y)/FRAME_HEIGHT;
 for(size_t n=1;n<f_width-1;n++)
 {
  cSprite_ScreenFrame.PutSpriteItem(iVideo_Ptr,n*FRAME_WIDTH,offset_y,FRAME_UNIT_OFFSET_X,FRAME_UNIT_OFFSET_Y,FRAME_WIDTH,FRAME_HEIGHT,false); 
  cSprite_ScreenFrame.PutSpriteItem(iVideo_Ptr,n*FRAME_WIDTH,SCREEN_HEIGHT-FRAME_HEIGHT,FRAME_UNIT_OFFSET_X,FRAME_UNIT_OFFSET_Y,FRAME_WIDTH,FRAME_HEIGHT,false); 
 }
 for(size_t n=1;n<f_height-1;n++)
 {
  cSprite_ScreenFrame.PutSpriteItem(iVideo_Ptr,0,offset_y+n*FRAME_HEIGHT,FRAME_UNIT_OFFSET_X,FRAME_UNIT_OFFSET_Y,FRAME_WIDTH,FRAME_HEIGHT,false); 
  cSprite_ScreenFrame.PutSpriteItem(iVideo_Ptr,SCREEN_WIDTH-FRAME_WIDTH,offset_y+n*FRAME_HEIGHT,FRAME_UNIT_OFFSET_X,FRAME_UNIT_OFFSET_Y,FRAME_WIDTH,FRAME_HEIGHT,false); 
 }
 cSprite_ScreenFrame.PutSpriteItem(iVideo_Ptr,0,offset_y,FRAME_ANGLE_OFFSET_X,FRAME_ANGLE_OFFSET_Y,FRAME_WIDTH,FRAME_HEIGHT,false); 
 cSprite_ScreenFrame.PutSpriteItem(iVideo_Ptr,SCREEN_WIDTH-FRAME_WIDTH,offset_y,FRAME_ANGLE_OFFSET_X,FRAME_ANGLE_OFFSET_Y,FRAME_WIDTH,FRAME_HEIGHT,false); 
 cSprite_ScreenFrame.PutSpriteItem(iVideo_Ptr,0,SCREEN_HEIGHT-FRAME_HEIGHT,FRAME_ANGLE_OFFSET_X,FRAME_ANGLE_OFFSET_Y,FRAME_WIDTH,FRAME_HEIGHT,false); 
 cSprite_ScreenFrame.PutSpriteItem(iVideo_Ptr,SCREEN_WIDTH-FRAME_WIDTH,SCREEN_HEIGHT-FRAME_HEIGHT,FRAME_ANGLE_OFFSET_X,FRAME_ANGLE_OFFSET_Y,FRAME_WIDTH,FRAME_HEIGHT,false); 

 char str[STRING_BUFFER_SIZE];
 //������� ����
 sprintf(str,"%05i",cGameState.Score);
 cFontPrinter_Ptr->PrintAt(77,32,str,iVideo_Ptr);
 //������� �����
 //������� �������
 static const int32_t ENERGY_OFFSET_POS_X=160;//��������� ����� ������� �� X
 static const int32_t ENERGY_OFFSET_POS_Y=32;//��������� ����� ������� �� Y
 static const int32_t ENERGY_WIDTH=48;//������ ������ ����� �������
 static const int32_t ENERGY_HEIGHT=6;//������ ����� �������
 static const int32_t ENERGY_PART=3;//�� ������� ������ ������� ����� �������
 
 int32_t x1=ENERGY_OFFSET_POS_X;
 int32_t x2=ENERGY_OFFSET_POS_X+ENERGY_WIDTH*cGameState.Energy/cGameState.ENERGY_MAX_VALUE;
 int32_t y1=ENERGY_OFFSET_POS_Y;
 int32_t y2=y1+ENERGY_HEIGHT;
 int32_t part=ENERGY_WIDTH/3;
 static const int32_t ENERGY_GOOD_COLOR=(0<<24)|(64<<16)|(255<<8)|(64<<0);//���� "�������"
 static const int32_t ENERGY_NORMAL_COLOR=(0<<24)|(255<<16)|(255<<8)|(64<<0);//���� "������"
 static const int32_t ENERGY_BAD_COLOR=(0<<24)|(255<<16)|(64<<8)|(64<<0);//���� "�����"

 int32_t x_bad=x1+part;
 if (x2<x_bad) x_bad=x2;
 iVideo_Ptr->FillRectangle(x1,y1,x_bad,y2,ENERGY_BAD_COLOR);
 if (x2>x_bad)
 {
  int32_t x_normal=x1+part*2;
  if (x2<x_normal) x_normal=x2;
  iVideo_Ptr->FillRectangle(x_bad,y1,x_normal,y2,ENERGY_NORMAL_COLOR);
  if (x2>x_normal)
  {
   int32_t x_good=x2;
   iVideo_Ptr->FillRectangle(x_normal,y1,x_good,y2,ENERGY_GOOD_COLOR);
  }
 }
 //������� ���������� ��������� ���������
 sprintf(str,"%02i",cGameState.Items);
 cFontPrinter_Ptr->PrintAt(129,32,str,iVideo_Ptr);
}
//----------------------------------------------------------------------------------------------------
//��������� �����
//----------------------------------------------------------------------------------------------------
bool CGame::LoadMap(const std::string &file_name)
{
 std::ifstream file;
 file.open(file_name,std::ios_base::in|std::ios_base::binary);
 if (file.is_open()==false) return(false);
 int32_t part;
 if (file.read(reinterpret_cast<char*>(&part),sizeof(part)).fail()==true) return(false);

 for(size_t n=0;n<part;n++)
 {
  std::shared_ptr<IPart> iPart_Ptr(new CPart());
  if (iPart_Ptr->Load(file)==false) return(false);
  cGameState.Map.push_back(iPart_Ptr);
 }
 return(true);
}

//----------------------------------------------------------------------------------------------------
//��������� ������� ����
//----------------------------------------------------------------------------------------------------
bool CGame::LoadConditional(const std::string &path,std::vector<std::string> &log)
{
 cGameState.ConditionalExpression.clear();
 log.clear();
 log.push_back(std::string("����������� ����� �������"));
 std::vector<std::string> file_list;
 CreateFileList(path,file_list);
 //������������ �����
 size_t size=file_list.size();
 for(size_t n=0;n<size;n++)
 {
  std::string &file_name=file_list[n];
  //��������� ����������
  size_t length=file_name.length();
  if (length<4) continue;
  if (file_name[length-4]!='.') continue;
  if (file_name[length-3]!='t' && file_name[length-3]!='T')  continue;
  if (file_name[length-2]!='x' && file_name[length-2]!='X') continue;
  if (file_name[length-1]!='t' && file_name[length-1]!='T') continue;
  //���������� ���� �� ���������
  log.clear();
  log.push_back(std::string("����: ")+file_name);
  log.push_back("");
  if (LoadConditionalFile(path+GetPathDivider()+file_name,log)==false) return(false);//������ ��������
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//��������� ���� ������� ����
//----------------------------------------------------------------------------------------------------
bool CGame::LoadConditionalFile(const std::string &file_name,std::vector<std::string> &log)
{
 //��������� �������
 CSyntaxAnalyzer cSyntaxAnalyzer;
 std::string message;
 FILE *file=fopen(file_name.c_str(),"rb");
 std::string line;
 int32_t line_index=0;
 bool error=false;
 if (file!=NULL)
 {
  bool done=false; 	
  while(done==false)
  {
   char s;
   if (fread(&s,sizeof(char),1,file)==0)
   {
    done=true;
    s='\r';
   }
   bool new_line;
   bool res=cSyntaxAnalyzer.Processing(s,line_index,message,new_line,cGameState);
   if (res==false)
   {   	   	
   	std::string str;
   	if (line.length()!=0) str=line+" ";
   	line="";
   	str=str+message;
	log.push_back(str);
   	error=true;
    break;
   }
   if (message.length()!=0)
   {
    line=line+message;
   }
   if (new_line==true)
   {
   	if (line.length()!=0) log.push_back(std::to_string((_Longlong)line_index)+": "+line);   	 
	line_index++;
    line="";
   }  
  } 	
  fclose(file);
  //��������� ���������� ���������
  if (error==false)
  {
   log.push_back("������� ��������� �������.");
   return(true);
  }
  else return(false);//��������� ������
 }
 else 
 {
  log.push_back("�� ���� ������� ���� �������.");
  return(false);
 }
 return(true);
}

//****************************************************************************************************
//�������� �������
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//��������� �������
//----------------------------------------------------------------------------------------------------
void CGame::OnTimer(bool left,bool right,bool up,bool down,bool fire,IVideo *iVideo_Ptr)
{
 if (UseDelayCounter>0 && fire==false) UseDelayCounter--; 
 FlashTickCounter++;
 FlashTickCounter%=6;

 //�����, ���� �� ���������
 if (cGameState.Message.size()>0)//���� ���� ���������, ����� �� �������, ����� ������� ��������� �� �������
 {
  //������� ���������
  PutMessage(cGameState.Message[0],iVideo_Ptr);
  if (UseDelayCounter==0)
  {
   if (fire==true)//������� ���������
   {
    cGameState.Message.erase(cGameState.Message.begin());
	UseDelayCounter=USE_DELAY_COUNTER_MAX_VALUE;
   }
  }
 }
 else
 {
  KeyboardControl(left,right,up,down,fire);
  if (cGameState.InventoryMode==true)//������� ����� ��������� ���������
  {
   PutInventory(iVideo_Ptr);
  }
  else
  {
   Processing(iVideo_Ptr);
   OnPaint(iVideo_Ptr);
  }
 }
}
//----------------------------------------------------------------------------------------------------
//��������� ����������� �����, ���� ���������
//----------------------------------------------------------------------------------------------------
bool CGame::MoveMap(int32_t width,int32_t height,int32_t offset_y)
{
 bool update=false;
 if (X<width/4 && Map_X>=2)
 {
  Map_X-=2;
  X+=2;
  update=true;
 }
 if (X>=3*width/4)
 {
  Map_X+=2;
  X-=2;
  update=true;
 }
 if (Y>=(3*height/4+offset_y))
 {
  Y-=2;
  Map_Y+=2;
  update=true;
 }
 if (Y<(height/4+offset_y) && Map_Y>=2)
 {
  Y+=2;
  Map_Y-=2;
  update=true;
 }
 return(update);
}

//----------------------------------------------------------------------------------------------------
//�������������
//----------------------------------------------------------------------------------------------------
bool CGame::Init(IVideo *iVideo_Ptr)
{
 sFrame_Ptr=sFrame_Stop_Ptr;

 X=160;
 Y=5;

 Map_X=0;
 Map_Y=0;
 
 dX=0;
 dY=0;

 MoveControl=true;

 TilesAnimationTickCounter=0;
 DizzyAnimationTickCounter=0;
 MoveTickCounter=0;

 UseDelayCounter=0;
 FlashTickCounter=0;

 cGameState.Init();

 iVideo_Ptr->ClearScreen(BLACK_COLOR);
 //��������� �����
 cGameState.Map.clear();
 if (LoadMap(MAP_FILE_NAME)==false)
 {
  std::string message="�� ���� ������� ���� ����� "+std::string(MAP_FILE_NAME)+" !";  
  iVideo_Ptr->PutString(0,0,message.c_str(),YELLOW_COLOR);
  return(false);
 }
 //��������� �������� ���������
 std::vector<std::string> log;
 int64_t y=0;
 uint32_t width;
 uint32_t height;
 iVideo_Ptr->GetStringImageSize(" ",width,height);
 if (LoadConditional("./ScreenPlay",log)==false)
 {  
  if (log.size()<2) return(false);
  iVideo_Ptr->PutStringWithIncrementHeight(0,y,"��������� ������ ���������� �����",YELLOW_COLOR);
  iVideo_Ptr->PutStringWithIncrementHeight(0,y,log[0].c_str(),YELLOW_COLOR);
  iVideo_Ptr->PutStringWithIncrementHeight(0,y," ",YELLOW_COLOR);  
  int32_t index=static_cast<int32_t>(log.size())-(static_cast<int32_t>(SCREEN_HEIGHT/height)-3);
  if (index<2) index=2;  
  for(size_t n=index;n<log.size();n++)
  {
   iVideo_Ptr->PutStringWithIncrementHeight(0,y,log[n].c_str(),YELLOW_COLOR);
  }
  return(false);
 }
 return(true);
}



 




