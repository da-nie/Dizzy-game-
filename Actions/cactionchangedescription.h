#ifndef C_ACTION_CHANGE_DESCRIPTION_H
#define C_ACTION_CHANGE_DESCRIPTION_H

//****************************************************************************************************
//����� �������� "�������� ��������"
//****************************************************************************************************

//****************************************************************************************************
//������������ ����������
//****************************************************************************************************
#include "iaction.h"
#include <stdint.h>
#include <string>
#include <memory>

//****************************************************************************************************
//����������������
//****************************************************************************************************

//****************************************************************************************************
//���������
//****************************************************************************************************

//****************************************************************************************************
//��������������� ����������
//****************************************************************************************************

//****************************************************************************************************
//����� �������� "�������� ��������"
//****************************************************************************************************
class CActionChangeDescription:public IAction
{
 public:
  //-������������---------------------------------------------------------------------------------------
  //-���������------------------------------------------------------------------------------------------
  //-���������------------------------------------------------------------------------------------------
 private:
  //-����������-----------------------------------------------------------------------------------------
  std::string Description;//����� ��������
  std::shared_ptr<IAction> iAction_NextPtr;//��������� �� ��������� ��������
 public:
  //-�����������----------------------------------------------------------------------------------------
  CActionChangeDescription(const std::string &description,std::shared_ptr<IAction> iAction_Ptr=std::shared_ptr<IAction>(NULL));
  //-����������-----------------------------------------------------------------------------------------
  ~CActionChangeDescription();
 public:
  //-�������� �������-----------------------------------------------------------------------------------
  void Execute(std::shared_ptr<IPart> iPart_Ptr,CGameState &cGameState);//��������� �������� � ���������
  void Init(void);//�������������
 private:
  //-�������� �������-----------------------------------------------------------------------------------  
};

#endif