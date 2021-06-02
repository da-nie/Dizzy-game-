//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cgame.h"

//****************************************************************************************************
//глобальные переменные
//****************************************************************************************************

//****************************************************************************************************
//константы
//****************************************************************************************************
static const int32_t SPEED_X=2;
static const int32_t SPEED_Y=2;

//****************************************************************************************************
//макроопределения
//****************************************************************************************************

//****************************************************************************************************
//конструктор и деструктор
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CGame::CGame(void)
{ 
 cSprite_Dizzy.Load("Sprites\\dizzy.tga");
 cSprite_Dizzy.SetAlpha(0,81,162,243);
 
 //Dizzy стоит
 sFrame_Array.push_back(SFrame(0,MOVE_STOP,NULL));//0 
 sFrame_Array.push_back(SFrame(1,MOVE_STOP,NULL));//1
 //Dizzy идёт влево
 sFrame_Array.push_back(SFrame(9,MOVE_LEFT,NULL));//2 
 sFrame_Array.push_back(SFrame(10,MOVE_LEFT,NULL));//3
 sFrame_Array.push_back(SFrame(11,MOVE_LEFT,NULL));//4
 sFrame_Array.push_back(SFrame(12,MOVE_LEFT,NULL));//5
 sFrame_Array.push_back(SFrame(13,MOVE_LEFT,NULL));//6
 sFrame_Array.push_back(SFrame(14,MOVE_LEFT,NULL));//7
 sFrame_Array.push_back(SFrame(15,MOVE_LEFT,NULL));//8
 sFrame_Array.push_back(SFrame(16,MOVE_LEFT,NULL));//9
 //Dizzy идёт вправо
 sFrame_Array.push_back(SFrame(17,MOVE_RIGHT,NULL));//10 
 sFrame_Array.push_back(SFrame(18,MOVE_RIGHT,NULL));//11
 sFrame_Array.push_back(SFrame(19,MOVE_RIGHT,NULL));//12
 sFrame_Array.push_back(SFrame(20,MOVE_RIGHT,NULL));//13
 sFrame_Array.push_back(SFrame(21,MOVE_RIGHT,NULL));//14
 sFrame_Array.push_back(SFrame(22,MOVE_RIGHT,NULL));//15
 sFrame_Array.push_back(SFrame(23,MOVE_RIGHT,NULL));//16
 sFrame_Array.push_back(SFrame(24,MOVE_RIGHT,NULL));//17
 //Dizzy прыгает на месте
 sFrame_Array.push_back(SFrame(2,MOVE_JUMP,NULL));//18 
 sFrame_Array.push_back(SFrame(3,MOVE_JUMP,NULL));//19
 sFrame_Array.push_back(SFrame(4,MOVE_JUMP,NULL));//20
 sFrame_Array.push_back(SFrame(5,MOVE_JUMP,NULL));//21
 sFrame_Array.push_back(SFrame(6,MOVE_JUMP,NULL));//22
 sFrame_Array.push_back(SFrame(7,MOVE_JUMP,NULL));//23
 sFrame_Array.push_back(SFrame(8,MOVE_JUMP,NULL));//24
 //Dizzy прыгает влево
 sFrame_Array.push_back(SFrame(25,MOVE_JUMP_LEFT,NULL));//25
 sFrame_Array.push_back(SFrame(26,MOVE_JUMP_LEFT,NULL));//26
 sFrame_Array.push_back(SFrame(27,MOVE_JUMP_LEFT,NULL));//27
 sFrame_Array.push_back(SFrame(28,MOVE_JUMP_LEFT,NULL));//28
 sFrame_Array.push_back(SFrame(29,MOVE_JUMP_LEFT,NULL));//29
 sFrame_Array.push_back(SFrame(30,MOVE_JUMP_LEFT,NULL));//30
 sFrame_Array.push_back(SFrame(31,MOVE_JUMP_LEFT,NULL));//31
 //Dizzy прыгает вправо
 sFrame_Array.push_back(SFrame(32,MOVE_JUMP_RIGHT,NULL));//32
 sFrame_Array.push_back(SFrame(33,MOVE_JUMP_RIGHT,NULL));//33
 sFrame_Array.push_back(SFrame(34,MOVE_JUMP_RIGHT,NULL));//34
 sFrame_Array.push_back(SFrame(35,MOVE_JUMP_RIGHT,NULL));//35
 sFrame_Array.push_back(SFrame(36,MOVE_JUMP_RIGHT,NULL));//36
 sFrame_Array.push_back(SFrame(37,MOVE_JUMP_RIGHT,NULL));//37
 sFrame_Array.push_back(SFrame(38,MOVE_JUMP_RIGHT,NULL));//38



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
 X=160;
 Y=5;

 dX=0;
 dY=0;

 MoveControl=true;

 SmallTickCounter=0;

 //создаём карту 
 int32_t top=MapHeight-5;
 int32_t dy=0;
 for(size_t x=0;x<MapWidth;x++)
 {
  for(size_t y=0;y<MapHeight;y++) Map[y][x]=false;
  int32_t r=rand();
  r%=8;
  int32_t dy_table[8]={1,2,1,0,-2,-3,-1,-1};
  dy=dy_table[r];
  top+=dy;
  if (top<0)
  {
   top=0;
   dy=1;
  }
  if (top>=MapHeight-10)
  {
   top=MapHeight-11;
   dy=-1;
  }
  for(size_t y=top;y<MapHeight;y++) Map[y][x]=true;
 }
 for(size_t y=0;y<MapHeight;y++)
 {
  Map[y][0]=true;
  Map[y][MapWidth-2]=true;
 }
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CGame::~CGame()
{
}

//****************************************************************************************************
//закрытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************************************
//открытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//перерисовать картинку
//----------------------------------------------------------------------------------------------------
void CGame::OnPaint(IVideo *iVideo_Ptr)
{
 for(size_t x=0;x<MapWidth;x++)
 {
  for(size_t y=0;y<MapHeight;y++) 
  {
   uint32_t color=0x000000;
   if (Map[y][x]==true) color=0x00ffffff;
   iVideo_Ptr->FillRectangle(x*BlockWidthSize,y*BlockHeightSize,x*BlockWidthSize+(BlockWidthSize-1),y*BlockHeightSize+(BlockHeightSize-1),color);   
  }
 } 

 int32_t map_x_left=(X)/BlockWidthSize;
 int32_t map_y_top=(Y)/BlockHeightSize;
 int32_t map_x_right=(X+DizzyWidth-1)/BlockWidthSize;
 int32_t map_y_bottom=(Y+DizzyHeight-1)/BlockHeightSize;

 if (map_x_left<0) map_x_left=0;
 if (map_x_right<0) map_x_right=0;

 if (map_y_top<0) map_y_top=0;
 if (map_y_bottom<0) map_y_bottom=0;

 if (map_x_left>=MapWidth) map_x_left=MapWidth-1;
 if (map_x_right>=MapWidth) map_x_right=MapWidth-1;

 if (map_y_top>=MapHeight) map_y_top=MapHeight-1;
 if (map_y_bottom>=MapHeight) map_y_bottom=MapHeight-1;

 for (size_t x=map_x_left;x<=map_x_right;x++)
 {
  for (size_t y=map_y_top;y<=map_y_bottom;y++)
  {
   //iVideo_Ptr->FillRectangle(x*BlockWidthSize,y*BlockHeightSize,x*BlockWidthSize+(BlockWidthSize-1),y*BlockHeightSize+(BlockHeightSize-1),0x00FFFF00);   
  }
 }

 cSprite_Dizzy.PutSpriteItem(iVideo_Ptr,X,Y,DizzyWidth*sFrame_Ptr->ImageFrame,0,25,22,true); 
}

//----------------------------------------------------------------------------------------------------
//определить, что столкновение произошло по нижней линии и на один блок (левый или правый)
//----------------------------------------------------------------------------------------------------
bool CGame::IsCollizionDownOneBlock(int32_t xp,int32_t yp)
{
 //определяем, в каких блоках объект
 int32_t map_x_left;
 int32_t map_y_top;
 int32_t map_x_right;
 int32_t map_y_bottom;

 GetMapCoord(xp,yp,map_x_left,map_y_top);
 GetMapCoord(xp+DizzyWidth-1,yp+DizzyHeight-1,map_x_right,map_y_bottom);

 int32_t collizion=0;
 for (size_t x=map_x_left;x<=map_x_right;x++)
 {
  for (size_t y=map_y_top;y<=map_y_bottom;y++)
  {
   if (Map[y][x]==true)
   {
    if (y!=map_y_bottom) return(false);
	collizion++;
   }
  }
 }
 if (collizion==1) return(true);
 return(false);
}


//----------------------------------------------------------------------------------------------------
//получить координаты блока
//----------------------------------------------------------------------------------------------------
void CGame::GetMapCoord(int32_t x,int32_t y,int32_t &map_x,int32_t &map_y)
{
 map_x=x/BlockWidthSize;
 map_y=y/BlockHeightSize;

 if (map_x<0) map_x=0;
 if (map_y<0) map_y=0;
 if (map_x>=MapWidth) map_x=MapWidth-1;
 if (map_y>=MapHeight) map_y=MapHeight-1;
}

//----------------------------------------------------------------------------------------------------
//проверить столкновение с блоками
//----------------------------------------------------------------------------------------------------
bool CGame::IsCollizion(int32_t xp,int32_t yp)
{
 //определяем, в каких блоках объект
 int32_t map_x_left;
 int32_t map_y_top;
 int32_t map_x_right;
 int32_t map_y_bottom;

 GetMapCoord(xp,yp,map_x_left,map_y_top);
 GetMapCoord(xp+DizzyWidth-1,yp+DizzyHeight-1,map_x_right,map_y_bottom);

 for (size_t x=map_x_left;x<=map_x_right;x++)
 {
  for (size_t y=map_y_top;y<=map_y_bottom;y++)
  {
   if (Map[y][x]==true) return(true);
  }
 }
 return(false);
}

//----------------------------------------------------------------------------------------------------
//обработка таймера
//----------------------------------------------------------------------------------------------------
void CGame::OnTimer(void)
{
 SmallTickCounter++;
 SmallTickCounter%=7;

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
  if (IsCollizion(X,Y)==true)//зафиксировано столкновение
  {
   if (IsCollizionDownOneBlock(X,Y)==true)//столкновение произошло на нижнем уровне и на один блок
   {
    Y-=BlockHeightSize;
   }
   X=last_x;
   dx=0;
  }

  if (dy>0) Y++;
  if (dy<0) Y--;
  if (IsCollizion(X,Y)==true)//зафиксировано столкновение
  {
   Y=last_y;
   dy=0;
   dY=0;
  }
 }

 if (IsCollizion(X,Y+1)==false)//можно падать
 {
  if (SmallTickCounter==0) 
  {
   if (dY<SPEED_Y) dY++;
  }
  MoveControl=false;
 }
 else MoveControl=true;
}
//----------------------------------------------------------------------------------------------------
//управление от клавиатуры
//----------------------------------------------------------------------------------------------------
void CGame::KeyboardControl(bool left,bool right,bool up,bool down,bool fire)
{
 if (sFrame_Ptr->sFrame_Next_Ptr!=NULL) sFrame_Ptr=sFrame_Ptr->sFrame_Next_Ptr;
                                   else sFrame_Ptr=sFrame_Stop_Ptr; 
 if (MoveControl==true)
 {
  if (left==true) dX=-SPEED_X;
  if (right==true) dX=SPEED_X;
  if (left==false && right==false) dX=0;
  if (up==true) 
  {
   SmallTickCounter=0;
   dY=-SPEED_Y;  
   //MoveControl=false;
   if (dX==0) sFrame_Ptr=sFrame_Jump_Ptr;
  } 
  if (dY<0)
  {
   if (dX>0 && sFrame_Ptr->Move!=MOVE_JUMP_RIGHT) 
   {
    sFrame_Ptr=sFrame_JumpRight_Ptr;
	//MoveControl=false;
   }
   if (dX<0 && sFrame_Ptr->Move!=MOVE_JUMP_LEFT) 
   {
    sFrame_Ptr=sFrame_JumpLeft_Ptr; 
	//MoveControl=false;
   }
   if (dX==0 && sFrame_Ptr->Move!=MOVE_JUMP && sFrame_Ptr->Move!=MOVE_JUMP_RIGHT && sFrame_Ptr->Move!=MOVE_JUMP_LEFT)
   {
  	sFrame_Ptr=sFrame_Stop_Ptr;
	//MoveControl=false;
   }
  }
  else
  {
   if (dX>0 && sFrame_Ptr->Move!=MOVE_RIGHT) sFrame_Ptr=sFrame_MoveRight_Ptr; 
   if (dX<0 && sFrame_Ptr->Move!=MOVE_LEFT) sFrame_Ptr=sFrame_MoveLeft_Ptr;
   if (dX==0 && dY==0 && sFrame_Ptr->Move!=MOVE_STOP) sFrame_Ptr=sFrame_Stop_Ptr;
  }
 }
}
