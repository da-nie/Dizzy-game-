//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cpartunion.h"
#include "cpart.h"
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
CPartUnion::CPartUnion(void)
{
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CPartUnion::~CPartUnion()
{
 Release();
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
//записать
//----------------------------------------------------------------------------------------------------
bool CPartUnion::Save(std::ofstream &file)
{
 //сохраняем тип элемента
 uint8_t type=0;
 type|=MASK_PART_IS_UNION;
 if (file.write(reinterpret_cast<char*>(&type),sizeof(type)).fail()==true) return(false);

 size_t part=Item.size();
 if (file.write(reinterpret_cast<char*>(&part),sizeof(part)).fail()==true) return(false);

 auto save_function=[&file](std::shared_ptr<IPart> iPart_Ptr)
 {
  iPart_Ptr->Save(file);
 };
 std::for_each(Item.begin(),Item.end(),save_function);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//загрузить
//----------------------------------------------------------------------------------------------------
bool CPartUnion::Load(std::ifstream &file)
{
 //считываем тип
 uint8_t type;
 if (file.read(reinterpret_cast<char*>(&type),sizeof(type)).fail()==true) return(false);

 if (!(type&MASK_PART_IS_UNION)) return(false);//неверный тип

 size_t part;
 if (file.read(reinterpret_cast<char*>(&part),sizeof(part)).fail()==true) return(false);
 for(size_t n=0;n<part;n++)
 {
  //загружаем, какого типа объект нам нужно создавать  
  if (file.read(reinterpret_cast<char*>(&type),sizeof(type)).fail()==true) return(false);
  //возвращаемся назад, так как сам класс тоже будет считывать свой тип
  file.seekg(-static_cast<int32_t>(sizeof(type)),std::ios_base::cur);

  IPart *iPart_Ptr=NULL;
  if (type&MASK_PART_IS_UNION) iPart_Ptr=new CPartUnion();
                          else iPart_Ptr=new CPart();
  iPart_Ptr->Load(file);
  Item.push_back(std::shared_ptr<IPart>(iPart_Ptr));
 }
 return(true);
}
//----------------------------------------------------------------------------------------------------
//экспортировать
//----------------------------------------------------------------------------------------------------
bool CPartUnion::Export(std::ofstream &file,int32_t scale_x,int32_t scale_y)
{
 auto export_function=[&file,scale_x,scale_y](std::shared_ptr<IPart> iPart_Ptr)
 {
  iPart_Ptr->Export(file,scale_x,scale_y);
 };
 std::for_each(Item.begin(),Item.end(),export_function);
}
//----------------------------------------------------------------------------------------------------
//получить указатель на список элементов
//----------------------------------------------------------------------------------------------------
std::list<std::shared_ptr<IPart> >* CPartUnion::GetItemPtr(void)
{
 return(&Item);
}
//----------------------------------------------------------------------------------------------------
//удалить все элементы
//----------------------------------------------------------------------------------------------------
void CPartUnion::Release(void)
{
 auto release_function=[](std::shared_ptr<IPart> iPart_Ptr)
 {
  iPart_Ptr->Release();
 };
 std::for_each(Item.begin(),Item.end(),release_function);
 Item.clear();
}
//----------------------------------------------------------------------------------------------------
//обойти все элементы
//----------------------------------------------------------------------------------------------------
void CPartUnion::Visit(std::function<void(std::shared_ptr<IPart>)> callback_function)
{
 callback_function(shared_from_this());//вызываем для самого себя
 auto visit_function=[&callback_function](std::shared_ptr<IPart> iPart_Ptr)
 {
  iPart_Ptr->Visit(callback_function);
 };
 std::for_each(Item.begin(),Item.end(),visit_function);
}
//----------------------------------------------------------------------------------------------------
//удалить часть
//----------------------------------------------------------------------------------------------------
void CPartUnion::RemovePart(std::function<bool(std::shared_ptr<IPart>)> callback_function)
{
 auto compare_function=[&callback_function](std::shared_ptr<IPart> iPart_Ptr)->bool
 {
  if (iPart_Ptr->GetItemPtr()!=NULL)
  {
   iPart_Ptr->RemovePart(callback_function);
   if (iPart_Ptr->GetItemPtr()->size()!=0) return(false);//ветка ещё не пустая
   return(true);//требуется удаление
  }
  if (callback_function(iPart_Ptr)==true) return(true);//требуется удаление
  return(false);
 };
 Item.erase(std::remove_if(Item.begin(),Item.end(),compare_function),Item.end());
}
//----------------------------------------------------------------------------------------------------
//выполнить анимацию тайлов
//----------------------------------------------------------------------------------------------------
void CPartUnion::AnimationTiles(void)
{
 auto animationtiles_function=[](std::shared_ptr<IPart> iPart_Ptr)
 {
  iPart_Ptr->AnimationTiles();
 };
 std::for_each(Item.begin(),Item.end(),animationtiles_function);
}
//----------------------------------------------------------------------------------------------------
//выполнить анимацию тайлов принудительно
//----------------------------------------------------------------------------------------------------
void CPartUnion::AnimationTilesByForce(void)
{
 auto animationtiles_function=[](std::shared_ptr<IPart> iPart_Ptr)
 {
  iPart_Ptr->AnimationTilesByForce();
 };
 std::for_each(Item.begin(),Item.end(),animationtiles_function);
}
//----------------------------------------------------------------------------------------------------
//задать кадр анимации
//----------------------------------------------------------------------------------------------------
void CPartUnion::SetTilesAnimationFrame(size_t frame)
{
 auto setanimationframe_function=[&frame](std::shared_ptr<IPart> iPart_Ptr)
 {
  iPart_Ptr->SetTilesAnimationFrame(frame);
 };
 std::for_each(Item.begin(),Item.end(),setanimationframe_function);
}


