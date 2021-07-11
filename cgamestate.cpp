//****************************************************************************************************
//������������ ����������
//****************************************************************************************************
#include "cgamestate.h"

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
CGameState::CGameState(void)
{ 
}
//----------------------------------------------------------------------------------------------------
//����������
//----------------------------------------------------------------------------------------------------
CGameState::~CGameState()
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
//�������� ������ ��������� ��� ������ ��������
//----------------------------------------------------------------------------------------------------
void CGameState::ClearTake(void)
{
 Take.clear();
}
//----------------------------------------------------------------------------------------------------
//�������� ������ � ������ ��������� ��� ������
//----------------------------------------------------------------------------------------------------
void CGameState::AddTake(std::shared_ptr<IPart> iPart_Ptr)
{
 Take.push_back(iPart_Ptr);
}
//----------------------------------------------------------------------------------------------------
//�������� ���������
//----------------------------------------------------------------------------------------------------
void CGameState::AddMessage(const std::string &message,int32_t screen_x,int32_t screen_y)
{
 //���������� ������ ��������� � ��������
 SMessage sMessage;
 size_t length=message.length();
 std::string line;
 line.reserve(length);
 sMessage.InSymbolWidth=0;
 const char *ptr=message.c_str();
 for(size_t n=0;n<length;n++,ptr++)
 {
  uint8_t symbol=static_cast<uint8_t>(*ptr);  
  if (symbol!=static_cast<uint8_t>('\n')) line+=(*ptr);
  if (symbol==static_cast<uint8_t>('\n') || n==length-1)
  {
   size_t line_width=line.length();
   if (line_width>sMessage.InSymbolWidth) sMessage.InSymbolWidth=line_width;
   sMessage.Message.push_back(line); 
   line="";
  }  
 }
 sMessage.ScreenX=screen_x;
 sMessage.ScreenY=screen_y;
 sMessage.InSymbolHeight=sMessage.Message.size();
 Message.push_back(sMessage);
}