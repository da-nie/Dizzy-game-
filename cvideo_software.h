#ifndef C_VIDEO_SOFTWARE_H
#define C_VIDEO_SOFTWARE_H

//****************************************************************************************************
//класс программной растеризации
//****************************************************************************************************

//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************

#include <stdint.h>
#include <memory>
#include "ivideo.h"

//****************************************************************************************************
//класс программной растеризации
//****************************************************************************************************

class CVideo_Software:public IVideo
{
 private:
  //-консанты-------------------------------------------------------------------------------------------
  static const uint32_t FONT_WIDTH=8;//ширина шрифта
  static const uint32_t FONT_HEIGHT=14;//высота шрифта
  //-переменные-----------------------------------------------------------------------------------------
  std::unique_ptr<uint32_t[]> VideoBuffer_Ptr;//видеобуфер
  std::unique_ptr<uint32_t[]> VideoBuffer_Copy_Ptr;//копия видеобуфера
  uint32_t LineSize;//длина строки
  uint32_t ScreenWidth;//ширина экрана
  uint32_t ScreenHeight;//высота экрана
 public:
  //-конструктор----------------------------------------------------------------------------------------
  CVideo_Software(uint32_t width,uint32_t height);
  //-деструктор-----------------------------------------------------------------------------------------
  ~CVideo_Software();
 public:
  //-открытые функции-----------------------------------------------------------------------------------
  void Init(void);//инициализизация видеорежима
  void GetScreenSize(uint32_t &width,uint32_t &height) const;//получить размеры экрана
  void SetScreenSize(uint32_t width,uint32_t height);//задать размеры экрана
  void GetVideoPointer(void* &vptr);//получить указатель на видеобуфер
  void GetLineSize(uint32_t &linesize) const;//получить размер строки в пикселях
  void PutSymbol(int64_t x,int64_t y,char symbol,uint32_t color);//вывод символа в позицию
  void PutString(int64_t x,int64_t y,const char *string,uint32_t color);//вывод строчки в позицию
   void PutStringWithIncrementHeight(int64_t x,int64_t &y,const char *string,uint32_t color);//вывод строчки в позицию с инкрементом координаты Y
  void DrawPoint(int64_t x,int64_t y,uint32_t color);//рисование точки
  void DrawLine(int64_t x1,int64_t y1,int64_t x2,int64_t y2,uint32_t color,uint32_t thickness,LINE_TYPE line_type);//рисование линии
  void GetStringImageSize(const char *string,uint32_t &width,uint32_t &height);//получить размер строки в пикселях  
  void FillRectangle(int64_t x1,int64_t y1,int64_t x2,int64_t y2,uint32_t color);//нарисовать закрашенный прямоугольник
  void SaveScreen(void);//сохранить изображение в память
  void RestoreScreen(void);//восстановить изображение из памяти
  void ClearScreen(uint32_t color);//очистить экран
 private:
  //-закрытые функции-----------------------------------------------------------------------------------
};

#endif
