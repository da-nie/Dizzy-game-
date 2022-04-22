//****************************************************************************************************
//������������ ����������
//****************************************************************************************************
#include "cgame.h"
#include "cpart.h"
#include "csyntaxanalyzer.h"
#include "system.h"
#include <algorithm>
#include <memory>
#include <deque>

//****************************************************************************************************
//���������� ����������
//****************************************************************************************************

//****************************************************************************************************
//���������
//****************************************************************************************************
static const char MAP_FILE_NAME[]="./map.gam";//��� ����� �����

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
 cSprite_Dizzy.Load("./Sprites/dizzy.tga");
 cSprite_Dizzy.SetAlpha(0,BLEND_COLOR_R,BLEND_COLOR_G,BLEND_COLOR_B);

 cSprite_Tiles.Load("./Tiles/tiles.tga");
 cSprite_Tiles.SetAlpha(0,BLEND_COLOR_R,BLEND_COLOR_G,BLEND_COLOR_B);

 cSprite_TilesBarrier.Load("./Tiles/tiles_barrier.tga");
 cSprite_TilesBarrier.SetAlpha(0,NO_BARRIER_COLOR_R,NO_BARRIER_COLOR_G,NO_BARRIER_COLOR_B);

 cSprite_Frame.Load("./Sprites/frame.tga");
 cSprite_Frame.SetAlpha(0,BLEND_COLOR_R,BLEND_COLOR_G,BLEND_COLOR_B);

 cSprite_ScreenFrame.Load("./Sprites/screen_frame.tga");
 cSprite_ScreenFrame.SetAlpha(0,BLEND_COLOR_R,BLEND_COLOR_G,BLEND_COLOR_B);
 cSprite_Header.Load("./Sprites/header.tga");

 cFontPrinter_Ptr.reset(new CFontPrinter("./Sprites/font.tga",8,8,BLEND_COLOR_R,BLEND_COLOR_G,BLEND_COLOR_B));
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
 //������ ����� ����� �����
 DrawBeforeBackgroundMap(iVideo_Ptr);
 //������ �����
 cSprite_Dizzy.PutSpriteItem(iVideo_Ptr,cGameState.X,cGameState.Y,DIZZY_WIDTH*cDizzy.sFrame_Ptr->ImageFrame,0,DIZZY_WIDTH,DIZZY_HEIGHT,true); 
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
   if (dX==0) cDizzy.sFrame_Ptr=cDizzy.sFrame_Jump_Ptr;
  } 
  if (dY<0)
  {
   if (dX>0 && cDizzy.sFrame_Ptr->Move!=CDizzy::MOVE_JUMP_RIGHT) 
   {
    cDizzy.sFrame_Ptr=cDizzy.sFrame_JumpRight_Ptr;
   }
   if (dX<0 && cDizzy.sFrame_Ptr->Move!=CDizzy::MOVE_JUMP_LEFT) 
   {
    cDizzy.sFrame_Ptr=cDizzy.sFrame_JumpLeft_Ptr; 
   }
   if (dX==0 && cDizzy.sFrame_Ptr->Move!=CDizzy::MOVE_JUMP && cDizzy.sFrame_Ptr->Move!=CDizzy::MOVE_JUMP_RIGHT && cDizzy.sFrame_Ptr->Move!=CDizzy::MOVE_JUMP_LEFT)
   {
  	cDizzy.sFrame_Ptr=cDizzy.sFrame_Stop_Ptr;
   }
  }
  else
  {
   if (dX>0 && cDizzy.sFrame_Ptr->Move!=CDizzy::MOVE_RIGHT) cDizzy.sFrame_Ptr=cDizzy.sFrame_MoveRight_Ptr; 
   if (dX<0 && cDizzy.sFrame_Ptr->Move!=CDizzy::MOVE_LEFT) cDizzy.sFrame_Ptr=cDizzy.sFrame_MoveLeft_Ptr;
   if (dX==0 && dY==0 && cDizzy.sFrame_Ptr->Move!=CDizzy::MOVE_STOP) cDizzy.sFrame_Ptr=cDizzy.sFrame_Stop_Ptr;
  }
  if (cDizzy.sFrame_Ptr->Move==CDizzy::MOVE_STOP && fire==true && UseDelayCounter==0)
  {
   //���������� ��������� ��� ������ �������� � ���������
   size_t size=cGameState.ConditionalExpression.size();
   cGameState.Take.clear();   
   for(size_t n=0;n<size;n++) cGameState.ConditionalExpression[n]->Execute(cGameState.X+cGameState.Map_X,cGameState.Y+cGameState.Map_Y,DIZZY_WIDTH,DIZZY_HEIGHT,TILE_WIDTH,TILE_HEIGHT,true,false,cGameState);
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
  unit->BlockPosX=(cGameState.X+DIZZY_WIDTH/2)-TILE_WIDTH/2+cGameState.Map_X;
  unit->BlockPosY=(cGameState.Y+DIZZY_HEIGHT)-TILE_HEIGHT+cGameState.Map_Y;
  //���������, ����� ������� �� ����� ������������
  cGameState.UsedObject=unit;
  //��������� ������� �������������
  size_t cond_size=cGameState.ConditionalExpression.size();
  cGameState.Take.clear();  
  for(size_t m=0;m<cond_size;m++) cGameState.ConditionalExpression[m]->Execute(cGameState.X+cGameState.Map_X,cGameState.Y+cGameState.Map_Y,DIZZY_WIDTH,DIZZY_HEIGHT,TILE_WIDTH,TILE_HEIGHT,true,false,cGameState);
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
 if (DizzyAnimationTickCounter==0) cDizzy.Animation();
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
    
  int32_t last_x=cGameState.X;
  int32_t last_y=cGameState.Y;
  
  if (dx>0) cGameState.X++;
  if (dx<0) cGameState.X--;
  
  if (IsCollizionLegs(iVideo_Ptr,cGameState.X,cGameState.Y)==true || IsCollizionBody(iVideo_Ptr,cGameState.X,cGameState.Y)==true)//������������� ������������
  {
   if (IsCollizionBody(iVideo_Ptr,cGameState.X,cGameState.Y)==false)//����������� �� ���� �������
   {
    //��������� ����� �� ������� ��� �����������
    while(IsCollizionLegs(iVideo_Ptr,cGameState.X,cGameState.Y)==true && IsCollizionBody(iVideo_Ptr,cGameState.X,cGameState.Y)==false) ChangeDizzyCoord(0,-1,iVideo_Ptr);
   }
   else
   {
    cGameState.X=last_x;
    dx=0;
	//dX=0;//TODO: ���� ��� �������, ����� �� ������ ���������� ������������� ����� ���� ������.
   }
  }
  
  if (dy>0) cGameState.Y++;
  if (dy<0) cGameState.Y--;
  
  if (IsCollizionLegs(iVideo_Ptr,cGameState.X,cGameState.Y)==true || IsCollizionBody(iVideo_Ptr,cGameState.X,cGameState.Y)==true)//������������� ������������
  {
   cGameState.Y=last_y;
   dy=0;
   dY=0;
  }  

  ChangeDizzyCoord(0,0,iVideo_Ptr);
 }

 if (IsCollizionLegs(iVideo_Ptr,cGameState.X,cGameState.Y+1)==false && IsCollizionBody(iVideo_Ptr,cGameState.X,cGameState.Y+1)==false)//����� ������
 {
  if (MoveTickCounter==0)
  {
   if (dY<SPEED_Y) dY++;
  }
  if (dY>0) cGameState.Y++;
  MoveControl=false;
 }
 else
 {
  if (cDizzy.sFrame_Ptr->Move==CDizzy::MOVE_JUMP_RIGHT || cDizzy.sFrame_Ptr->Move==CDizzy::MOVE_JUMP_LEFT)//����� ������ ������ �����������
  {
   if (cDizzy.sFrame_Ptr->EndFrame==true) MoveControl=true;//������������� ���������
  }
  else MoveControl=true;
 } 
 //������ ������: ����� �� ��������, �� ��������� ������������ (��� ��� �������� ������ �������)
 if (IsCollizionLegs(iVideo_Ptr,cGameState.X,cGameState.Y)==true || IsCollizionBody(iVideo_Ptr,cGameState.X,cGameState.Y)==true)//������������� ������������
 {
  //������� ��������� ����� �����
  for(size_t n=0;n<TILE_WIDTH/4;n++)
  {
   if (IsCollizionLegs(iVideo_Ptr,cGameState.X,cGameState.Y)==true || IsCollizionBody(iVideo_Ptr,cGameState.X,cGameState.Y)==true) ChangeDizzyCoord(0,-1,iVideo_Ptr);
  }
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
 for(size_t n=0;n<size;n++) cGameState.ConditionalExpression[n]->Execute(cGameState.X+cGameState.Map_X,cGameState.Y+cGameState.Map_Y,DIZZY_WIDTH,DIZZY_HEIGHT,TILE_WIDTH,TILE_HEIGHT,false,true,cGameState);
}
//----------------------------------------------------------------------------------------------------
//��������� ��������� ������� �����
//----------------------------------------------------------------------------------------------------
void CGame::DizzyEnergyProcessing(IVideo *iVideo_Ptr)
{
 static const char RESPAWN[]="RESPAWN";//�������� ����� ��������������

 if (cGameState.Energy==0)//����� �����
 {
  cGameState.AddMessageLifeLost();  
  if (cGameState.Life>1) cGameState.Life--;
  else//���� ���������� �������
  {
   cGameState.AddMessageGameOver();   
   Init(iVideo_Ptr);
   return;
  }
  //���� ��������� ����� ��������������
  float min_distance=0;
  int32_t y=0;
  int32_t x=0;  
  size_t size=cGameState.MapNamed.size();
  bool first=true;
  for(size_t n=0;n<size;n++)
  {
   std::shared_ptr<IPart> iPart_Ptr=cGameState.MapNamed[n];
   if (iPart_Ptr->Name.compare(RESPAWN)!=0) continue;

   float dx=((cGameState.X+cGameState.Map_X)-iPart_Ptr->BlockPosX)/TILE_WIDTH;
   float dy=((cGameState.Y+cGameState.Map_Y)-iPart_Ptr->BlockPosY)/TILE_HEIGHT;
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
  cGameState.ScreenEnergy=0;
  cGameState.X=x-cGameState.Map_X;
  cGameState.Y=y-cGameState.Map_Y;
  dX=0;
  dY=0;  
  cDizzy.sFrame_Ptr=cDizzy.sFrame_Stop_Ptr;
  //���������� �����
  MoveMap(iVideo_Ptr);
 }
}


//----------------------------------------------------------------------------------------------------
//��������� �������� ����
//----------------------------------------------------------------------------------------------------
void CGame::Processing(IVideo *iVideo_Ptr)
{
 DizzyAnimation();//��������� �������� �����
 TilesAnimation();//��������� �������� ���� ������
 ConditionalProcessing();//��������� ��������� �������
 DizzyEnergyProcessing(iVideo_Ptr);
 DizzyMoveProcessing(iVideo_Ptr);//��������� ��������� �������� �����
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

  int32_t screen_x=block_x-cGameState.Map_X;
  int32_t screen_y=block_y-cGameState.Map_Y;

  size_t tile_index=iPart_Ptr->cTilesSequence.GetCurrentIndex();
  CTile &cTile=iPart_Ptr->cTilesSequence.GetTile(tile_index);

  int32_t tx=cTile.X*TILE_WITH_BORDER_WIDTH+TILE_BORDER_WIDTH;
  int32_t ty=cTile.Y*TILE_WITH_BORDER_HEIGHT+TILE_BORDER_HEIGHT;

  tiles.PutSpriteItem(iVideo_Ptr,screen_x,screen_y,tx,ty,TILE_WIDTH,TILE_HEIGHT,true);
 };

 CGameState::SVisitTree sVisitTree;
 sVisitTree.callback_function=drawing_barrier_function;
 sVisitTree.ScreenLeft=cGameState.Map_X;
 sVisitTree.ScreenTop=cGameState.Map_Y;
 sVisitTree.ScreenRight=sVisitTree.ScreenLeft+SCREEN_WIDTH;
 sVisitTree.ScreenBottom=sVisitTree.ScreenTop+SCREEN_HEIGHT;

 VisitTree(cGameState.QuadricTree_Ptr,sVisitTree);

 std::for_each(cGameState.MapNamed.begin(),cGameState.MapNamed.end(),drawing_barrier_function);
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
  if (iPart_Ptr->BeforeBackground==true) return;//����� ����� ����� ��������� ��������
  if (iPart_Ptr->InInventory==true) return;//�������� � ��������� �� ���������
  if (iPart_Ptr->Enabled==false) return;//������� ���������

  int32_t block_x=iPart_Ptr->BlockPosX;
  int32_t block_y=iPart_Ptr->BlockPosY;

  int32_t screen_x=block_x-cGameState.Map_X;
  int32_t screen_y=block_y-cGameState.Map_Y;

  size_t tile_index=iPart_Ptr->cTilesSequence.GetCurrentIndex();
  CTile &cTile=iPart_Ptr->cTilesSequence.GetTile(tile_index);

  int32_t tx=cTile.X*TILE_WITH_BORDER_WIDTH+TILE_BORDER_WIDTH;
  int32_t ty=cTile.Y*TILE_WITH_BORDER_HEIGHT+TILE_BORDER_HEIGHT;

  tiles.PutSpriteItem(iVideo_Ptr,screen_x,screen_y,tx,ty,TILE_WIDTH,TILE_HEIGHT,true);
 };

 CGameState::SVisitTree sVisitTree;
 sVisitTree.callback_function=drawing_function;
 sVisitTree.ScreenLeft=cGameState.Map_X;
 sVisitTree.ScreenTop=cGameState.Map_Y;
 sVisitTree.ScreenRight=sVisitTree.ScreenLeft+SCREEN_WIDTH;
 sVisitTree.ScreenBottom=sVisitTree.ScreenTop+SCREEN_HEIGHT;

 VisitTree(cGameState.QuadricTree_Ptr,sVisitTree);

 std::for_each(cGameState.MapNamed.begin(),cGameState.MapNamed.end(),drawing_function);
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

  int32_t screen_x=block_x-cGameState.Map_X;
  int32_t screen_y=block_y-cGameState.Map_Y;

  size_t tile_index=iPart_Ptr->cTilesSequence.GetCurrentIndex();
  CTile &cTile=iPart_Ptr->cTilesSequence.GetTile(tile_index);

  int32_t tx=cTile.X*TILE_WITH_BORDER_WIDTH+TILE_BORDER_WIDTH;
  int32_t ty=cTile.Y*TILE_WITH_BORDER_HEIGHT+TILE_BORDER_HEIGHT;

  tiles.PutSpriteItem(iVideo_Ptr,screen_x,screen_y,tx,ty,TILE_WIDTH,TILE_HEIGHT,true);
 };
 
 CGameState::SVisitTree sVisitTree;
 sVisitTree.callback_function=drawing_function;
 sVisitTree.ScreenLeft=cGameState.Map_X;
 sVisitTree.ScreenTop=cGameState.Map_Y;
 sVisitTree.ScreenRight=sVisitTree.ScreenLeft+SCREEN_WIDTH;
 sVisitTree.ScreenBottom=sVisitTree.ScreenTop+SCREEN_HEIGHT;

 VisitTree(cGameState.QuadricTree_Ptr,sVisitTree);

 std::for_each(cGameState.MapNamed.begin(),cGameState.MapNamed.end(),drawing_function);
}

