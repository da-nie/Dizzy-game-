//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "cdizzy.h"

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
CDizzy::CDizzy(void)
{ 
 //Диззи стоит
 sFrame_Array.push_back(SFrame(0,MOVE_STOP,false,NULL));//0 
 sFrame_Array.push_back(SFrame(1,MOVE_STOP,true,NULL));//1
 //Диззи идёт влево
 sFrame_Array.push_back(SFrame(9,MOVE_LEFT,false,NULL));//2 
 sFrame_Array.push_back(SFrame(10,MOVE_LEFT,false,NULL));//3
 sFrame_Array.push_back(SFrame(11,MOVE_LEFT,false,NULL));//4
 sFrame_Array.push_back(SFrame(12,MOVE_LEFT,false,NULL));//5
 sFrame_Array.push_back(SFrame(13,MOVE_LEFT,false,NULL));//6
 sFrame_Array.push_back(SFrame(14,MOVE_LEFT,false,NULL));//7
 sFrame_Array.push_back(SFrame(15,MOVE_LEFT,false,NULL));//8
 sFrame_Array.push_back(SFrame(16,MOVE_LEFT,true,NULL));//9
 //Диззи идёт вправо
 sFrame_Array.push_back(SFrame(17,MOVE_RIGHT,false,NULL));//10 
 sFrame_Array.push_back(SFrame(18,MOVE_RIGHT,false,NULL));//11
 sFrame_Array.push_back(SFrame(19,MOVE_RIGHT,false,NULL));//12
 sFrame_Array.push_back(SFrame(20,MOVE_RIGHT,false,NULL));//13
 sFrame_Array.push_back(SFrame(21,MOVE_RIGHT,false,NULL));//14
 sFrame_Array.push_back(SFrame(22,MOVE_RIGHT,false,NULL));//15
 sFrame_Array.push_back(SFrame(23,MOVE_RIGHT,false,NULL));//16
 sFrame_Array.push_back(SFrame(24,MOVE_RIGHT,true,NULL));//17
 //Диззи прыгает на месте
 sFrame_Array.push_back(SFrame(2,MOVE_JUMP,false,NULL));//18 
 sFrame_Array.push_back(SFrame(3,MOVE_JUMP,false,NULL));//19
 sFrame_Array.push_back(SFrame(4,MOVE_JUMP,false,NULL));//20
 sFrame_Array.push_back(SFrame(5,MOVE_JUMP,false,NULL));//21
 sFrame_Array.push_back(SFrame(6,MOVE_JUMP,false,NULL));//22
 sFrame_Array.push_back(SFrame(7,MOVE_JUMP,false,NULL));//23
 sFrame_Array.push_back(SFrame(8,MOVE_JUMP,true,NULL));//24
 //Диззи прыгает влево
 sFrame_Array.push_back(SFrame(25,MOVE_JUMP_LEFT,false,NULL));//25
 sFrame_Array.push_back(SFrame(26,MOVE_JUMP_LEFT,false,NULL));//26
 sFrame_Array.push_back(SFrame(27,MOVE_JUMP_LEFT,false,NULL));//27
 sFrame_Array.push_back(SFrame(28,MOVE_JUMP_LEFT,false,NULL));//28
 sFrame_Array.push_back(SFrame(29,MOVE_JUMP_LEFT,false,NULL));//29
 sFrame_Array.push_back(SFrame(30,MOVE_JUMP_LEFT,false,NULL));//30
 sFrame_Array.push_back(SFrame(31,MOVE_JUMP_LEFT,true,NULL));//31
 //Диззи прыгает вправо
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
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CDizzy::~CDizzy()
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
//анимация Диззи
//----------------------------------------------------------------------------------------------------
void CDizzy::Animation(void)
{
 if (sFrame_Ptr->sFrame_Next_Ptr!=NULL) sFrame_Ptr=sFrame_Ptr->sFrame_Next_Ptr;
                                   else sFrame_Ptr=sFrame_Stop_Ptr;
}
//----------------------------------------------------------------------------------------------------
//инициализация Диззи
//----------------------------------------------------------------------------------------------------
void CDizzy::Init(void)
{
 sFrame_Ptr=sFrame_Stop_Ptr;
}