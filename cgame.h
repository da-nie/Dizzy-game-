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
#include "cdizzy.h"

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

  static const uint8_t BLEND_COLOR_R=81;//прозрачный цвет, компонент R
  static const uint8_t BLEND_COLOR_G=162;//прозрачный цвет, компонент G
  static const uint8_t BLEND_COLOR_B=243;//прозрачный цвет, компонент B
  static const uint32_t SKY_COLOR=(0<<24)|(BLEND_COLOR_R<<16)|(BLEND_COLOR_G<<8)|(BLEND_COLOR_B<<0);//цвет неба
  static const uint32_t BLEND_COLOR=(00<<24)|(BLEND_COLOR_R<<16)|(BLEND_COLOR_G<<8)|(BLEND_COLOR_B<<0);//прозрачный цвет

  static const uint8_t NO_BARRIER_COLOR_R=0;//цвет отсутствия препятствий, компонент R
  static const uint8_t NO_BARRIER_COLOR_G=0;//цвет отсутствия препятствий, компонент G
  static const uint8_t NO_BARRIER_COLOR_B=0;//цвет отсутствия препятствий, компонент B
  static const uint32_t NO_BARRIER_COLOR=(0x00<<24)|(NO_BARRIER_COLOR_R<<16)|(NO_BARRIER_COLOR_G<<8)|(NO_BARRIER_COLOR_B<<0);//цвет остутствия препятствий

  static const uint32_t ENERGY_GOOD_COLOR=(0<<24)|(64<<16)|(255<<8)|(64<<0);//цвет "отлично"
  static const uint32_t ENERGY_NORMAL_COLOR=(0<<24)|(255<<16)|(255<<8)|(64<<0);//цвет "хорошо"
  static const uint32_t ENERGY_BAD_COLOR=(0<<24)|(255<<16)|(64<<8)|(64<<0);//цвет "плохо"

  static const int32_t TILES_ANIMATION_TICK_COUNTER_DIVIDER=7;//делитель такта анимации тайлов
  static const int32_t FLASH_TICK_COUNTER_DIVIDER=6;//делитель такта для мигания инвентаря
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

  static const size_t STRING_BUFFER_SIZE=255;//размер буфера строки
 private:
  //-переменные-----------------------------------------------------------------------------------------
  CDizzy cDizzy;//Диззи

  CSprite cSprite_Dizzy;//спрайт Диззи
  CSprite cSprite_Frame;//рамки
  CSprite cSprite_ScreenFrame;//рамки для экрана
  CSprite cSprite_Header;//заголовок экрана

  CSprite cSprite_Tiles;//тайлы
  CSprite cSprite_TilesBarrier;//непроницаемость тайлов
  
  int32_t dX;//скорости Диззи
  int32_t dY;

  bool MoveControl;//управляем ли Dizzy игроком

  int32_t TilesAnimationTickCounter;//счётчик анимации тайлов
  int32_t DizzyAnimationTickCounter;//счётчик анимации Диззи
  int32_t FlashTickCounter;//счётчик мигания надписи в инвентаре
  int32_t MoveTickCounter;//счётчик перемещения Диззи
  
  std::shared_ptr<CFontPrinter> cFontPrinter_Ptr;//указатель на класс работы со шрифтами

  CGameState cGameState;//состояние игры

  uint32_t UseDelayCounter;//счётчик до следующего нажатия кнопки "использовать"
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
  void DizzyEnergyProcessing(IVideo *iVideo_Ptr);//выполнить обработку энергии Диззи
  void Processing(IVideo *iVideo_Ptr);//обработка игрового поля
  bool IsCollizionLegs(IVideo *iVideo_Ptr,int32_t xp,int32_t yp);//проверить столкновение с блоками ног Диззи
  bool IsCollizionBody(IVideo *iVideo_Ptr,int32_t xp,int32_t yp);//проверить столкновение с блоками корпуса Диззи
  void DrawBarrier(IVideo *iVideo_Ptr);//нарисовать преграды
  void DrawMap(IVideo *iVideo_Ptr);//нарисовать карту
  void DrawFirstPlaneMap(IVideo *iVideo_Ptr);//нарисовать карту переднего плана
  void DrawBeforeBackgroundMap(IVideo *iVideo_Ptr);//нарисовать карту тайлов перед фоном
  void PutMessage(CGameState::SMessage &sMessage,IVideo *iVideo_Ptr);//вывод сообщения
  void PutFrame(int32_t x,int32_t y,int32_t text_width,int32_t text_height,IVideo *iVideo_Ptr);//нарисовать рамку с заданным внутренним полем для текста (x,y,text_width,text_height - зона вывода текста)
  void PutInventory(IVideo *iVideo_Ptr);//вывести инвентарь
  void SetDescription(const std::string &name,const std::string &description);//задать описание
  void PushInventory(std::shared_ptr<IPart> iPart_Ptr);//положить в инвентарь
  std::shared_ptr<IPart> PopInventory(size_t index);//вынуть из инвентаря
  void DrawScreenFrame(IVideo *iVideo_Ptr);//нарисовать экранную рамку
  void VisitTree(std::shared_ptr<CGameState::SQuadricTree> &sQuadricTree_Ptr,CGameState::SVisitTree &sVisitTree);//функция обхода дерева
  bool LoadMap(const std::string &file_name);//загрузить карту
  std::shared_ptr<CGameState::SQuadricTree> LoadNode(std::ifstream &file,bool &is_tree,uint8_t &leaf_mask);//загрузить узел квадратичного дерева
  std::shared_ptr<CGameState::SQuadricTree> LoadQuadricTree(std::ifstream &file);//загрузить квадратичное дерево
  bool LoadConditional(const std::string &path,std::vector<std::string> &log);//загрузить условия игры
  bool LoadConditionalFile(const std::string &file_name,std::vector<std::string> &log);//загрузить файл условий игры
  void ChangeDizzyCoord(int32_t dx,int32_t dy,IVideo *iVideo_Ptr);//изменить координаты Диззи, переместить карту и перерисовать барьеры
  void MoveMap(IVideo *iVideo_Ptr);//выполнить перемещение карты, если требуется
  bool MoveMapStep(int32_t width,int32_t height,int32_t offset_y);//выполнить перемещение карты на один шаг, если требуется
};

#endif