//----------------------------------------------------------------------------------------------------
//���������� ����� ����� �����
//----------------------------------------------------------------------------------------------------
void CGame::DrawBeforeBackgroundMap(IVideo *iVideo_Ptr)
{
 //������ ���
 CSprite &tiles=cSprite_Tiles;

 auto drawing_function=[this,&tiles,&iVideo_Ptr](std::shared_ptr<IPart> iPart_Ptr)
 { 
  if (iPart_Ptr->BeforeBackground==false) return;//����� ��������� ������ ����� ����� �����
  if (iPart_Ptr->InInventory==true) return;//�������� � ��������� �� ���������
  if (iPart_Ptr->Enabled==false) return;//������� ���������

  int32_t block_x=iPart_Ptr->BlockPosX;
  int32_t block_y=iPart_Ptr->BlockPosY;

  int32_t screen_x=block_x-cGameState.Map_X;
  int32_t screen_y=block_y-cGameState.Map_Y;

  size_t tile_index=iPart_Ptr->cTilesSequence.GetCurrentIndex();
  CTile &cTile=iPart_Ptr->cTilesSequence.GetTile(tile_index);

  int32_t tx=cTile.X*TILE_WITH_BORDER_WIDTH+TILE_BORDER_WIDTH;
  int32_t ty=cTile.Y*TILE_WITH_BORDER_HEIGHT+TILE_BORDER_HEIGHT;

  tiles.PutSpriteItem(iVideo_Ptr,screen_x,screen_y,tx,ty,TILE_WIDTH,TILE_HEIGHT,true);
 };

 CGameState::SVisitTree sVisitTree;
 sVisitTree.callback_function=drawing_function;
 sVisitTree.ScreenLeft=cGameState.Map_X;
 sVisitTree.ScreenTop=cGameState.Map_Y;
 sVisitTree.ScreenRight=sVisitTree.ScreenLeft+SCREEN_WIDTH;
 sVisitTree.ScreenBottom=sVisitTree.ScreenTop+SCREEN_HEIGHT;

 VisitTree(cGameState.QuadricTree_Ptr,sVisitTree);

 std::for_each(cGameState.MapNamed.begin(),cGameState.MapNamed.end(),drawing_function);
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
 iVideo_Ptr->FillRectangle(rx1,ry1,rx2,ry2,BLACK_COLOR);
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
 if (cGameState.ScreenEnergy<cGameState.Energy) cGameState.ScreenEnergy++;
 if (cGameState.ScreenEnergy>cGameState.Energy) cGameState.ScreenEnergy--;

 if (cGameState.ScreenScore<cGameState.Score) cGameState.ScreenScore++;
 if (cGameState.ScreenScore>cGameState.Score) cGameState.ScreenScore--;

 static const int32_t FRAME_WIDTH=8;
 static const int32_t FRAME_HEIGHT=8;

 static const int32_t FRAME_UNIT_OFFSET_X=11;
 static const int32_t FRAME_UNIT_OFFSET_Y=1;

 static const int32_t FRAME_ANGLE_OFFSET_X=1;
 static const int32_t FRAME_ANGLE_OFFSET_Y=1;

 static const int32_t FRAME_LIFE_OFFSET_X=21;
 static const int32_t FRAME_LIFE_OFFSET_Y=1;

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
 sprintf(str,"%05i",cGameState.ScreenScore);
 cFontPrinter_Ptr->PrintAt(77,32,str,iVideo_Ptr);
 //������� �����
 static const int32_t LIFE_OFFSET_POS_Y=32;//��������� ���������� ������ �� Y
 static const int32_t LIFE_OFFSET_POS_X=224;//��������� ���������� ������ �� X
 for(int32_t n=0;n<cGameState.Life;n++)
 {
  cSprite_ScreenFrame.PutSpriteItem(iVideo_Ptr,n*FRAME_WIDTH+LIFE_OFFSET_POS_X,LIFE_OFFSET_POS_Y,FRAME_LIFE_OFFSET_X,FRAME_LIFE_OFFSET_Y,FRAME_WIDTH,FRAME_HEIGHT,true); 
 }
 //������� �������
 static const int32_t ENERGY_OFFSET_POS_X=160;//��������� ����� ������� �� X
 static const int32_t ENERGY_OFFSET_POS_Y=32;//��������� ����� ������� �� Y
 static const int32_t ENERGY_WIDTH=48;//������ ������ ����� �������
 static const int32_t ENERGY_HEIGHT=6;//������ ����� �������
 static const int32_t ENERGY_PART=3;//�� ������� ������ ������� ����� �������
 
 int32_t x1=ENERGY_OFFSET_POS_X;
 int32_t x2=ENERGY_OFFSET_POS_X+ENERGY_WIDTH*cGameState.ScreenEnergy/cGameState.ENERGY_MAX_VALUE;
 int32_t y1=ENERGY_OFFSET_POS_Y;
 int32_t y2=y1+ENERGY_HEIGHT;
 int32_t part=ENERGY_WIDTH/ENERGY_PART;

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
 static const int32_t ITEM_OFFSET_POS_X=129;//��������� ���������� ��������� ��������� �� X
 static const int32_t ITEM_OFFSET_POS_Y=32;//��������� ���������� ��������� ��������� �� Y

 sprintf(str,"%02i",cGameState.Items);
 cFontPrinter_Ptr->PrintAt(ITEM_OFFSET_POS_X,ITEM_OFFSET_POS_Y,str,iVideo_Ptr);
}


