//****************************************************************************************************
//������������ ����������
//****************************************************************************************************
#include "csyntaxanalyzer.h"
#include "cconditionalofintersection.h"
#include "cconditionalofuse.h"
#include "cconditionalofpickup.h"
#include "cactionchangename.h"
#include "cactionchangenameglobal.h"
#include "cactionchangedescription.h"
#include "cactionchangedescriptionglobal.h"
#include "cactioncopyposition.h"
#include "cactionchangeposition.h"
#include "cactionsetanimationstep.h"
#include "cactionmessage.h"
#include "cactionsingle.h"
#include "cactionsetenabled.h"
#include "cactionpickup.h"

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
CSyntaxAnalyzer::CSyntaxAnalyzer(void)
{ 
 //������ ������ ������ ������
 //���������� ���
 cLexicalAnalyzer.AddLexeme("true",ID_LEXEME_TYPE_BOOL);
 cLexicalAnalyzer.AddLexeme("false",ID_LEXEME_TYPE_BOOL); 
 //��������� �������
 cLexicalAnalyzer.AddLexeme("SetDescription",ID_LEXEME_TYPE_SET_DESCRIPTION);
 //������� ��������
   
 cLexicalAnalyzer.AddLexeme("ActionMessage",ID_LEXEME_TYPE_ACTION_MESSAGE); 
 cLexicalAnalyzer.AddLexeme("ActionChangeName",ID_LEXEME_TYPE_ACTION_CHANGE_NAME); 
 cLexicalAnalyzer.AddLexeme("ActionChangeDescription",ID_LEXEME_TYPE_ACTION_CHANGE_DESCRIPTION); 
 cLexicalAnalyzer.AddLexeme("ActionChangeGlobalName",ID_LEXEME_TYPE_ACTION_CHANGE_NAME_GLOBAL); 
 cLexicalAnalyzer.AddLexeme("ActionChangeGlobalDescription",ID_LEXEME_TYPE_ACTION_CHANGE_DESCRIPTION_GLOBAL);                              
 cLexicalAnalyzer.AddLexeme("ActionChangePosition",ID_LEXEME_TYPE_ACTION_CHANGE_POSITION); 
 cLexicalAnalyzer.AddLexeme("ActionCopyPosition",ID_LEXEME_TYPE_ACTION_COPY_POSITION); 
 cLexicalAnalyzer.AddLexeme("ActionPickUp",ID_LEXEME_TYPE_ACTION_PICK_UP); 
 cLexicalAnalyzer.AddLexeme("ActionSetAnimationStep",ID_LEXEME_TYPE_ACTION_SET_ANIMATION_STEP); 
 cLexicalAnalyzer.AddLexeme("ActionSetEnabled",ID_LEXEME_TYPE_ACTION_SET_ENABLED); 
 cLexicalAnalyzer.AddLexeme("ActionSingle",ID_LEXEME_TYPE_ACTION_SINGLE); 
 //������� �������

 cLexicalAnalyzer.AddLexeme("IfIntersection",ID_LEXEME_TYPE_IF_INTERSECTION); 
 cLexicalAnalyzer.AddLexeme("IfPickUp",ID_LEXEME_TYPE_IF_PICK_UP); 
 cLexicalAnalyzer.AddLexeme("IfUse",ID_LEXEME_TYPE_IF_USE); 

 cLexicalAnalyzer.AddLexeme("ActionFirstBegin",ID_LEXEME_TYPE_ACTION_FIRST_BEGIN); 
 cLexicalAnalyzer.AddLexeme("ActionFirstEnd",ID_LEXEME_TYPE_ACTION_FIRST_END); 

 cLexicalAnalyzer.AddLexeme("ActionSecondBegin",ID_LEXEME_TYPE_ACTION_SECOND_BEGIN); 
 cLexicalAnalyzer.AddLexeme("ActionSecondEnd",ID_LEXEME_TYPE_ACTION_SECOND_END); 

 cLexicalAnalyzer.AddLexeme("ActionBegin",ID_LEXEME_TYPE_ACTION_BEGIN); 
 cLexicalAnalyzer.AddLexeme("ActionEnd",ID_LEXEME_TYPE_ACTION_END); 

 //������ ������� �������� ��� ������� ���������

 //������� ActionMessage(20,100,"���������")
 cAutomath_Syntax.AddRule("begin","action_message",ID_LEXEME_TYPE_ACTION_MESSAGE,ID_LEXEME_TYPE_ACTION_MESSAGE,false);
 cAutomath_Syntax.AddRule("action_message","action_message(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_message(","action_message(N",CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_message(N","action_message(N,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("action_message(N,","action_message(N,N",CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_message(N,N","action_message(N,N,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("action_message(N,N,","action_message(N,N,`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("action_message(N,N,`A`","action_message(N,N,`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //������� ActionChangeName("BOTTLE OF WATER")
 cAutomath_Syntax.AddRule("begin","action_change_name",ID_LEXEME_TYPE_ACTION_CHANGE_NAME,ID_LEXEME_TYPE_ACTION_CHANGE_NAME,false);
 cAutomath_Syntax.AddRule("action_change_name","action_change_name(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_change_name(","action_change_name(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("action_change_name(`A`","action_change_name(`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //������� ActionChangeDescription("������� ����")
 cAutomath_Syntax.AddRule("begin","action_change_description",ID_LEXEME_TYPE_ACTION_CHANGE_DESCRIPTION,ID_LEXEME_TYPE_ACTION_CHANGE_DESCRIPTION,false);
 cAutomath_Syntax.AddRule("action_change_description","action_change_description(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_change_description(","action_change_description(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("action_change_description(`A`","action_change_description(`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //������� ActionChangeGlobalName("BOTTLE OF WATER")
 cAutomath_Syntax.AddRule("begin","action_change_name_global",ID_LEXEME_TYPE_ACTION_CHANGE_NAME_GLOBAL,ID_LEXEME_TYPE_ACTION_CHANGE_NAME_GLOBAL,false);
 cAutomath_Syntax.AddRule("action_change_name_global","action_change_name_global(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_change_name_global(","action_change_name_global(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("action_change_name_global(`A`","action_change_name_global(`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //������� ActionChangeGlobalDescription("������� ����")
 cAutomath_Syntax.AddRule("begin","action_change_description_global",ID_LEXEME_TYPE_ACTION_CHANGE_DESCRIPTION_GLOBAL,ID_LEXEME_TYPE_ACTION_CHANGE_DESCRIPTION_GLOBAL,false);
 cAutomath_Syntax.AddRule("action_change_description_global","action_change_description_global(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_change_description_global(","action_change_description_global(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("action_change_description_global(`A`","action_change_description_global(`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //������� ActionChangePosition(100,100)
 cAutomath_Syntax.AddRule("begin","action_change_position",ID_LEXEME_TYPE_ACTION_CHANGE_POSITION,ID_LEXEME_TYPE_ACTION_CHANGE_POSITION,false);
 cAutomath_Syntax.AddRule("action_change_position","action_change_position(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_change_position(","action_change_position(N",CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_change_position(N","action_change_position(N,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("action_change_position(N,","action_change_position(N,N",CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_change_position(N,N","action_change_position(N,N)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //������� ActionCopyPosition("RING","RING_POS")
 cAutomath_Syntax.AddRule("begin","action_copy_position",ID_LEXEME_TYPE_ACTION_COPY_POSITION,ID_LEXEME_TYPE_ACTION_COPY_POSITION,false);
 cAutomath_Syntax.AddRule("action_copy_position","action_copy_position(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_copy_position(","action_copy_position(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("action_copy_position(`A`","action_copy_position(`A`,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("action_copy_position(`A`,","action_copy_position(`A`,`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("action_copy_position(`A`,`A`","action_copy_position(`A`,`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //������� ActionPickUp()
 cAutomath_Syntax.AddRule("begin","action_pick_up",ID_LEXEME_TYPE_ACTION_PICK_UP,ID_LEXEME_TYPE_ACTION_PICK_UP,false);
 cAutomath_Syntax.AddRule("action_pick_up","action_pick_up(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_pick_up(","action_pick_up()",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //������� ActionSingle()
 cAutomath_Syntax.AddRule("begin","action_single",ID_LEXEME_TYPE_ACTION_SINGLE,ID_LEXEME_TYPE_ACTION_SINGLE,false);
 cAutomath_Syntax.AddRule("action_single","action_single(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_single(","action_single()",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //������� ActionSetAnimationStep(10)
 cAutomath_Syntax.AddRule("begin","action_set_animation_step",ID_LEXEME_TYPE_ACTION_SET_ANIMATION_STEP,ID_LEXEME_TYPE_ACTION_SET_ANIMATION_STEP,false);
 cAutomath_Syntax.AddRule("action_set_animation_step","action_set_animation_step(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_set_animation_step(","action_set_animation_step(N",CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_set_animation_step(N","action_set_animation_step(N)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //������� ActionSetEnabled(true)
 cAutomath_Syntax.AddRule("begin","action_set_enabled",ID_LEXEME_TYPE_ACTION_SET_ENABLED,ID_LEXEME_TYPE_ACTION_SET_ENABLED,false);
 cAutomath_Syntax.AddRule("action_set_enabled","action_set_enabled(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_set_enabled(","action_set_enabled(B",ID_LEXEME_TYPE_BOOL,ID_LEXEME_TYPE_BOOL,false);
 cAutomath_Syntax.AddRule("action_set_enabled(B","action_set_enabled(B)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);
 
 //������� ActionBegin
 cAutomath_Syntax.AddRule("begin","action_begin",ID_LEXEME_TYPE_ACTION_BEGIN,ID_LEXEME_TYPE_ACTION_BEGIN,true);
 //������� ActionEnd
 cAutomath_Syntax.AddRule("begin","action_end",ID_LEXEME_TYPE_ACTION_END,ID_LEXEME_TYPE_ACTION_END,true);

 //������� ActionFirstBegin
 cAutomath_Syntax.AddRule("begin","action_first_begin",ID_LEXEME_TYPE_ACTION_FIRST_BEGIN,ID_LEXEME_TYPE_ACTION_FIRST_BEGIN,true);
 //������� ActionFirstEnd
 cAutomath_Syntax.AddRule("begin","action_first_end",ID_LEXEME_TYPE_ACTION_FIRST_END,ID_LEXEME_TYPE_ACTION_FIRST_END,true);

 //������� ActionSecondBegin
 cAutomath_Syntax.AddRule("begin","action_second_begin",ID_LEXEME_TYPE_ACTION_SECOND_BEGIN,ID_LEXEME_TYPE_ACTION_SECOND_BEGIN,true);
 //������� ActionSecondEnd
 cAutomath_Syntax.AddRule("begin","action_second_end",ID_LEXEME_TYPE_ACTION_SECOND_END,ID_LEXEME_TYPE_ACTION_SECOND_END,true);

 //������� IfIntersection("CAT")
 cAutomath_Syntax.AddRule("begin","if_intersection",ID_LEXEME_TYPE_IF_INTERSECTION,ID_LEXEME_TYPE_IF_INTERSECTION,false);
 cAutomath_Syntax.AddRule("if_intersection","if_intersection(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("if_intersection(","if_intersection(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("if_intersection(`A`","if_intersection(`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //������� IfPickUp("RING")
 cAutomath_Syntax.AddRule("begin","if_pick_up",ID_LEXEME_TYPE_IF_PICK_UP,ID_LEXEME_TYPE_IF_PICK_UP,false);
 cAutomath_Syntax.AddRule("if_pick_up","if_pick_up(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("if_pick_up(","if_pick_up(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("if_pick_up(`A`","if_pick_up(`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //������� IfUse("BOTTLE WATER","CAT")
 cAutomath_Syntax.AddRule("begin","if_use",ID_LEXEME_TYPE_IF_USE,ID_LEXEME_TYPE_IF_USE,false);
 cAutomath_Syntax.AddRule("if_use","if_use(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("if_use(","if_use(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("if_use(`A`","if_use(`A`,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("if_use(`A`,","if_use(`A`,`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("if_use(`A`,`A`","if_use(`A`,`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //������� SetDescription("BOTTLE WATER","������� ����")
 cAutomath_Syntax.AddRule("begin","set_description",ID_LEXEME_TYPE_SET_DESCRIPTION,ID_LEXEME_TYPE_SET_DESCRIPTION,false);
 cAutomath_Syntax.AddRule("set_description","set_description(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("set_description(","set_description(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("set_description(`A`","set_description(`A`,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("set_description(`A`,","set_description(`A`,`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("set_description(`A`,`A`","set_description(`A`,`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 vector_CLexeme.clear();
 Mode=MODE_WAIT_COMMAND;
}
//----------------------------------------------------------------------------------------------------
//����������
//----------------------------------------------------------------------------------------------------
CSyntaxAnalyzer::~CSyntaxAnalyzer()
{
}

//****************************************************************************************************
//�������� �������
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//�������� ���� �� ������ ������� a'b'c
//----------------------------------------------------------------------------------------------------
double CSyntaxAnalyzer::ConvertAngleToSec(const char *string)
{
 //��������� ����� �����, ����� � ������
 std::string grad;
 std::string min;
 std::string sec;
 size_t size=strlen(string);
 size_t mode=0;
 for(size_t n=0;n<size;n++)
 {
  char s=string[n];
  if (s=='`')
  {
   mode++;
   continue;
  }
  if (mode==0) grad+=s;
  if (mode==1) min+=s;
  if (mode==2) sec+=s;
 }
 double g=atoi(grad.c_str());
 double m=atoi(min.c_str());
 double s=atoi(sec.c_str());
 double value=g*3600+m*60+s;
 return(value);
}

//----------------------------------------------------------------------------------------------------
//������ ��������
//----------------------------------------------------------------------------------------------------
void CSyntaxAnalyzer::SetDescription(const std::string &name,const std::string &description,std::vector<std::shared_ptr<IPart> > &Map)
{
 size_t size=Map.size();
 for(size_t n=0;n<size;n++)
 {
  std::shared_ptr<IPart> iPart_Ptr=Map[n];
  if (iPart_Ptr->Name.compare(name)==0) iPart_Ptr->Description=description;
 }
}

//----------------------------------------------------------------------------------------------------
//��������� ������� � ������ MODE_WAIT_COMMAND
//----------------------------------------------------------------------------------------------------
bool CSyntaxAnalyzer::ModeWaitCommand(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message,std::vector<std::shared_ptr<IPart> > &Map)
{
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_SET_DESCRIPTION)
 {
  if (CommandLexeme.size()==0) return(true);
  std::string name_first;
  CommandLexeme[0][2].GetName(name_first);
  std::string name_second;
  CommandLexeme[0][4].GetName(name_second);
  SetDescription(name_first,name_second,Map);
  CommandLexeme.clear();
  return(true);
 }

 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_IF_INTERSECTION)
 {
  Mode=MODE_WAIT_ACTION_BEGIN;
  return(true);
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_IF_PICK_UP)
 {
  Mode=MODE_WAIT_ACTION_BEGIN;
  return(true);
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_IF_USE)
 {
  Mode=MODE_WAIT_ACTION_FIRST_BEGIN;
  return(true);
 }
 message="�������� ��������� �������! ��������� �������� ���������.";
 return(false);
}
//----------------------------------------------------------------------------------------------------
//��������� ������� � ������ MODE_WAIT_ACTION_BEGIN
//----------------------------------------------------------------------------------------------------
bool CSyntaxAnalyzer::ModeWaitActionBegin(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message)
{
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_BEGIN)
 {
  Mode=MODE_ADD_ACTION;
  return(true);
 }
 message="�������� ��������� �������! ��������� ActionBegin.";
 return(false);
}
//----------------------------------------------------------------------------------------------------
//��������� ������� � ������ MODE_WAIT_ACTION_FIRST_BEGIN
//----------------------------------------------------------------------------------------------------
bool CSyntaxAnalyzer::ModeWaitActionFirstBegin(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message)
{
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_FIRST_BEGIN)
 {
  Mode=MODE_ADD_ACTION_FIRST;
  return(true);
 }
 message="�������� ��������� �������! ��������� ActionFirstBegin";
 return(false);
}
//----------------------------------------------------------------------------------------------------
//��������� ������� � ������ MODE_WAIT_ACTION_SECOND_BEGIN
//----------------------------------------------------------------------------------------------------
bool CSyntaxAnalyzer::ModeWaitActionSecondBegin(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message)
{
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_SECOND_BEGIN)
 {
  Mode=MODE_ADD_ACTION_SECOND;
  return(true);
 }
 message="�������� ��������� �������! ��������� ActionSecondBegin";
 return(false);
}

//----------------------------------------------------------------------------------------------------
//�������� �������������� ������� � ���� ��������
//----------------------------------------------------------------------------------------------------
bool CSyntaxAnalyzer::IsAction(const CLexeme &cLexeme_Command)
{ 
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_MESSAGE) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_CHANGE_NAME) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_CHANGE_DESCRIPTION) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_CHANGE_NAME_GLOBAL) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_CHANGE_DESCRIPTION_GLOBAL) return(true); 
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_CHANGE_POSITION) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_COPY_POSITION) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_PICK_UP) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_SET_ANIMATION_STEP) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_SET_ENABLED) return(true); 
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_SINGLE) return(true);
 return(false);
}

//----------------------------------------------------------------------------------------------------
//��������� ������� � ������ MODE_ADD_ACTION_FIRST
//----------------------------------------------------------------------------------------------------
bool CSyntaxAnalyzer::ModeAddActionFirst(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message)
{
 if (IsAction(cLexeme_Command)==true) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_FIRST_END)
 {
  Mode=MODE_WAIT_ACTION_SECOND_BEGIN;
  return(true);
 }
 message="�������� ��������� �������! ��������� ActionFirstEnd";
 return(false);
}

//----------------------------------------------------------------------------------------------------
//��������� ������� � ������ MODE_ADD_ACTION_SECOND
//----------------------------------------------------------------------------------------------------
bool CSyntaxAnalyzer::ModeAddActionSecond(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message,std::vector<std::shared_ptr<IConditionalExpression> > &ConditionalExpression)
{
 if (IsAction(cLexeme_Command)==true) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_SECOND_END)
 {
  Mode=MODE_WAIT_COMMAND;
  //���������� ������� �� ��������
  std::shared_ptr<IConditionalExpression> iConditionalExpression_Ptr=CreateConditional();
  if (iConditionalExpression_Ptr.get()!=NULL) ConditionalExpression.push_back(iConditionalExpression_Ptr);
  CommandLexeme.clear();
  return(true);
 }
 message="�������� ��������� �������! ��������� ActionSecondEnd";
 return(false);
}
//----------------------------------------------------------------------------------------------------
//��������� ������� � ������ MODE_ADD_ACTION
//----------------------------------------------------------------------------------------------------
bool CSyntaxAnalyzer::ModeAddAction(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message,std::vector<std::shared_ptr<IConditionalExpression> > &ConditionalExpression)
{
 if (IsAction(cLexeme_Command)==true) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_END)
 {
  Mode=MODE_WAIT_COMMAND;
  //���������� ������� �� ��������  
  std::shared_ptr<IConditionalExpression> iConditionalExpression_Ptr=CreateConditional();
  if (iConditionalExpression_Ptr.get()!=NULL) ConditionalExpression.push_back(iConditionalExpression_Ptr);
  CommandLexeme.clear();
  return(true);
 }
 message="�������� ��������� �������! ��������� ActionEnd";
 return(false);
}

//----------------------------------------------------------------------------------------------------
//������������ ����� �������
//----------------------------------------------------------------------------------------------------
bool CSyntaxAnalyzer::NewCommand(const std::vector<CLexeme> &lexeme,int32_t line_index,std::string &message,std::vector<std::shared_ptr<IConditionalExpression> > &ConditionalExpression,std::vector<std::shared_ptr<IPart> > &Map)
{ 
 if (lexeme.size()==0) return(true);
 //��������� ������� (��������� �������� � ������� ����� � �������� �������)
 CommandLexeme.push_back(lexeme);
 //�������, � ����� ������ �������� ����������
 const CLexeme &cLexeme_Command=lexeme[0];
 //�������� �������
 if (Mode==MODE_WAIT_COMMAND) return(ModeWaitCommand(cLexeme_Command,line_index,message,Map));
 if (Mode==MODE_WAIT_ACTION_BEGIN) return(ModeWaitActionBegin(cLexeme_Command,line_index,message));
 if (Mode==MODE_WAIT_ACTION_FIRST_BEGIN) return(ModeWaitActionFirstBegin(cLexeme_Command,line_index,message));
 if (Mode==MODE_WAIT_ACTION_SECOND_BEGIN) return(ModeWaitActionSecondBegin(cLexeme_Command,line_index,message));
 if (Mode==MODE_ADD_ACTION_FIRST) return(ModeAddActionFirst(cLexeme_Command,line_index,message));
 if (Mode==MODE_ADD_ACTION_SECOND) return(ModeAddActionSecond(cLexeme_Command,line_index,message,ConditionalExpression));
 if (Mode==MODE_ADD_ACTION) return(ModeAddAction(cLexeme_Command,line_index,message,ConditionalExpression));
 return(false);
}

//----------------------------------------------------------------------------------------------------
//������� �������� �� �������
//----------------------------------------------------------------------------------------------------
std::shared_ptr<IAction> CSyntaxAnalyzer::CreateAction(const std::vector<CLexeme> &lexeme,std::shared_ptr<IAction> next_ptr)
{
 const CLexeme &cLexeme_Command=lexeme[0];
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_MESSAGE)
 {
  std::string message;
  lexeme[6].GetName(message);
  std::string x_pos;
  lexeme[2].GetName(x_pos);
  std::string y_pos;
  lexeme[4].GetName(y_pos);
  int32_t x=atoi(x_pos.c_str());
  int32_t y=atoi(y_pos.c_str());
  return(std::shared_ptr<IAction>(new CActionMessage(message,x,y,next_ptr)));
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_CHANGE_NAME)
 {
  std::string name;
  lexeme[2].GetName(name);
  return(std::shared_ptr<IAction>(new CActionChangeName(name,next_ptr)));
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_CHANGE_NAME_GLOBAL)
 {
  std::string name;
  lexeme[2].GetName(name);
  return(std::shared_ptr<IAction>(new CActionChangeNameGlobal(name,next_ptr)));
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_CHANGE_DESCRIPTION)
 {
  std::string description;
  lexeme[2].GetName(description);
  return(std::shared_ptr<IAction>(new CActionChangeDescription(description,next_ptr)));
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_CHANGE_DESCRIPTION_GLOBAL)
 {
  std::string description;
  lexeme[2].GetName(description);
  return(std::shared_ptr<IAction>(new CActionChangeDescription(description,next_ptr)));
 }

 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_CHANGE_POSITION)
 {
  std::string x_pos;
  lexeme[2].GetName(x_pos);
  std::string y_pos;
  lexeme[4].GetName(y_pos);
  int32_t x=atoi(x_pos.c_str());
  int32_t y=atoi(x_pos.c_str());
  return(std::shared_ptr<IAction>(new CActionChangePosition(x,y,next_ptr)));
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_COPY_POSITION)
 {
  std::string name_first;
  lexeme[2].GetName(name_first);
  std::string name_second;
  lexeme[4].GetName(name_second);
  return(std::shared_ptr<IAction>(new CActionCopyPosition(name_first,name_second,next_ptr)));
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_SET_ANIMATION_STEP)
 {
  std::string frame;
  lexeme[2].GetName(frame);
  int32_t set_frame=atoi(frame.c_str());
  return(std::shared_ptr<IAction>(new CActionSetAnimationStep(set_frame,next_ptr)));
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_SET_ENABLED)
 {
  std::string state;
  lexeme[2].GetName(state);
  if (state.compare("true")==0) return(std::shared_ptr<IAction>(new CActionSetEnabled(true,next_ptr)));
  return(std::shared_ptr<IAction>(new CActionSetEnabled(false,next_ptr)));
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_SINGLE)
 {
  return(std::shared_ptr<IAction>(new CActionSingle(next_ptr)));
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_PICK_UP)
 {
  return(std::shared_ptr<IAction>(new CActionPickUp(next_ptr)));
 }
 return(std::shared_ptr<IAction>(NULL));
}
//----------------------------------------------------------------------------------------------------
//�������� ��������� ��������� �� ������ ������
//----------------------------------------------------------------------------------------------------
std::shared_ptr<IConditionalExpression> CSyntaxAnalyzer::CreateConditional(void)
{
 //������ �������� � �������� �������
 size_t size=CommandLexeme.size();
 if (size==0) return(std::shared_ptr<IConditionalExpression>(NULL));
 //������, ��� �� ������� �� ������
 if (CommandLexeme[0][0].GetType()==ID_LEXEME_TYPE_IF_INTERSECTION)
 {  
  std::shared_ptr<IAction> iAction_Ptr;
  for(size_t n=size-1;n>0;n--)
  {
   if (IsAction(CommandLexeme[n][0])==true)
   {
    iAction_Ptr=CreateAction(CommandLexeme[n],iAction_Ptr);
   }
  }
  std::string name;
  CommandLexeme[0][2].GetName(name);
  return(std::shared_ptr<IConditionalExpression>(new CConditionalOfIntersection(name,iAction_Ptr)));
 }

 if (CommandLexeme[0][0].GetType()==ID_LEXEME_TYPE_IF_PICK_UP)
 {  
  std::shared_ptr<IAction> iAction_Ptr;
  for(size_t n=size-1;n>0;n--)
  {
   if (IsAction(CommandLexeme[n][0])==true)
   {
    iAction_Ptr=CreateAction(CommandLexeme[n],iAction_Ptr);
   }
  }
  std::string name;
  CommandLexeme[0][2].GetName(name);

  return(std::shared_ptr<IConditionalExpression>(new CConditionalOfPickUp(name,iAction_Ptr)));
 } 

 if (CommandLexeme[0][0].GetType()==ID_LEXEME_TYPE_IF_USE)
 {  
  std::shared_ptr<IAction> iAction_First_Ptr;
  std::shared_ptr<IAction> iAction_Second_Ptr;  
  std::shared_ptr<IAction> iAction_Ptr;
  for(size_t n=size-1;n>0;n--)
  {   
   if (IsAction(CommandLexeme[n][0])==true)
   {
    iAction_Ptr=CreateAction(CommandLexeme[n],iAction_Ptr);
   }
   else
   {
	if (CommandLexeme[n][0].GetType()==ID_LEXEME_TYPE_ACTION_SECOND_BEGIN) 
	{
     iAction_Second_Ptr=iAction_Ptr;
     iAction_Ptr.reset();
	}
	if (CommandLexeme[n][0].GetType()==ID_LEXEME_TYPE_ACTION_FIRST_BEGIN) 
	{
     iAction_First_Ptr=iAction_Ptr;
     iAction_Ptr.reset();
	}
   }
  }
  std::string name_first;
  CommandLexeme[0][2].GetName(name_first);
  std::string name_second;
  CommandLexeme[0][4].GetName(name_second);
  return(std::shared_ptr<IConditionalExpression>(new CConditionalOfUse(name_first,name_second,iAction_First_Ptr,iAction_Second_Ptr)));
 }
 return(std::shared_ptr<IConditionalExpression>(NULL));
}

//****************************************************************************************************
//�������� �������
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//������� �������
//----------------------------------------------------------------------------------------------------
bool CSyntaxAnalyzer::Processing(char symbol,int32_t line_index,std::string &message,bool &new_line,std::vector<std::shared_ptr<IConditionalExpression> > &ConditionalExpression,std::vector<std::shared_ptr<IPart> > &Map)
{
 message="";
 new_line=false;
 //�������� �������
 std::vector<CLexeme> vector_CLexeme_Get;
 if (cLexicalAnalyzer.GetLexeme(symbol,vector_CLexeme_Get)==false)
 {
  if (symbol==0)//���� ����������
  {
   if (cAutomath_Syntax.CompareCurrentState("begin")==false && cAutomath_Syntax.IsCurrentStateEndingType()==false)//������� �� ���������
   {
    message="������! ������� �� ���������:";
    std::string line;
    cAutomath_Syntax.GetInputLineToString(line);
    message=message+line;
    new_line=true;
    return(false);
   }
  }
  return(true);
 }
 //��������� �������
 size_t size=vector_CLexeme_Get.size();
 for(size_t n=0;n<size;n++)
 {
  CLexeme &cLexeme=vector_CLexeme_Get[n];
  //������� ������ �������
  //����� ������� � �������� �����
  if (cLexeme.GetType()!=CLexeme::ID_LEXEME_TYPE_TERMINAL)//������������ ������ �� ��������
  {
   std::string name;  	
   cLexeme.GetName(name);
   message=message+name;
  }
  //���������� ������� �������� ��������������� �������
  if (cAutomath_Syntax.Push(cLexeme.GetType())==true)//������� ������ �������
  {
   vector_CLexeme.push_back(cLexeme);
   if (cAutomath_Syntax.IsCurrentStateEndingType()==true)
   {
    if (NewCommand(vector_CLexeme,line_index,message,ConditionalExpression,Map)==false) return(false);
    vector_CLexeme.clear();
    new_line=true;
   }
  }
  else//������!
  {
  //���� ��� ������������ ������
   if (cLexeme.GetType()==CLexeme::ID_LEXEME_TYPE_TERMINAL)
   {
    //���� �������� ����� �������
    if (cAutomath_Syntax.CompareCurrentState("begin")==false && cAutomath_Syntax.IsCurrentStateEndingType()==false)
    {
     message="������! ������� �� ���������:";
     std::string line;
     cAutomath_Syntax.GetInputLineToString(line);
     message=message+line;
     new_line=true;
     return(false);
    }
    //������ ������������ ������ ����������   
    cAutomath_Syntax.Reset();
    vector_CLexeme.clear();
    continue;
   }
   message="������! �������� �������:";
   std::string line;
   cLexeme.GetName(line);
   message=message+line;
   new_line=true;  
   return(false);
  }
 } 
 return(true);
}
