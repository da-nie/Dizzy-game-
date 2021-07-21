//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cpart.h"

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
CPart::CPart(int32_t block_x,int32_t block_y,const CTilesSequence &cTilesSequence_Set,bool barrier,bool first_plane,bool before_background,const std::string &name)
{
 BlockPosX=block_x;
 BlockPosY=block_y;
 cTilesSequence=cTilesSequence_Set;
 Barrier=barrier;
 FirstPlane=first_plane;
 BeforeBackground=before_background;
 Name=name;

 InInventory=false;
 Enabled=true;
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CPart::~CPart()
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
bool CPart::Save(std::ofstream &file)
{
 //сохраняем тип элемента
 uint8_t type=0;
 if (Barrier==true) type|=MASK_PART_IS_BARRIER;
 if (FirstPlane==true) type|=MASK_PART_IS_FIRST_PLANE;
 if (BeforeBackground==true) type|=MASK_PART_IS_BEFORE_BACKGROUND;
 if (file.write(reinterpret_cast<char*>(&type),sizeof(type)).fail()==true) return(false);
 //сохраняем координаты элемента
 if (file.write(reinterpret_cast<char*>(&BlockPosX),sizeof(BlockPosX)).fail()==true) return(false);
 if (file.write(reinterpret_cast<char*>(&BlockPosY),sizeof(BlockPosY)).fail()==true) return(false);
 //сохраняем имя элемента
 uint32_t name_length=Name.length();
 if (file.write(reinterpret_cast<char*>(&name_length),sizeof(name_length)).fail()==true) return(false);
 if (file.write(reinterpret_cast<const char*>(Name.c_str()),sizeof(char)*name_length).fail()==true) return(false);
 //сохраняем последовательность анимации тайлов элемента
 cTilesSequence.Save(file);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//сохранить
//----------------------------------------------------------------------------------------------------
bool CPart::Load(std::ifstream &file)
{
 //считываем тип
 uint8_t type;
 if (file.read(reinterpret_cast<char*>(&type),sizeof(type)).fail()==true) return(false);

 if (type&MASK_PART_IS_UNION) return(false);//неверный тип

 if (file.read(reinterpret_cast<char*>(&BlockPosX),sizeof(BlockPosX)).fail()==true) return(false);
 if (file.read(reinterpret_cast<char*>(&BlockPosY),sizeof(BlockPosY)).fail()==true) return(false);

 uint32_t name_length;
 if (file.read(reinterpret_cast<char*>(&name_length),sizeof(name_length)).fail()==true) return(false);
 Name.clear();
 std::vector<char> name(name_length+1);
 if (file.read(reinterpret_cast<char*>(&name[0]),sizeof(char)*name_length).fail()==true) return(false);
 name[name_length]=0;
 Name=&name[0];

 cTilesSequence.Load(file);

 if (type&MASK_PART_IS_BARRIER) Barrier=true;
                           else Barrier=false;
 if (type&MASK_PART_IS_FIRST_PLANE) FirstPlane=true;
                               else FirstPlane=false;
 if (type&MASK_PART_IS_BEFORE_BACKGROUND) BeforeBackground=true;
                        else BeforeBackground=false;
 return(true);
}
//----------------------------------------------------------------------------------------------------
//экспортировать
//----------------------------------------------------------------------------------------------------
bool CPart::Export(std::ofstream &file,int32_t scale_x,int32_t scale_y)
{
 //сохраняем тип элемента
 uint8_t type=0;
 if (Barrier==true) type|=MASK_PART_IS_BARRIER;
 if (FirstPlane==true) type|=MASK_PART_IS_FIRST_PLANE;
 if (BeforeBackground==true) type|=MASK_PART_IS_BEFORE_BACKGROUND;
 if (file.write(reinterpret_cast<char*>(&type),sizeof(type)).fail()==true) return(false);

 int32_t pos_x=scale_x*BlockPosX;
 int32_t pos_y=scale_y*BlockPosY;

 if (file.write(reinterpret_cast<char*>(&pos_x),sizeof(pos_x)).fail()==true) return(false);
 if (file.write(reinterpret_cast<char*>(&pos_y),sizeof(pos_y)).fail()==true) return(false);

 uint32_t name_length=Name.length();
 if (file.write(reinterpret_cast<char*>(&name_length),sizeof(name_length)).fail()==true) return(false);
 if (file.write(reinterpret_cast<const char*>(Name.c_str()),sizeof(char)*name_length).fail()==true) return(false);

 cTilesSequence.Save(file);

 return(true);
}
//----------------------------------------------------------------------------------------------------
//удалить все элементы
//----------------------------------------------------------------------------------------------------
void CPart::Release(void)
{
}
//----------------------------------------------------------------------------------------------------
//выполнить анимацию тайлов
//----------------------------------------------------------------------------------------------------
void CPart::AnimationTiles(void)
{
 cTilesSequence.ToNextTile();
}
//----------------------------------------------------------------------------------------------------
//выполнить анимацию тайлов принудительно
//----------------------------------------------------------------------------------------------------
void CPart::AnimationTilesByForce(void)
{
 cTilesSequence.ToNextTileByForce();
}
//----------------------------------------------------------------------------------------------------
//задать кадр анимации
//----------------------------------------------------------------------------------------------------
void CPart::SetTilesAnimationFrame(size_t frame)
{
 cTilesSequence.ToTile(frame);
}
//----------------------------------------------------------------------------------------------------
//обойти все элементы
//----------------------------------------------------------------------------------------------------
void CPart::Visit(std::function<void(std::shared_ptr<IPart>)> callback_function)
{
 callback_function(shared_from_this());//вызываем для самого себя
}
//----------------------------------------------------------------------------------------------------
//удалить часть
//----------------------------------------------------------------------------------------------------
void CPart::RemovePart(std::function<bool(std::shared_ptr<IPart>)> callback_function)
{
 //удаление возможно только для объединения частей
}
//----------------------------------------------------------------------------------------------------
//получить указатель на список элементов
//----------------------------------------------------------------------------------------------------
std::list<std::shared_ptr<IPart> >* CPart::GetItemPtr(void)
{
 return(NULL);
}
//----------------------------------------------------------------------------------------------------
//поместить предмет в инвентарь
//----------------------------------------------------------------------------------------------------
void CPart::PushInventory(void)
{
 InInventory=true;
}
//----------------------------------------------------------------------------------------------------
//забрать предмет из инвентаря
//----------------------------------------------------------------------------------------------------
void CPart::PopInventory(void)
{
 InInventory=false;
}
//----------------------------------------------------------------------------------------------------
//разрешить использование предмета
//----------------------------------------------------------------------------------------------------
void CPart::Enable(void)
{
 Enabled=true;
}
//----------------------------------------------------------------------------------------------------
//запретить использование предмета
//----------------------------------------------------------------------------------------------------
void CPart::Disable(void)
{
 Enabled=false;
}
