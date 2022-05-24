//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cconditionalofintersection.h"
#include <algorithm>

//****************************************************************************************************
//глобальные переменные
//****************************************************************************************************

//****************************************************************************************************
//константы
//****************************************************************************************************

//****************************************************************************************************
//макроопределения
//****************************************************************************************************

//****************************************************************************************************
//конструктор и деструктор
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CConditionalOfIntersection::CConditionalOfIntersection(const std::string &name_one,const std::string &name_two,std::shared_ptr<IAction> iAction_OneSetPtr,std::shared_ptr<IAction> iAction_TwoSetPtr)
{ 
 Name_One=name_one;
 Name_Two=name_two;
 iAction_OnePtr=iAction_OneSetPtr;
 iAction_TwoPtr=iAction_TwoSetPtr;
 Init();
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CConditionalOfIntersection::~CConditionalOfIntersection()
{
}

//****************************************************************************************************
//закрытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//инициализация
//----------------------------------------------------------------------------------------------------
void CConditionalOfIntersection::Init(void)
{
 if (iAction_OnePtr.get()!=NULL) iAction_OnePtr->Init();
 if (iAction_TwoPtr.get()!=NULL) iAction_TwoPtr->Init(); 
}

//****************************************************************************************************
//открытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//проверить условие и выполнить действие
//----------------------------------------------------------------------------------------------------
void CConditionalOfIntersection::Execute(int32_t dizzy_x,int32_t dizzy_y,int32_t dizzy_width,int32_t dizzy_height,int32_t part_width,int32_t part_height,bool use,bool timer,CGameState &cGameState)
{
 Init();
 //собираем список объектов для взаимодействия
 std::vector<std::shared_ptr<IPart> > first_part;
 std::vector<std::shared_ptr<IPart> > second_part;
 size_t size=cGameState.MapNamed.size();
 for(size_t n=0;n<size;n++)
 {
  std::shared_ptr<IPart> &iPart_Ptr=cGameState.MapNamed[n];
  if (iPart_Ptr->InInventory==true) continue;//предмет находится в инвентаре и с ним взаимодействовать нельзя
  if (iPart_Ptr->Enabled==false) continue;//предмет неактивен
  if (iPart_Ptr->Name.compare(Name_One)==0) first_part.push_back(iPart_Ptr);
  if (iPart_Ptr->Name.compare(Name_Two)==0) second_part.push_back(iPart_Ptr);
 }
 //проверяем пересечения их между собой
 size_t first_size=first_part.size();
 size_t second_size=second_part.size();
 for(size_t n=0;n<first_size;n++)
 {
  std::shared_ptr<IPart> &iPart_First_Ptr=first_part[n];
  int32_t x1=iPart_First_Ptr->BlockPosX;
  int32_t y1=iPart_First_Ptr->BlockPosY;
  int32_t x2=x1+part_width-1;
  int32_t y2=y1+part_height-1;

  for(size_t m=0;m<second_size;m++)
  {
   std::shared_ptr<IPart> &iPart_Second_Ptr=second_part[m];
   //проверяем пересечение
   int32_t xd1=iPart_Second_Ptr->BlockPosX;
   int32_t yd1=iPart_Second_Ptr->BlockPosY;
   int32_t xd2=xd1+part_width-1;
   int32_t yd2=yd1+part_height-1;
  
   if (xd1<x1 && xd2<x1) continue;
   if (xd1>x2 && xd2>x2) continue;
   if (yd1<y1 && yd2<y1) continue;
   if (yd1>y2 && yd2>y2) continue;

   //объекты пересекаются
   if (iAction_OnePtr.get()!=NULL) iAction_OnePtr->Execute(iPart_First_Ptr,cGameState);
   if (iAction_TwoPtr.get()!=NULL) iAction_TwoPtr->Execute(iPart_Second_Ptr,cGameState);
  }
 }
}
