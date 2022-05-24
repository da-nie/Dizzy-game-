//****************************************************************************************************
//������������ ����������
//****************************************************************************************************
#include "cconditionalofuse.h"
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
CConditionalOfUse::CConditionalOfUse(const std::string &name_one,const std::string &name_two,std::shared_ptr<IAction> iAction_OneSetPtr,std::shared_ptr<IAction> iAction_TwoSetPtr)
{ 
 Name_One=name_one;
 Name_Two=name_two;
 iAction_OnePtr=iAction_OneSetPtr;
 iAction_TwoPtr=iAction_TwoSetPtr;
 Init();
}
//----------------------------------------------------------------------------------------------------
//����������
//----------------------------------------------------------------------------------------------------
CConditionalOfUse::~CConditionalOfUse()
{
}

//****************************************************************************************************
//�������� �������
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//�������������
//----------------------------------------------------------------------------------------------------
void CConditionalOfUse::Init(void)
{
 if (iAction_OnePtr.get()!=NULL) iAction_OnePtr->Init();
 if (iAction_TwoPtr.get()!=NULL) iAction_TwoPtr->Init();
}

//****************************************************************************************************
//�������� �������
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//��������� ������� � ��������� ��������
//----------------------------------------------------------------------------------------------------
void CConditionalOfUse::Execute(int32_t dizzy_x,int32_t dizzy_y,int32_t dizzy_width,int32_t dizzy_height,int32_t part_width,int32_t part_height,bool use,bool timer,CGameState &cGameState)
{
 Init();

 if (use==false) return;//����� �������������� �� �������
 if (cGameState.UsedObject.get()==NULL) return;//��� ������������� ��������
 if (Name_One.compare(cGameState.UsedObject->Name)!=0) return;//����� �� ��������� 
 if (cGameState.UsedObject->InInventory==false) return;//������� �� ��������� � ���������
 if (cGameState.UsedObject->Enabled==false) return;//������� ���������
 
 std::shared_ptr<IAction> iAction_LocalTwoPtr=iAction_TwoPtr;
 bool one_object_is_used=false;
 std::string &name_two=Name_Two;
 auto execute_function=[this,&name_two,&one_object_is_used,&cGameState,&iAction_LocalTwoPtr,part_width,part_height](std::shared_ptr<IPart> iPart_Ptr)
 { 
  if (iPart_Ptr->Name.compare(name_two)!=0) return;//����� �� ���������
  if (iPart_Ptr->InInventory==true) return;//������� ��������� � ��������� � � ��� ����������������� ������
  if (iPart_Ptr->Enabled==false) return;//������� ���������
  //��������� �����������
  int32_t x1=iPart_Ptr->BlockPosX;
  int32_t y1=iPart_Ptr->BlockPosY;
  int32_t x2=x1+part_width-1;
  int32_t y2=y1+part_height-1;

  int32_t xd1=cGameState.UsedObject->BlockPosX;
  int32_t yd1=cGameState.UsedObject->BlockPosY;
  int32_t xd2=xd1+part_width-1;
  int32_t yd2=yd1+part_height-1;
  
  if (xd1<x1 && xd2<x1) return;
  if (xd1>x2 && xd2>x2) return;
  if (yd1<y1 && yd2<y1) return;
  if (yd1>y2 && yd2>y2) return;
  
  //������� ������������
  if (iAction_LocalTwoPtr.get()!=NULL) iAction_LocalTwoPtr->Execute(iPart_Ptr,cGameState);
  one_object_is_used=true;
 };
 std::for_each(cGameState.MapNamed.begin(),cGameState.MapNamed.end(),execute_function);

 if (one_object_is_used==true) 
 {  
  if (iAction_OnePtr.get()!=NULL) iAction_OnePtr->Execute(cGameState.UsedObject,cGameState);//��������� �������� � ������ ��������
  cGameState.UsedObject.reset();//������� ������ �� ������������
 }
}
