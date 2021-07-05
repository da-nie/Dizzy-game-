//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cgame.h"
#include "cpart.h"
#include <algorithm>
#include <memory>

//****************************************************************************************************
//глобальные переменные
//****************************************************************************************************

//****************************************************************************************************
//константы
//****************************************************************************************************
static const int32_t SPEED_X=2;//скорость Диззи по X
static const int32_t SPEED_Y=2;//скорость Диззи по Y

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

 cSprite_Tiles.Load("Tiles\\tiles.tga");
 cSprite_Tiles.SetAlpha(0,81,162,243);

 cSprite_TilesBarrier.Load("Tiles\\tiles_barrier.tga");
 cSprite_TilesBarrier.SetAlpha(0,0,0,0);

 //Dizzy стоит
 sFrame_Array.push_back(SFrame(0,MOVE_STOP,false,NULL));//0 
 sFrame_Array.push_back(SFrame(1,MOVE_STOP,true,NULL));//1
 //Dizzy идёт влево
 sFrame_Array.push_back(SFrame(9,MOVE_LEFT,false,NULL));//2 
 sFrame_Array.push_back(SFrame(10,MOVE_LEFT,false,NULL));//3
 sFrame_Array.push_back(SFrame(11,MOVE_LEFT,false,NULL));//4
 sFrame_Array.push_back(SFrame(12,MOVE_LEFT,false,NULL));//5
 sFrame_Array.push_back(SFrame(13,MOVE_LEFT,false,NULL));//6
 sFrame_Array.push_back(SFrame(14,MOVE_LEFT,false,NULL));//7
 sFrame_Array.push_back(SFrame(15,MOVE_LEFT,false,NULL));//8
 sFrame_Array.push_back(SFrame(16,MOVE_LEFT,true,NULL));//9
 //Dizzy идёт вправо
 sFrame_Array.push_back(SFrame(17,MOVE_RIGHT,false,NULL));//10 
 sFrame_Array.push_back(SFrame(18,MOVE_RIGHT,false,NULL));//11
 sFrame_Array.push_back(SFrame(19,MOVE_RIGHT,false,NULL));//12
 sFrame_Array.push_back(SFrame(20,MOVE_RIGHT,false,NULL));//13
 sFrame_Array.push_back(SFrame(21,MOVE_RIGHT,false,NULL));//14
 sFrame_Array.push_back(SFrame(22,MOVE_RIGHT,false,NULL));//15
 sFrame_Array.push_back(SFrame(23,MOVE_RIGHT,false,NULL));//16
 sFrame_Array.push_back(SFrame(24,MOVE_RIGHT,true,NULL));//17
 //Dizzy прыгает на месте
 sFrame_Array.push_back(SFrame(2,MOVE_JUMP,false,NULL));//18 
 sFrame_Array.push_back(SFrame(3,MOVE_JUMP,false,NULL));//19
 sFrame_Array.push_back(SFrame(4,MOVE_JUMP,false,NULL));//20
 sFrame_Array.push_back(SFrame(5,MOVE_JUMP,false,NULL));//21
 sFrame_Array.push_back(SFrame(6,MOVE_JUMP,false,NULL));//22
 sFrame_Array.push_back(SFrame(7,MOVE_JUMP,false,NULL));//23
 sFrame_Array.push_back(SFrame(8,MOVE_JUMP,true,NULL));//24
 //Dizzy прыгает влево
 sFrame_Array.push_back(SFrame(25,MOVE_JUMP_LEFT,false,NULL));//25
 sFrame_Array.push_back(SFrame(26,MOVE_JUMP_LEFT,false,NULL));//26
 sFrame_Array.push_back(SFrame(27,MOVE_JUMP_LEFT,false,NULL));//27
 sFrame_Array.push_back(SFrame(28,MOVE_JUMP_LEFT,false,NULL));//28
 sFrame_Array.push_back(SFrame(29,MOVE_JUMP_LEFT,false,NULL));//29
 sFrame_Array.push_back(SFrame(30,MOVE_JUMP_LEFT,false,NULL));//30
 sFrame_Array.push_back(SFrame(31,MOVE_JUMP_LEFT,true,NULL));//31
 //Dizzy прыгает вправо
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
 X=160;
 Y=5;

 Map_X=0;
 Map_Y=0;

 dX=0;
 dY=0;

 MoveControl=true;

 SmallTickCounter=0;

 //загружаем карту
 Map.clear();
 if (LoadMap("map.gam")==false) MessageBox(NULL,"Ошибка загрузки файла карты!","Ошибка",MB_OK);
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
//проверить столкновение с блоками ног Диззи
//----------------------------------------------------------------------------------------------------
bool CGame::IsCollizionLegs(IVideo *iVideo_Ptr,int32_t xp,int32_t yp)
{
 return(cSprite_Dizzy.IsCollizionSpriteItem(iVideo_Ptr,xp,yp,DizzyWidth*39,0,DizzyWidth,DizzyHeight,true,0,0,0)); 
}
//----------------------------------------------------------------------------------------------------
//проверить столкновение с блоками корпуса Диззи
//----------------------------------------------------------------------------------------------------
bool CGame::IsCollizionBody(IVideo *iVideo_Ptr,int32_t xp,int32_t yp)
{
 return(cSprite_Dizzy.IsCollizionSpriteItem(iVideo_Ptr,xp,yp,DizzyWidth*40,0,DizzyWidth,DizzyHeight,true,0,0,0)); 
}