//----------------------------------------------------------------------------------------------------
//������� ������ ������
//----------------------------------------------------------------------------------------------------
void CGame::VisitTree(std::shared_ptr<CGameState::SQuadricTree> &sQuadricTree_Ptr,CGameState::SVisitTree &sVisitTree)
{
 std::deque<std::shared_ptr<CGameState::SQuadricTree>> deque_ptr;
 deque_ptr.push_front(sQuadricTree_Ptr);
 while(deque_ptr.empty()==false)
 {
  std::shared_ptr<CGameState::SQuadricTree> ptr=deque_ptr[0];
  deque_ptr.pop_front();

  if (ptr.get()==NULL) continue;
  if (ptr->Left>sVisitTree.ScreenRight) continue;
  if (ptr->Top>sVisitTree.ScreenBottom) continue;
  if (ptr->Right<sVisitTree.ScreenLeft) continue;
  if (ptr->Bottom<sVisitTree.ScreenTop) continue;

  size_t size=ptr->LeafItem.size();
  if (size>0)//��� ����
  {
   for(size_t n=0;n<size;n++) sVisitTree.callback_function(ptr->LeafItem[n]);
   continue;
  }
  //��������� ����������
  deque_ptr.push_front(ptr->LeftTop_Ptr);
  deque_ptr.push_front(ptr->LeftBottom_Ptr);
  deque_ptr.push_front(ptr->RightTop_Ptr);
  deque_ptr.push_front(ptr->RightBottom_Ptr);
 }
}

