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
#include "cfontprinter.h"
#include "csprite.h"
#include "ipart.h"
#include "iconditionalexpression.h"
#include "cgamestate.h"

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
  static const uint32_t BLACK_COLOR=(0<<24)|(0<<16)|(0<<8)|(0<<0);//чёрный цвет
  static const uint32_t YELLOW_COLOR=(0<<24)|(255<<16)|(255<<8)|(0<<0);//жёлтый цвет цвет

  static const uint32_t SKY_COLOR=(0<<24)|(81<<16)|(162<<8)|(243<<0);//цвет неба
  static const uint32_t BLEND_COLOR=(00<<24)|(81<<16)|(162<<8)|(243<<0);//прозрачный цвет
  static const uint8_t BLEND_COLOR_R=81;//прозрачный цвет, компонент R
  static const uint8_t BLEND_COLOR_G=162;//прозрачный цвет, компонент G
  static const uint8_t BLEND_COLOR_B=243;//прозрачный цвет, компонент B

  static const uint32_t NO_BARRIER_COLOR=(0x00<<24)|(0x00<<16)|(0x00<<8)|(0x00<<0);//цвет остутствия препятствий
  static const uint8_t NO_BARRIER_COLOR_R=0;//цвет отсутствия препятствий, компонент R
  static const uint8_t NO_BARRIER_COLOR_G=0;//цвет отсутствия препятствий, компонент G
  static const uint8_t NO_BARRIER_COLOR_B=0;//цвет отсутствия препятствий, компонент B

  static const int32_t TILES_ANIMATION_TICK_COUNTER_DIVIDER=7;//делитель такта анимации тайлов
  static const int32_t DIZZY_ANIMATION_TICK_COUNTER_DIVIDER=3;//делитель такта анимации Диззи
  static const int32_t MOVE_TICK_COUNTER_DIVIDER=7;//делитель такта перемещения Диззи
  
  static const int32_t DIZZY_WIDTH=25;//ширина спрайта Диззи
  static const int32_t DIZZY_HEIGHT=22;//высота спрайта Диззи
    
  static const int32_t SCREEN_WIDTH=320;//ширина экрана
  static const int32_t SCREEN_HEIGHT=240;//высота экрана

  static const int32_t TILE_WIDTH=16;//ширина тайла
  static const int32_t TILE_HEIGHT=16;//высота тайла
  static const int32_t TILE_BORDER_WIDTH=1;//ширина рамки
  static const int32_t TILE_BORDER_HEIGHT=1;//высота рамки  
  static const int32_t TILE_WITH_BORDER_WIDTH=TILE_WIDTH+TILE_BORDER_WIDTH+TILE_BORDER_WIDTH;//ширина тайла с рамкой
  static const int32_t TILE_WITH_BORDER_HEIGHT=TILE_HEIGHT+TILE_BORDER_HEIGHT+TILE_BORDER_HEIGHT;//высота тайла с рамкой

  static const int32_t USE_DELAY_COUNTER_MAX_VALUE=5;//максимальное значнение счётчика задержки до следующего нажатия кнопки "использовать"

  static const int32_t MAX_INVENTORY_SIZE=3;//максимальное количество предметов в инвентаре

  static const int32_t SPEED_X=2;//скорость Диззи по X
  static const int32_t SPEED_Y=2;//скорость Диззи по Y
 private:
  //-переменные-----------------------------------------------------------------------------------------
	   
  int32_t Map_X;//координаты левого верхнего угла карты
  int32_t Map_Y;

  CSprite cSprite_Dizzy;//спрайт Диззи
  CSprite cSprite_Frame;//рамки

  CSprite cSprite_Tiles;//тайлы
  CSprite cSprite_TilesBarrier;//непроницаемость тайлов
  
  int32_t X;//координаты Диззи на экране
  int32_t Y;

  int32_t dX;//скорости Диззи
  int32_t dY;

  //режимы движения Диззи
  enum MOVE
  {
   MOVE_STOP,
   MOVE_LEFT,
   MOVE_RIGHT,
   MOVE_JUMP,
   MOVE_JUMP_LEFT,
   MOVE_JUMP_RIGHT,
  };

  bool MoveControl;//управляем ли Dizzy игроком

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
  
  SFrame *sFrame_Stop_Ptr;//указатель на последовательность анимации "Диззи стоит"
  SFrame *sFrame_MoveLeft_Ptr;//указатель на последовательность анимации "Диззи идёт влево"
  SFrame *sFrame_MoveRight_Ptr;//указатель на последовательность анимации "Диззи идёт вправо"
  SFrame *sFrame_Jump_Ptr;//указатель на последовательность анимации "Диззи прыгает на месте"
  SFrame *sFrame_JumpLeft_Ptr;//указатель на последовательность анимации "Диззи прыгает влево"
  SFrame *sFrame_JumpRight_Ptr;//указатель на последовательность анимации "Диззи прыгает вправо"

  SFrame *sFrame_Ptr;//указатель на текущий кадр анимации

  std::vector<SFrame> sFrame_Array;//набор кадров для анимации Диззи

  int32_t TilesAnimationTickCounter;//счётчик анимации тайлов
  int32_t DizzyAnimationTickCounter;//счётчик анимации Диззи
  int32_t FlashTickCounter;//счётчик мигания надписи в инвентаре
  int32_t MoveTickCounter;//счётчик перемещения Диззи
  
  std::shared_ptr<CFontPrinter> cFontPrinter_Ptr;//указатель на класс работы со шрифтами

  CGameState cGameState;//состояние игры

  uint32_t UseDelayCounter;//счётчик до следующего нажатия кнопки "использовать"
  
  bool InventoryMode;//режим работы с инвентарём
  int32_t InventorySelectedIndex;//выбранная позиция в инвентаре
 public:
  //-конструктор----------------------------------------------------------------------------------------
  CGame(void);
  //-деструктор-----------------------------------------------------------------------------------------
  ~CGame();
 public:
  //-открытые функции-----------------------------------------------------------------------------------
  void OnTimer(bool left,bool right,bool up,bool down,bool fire,IVideo *iVideo_Ptr);//обработка таймера  
  bool Init(IVideo *iVideo_Ptr);//инициализация
 private:
  //-закрытые функции-----------------------------------------------------------------------------------  
  void OnPaint(IVideo *iVideo_Ptr);//отрисовать картинку  
  void KeyboardControl(bool left,bool right,bool up,bool down,bool fire);//управление от клавиатуры
  void PressUse(void);//нажата кнопка "использовать"
  void DizzyAnimation(void);//выполнить анимацию Диззи
  void DizzyMoveProcessing(IVideo *iVideo_Ptr);//обработка движения Диззи
  void TilesAnimation(void);//анимация всех тайлов
  void ConditionalProcessing(void);//выполнить обработку событий
  void Processing(IVideo *iVideo_Ptr);//обработка игрового поля
  bool IsCollizionLegs(IVideo *iVideo_Ptr,int32_t xp,int32_t yp);//проверить столкновение с блоками ног Диззи
  bool IsCollizionBody(IVideo *iVideo_Ptr,int32_t xp,int32_t yp);//проверить столкновение с блоками корпуса Диззи
  bool LoadMap(const std::string &file_name);//загрузить карту
  void DrawBarrier(IVideo *iVideo_Ptr);//нарисовать преграды
  void DrawMap(IVideo *iVideo_Ptr);//нарисовать карту
  void DrawFirstPlaneMap(IVideo *iVideo_Ptr);//нарисовать карту переднего плана
  void DrawItemMap(IVideo *iVideo_Ptr);//нарисовать карту предметов
  void PutMessage(CGameState::SMessage &sMessage,IVideo *iVideo_Ptr);//вывод сообщения
  void PutFrame(int32_t x,int32_t y,int32_t text_width,int32_t text_height,IVideo *iVideo_Ptr);//нарисовать рамку с заданным внутренним полем для текста (x,y,text_width,text_height - зона вывода текста)
  void PutInventory(IVideo *iVideo_Ptr);//вывести инвентарь
  void SetDescription(const std::string &name,const std::string &description);//задать описание
  void PushInventory(std::shared_ptr<IPart> iPart_Ptr);//положить в инвентарь
  std::shared_ptr<IPart> PopInventory(size_t index);//вынуть из инвентаря
  bool LoadConditional(const std::string &path,std::vector<std::string> &log);//загрузить условия игры
  bool LoadConditionalFile(const std::string &file_name,std::vector<std::string> &log);//загрузить файл условий игры
};

#endif