//----------------------------------------------------------------------------------------------------
//загрузить карту
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
  Map.push_back(iPart_Ptr);
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//нарисовать преграды
//----------------------------------------------------------------------------------------------------
void CGame::DrawBarrier(IVideo *iVideo_Ptr)
{
 //рисуем фон с непроницаемыми объектами
 CSprite &tiles=cSprite_TilesBarrier;

 auto drawing_barrier_function=[this,&tiles,&iVideo_Ptr](std::shared_ptr<IPart> iPart_Ptr)
 { 
  if (iPart_Ptr->Barrier==false) return;

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
 std::for_each(Map.begin(),Map.end(),drawing_barrier_function);
}
//----------------------------------------------------------------------------------------------------
//нарисовать карту
//----------------------------------------------------------------------------------------------------
void CGame::DrawMap(IVideo *iVideo_Ptr)
{
 //рисуем фон
 CSprite &tiles=cSprite_Tiles;

 auto drawing_function=[this,&tiles,&iVideo_Ptr](std::shared_ptr<IPart> iPart_Ptr)
 { 
  if (iPart_Ptr->FirstPlane==true) return;//передний план выводится отдельно

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
 std::for_each(Map.begin(),Map.end(),drawing_function);
}
//----------------------------------------------------------------------------------------------------
//нарисовать карту переднего плана
//----------------------------------------------------------------------------------------------------
void CGame::DrawFirstPlaneMap(IVideo *iVideo_Ptr)
{
 //рисуем фон
 CSprite &tiles=cSprite_Tiles;

 auto drawing_function=[this,&tiles,&iVideo_Ptr](std::shared_ptr<IPart> iPart_Ptr)
 { 
  if (iPart_Ptr->FirstPlane==false) return;//здесь выводится только передний план

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
 std::for_each(Map.begin(),Map.end(),drawing_function);
}
//----------------------------------------------------------------------------------------------------
//очистить экран
//----------------------------------------------------------------------------------------------------
void CGame::ClearScreen(IVideo *iVideo_Ptr,uint32_t color)
{
 uint32_t width;
 uint32_t height;
 iVideo_Ptr->GetScreenSize(width,height);
 iVideo_Ptr->FillRectangle(0,0,width,height,color);
}

//****************************************************************************************************
//открытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//перерисовать картинку
//----------------------------------------------------------------------------------------------------
void CGame::OnPaint(IVideo *iVideo_Ptr)
{
 //стираем фон
 uint32_t sky=(0<<24)|(81<<16)|(162<<8)|(243<<0);
 ClearScreen(iVideo_Ptr,sky);
 //рисуем карту
 DrawMap(iVideo_Ptr);
 //рисуем Диззи
 cSprite_Dizzy.PutSpriteItem(iVideo_Ptr,X,Y,DizzyWidth*sFrame_Ptr->ImageFrame,0,DizzyWidth,DizzyHeight,true); 
 //рисуем элементы переднего плана
 DrawFirstPlaneMap(iVideo_Ptr);
}

//----------------------------------------------------------------------------------------------------
//обработка таймера
//----------------------------------------------------------------------------------------------------
void CGame::OnTimer(IVideo *iVideo_Ptr)
{ 
 static int counter=0;
 if (counter==0)
 {
  if (sFrame_Ptr->sFrame_Next_Ptr!=NULL) sFrame_Ptr=sFrame_Ptr->sFrame_Next_Ptr;
                                    else sFrame_Ptr=sFrame_Stop_Ptr;
 }
 counter++;
 counter%=3;

 //стираем фон
 uint32_t width;
 uint32_t height;
 iVideo_Ptr->GetScreenSize(width,height);
 
 ClearScreen(iVideo_Ptr,0x00000000); 
 DrawBarrier(iVideo_Ptr);
 
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

  if (IsCollizionLegs(iVideo_Ptr,X,Y)==true || IsCollizionBody(iVideo_Ptr,X,Y)==true)//зафиксировано столкновение
  {
   if (IsCollizionBody(iVideo_Ptr,X,Y)==false)//пересечение не выше допуска
   {
    //поднимаем Диззи на уровень без пересечения
    while(IsCollizionLegs(iVideo_Ptr,X,Y)==true) Y--;
   }
   else
   {
    X=last_x;
    dx=0;
	//dX=0;//TODO: если так сделать, Диззи не сможет забираться перекатываясь через края блоков.
   }
  }

  if (dy>0) Y++;
  if (dy<0) Y--;
  if (IsCollizionLegs(iVideo_Ptr,X,Y)==true || IsCollizionBody(iVideo_Ptr,X,Y)==true)//зафиксировано столкновение
  {
   Y=last_y;
   dy=0;
   dY=0;
  }

  bool redraw_barrier=false;
  if (X<width/4 && Map_X>=2)
  {
   Map_X-=2;
   //Map_X-=width/8;
   //X+=width/8;
   X+=2;
   redraw_barrier=true;
  }
  if (X>=3*width/4)
  {
   Map_X+=2;
   X-=2;
   //X-=7*width/8;
   //Map_X+=7*width/8;
   redraw_barrier=true;
  }
  if (Y>=3*height/4)
  {
   Y-=2;
   Map_Y+=2;
   redraw_barrier=true;
  }
  if (Y<height/4 && Map_Y>=2)
  {
   Y+=2;
   Map_Y-=2;
   redraw_barrier=true;
  }

  if (redraw_barrier==true)
  {
   ClearScreen(iVideo_Ptr,0x00000000); 
   DrawBarrier(iVideo_Ptr);
  }
 }

 if (IsCollizionLegs(iVideo_Ptr,X,Y+1)==false)//можно падать
 {
  if (SmallTickCounter==0)
  {
   if (dY<SPEED_Y) dY++;
  }
  MoveControl=false;
 }
 else
 {
  if (sFrame_Ptr->Move==MOVE_JUMP_RIGHT || sFrame_Ptr->Move==MOVE_JUMP_LEFT)//режим прыжка должен завершиться
  {
   if (sFrame_Ptr->EndFrame==true) MoveControl=true;//перекатывание завершено
  }
  else MoveControl=true;
 }
 //выполняем анимацию
 if (SmallTickCounter==0)
 { 
  size_t size=Map.size();
  for(size_t n=0;n<size;n++) Map[n]->AnimationTiles();
 }
}

//----------------------------------------------------------------------------------------------------
//управление от клавиатуры
//----------------------------------------------------------------------------------------------------
void CGame::KeyboardControl(bool left,bool right,bool up,bool down,bool fire)
{
 if (MoveControl==true)
 {
  if (left==true) dX=-SPEED_X;
  if (right==true) dX=SPEED_X;
  if (left==false && right==false) dX=0;
  if (up==true) 
  {
   SmallTickCounter=0;
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
 }
}

