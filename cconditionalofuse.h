#ifndef C_CONDITIONAL_OF_USE_H
#define C_CONDITIONAL_OF_USE_H

//****************************************************************************************************
//����� ��������� ��������� "������������"
//****************************************************************************************************

//****************************************************************************************************
//������������ ����������
//****************************************************************************************************
#include "iconditionalexpression.h"
#include "iaction.h"
#include <string>
#include <stdint.h>

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
//����� ��������� ��������� "������������"
//****************************************************************************************************
class CConditionalOfUse:public IConditionalExpression
{
 public:
  //-������������---------------------------------------------------------------------------------------
  //-���������------------------------------------------------------------------------------------------
  //-���������------------------------------------------------------------------------------------------
 private:
  //-����������-----------------------------------------------------------------------------------------
  std::string Name_One;//������ �������
  std::string Name_Two;//������ �������
  std::shared_ptr<IAction> iAction_OnePtr;//��������� �� �������� � ������ ��������
  std::shared_ptr<IAction> iAction_TwoPtr;//��������� �� �������� �� ������ ��������
 public:
  //-�����������----------------------------------------------------------------------------------------
  CConditionalOfUse(const std::string &name_one,const std::string &name_two,std::shared_ptr<IAction> iAction_OneSetPtr,std::shared_ptr<IAction> iAction_TwoSetPtr);
  //-����������-----------------------------------------------------------------------------------------
  ~CConditionalOfUse();
 public:
  //-�������� �������-----------------------------------------------------------------------------------
  void Execute(std::vector<std::shared_ptr<IPart> > &Map,int32_t dizzy_x,int32_t dizzy_y,int32_t dizzy_width,int32_t dizzy_height,int32_t part_width,int32_t part_height,bool use,CGameState &cGameState);//��������� ������� � ��������� ��������
  void Init(void);//�������������
 private:
  //-�������� �������-----------------------------------------------------------------------------------  
};

#endif