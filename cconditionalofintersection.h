#ifndef C_CONDITIONAL_OF_INTERSECTION_H
#define C_CONDITIONAL_OF_INTERSECTION_H

//****************************************************************************************************
//����� ��������� ��������� "�����������"
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
//����� ��������� ��������� "�����������"
//****************************************************************************************************
class CConditionalOfIntersection:public IConditionalExpression
{
 public:
  //-������������---------------------------------------------------------------------------------------
  //-���������------------------------------------------------------------------------------------------
  //-���������------------------------------------------------------------------------------------------
 private:
  //-����������-----------------------------------------------------------------------------------------
  std::string Name;//��� �������, ����������� � ������� �����������
  std::shared_ptr<IAction> iAction_Ptr;//��������� �� ����������� ��������
 public:
  //-�����������----------------------------------------------------------------------------------------
  CConditionalOfIntersection(const std::string &name,std::shared_ptr<IAction> iAction_SetPtr);
  //-����������-----------------------------------------------------------------------------------------
  ~CConditionalOfIntersection();
 public:
  //-�������� �������-----------------------------------------------------------------------------------
  void Execute(std::vector<std::shared_ptr<IPart> > &Map,int32_t dizzy_x,int32_t dizzy_y,int32_t dizzy_width,int32_t dizzy_height,int32_t part_width,int32_t part_height,bool use,CGameState &cGameState);//��������� ������� � ��������� ��������
 private:
  //-�������� �������-----------------------------------------------------------------------------------  
  void Init(void);//�������������
};

#endif