#ifndef C_GAME_H
#define C_GAME_H

//****************************************************************************************************
//Класс игры
//****************************************************************************************************

//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>

#include "ivideo.h"
#include "csprite.h"
#include "ipart.h"

//****************************************************************************************************
//макроопределения
//****************************************************************************************************

//****************************************************************************************************
//константы
//****************************************************************************************************

//****************************************************************************************************
//предварительные объявления
//****************************************************************************************************

//****************************************************************************************************
//Класс игры
//****************************************************************************************************
class CGame
{
 public:
  //-перечисления---------------------------------------------------------------------------------------
  //-структуры------------------------------------------------------------------------------------------
  //-константы------------------------------------------------------------------------------------------
  static const int32_t DizzyWidth=25;
  static const int32_t DizzyHeight=22;

  static const int32_t TILE_WIDTH=16;//ширина тайла
  static const int32_t TILE_HEIGHT=16;//высота тайла
  static const int32_t TILE_BORDER_WIDTH=1;//ширина рамки
  static const int32_t TILE_BORDER_HEIGHT=1;//высота рамки  
  static const int32_t TILE_WITH_BORDER_WIDTH=TILE_WIDTH+TILE_BORDER_WIDTH+TILE_BORDER_WIDTH;//ширина тайла с рамкой
  static const int32_t TILE_WITH_BORDER_HEIGHT=TILE_HEIGHT+TILE_BORDER_HEIGHT+TILE_BORDER_HEIGHT;//высота тайла с рамкой
 private:
  //-переменные-----------------------------------------------------------------------------------------

  //карта  

  CSprite cSprite_Dizzy;//спрайт Диззи

  CSprite cSprite_Tiles;//тайлы
  CSprite cSprite_TilesBarrier;//непроницаемость тайлов
  
  int32_t X;//координаты
  int32_t Y;

  int32_t dX;//скорости
  int32_t dY;

  int32_t FrameFall;
  int32_t FrameJumpUp;
  int32_t FrameJumpLeft;
  int32_t FrameJumpRight;

  //режимы движения
  enum MOVE
  {
   MOVE_STOP,
   MOVE_LEFT,
   MOVE_RIGHT,
   MOVE_JUMP,
   MOVE_JUMP_LEFT,
   MOVE_JUMP_RIGHT,
  };

  bool MoveControl;//управляем ли Dizzy

  struct SFrame
  {   
   MOVE Move;//режим движения
   int32_t ImageFrame;//номер кадра в изображении
   SFrame *sFrame_Next_Ptr;//указатель на следующий кадр
   bool EndFrame;//является ли кадр последним кадром
   
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

  std::vector<SFrame> sFrame_Array;//набор кадров для анимации

  int32_t SmallTickCounter;//счётчик малого такта

  std::vector<std::shared_ptr<IPart>> Map;//карта
 public:
  //-конструктор----------------------------------------------------------------------------------------
  CGame(void);
  //-деструктор-----------------------------------------------------------------------------------------
  ~CGame();
 public:
  //-открытые функции-----------------------------------------------------------------------------------
  void OnPaint(IVideo *iVideo_Ptr);//отрисовать картинку  
  void OnTimer(IVideo *iVideo_Ptr);//обработка таймера  
  void KeyboardControl(bool left,bool right,bool up,bool down,bool fire);//управление от клавиатуры
 private:
  //-закрытые функции-----------------------------------------------------------------------------------  
  bool IsCollizionLegs(IVideo *iVideo_Ptr,int32_t xp,int32_t yp);//проверить столкновение с блоками ног Диззи
  bool IsCollizionBody(IVideo *iVideo_Ptr,int32_t xp,int32_t yp);//проверить столкновение с блоками корпуса Диззи
  bool LoadMap(const std::string &file_name);//загрузить карту
};

#endif