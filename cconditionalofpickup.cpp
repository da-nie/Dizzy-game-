//****************************************************************************************************
//������������ ����������
//****************************************************************************************************
#include "cconditionalofpickup.h"
#include <algorithm>

//****************************************************************************************************
//���������� ����������
//****************************************************************************************************

//****************************************************************************************************
//���������
//****************************************************************************************************

//****************************************************************************************************
//����������������
//****************************************************************************************************

//****************************************************************************************************
//����������� � ����������
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//�����������
//----------------------------------------------------------------------------------------------------
CConditionalOfPickUp::CConditionalOfPickUp(const std::string &name,std::shared_ptr<IAction> iAction_SetPtr)
{
 Name=name;
 iAction_Ptr=iAction_SetPtr;
 Init();
}
//----------------------------------------------------------------------------------------------------
//����������
//----------------------------------------------------------------------------------------------------
CConditionalOfPickUp::~CConditionalOfPickUp()
{
}

//****************************************************************************************************
//�������� �������
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//�������������
//----------------------------------------------------------------------------------------------------
void CConditionalOfPickUp::Init(void)
{
 if (iAction_Ptr.get()!=NULL) iAction_Ptr->Init();
}

//****************************************************************************************************
//�������� �������
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//��������� ������� � ��������� ��������
//----------------------------------------------------------------------------------------------------
void CConditionalOfPickUp::Execute(int32_t dizzy_x,int32_t dizzy_y,int32_t dizzy_width,int32_t dizzy_height,int32_t part_width,int32_t part_height,bool use,bool timer,CGameState &cGameState)
{
 Init();

 if (use==false) return;

 std::shared_ptr<IAction> iAction_LocalPtr=iAction_Ptr;
 auto execute_function=[this,&cGameState,&iAction_LocalPtr,part_width,part_height,dizzy_x,dizzy_y,dizzy_width,dizzy_height](std::shared_ptr<IPart> iPart_Ptr)
 {  
  if (iPart_Ptr->Name.compare(Name)!=0) return;//����� �� ���������
  if (iPart_Ptr->InInventory==true) return;//������� ��� � ���������
  if (iPart_Ptr->Enabled==false) return;//������� ���������

  //��������� �����������
  int32_t x1=iPart_Ptr->BlockPosX;
  int32_t y1=iPart_Ptr->BlockPosY;
  int32_t x2=x1+part_width-1;
  int32_t y2=y1+part_height-1;

  int32_t xd1=dizzy_x;
  int32_t yd1=dizzy_y;
  int32_t xd2=xd1+dizzy_width-1;
  int32_t yd2=yd1+dizzy_height-1;
  
  if (xd1<x1 && xd2<x1) return;
  if (xd1>x2 && xd2>x2) return;
  if (yd1<y1 && yd2<y1) return;
  if (yd1>y2 && yd2>y2) return;
  
  //������� ������������
  if (iAction_LocalPtr.get()!=NULL) iAction_LocalPtr->Execute(iPart_Ptr,cGameState);
 };
 std::for_each(cGameState.Map.begin(),cGameState.Map.end(),execute_function);
}
