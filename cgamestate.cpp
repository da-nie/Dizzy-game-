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