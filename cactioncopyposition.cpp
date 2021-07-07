//****************************************************************************************************
//������������ ����������
//****************************************************************************************************
#include "cactioncopyposition.h"
#include <Windows.h>

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
CActionCopyPosition::CActionCopyPosition(const std::string &name_one,const std::string &name_two,std::shared_ptr<IAction> iAction_Ptr)
{ 
 Name_One=name_one;
 Name_Two=name_two;
 iAction_NextPtr=iAction_Ptr;
}
//----------------------------------------------------------------------------------------------------
//����������
//----------------------------------------------------------------------------------------------------
CActionCopyPosition::~CActionCopyPosition()
{
}

//****************************************************************************************************
//�������� �������
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------

//****************************************************************************************************
//�������� �������
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//��������� �������� � ���������
//----------------------------------------------------------------------------------------------------
void CActionCopyPosition::Execute(std::shared_ptr<IPart> iPart_Ptr,CGameState &cGameState)
{
 //���� ������ ��������
 std::shared_ptr<IPart> part_one_ptr;
 std::shared_ptr<IPart> part_two_ptr;
 size_t size=cGameState.Map.size();
 for(size_t n=0;n<size;n++)
 {
  if (cGameState.Map[n]->Name.compare(Name_One)==0) part_one_ptr=cGameState.Map[n];
  if (cGameState.Map[n]->Name.compare(Name_Two)==0) part_two_ptr=cGameState.Map[n];
 }
 if (part_one_ptr.get()!=NULL && part_two_ptr.get()!=NULL)//��������� ������ ���������
 {  
  part_one_ptr->BlockPosX=part_two_ptr->BlockPosX;
  part_one_ptr->BlockPosY=part_two_ptr->BlockPosY;
 }
 if (iAction_NextPtr.get()!=NULL) iAction_NextPtr->Execute(iPart_Ptr,cGameState);	
}