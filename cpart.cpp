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
CPart::CPart(int32_t block_x,int32_t block_y,const CTilesSequence &cTilesSequence_Set,bool barrier,const std::string &name)
{
 BlockPosX=block_x;
 BlockPosY=block_y;
 cTilesSequence=cTilesSequence_Set;
 Barrier=barrier;
 Name=name;
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
 if (file.write(reinterpret_cast<char*>(&BlockPosX),sizeof(BlockPosX)).fail()==true) return(false);
 if (file.write(reinterpret_cast<char*>(&BlockPosY),sizeof(BlockPosY)).fail()==true) return(false);

 uint32_t name_length=Name.length();
 if (file.write(reinterpret_cast<char*>(&name_length),sizeof(name_length)).fail()==true) return(false);
 if (file.write(reinterpret_cast<const char*>(Name.c_str()),sizeof(char)*name_length).fail()==true) return(false);

 cTilesSequence.Save(file);

 static const uint8_t NO_BARRIER_TYPE=0;
 static const uint8_t BARRIER_TYPE=1;
 uint8_t barrier=NO_BARRIER_TYPE;
 if (Barrier==true) barrier=BARRIER_TYPE;

 if (file.write(reinterpret_cast<char*>(&barrier),sizeof(barrier)).fail()==true) return(false);

 return(true);
}
//----------------------------------------------------------------------------------------------------
//сохранить
//----------------------------------------------------------------------------------------------------
bool CPart::Load(std::ifstream &file)
{
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

 static const uint8_t NO_BARRIER_TYPE=0;
 static const uint8_t BARRIER_TYPE=1;

 uint8_t barrier;
 if (file.read(reinterpret_cast<char*>(&barrier),sizeof(barrier)).fail()==true) return(false);

 Barrier=false;
 if (barrier==BARRIER_TYPE) Barrier=true;

 return(true);
}
//----------------------------------------------------------------------------------------------------
//экспортировать
//----------------------------------------------------------------------------------------------------
bool CPart::Export(std::ofstream &file,int32_t scale_x,int32_t scale_y)
{
 int32_t pos_x=scale_x*BlockPosX;
 int32_t pos_y=scale_y*BlockPosY;

 if (file.write(reinterpret_cast<char*>(&pos_x),sizeof(pos_x)).fail()==true) return(false);
 if (file.write(reinterpret_cast<char*>(&pos_y),sizeof(pos_y)).fail()==true) return(false);

 uint32_t name_length=Name.length();
 if (file.write(reinterpret_cast<char*>(&name_length),sizeof(name_length)).fail()==true) return(false);
 if (file.write(reinterpret_cast<const char*>(Name.c_str()),sizeof(char)*name_length).fail()==true) return(false);

 cTilesSequence.Save(file);

 static const uint8_t NO_BARRIER_TYPE=0;
 static const uint8_t BARRIER_TYPE=1;
 uint8_t barrier=NO_BARRIER_TYPE;
 if (Barrier==true) barrier=BARRIER_TYPE;

 if (file.write(reinterpret_cast<char*>(&barrier),sizeof(barrier)).fail()==true) return(false);
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
void CPart::AnimateTiles(void)
{
 cTilesSequence.ToNextTile();
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
std::list<std::shared_ptr<IPart>>* CPart::GetItemPtr(void)
{
 return(NULL);
}
