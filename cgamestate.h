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
#include "iconditionalexpression.h"

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
  static const int32_t ENERGY_MAX_VALUE=100;//������������ �������� �������
  static const int32_t MAX_DIZZY_LIFE=3;//������������ ���������� ������ �����
  //-����������-----------------------------------------------------------------------------------------  
  std::vector<std::shared_ptr<IPart> > Take;//��������, ������� ����� �����
  std::vector<std::shared_ptr<IPart> > Inventory;//����������
  std::shared_ptr<IPart> UsedObject;//������������ �������
  std::vector<std::shared_ptr<IPart> > Map;//�����
  std::vector<std::shared_ptr<IPart> > MapNamed;//���������� ����� �����

  std::vector<SMessage> Message;//������ ���������

  std::vector<std::shared_ptr<IConditionalExpression> > ConditionalExpression;//����� �������� ��������� ������� ������

  int32_t Life;//���������� ������ �����
  int32_t Energy;//������� �����
  int32_t ScreenEnergy;//������������ �� ������ ������� �����
  int32_t Score;//��������� ���� �����
  int32_t ScreenScore;//������������ �� ������ ���� �����
  int32_t Items;//��������� ����� ��������

  bool InventoryMode;//����� ������ � ���������
  int32_t InventorySelectedIndex;//��������� ������� � ���������

  int32_t DizzyStartPositionX;//���������� X ��������� ������� �����
  int32_t DizzyStartPositionY;//���������� Y ��������� ������� �����

  int32_t X;//���������� ����� �� ������
  int32_t Y;

  int32_t Map_X;//���������� ������ �������� ���� �����
  int32_t Map_Y;


  SMessage sMessage_GameOver;//��������� � ����� ����
  SMessage sMessage_LifeLost;//��������� � ��������� �����
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
  SMessage CreateMessage(const std::string &message,int32_t screen_x,int32_t screen_y);//������� ���������
  void AddMessage(const std::string &message,int32_t screen_x,int32_t screen_y);//�������� ���������
  void AddMessageLifeLost(void);//�������� ��������� � ������ �����
  void AddMessageGameOver(void);//�������� ��������� � ���������� ����
  void SetLifeLostMessage(const std::string &message,int32_t screen_x,int32_t screen_y);//������ ��������� � ������ �����
  void SetGameOverMessage(const std::string &message,int32_t screen_x,int32_t screen_y);//������ ��������� � ���������� ����
  void EnergyUpdate(int32_t d_energy);//��������� ��������� ������� �����
  void AddScore(int32_t d_score);//�������� ���� �����
  void AddLife(void);//�������� ����� �����
  void AddItem(void);//�������� ��������� ������� �����
  void SetDizzyStartPosition(int32_t x,int32_t y);//������ ��������� ������� �����
  void Init(void);//������������� ����    
 private:
  //-�������� �������-----------------------------------------------------------------------------------  
};

#endif