//----------------------------------------------------------------------------------------------------
//��������� �����
//----------------------------------------------------------------------------------------------------
bool CGame::LoadMap(const std::string &file_name)
{
 std::ifstream file;
 file.open(file_name,std::ios_base::in|std::ios_base::binary);
 if (file.is_open()==false) return(false);
 //��������� ������ ��������� �����
 uint32_t part;
 if (file.read(reinterpret_cast<char*>(&part),sizeof(part)).fail()==true) return(false);

 for(uint32_t n=0;n<part;n++)
 {
  std::shared_ptr<IPart> iPart_Ptr(new CPart());
  if (iPart_Ptr->Load(file)==false) return(false);
  cGameState.Map.push_back(iPart_Ptr);
 }
 //��������� ������ �������� ����������� ���������
 if (file.read(reinterpret_cast<char*>(&part),sizeof(part)).fail()==true) return(false);
 for(uint32_t n=0;n<part;n++)
 {
  uint32_t index;
  if (file.read(reinterpret_cast<char*>(&index),sizeof(index)).fail()==true) return(false);
  cGameState.MapNamed.push_back(cGameState.Map[index]);
 }
 //��������� ������������ ������ ������������� ���������
 cGameState.QuadricTree_Ptr=LoadQuadricTree(file);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//��������� ���� ������������� ������
//----------------------------------------------------------------------------------------------------
std::shared_ptr<CGameState::SQuadricTree> CGame::LoadNode(std::ifstream &file,bool &is_tree,uint8_t &leaf_mask)
{
 is_tree=false;
 leaf_mask=0;

 static const uint8_t STATE_LEAF=0;//������� �������� ������ ������
 static const uint8_t STATE_TREE=1;//������� �������� ����� �������

 std::shared_ptr<CGameState::SQuadricTree> sQuadricTree(new CGameState::SQuadricTree());
 //��������� ��� ����
 uint8_t state;
 if (file.read(reinterpret_cast<char*>(&state),sizeof(state)).fail()==true) return(std::shared_ptr<CGameState::SQuadricTree>(NULL));
 //��������� ����������� �������������
 if (file.read(reinterpret_cast<char*>(&sQuadricTree->Left),sizeof(sQuadricTree->Left)).fail()==true) return(std::shared_ptr<CGameState::SQuadricTree>(NULL));
 if (file.read(reinterpret_cast<char*>(&sQuadricTree->Right),sizeof(sQuadricTree->Right)).fail()==true) return(std::shared_ptr<CGameState::SQuadricTree>(NULL));
 if (file.read(reinterpret_cast<char*>(&sQuadricTree->Top),sizeof(sQuadricTree->Top)).fail()==true) return(std::shared_ptr<CGameState::SQuadricTree>(NULL));
 if (file.read(reinterpret_cast<char*>(&sQuadricTree->Bottom),sizeof(sQuadricTree->Bottom)).fail()==true) return(std::shared_ptr<CGameState::SQuadricTree>(NULL));
 //��������� ������ ������
 if (state==STATE_LEAF)//��������� ������ �����
 {
  uint32_t part;
  if (file.read(reinterpret_cast<char*>(&part),sizeof(part)).fail()==true) return(std::shared_ptr<CGameState::SQuadricTree>(NULL));
  for(uint32_t n=0;n<part;n++)
  {
   uint32_t index;
   if (file.read(reinterpret_cast<char*>(&index),sizeof(index)).fail()==true) return(std::shared_ptr<CGameState::SQuadricTree>(NULL));
   sQuadricTree->LeafItem.push_back(cGameState.Map[index]);
  }
  return(sQuadricTree);
 }
 //��������� �����
 if (file.read(reinterpret_cast<char*>(&sQuadricTree->CenterX),sizeof(sQuadricTree->CenterX)).fail()==true) return(std::shared_ptr<CGameState::SQuadricTree>(NULL));
 if (file.read(reinterpret_cast<char*>(&sQuadricTree->CenterY),sizeof(sQuadricTree->CenterY)).fail()==true) return(std::shared_ptr<CGameState::SQuadricTree>(NULL));
 if (state==STATE_TREE) is_tree=true;
 if (file.read(reinterpret_cast<char*>(&state),sizeof(state)).fail()==true) return(std::shared_ptr<CGameState::SQuadricTree>(NULL));
 leaf_mask=state;
 return(sQuadricTree);
}

//----------------------------------------------------------------------------------------------------
//��������� ������������ ������
//----------------------------------------------------------------------------------------------------
std::shared_ptr<CGameState::SQuadricTree> CGame::LoadQuadricTree(std::ifstream &file)
{
 static const uint8_t TREE_LEFT_TOP_MASK=(1<<0);//���� ����� ������� ���������
 static const uint8_t TREE_LEFT_BOTTOM_MASK=(1<<1);//���� ����� ������ ���������
 static const uint8_t TREE_RIGHT_TOP_MASK=(1<<2);//���� ������ ������� ���������
 static const uint8_t TREE_RIGHT_BOTTOM_MASK=(1<<3);//���� ������ ������ ���������
 
 std::shared_ptr<CGameState::SQuadricTree> sQuadricTree_Root(NULL); 

 struct SParent
 {
 };
 std::deque<std::shared_ptr<CGameState::SQuadricTree>*> deque_ptr; 
 deque_ptr.push_back(NULL);
 while(deque_ptr.empty()==false)
 {
  //��������� ��������� �� ��������� ������ ��� �������
  std::shared_ptr<CGameState::SQuadricTree> *parent;
  parent=deque_ptr[0];
  deque_ptr.pop_front();
  //��������� ����
  bool is_tree;//�������� �� ������� ��� ������
  uint8_t leaf_mask;//����� �������������� �����������
  std::shared_ptr<CGameState::SQuadricTree> node=LoadNode(file,is_tree,leaf_mask);
  if (node.get()==NULL) break;//������ �����������
  if (sQuadricTree_Root.get()==NULL) sQuadricTree_Root=node;
  if (parent!=NULL) *parent=node;
  //��������� ����������
  if (is_tree==true)
  {  
   if (leaf_mask&TREE_LEFT_TOP_MASK) deque_ptr.push_front(&node->LeftTop_Ptr);
   if (leaf_mask&TREE_LEFT_BOTTOM_MASK) deque_ptr.push_front(&node->LeftBottom_Ptr);
   if (leaf_mask&TREE_RIGHT_TOP_MASK) deque_ptr.push_front(&node->RightTop_Ptr);
   if (leaf_mask&TREE_RIGHT_BOTTOM_MASK) deque_ptr.push_front(&node->RightBottom_Ptr);
  }
 }
 return(sQuadricTree_Root);
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
   	if (line.length()!=0) log.push_back(std::to_string(static_cast<_Longlong>(line_index))+": "+line);   	 
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
//----------------------------------------------------------------------------------------------------
//�������� ���������� �����, ����������� ����� � ������������ �������
//----------------------------------------------------------------------------------------------------
void CGame::ChangeDizzyCoord(int32_t dx,int32_t dy,IVideo *iVideo_Ptr)
{
 uint32_t w;
 uint32_t h;
 iVideo_Ptr->GetScreenSize(w,h);
 int32_t width=w;
 int32_t height=h;
 int32_t offset_y=cSprite_Header.GetHeight();
 height-=offset_y; 

 cGameState.X+=dx;
 cGameState.Y+=dy;
 
 bool redraw_barrier=MoveMapStep(width,height,offset_y);
 if (redraw_barrier==true)
 {
  iVideo_Ptr->ClearScreen(NO_BARRIER_COLOR); 
  DrawBarrier(iVideo_Ptr);
 }
}
//----------------------------------------------------------------------------------------------------
//��������� ����������� �����, ���� ���������
//----------------------------------------------------------------------------------------------------
void CGame::MoveMap(IVideo *iVideo_Ptr)
{
 uint32_t w;
 uint32_t h;
 iVideo_Ptr->GetScreenSize(w,h);
 int32_t width=w;
 int32_t height=h;
 int32_t offset_y=cSprite_Header.GetHeight();
 height-=offset_y; 
 while(1) 
 {
  if (MoveMapStep(width,height,offset_y)==false) break;
 }
}

//----------------------------------------------------------------------------------------------------
//��������� ����������� ����� �� ���� ���, ���� ���������
//----------------------------------------------------------------------------------------------------
bool CGame::MoveMapStep(int32_t width,int32_t height,int32_t offset_y)
{
 static const int32_t DELTA=0;

 bool update=false;
 if (cGameState.X<width/4 && cGameState.Map_X>=DELTA)
 {
  cGameState.Map_X-=(width/4-cGameState.X);
  cGameState.X=width/4;
  update=true;
 }
 if (cGameState.X>3*width/4)
 {
  cGameState.Map_X+=(cGameState.X-3*width/4);
  cGameState.X=3*width/4;
  update=true;
 }
 if (cGameState.Y>(3*height/4+offset_y))
 {
  cGameState.Map_Y+=(cGameState.Y-(3*height/4+offset_y));
  cGameState.Y=(3*height/4+offset_y);
  update=true;
 } 
 if (cGameState.Y<(height/4+offset_y) && cGameState.Map_Y>=DELTA)
 {
  cGameState.Map_Y-=((height/4+offset_y)-cGameState.Y);
  cGameState.Y=(height/4+offset_y);
  update=true;
 }
 return(update);
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
 FlashTickCounter%=FLASH_TICK_COUNTER_DIVIDER;

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
//�������������
//----------------------------------------------------------------------------------------------------
bool CGame::Init(IVideo *iVideo_Ptr)
{
 cDizzy.Init(); 

 cGameState.X=160;
 cGameState.Y=5;

 cGameState.Map_X=0;
 cGameState.Map_Y=0;
 
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
 cGameState.MapNamed.clear();
 cGameState.QuadricTree_Ptr.reset();
 if (LoadMap(MAP_FILE_NAME)==false)
 {
  std::string message="�� ���� ������� ���� ����� "+std::string(MAP_FILE_NAME)+" !";  
  iVideo_Ptr->PutString(0,0,message.c_str(),YELLOW_COLOR);
  return(false);
 }
 //��������� �������� ���������
 std::vector<std::string> log;
 int64_t y=0;
 uint32_t swidth;
 uint32_t sheight;
 iVideo_Ptr->GetStringImageSize(" ",swidth,sheight);
 if (LoadConditional("./ScreenPlay",log)==false)
 {  
  if (log.size()<2) return(false);
  iVideo_Ptr->PutStringWithIncrementHeight(0,y,"��������� ������ ���������� �����",YELLOW_COLOR);
  iVideo_Ptr->PutStringWithIncrementHeight(0,y,log[0].c_str(),YELLOW_COLOR);
  iVideo_Ptr->PutStringWithIncrementHeight(0,y," ",YELLOW_COLOR);  
  int32_t index=static_cast<int32_t>(log.size())-(static_cast<int32_t>(SCREEN_HEIGHT/sheight)-3);
  if (index<2) index=2;  
  for(size_t n=index;n<log.size();n++)
  {
   iVideo_Ptr->PutStringWithIncrementHeight(0,y,log[n].c_str(),YELLOW_COLOR);
  }
  return(false);
 }
 //������ ������� �����
 cGameState.X=cGameState.DizzyStartPositionX;
 cGameState.Y=cGameState.DizzyStartPositionY;

 //���������� �����
 MoveMap(iVideo_Ptr);
 return(true);
}



 




