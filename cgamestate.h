#ifndef C_GAME_STATE_H
#define C_GAME_STATE_H

//****************************************************************************************************
//����� ��������� ����
//****************************************************************************************************

//****************************************************************************************************
//������������ ����������
//****************************************************************************************************
#include <memory>
#include <stdint.h>
#include <vector>
#include <string>
#include "ipart.h"

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
//����� ��������� ����
//****************************************************************************************************
class CGameState
{
 public:
  //-������������---------------------------------------------------------------------------------------
  //-���������------------------------------------------------------------------------------------------
  //��������� ���������
  struct SMessage
  {
   int32_t ScreenX;//���������� ������ �������� ���� �� ������
   int32_t ScreenY;
   int32_t InSymbolWidth;//������ � ��������
   int32_t InSymbolHeight;//������ � ��������
   std::vector<std::string> Message;//��������� ���������
  };
  //-���������------------------------------------------------------------------------------------------
  //-����������-----------------------------------------------------------------------------------------  
  std::vector<std::shared_ptr<IPart> > Take;//��������, ������� ����� �����
  std::vector<std::shared_ptr<IPart> > Inventory;//����������
  std::shared_ptr<IPart> UsedObject;//������������ �������
  std::vector<std::shared_ptr<IPart> > Map;//�����

  std::vector<SMessage> Message;//������ ���������
 private:
  //-����������-----------------------------------------------------------------------------------------  
 public:
  //-�����������----------------------------------------------------------------------------------------
  CGameState(void);
  //-����������-----------------------------------------------------------------------------------------
  ~CGameState();
 public:
  //-�������� �������-----------------------------------------------------------------------------------
  void ClearTake(void);//�������� ������ ��������� ��� ������ ��������
  void AddTake(std::shared_ptr<IPart> iPart_Ptr);//�������� ������ � ������ ��������� ��� ������
  void AddMessage(const std::string &message,int32_t screen_x,int32_t screen_y);//�������� ���������
 private:
  //-�������� �������-----------------------------------------------------------------------------------  
};

#endif