#ifndef C_SYNTAX_ANALYZER_H
#define C_SYNTAX_ANALYZER_H

//****************************************************************************************************
//����� ��������������� �����������
//****************************************************************************************************

//****************************************************************************************************
//������������ ����������
//****************************************************************************************************
#include "clexicalanalyzer.h"
#include "cautomath.h"
#include "iconditionalexpression.h"
#include "iaction.h"
#include "cgamestate.h"
#include <vector>
#include <string>

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
//����� ��������������� �����������
//****************************************************************************************************
class CSyntaxAnalyzer
{
 public:
  //-������������---------------------------------------------------------------------------------------
  enum LEXEME_TYPE
  {
   ID_LEXEME_TYPE_MNW_MODE=CLexeme::ID_LEXEME_USER,
   ID_LEXEME_TYPE_BOOL,
   ID_LEXEME_TYPE_ANIMATION_MODE,
   ID_LEXEME_TYPE_SET_DESCRIPTION,
   ID_LEXEME_TYPE_COPY_POSITION,
   ID_LEXEME_TYPE_COPY_POSITION_OFFSET,
   ID_LEXEME_TYPE_SET_DIZZY_POSITION,
   ID_LEXEME_TYPE_SET_LIFE_LOST_MESSAGE,
   ID_LEXEME_TYPE_SET_GAME_OVER_MESSAGE,
   //������� ��������
   ID_LEXEME_TYPE_ACTION_MESSAGE,
   ID_LEXEME_TYPE_ACTION_CHANGE_NAME,
   ID_LEXEME_TYPE_ACTION_CHANGE_DESCRIPTION, 
   ID_LEXEME_TYPE_ACTION_CHANGE_NAME_GLOBAL,
   ID_LEXEME_TYPE_ACTION_CHANGE_DESCRIPTION_GLOBAL, 
   ID_LEXEME_TYPE_ACTION_CHANGE_POSITION,
   ID_LEXEME_TYPE_ACTION_COPY_POSITION,
   ID_LEXEME_TYPE_ACTION_COPY_POSITION_OFFSET,
   ID_LEXEME_TYPE_ACTION_PICK_UP,
   ID_LEXEME_TYPE_ACTION_SET_ANIMATION_STEP,
   ID_LEXEME_TYPE_ACTION_SET_ENABLED, 
   ID_LEXEME_TYPE_ACTION_SINGLE, 
   ID_LEXEME_TYPE_ACTION_MOVE,
   ID_LEXEME_TYPE_ACTION_ENERGY_UPDATE,
   ID_LEXEME_TYPE_ACTION_ADD_SCORE,
   ID_LEXEME_TYPE_ACTION_ADD_LIFE,
   ID_LEXEME_TYPE_ACTION_ADD_ITEM,
   ID_LEXEME_TYPE_ACTION_CHANGE_ANIMATION_MODE,
   //������� �������
   ID_LEXEME_TYPE_IF_INTERSECTION,
   ID_LEXEME_TYPE_IF_DIZZY_INTERSECTION,
   ID_LEXEME_TYPE_IF_NOT_DIZZY_INTERSECTION,
   ID_LEXEME_TYPE_IF_PICK_UP,
   ID_LEXEME_TYPE_IF_USE,
   ID_LEXEME_TYPE_IF_TIMER,

   ID_LEXEME_TYPE_ACTION_FIRST_BEGIN,
   ID_LEXEME_TYPE_ACTION_FIRST_END,

   ID_LEXEME_TYPE_ACTION_SECOND_BEGIN,
   ID_LEXEME_TYPE_ACTION_SECOND_END,

   ID_LEXEME_TYPE_ACTION_BEGIN,
   ID_LEXEME_TYPE_ACTION_END
  };  

  enum MODE//����� ������
  {
   MODE_WAIT_COMMAND,//�������� �������
   MODE_WAIT_ACTION_FIRST_BEGIN,//�������� ������ ������� ��������
   MODE_WAIT_ACTION_SECOND_BEGIN,//�������� ������ ������� ��������
   MODE_WAIT_ACTION_BEGIN,//�������� ������ ��������
   MODE_ADD_ACTION_FIRST,//������ ������� ��������
   MODE_ADD_ACTION_SECOND,//������ ������� ��������
   MODE_ADD_ACTION//������ ��������
  };

  //-���������------------------------------------------------------------------------------------------
  //-���������------------------------------------------------------------------------------------------
 private:
  //-����������-----------------------------------------------------------------------------------------
  CLexicalAnalyzer cLexicalAnalyzer;//����������� ����������
  CAutomath cAutomath_Syntax;//������� ��������������� �������  
  std::vector<CLexeme> vector_CLexeme;//��������� ������ ������ �������

  MODE Mode;//����� ������ �����������

  std::vector<std::vector<CLexeme> > CommandLexeme;//������ ������ �������
 public:
  //-�����������----------------------------------------------------------------------------------------
  CSyntaxAnalyzer(void);
  //-����������-----------------------------------------------------------------------------------------
  ~CSyntaxAnalyzer();
 public:
  //-�������� �������-----------------------------------------------------------------------------------
  bool Processing(char symbol,int32_t line_index,std::string &message,bool &new_line,CGameState &cGameState);//������� ������� ������
 private:
  //-�������� �������-----------------------------------------------------------------------------------  
  double ConvertAngleToSec(const char *string);//�������� ���� �� ������ ������� a'b'c
  void SetDescription(const std::string &name,const std::string &description,std::vector<std::shared_ptr<IPart> > &Map);//������ ��������
  void CopyPosition(const std::string &name_first,const std::string &name_second,int32_t offset_x,int32_t offset_y,std::vector<std::shared_ptr<IPart> > &Map);//����������� ������ � �������� �������
  void SetDizzyPosition(const std::string &name,CGameState &cGameState);//����������� ����� � �������� �������
  bool ModeWaitCommand(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message,CGameState &cGameState);//��������� ������� � ������ MODE_WAIT_COMMAND
  bool ModeWaitActionBegin(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message);//��������� ������� � ������ MODE_WAIT_ACTION_BEGIN
  bool ModeWaitActionFirstBegin(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message);//��������� ������� � ������ MODE_WAIT_ACTION_FIRST_BEGIN
  bool ModeWaitActionSecondBegin(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message);//��������� ������� � ������ MODE_WAIT_ACTION_SECOND_BEGIN
  bool IsAction(const CLexeme &cLexeme_Command);//�������� �������������� ������� � ���� ��������
  bool ModeAddActionFirst(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message);//��������� ������� � ������ MODE_ADD_ACTION_FIRST
  bool ModeAddActionSecond(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message,std::vector<std::shared_ptr<IConditionalExpression> > &ConditionalExpression);//��������� ������� � ������ MODE_ADD_ACTION_SECOND
  bool ModeAddAction(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message,std::vector<std::shared_ptr<IConditionalExpression> > &ConditionalExpression);//��������� ������� � ������ MODE_ADD_ACTION
  bool NewCommand(const std::vector<CLexeme> &lexeme,int32_t line_index,std::string &message,std::vector<std::shared_ptr<IConditionalExpression> > &ConditionalExpression,CGameState &cGameState);//������������ ����� �������
  std::shared_ptr<IAction> CreateAction(const std::vector<CLexeme> &lexeme,std::shared_ptr<IAction> next_ptr);//������� �������� �� �������
  std::shared_ptr<IConditionalExpression> CreateConditional(void);//�������� ��������� ��������� �� ������ ������  
};

#endif

