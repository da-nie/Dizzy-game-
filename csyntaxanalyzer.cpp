//****************************************************************************************************
//подключаемые библиотеки
//****************************************************************************************************
#include "csyntaxanalyzer.h"
#include "cconditionalofintersection.h"
#include "cconditionalofdizzyintersection.h"
#include "cconditionalofnotdizzyintersection.h"
#include "cconditionalofuse.h"
#include "cconditionalofpickup.h"
#include "cconditionaloftimer.h"
#include "cactionchangename.h"
#include "cactionchangenameglobal.h"
#include "cactionchangedescription.h"
#include "cactionchangedescriptionglobal.h"
#include "cactioncopyposition.h"
#include "cactioncopypositionoffset.h"
#include "cactionchangeposition.h"
#include "cactionsetanimationstep.h"
#include "cactionmessage.h"
#include "cactionsingle.h"
#include "cactionsetenabled.h"
#include "cactionpickup.h"
#include "cactionmove.h"
#include "cactionenergyupdate.h"
#include "cactionaddlife.h"
#include "cactionaddscore.h"
#include "cactionadditem.h"
#include "cactionchangeanimationmode.h"

//****************************************************************************************************
//глобальные переменные
//****************************************************************************************************

//****************************************************************************************************
//константы
//****************************************************************************************************

//****************************************************************************************************
//макроопределения
//****************************************************************************************************

//****************************************************************************************************
//конструктор и деструктор
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//конструктор
//----------------------------------------------------------------------------------------------------
CSyntaxAnalyzer::CSyntaxAnalyzer(void)
{ 
 //создаём список лексем команд
 //логический тип
 cLexicalAnalyzer.AddLexeme("true",ID_LEXEME_TYPE_BOOL);
 cLexicalAnalyzer.AddLexeme("false",ID_LEXEME_TYPE_BOOL); 
 //типы анимации
 cLexicalAnalyzer.AddLexeme("animation_cyclic",ID_LEXEME_TYPE_ANIMATION_MODE);
 cLexicalAnalyzer.AddLexeme("animation_set_step",ID_LEXEME_TYPE_ANIMATION_MODE); 
 cLexicalAnalyzer.AddLexeme("animation_one_shot",ID_LEXEME_TYPE_ANIMATION_MODE); 
 //служебные команды
 cLexicalAnalyzer.AddLexeme("SetDescription",ID_LEXEME_TYPE_SET_DESCRIPTION);
 cLexicalAnalyzer.AddLexeme("CopyPosition",ID_LEXEME_TYPE_COPY_POSITION);
 cLexicalAnalyzer.AddLexeme("CopyPositionOffset",ID_LEXEME_TYPE_COPY_POSITION_OFFSET);
 cLexicalAnalyzer.AddLexeme("SetDizzyPosition",ID_LEXEME_TYPE_SET_DIZZY_POSITION);
 //команды действий
   
 cLexicalAnalyzer.AddLexeme("ActionMessage",ID_LEXEME_TYPE_ACTION_MESSAGE); 
 cLexicalAnalyzer.AddLexeme("ActionChangeName",ID_LEXEME_TYPE_ACTION_CHANGE_NAME); 
 cLexicalAnalyzer.AddLexeme("ActionChangeDescription",ID_LEXEME_TYPE_ACTION_CHANGE_DESCRIPTION); 
 cLexicalAnalyzer.AddLexeme("ActionChangeGlobalName",ID_LEXEME_TYPE_ACTION_CHANGE_NAME_GLOBAL); 
 cLexicalAnalyzer.AddLexeme("ActionChangeGlobalDescription",ID_LEXEME_TYPE_ACTION_CHANGE_DESCRIPTION_GLOBAL);                              
 cLexicalAnalyzer.AddLexeme("ActionChangePosition",ID_LEXEME_TYPE_ACTION_CHANGE_POSITION); 
 cLexicalAnalyzer.AddLexeme("ActionCopyPosition",ID_LEXEME_TYPE_ACTION_COPY_POSITION); 
 cLexicalAnalyzer.AddLexeme("ActionCopyPositionOffset",ID_LEXEME_TYPE_ACTION_COPY_POSITION_OFFSET);
 cLexicalAnalyzer.AddLexeme("ActionPickUp",ID_LEXEME_TYPE_ACTION_PICK_UP); 
 cLexicalAnalyzer.AddLexeme("ActionSetAnimationStep",ID_LEXEME_TYPE_ACTION_SET_ANIMATION_STEP); 
 cLexicalAnalyzer.AddLexeme("ActionSetEnabled",ID_LEXEME_TYPE_ACTION_SET_ENABLED); 
 cLexicalAnalyzer.AddLexeme("ActionSingle",ID_LEXEME_TYPE_ACTION_SINGLE); 
 cLexicalAnalyzer.AddLexeme("ActionMove",ID_LEXEME_TYPE_ACTION_MOVE);
 cLexicalAnalyzer.AddLexeme("ActionEnergyUpdate",ID_LEXEME_TYPE_ACTION_ENERGY_UPDATE);
 cLexicalAnalyzer.AddLexeme("ActionAddScore",ID_LEXEME_TYPE_ACTION_ADD_SCORE);
 cLexicalAnalyzer.AddLexeme("ActionAddLife",ID_LEXEME_TYPE_ACTION_ADD_LIFE);
 cLexicalAnalyzer.AddLexeme("ActionAddItem",ID_LEXEME_TYPE_ACTION_ADD_ITEM);
 cLexicalAnalyzer.AddLexeme("ActionChangeAnimationMode",ID_LEXEME_TYPE_ACTION_CHANGE_ANIMATION_MODE);
 //команды условий

 cLexicalAnalyzer.AddLexeme("IfIntersection",ID_LEXEME_TYPE_IF_INTERSECTION); 
 cLexicalAnalyzer.AddLexeme("IfDizzyIntersection",ID_LEXEME_TYPE_IF_DIZZY_INTERSECTION);
 cLexicalAnalyzer.AddLexeme("IfNotDizzyIntersection",ID_LEXEME_TYPE_IF_NOT_DIZZY_INTERSECTION);
 cLexicalAnalyzer.AddLexeme("IfPickUp",ID_LEXEME_TYPE_IF_PICK_UP); 
 cLexicalAnalyzer.AddLexeme("IfUse",ID_LEXEME_TYPE_IF_USE); 
 cLexicalAnalyzer.AddLexeme("IfTimer",ID_LEXEME_TYPE_IF_TIMER);

 cLexicalAnalyzer.AddLexeme("ActionFirstBegin",ID_LEXEME_TYPE_ACTION_FIRST_BEGIN); 
 cLexicalAnalyzer.AddLexeme("ActionFirstEnd",ID_LEXEME_TYPE_ACTION_FIRST_END); 

 cLexicalAnalyzer.AddLexeme("ActionSecondBegin",ID_LEXEME_TYPE_ACTION_SECOND_BEGIN); 
 cLexicalAnalyzer.AddLexeme("ActionSecondEnd",ID_LEXEME_TYPE_ACTION_SECOND_END); 

 cLexicalAnalyzer.AddLexeme("ActionBegin",ID_LEXEME_TYPE_ACTION_BEGIN); 
 cLexicalAnalyzer.AddLexeme("ActionEnd",ID_LEXEME_TYPE_ACTION_END); 

 //создаём правила автомату для разбора выражений

 //команда ActionMessage(20,100,"СООБЩЕНИЕ")
 cAutomath_Syntax.AddRule("begin","action_message",ID_LEXEME_TYPE_ACTION_MESSAGE,ID_LEXEME_TYPE_ACTION_MESSAGE,false);
 cAutomath_Syntax.AddRule("action_message","action_message(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_message(","action_message(N",CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_message(N","action_message(N,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("action_message(N,","action_message(N,N",CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_message(N,N","action_message(N,N,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("action_message(N,N,","action_message(N,N,`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("action_message(N,N,`A`","action_message(N,N,`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда ActionChangeName("BOTTLE OF WATER")
 cAutomath_Syntax.AddRule("begin","action_change_name",ID_LEXEME_TYPE_ACTION_CHANGE_NAME,ID_LEXEME_TYPE_ACTION_CHANGE_NAME,false);
 cAutomath_Syntax.AddRule("action_change_name","action_change_name(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_change_name(","action_change_name(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("action_change_name(`A`","action_change_name(`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда ActionChangeDescription("БУТЫЛКА ВОДЫ")
 cAutomath_Syntax.AddRule("begin","action_change_description",ID_LEXEME_TYPE_ACTION_CHANGE_DESCRIPTION,ID_LEXEME_TYPE_ACTION_CHANGE_DESCRIPTION,false);
 cAutomath_Syntax.AddRule("action_change_description","action_change_description(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_change_description(","action_change_description(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("action_change_description(`A`","action_change_description(`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда ActionChangeGlobalName("BOTTLE OF WATER")
 cAutomath_Syntax.AddRule("begin","action_change_name_global",ID_LEXEME_TYPE_ACTION_CHANGE_NAME_GLOBAL,ID_LEXEME_TYPE_ACTION_CHANGE_NAME_GLOBAL,false);
 cAutomath_Syntax.AddRule("action_change_name_global","action_change_name_global(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_change_name_global(","action_change_name_global(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("action_change_name_global(`A`","action_change_name_global(`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда ActionChangeGlobalDescription("БУТЫЛКА ВОДЫ")
 cAutomath_Syntax.AddRule("begin","action_change_description_global",ID_LEXEME_TYPE_ACTION_CHANGE_DESCRIPTION_GLOBAL,ID_LEXEME_TYPE_ACTION_CHANGE_DESCRIPTION_GLOBAL,false);
 cAutomath_Syntax.AddRule("action_change_description_global","action_change_description_global(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_change_description_global(","action_change_description_global(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("action_change_description_global(`A`","action_change_description_global(`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда ActionChangePosition(100,100)
 cAutomath_Syntax.AddRule("begin","action_change_position",ID_LEXEME_TYPE_ACTION_CHANGE_POSITION,ID_LEXEME_TYPE_ACTION_CHANGE_POSITION,false);
 cAutomath_Syntax.AddRule("action_change_position","action_change_position(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_change_position(","action_change_position(N",CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_change_position(N","action_change_position(N,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("action_change_position(N,","action_change_position(N,N",CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_change_position(N,N","action_change_position(N,N)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда ActionCopyPosition("RING","RING_POS")
 cAutomath_Syntax.AddRule("begin","action_copy_position",ID_LEXEME_TYPE_ACTION_COPY_POSITION,ID_LEXEME_TYPE_ACTION_COPY_POSITION,false);
 cAutomath_Syntax.AddRule("action_copy_position","action_copy_position(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_copy_position(","action_copy_position(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("action_copy_position(`A`","action_copy_position(`A`,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("action_copy_position(`A`,","action_copy_position(`A`,`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("action_copy_position(`A`,`A`","action_copy_position(`A`,`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда ActionCopyPositionOffset("RING","RING_POS",8,0)
 cAutomath_Syntax.AddRule("begin","action_copy_position_offset",ID_LEXEME_TYPE_ACTION_COPY_POSITION_OFFSET,ID_LEXEME_TYPE_ACTION_COPY_POSITION_OFFSET,false);
 cAutomath_Syntax.AddRule("action_copy_position_offset","action_copy_position_offset(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_copy_position_offset(","action_copy_position_offset(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("action_copy_position_offset(`A`","action_copy_position_offset(`A`,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("action_copy_position_offset(`A`,","action_copy_position_offset(`A`,`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("action_copy_position_offset(`A`,`A`","action_copy_position_offset(`A`,`A`,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("action_copy_position_offset(`A`,`A`,","action_copy_position_offset(`A`,`A`,N",CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_copy_position_offset(`A`,`A`,","action_copy_position_offset(`A`,`A`,N",CLexeme::ID_LEXEME_TYPE_NEGATIVE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NEGATIVE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_copy_position_offset(`A`,`A`,N","action_copy_position_offset(`A`,`A`,N,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("action_copy_position_offset(`A`,`A`,N,","action_copy_position_offset(`A`,`A`,N,N",CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_copy_position_offset(`A`,`A`,N","action_copy_position_offset(`A`,`A`,N,N",CLexeme::ID_LEXEME_TYPE_NEGATIVE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NEGATIVE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_copy_position_offset(`A`,`A`,N,N","action_copy_position_offset(`A`,`A`,N,N)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда ActionPickUp()
 cAutomath_Syntax.AddRule("begin","action_pick_up",ID_LEXEME_TYPE_ACTION_PICK_UP,ID_LEXEME_TYPE_ACTION_PICK_UP,false);
 cAutomath_Syntax.AddRule("action_pick_up","action_pick_up(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_pick_up(","action_pick_up()",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда ActionSingle()
 cAutomath_Syntax.AddRule("begin","action_single",ID_LEXEME_TYPE_ACTION_SINGLE,ID_LEXEME_TYPE_ACTION_SINGLE,false);
 cAutomath_Syntax.AddRule("action_single","action_single(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_single(","action_single()",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда ActionSetAnimationStep(10)
 cAutomath_Syntax.AddRule("begin","action_set_animation_step",ID_LEXEME_TYPE_ACTION_SET_ANIMATION_STEP,ID_LEXEME_TYPE_ACTION_SET_ANIMATION_STEP,false);
 cAutomath_Syntax.AddRule("action_set_animation_step","action_set_animation_step(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_set_animation_step(","action_set_animation_step(N",CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_set_animation_step(N","action_set_animation_step(N)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда ActionMove(1,0)
 cAutomath_Syntax.AddRule("begin","action_move",ID_LEXEME_TYPE_ACTION_MOVE,ID_LEXEME_TYPE_ACTION_MOVE,false);
 cAutomath_Syntax.AddRule("action_move","action_move(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_move(","action_move(N",CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_move(","action_move(N",CLexeme::ID_LEXEME_TYPE_NEGATIVE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NEGATIVE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_move(N","action_move(N,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("action_move(N,","action_move(N,N",CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_move(N,","action_move(N,N",CLexeme::ID_LEXEME_TYPE_NEGATIVE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NEGATIVE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_move(N,N","action_move(N,N)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда ActionSetEnabled(true)
 cAutomath_Syntax.AddRule("begin","action_set_enabled",ID_LEXEME_TYPE_ACTION_SET_ENABLED,ID_LEXEME_TYPE_ACTION_SET_ENABLED,false);
 cAutomath_Syntax.AddRule("action_set_enabled","action_set_enabled(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_set_enabled(","action_set_enabled(B",ID_LEXEME_TYPE_BOOL,ID_LEXEME_TYPE_BOOL,false);
 cAutomath_Syntax.AddRule("action_set_enabled(B","action_set_enabled(B)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);
 
 //команда ActionBegin
 cAutomath_Syntax.AddRule("begin","action_begin",ID_LEXEME_TYPE_ACTION_BEGIN,ID_LEXEME_TYPE_ACTION_BEGIN,true);
 //команда ActionEnd
 cAutomath_Syntax.AddRule("begin","action_end",ID_LEXEME_TYPE_ACTION_END,ID_LEXEME_TYPE_ACTION_END,true);

 //команда ActionFirstBegin
 cAutomath_Syntax.AddRule("begin","action_first_begin",ID_LEXEME_TYPE_ACTION_FIRST_BEGIN,ID_LEXEME_TYPE_ACTION_FIRST_BEGIN,true);
 //команда ActionFirstEnd
 cAutomath_Syntax.AddRule("begin","action_first_end",ID_LEXEME_TYPE_ACTION_FIRST_END,ID_LEXEME_TYPE_ACTION_FIRST_END,true);

 //команда ActionSecondBegin
 cAutomath_Syntax.AddRule("begin","action_second_begin",ID_LEXEME_TYPE_ACTION_SECOND_BEGIN,ID_LEXEME_TYPE_ACTION_SECOND_BEGIN,true);
 //команда ActionSecondEnd
 cAutomath_Syntax.AddRule("begin","action_second_end",ID_LEXEME_TYPE_ACTION_SECOND_END,ID_LEXEME_TYPE_ACTION_SECOND_END,true);

 //команда ActionEnergyUpdate(-1)
 cAutomath_Syntax.AddRule("begin","action_energy_update",ID_LEXEME_TYPE_ACTION_ENERGY_UPDATE,ID_LEXEME_TYPE_ACTION_ENERGY_UPDATE,false);
 cAutomath_Syntax.AddRule("action_energy_update","action_energy_update(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_energy_update(","action_energy_update(N",CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_energy_update(","action_energy_update(N",CLexeme::ID_LEXEME_TYPE_NEGATIVE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NEGATIVE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_energy_update(N","action_energy_update(N)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда ActionAddScore(100)
 cAutomath_Syntax.AddRule("begin","action_add_score",ID_LEXEME_TYPE_ACTION_ADD_SCORE,ID_LEXEME_TYPE_ACTION_ADD_SCORE,false);
 cAutomath_Syntax.AddRule("action_add_score","action_add_score(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_add_score(","action_add_score(N",CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_add_score(","action_add_score(N",CLexeme::ID_LEXEME_TYPE_NEGATIVE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NEGATIVE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("action_add_score(N","action_add_score(N)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда ActionAddLife()
 cAutomath_Syntax.AddRule("begin","action_add_life",ID_LEXEME_TYPE_ACTION_ADD_LIFE,ID_LEXEME_TYPE_ACTION_ADD_LIFE,false);
 cAutomath_Syntax.AddRule("action_add_life","action_add_life(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_add_life(","action_add_life()",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда ActionAddItem()
 cAutomath_Syntax.AddRule("begin","action_add_item",ID_LEXEME_TYPE_ACTION_ADD_ITEM,ID_LEXEME_TYPE_ACTION_ADD_ITEM,false);
 cAutomath_Syntax.AddRule("action_add_item","action_add_item(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_add_item(","action_add_item()",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);


 //команда ActionChangeAnimationMode(animation_mode_stop)
 cAutomath_Syntax.AddRule("begin","action_change_animation_mode",ID_LEXEME_TYPE_ACTION_CHANGE_ANIMATION_MODE,ID_LEXEME_TYPE_ACTION_CHANGE_ANIMATION_MODE,false);
 cAutomath_Syntax.AddRule("action_change_animation_mode","action_change_animation_mode(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("action_change_animation_mode(","action_change_animation_mode(M",ID_LEXEME_TYPE_ANIMATION_MODE,ID_LEXEME_TYPE_ANIMATION_MODE,false);
 cAutomath_Syntax.AddRule("action_change_animation_mode(M","action_change_animation_mode(M)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);


 //команда IfDizzyIntersection("CAT")
 cAutomath_Syntax.AddRule("begin","if_dizzy_intersection",ID_LEXEME_TYPE_IF_DIZZY_INTERSECTION,ID_LEXEME_TYPE_IF_DIZZY_INTERSECTION,false);
 cAutomath_Syntax.AddRule("if_dizzy_intersection","if_dizzy_intersection(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("if_dizzy_intersection(","if_dizzy_intersection(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("if_dizzy_intersection(`A`","if_dizzy_intersection(`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда IfNotDizzyIntersection("CAT")
 cAutomath_Syntax.AddRule("begin","if_not_dizzy_intersection",ID_LEXEME_TYPE_IF_NOT_DIZZY_INTERSECTION,ID_LEXEME_TYPE_IF_NOT_DIZZY_INTERSECTION,false);
 cAutomath_Syntax.AddRule("if_not_dizzy_intersection","if_not_dizzy_intersection(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("if_not_dizzy_intersection(","if_not_dizzy_intersection(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("if_not_dizzy_intersection(`A`","if_not_dizzy_intersection(`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда IfIntersection("CAT","WATER")
 cAutomath_Syntax.AddRule("begin","if_intersection",ID_LEXEME_TYPE_IF_INTERSECTION,ID_LEXEME_TYPE_IF_INTERSECTION,false);
 cAutomath_Syntax.AddRule("if_intersection","if_intersection(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("if_intersection(","if_intersection(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("if_intersection(`A`","if_intersection(`A`,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("if_intersection(`A`,","if_intersection(`A`,`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("if_intersection(`A`,`A`","if_intersection(`A`,`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда IfPickUp("RING")
 cAutomath_Syntax.AddRule("begin","if_pick_up",ID_LEXEME_TYPE_IF_PICK_UP,ID_LEXEME_TYPE_IF_PICK_UP,false);
 cAutomath_Syntax.AddRule("if_pick_up","if_pick_up(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("if_pick_up(","if_pick_up(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("if_pick_up(`A`","if_pick_up(`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда IfUse("BOTTLE WATER","CAT")
 cAutomath_Syntax.AddRule("begin","if_use",ID_LEXEME_TYPE_IF_USE,ID_LEXEME_TYPE_IF_USE,false);
 cAutomath_Syntax.AddRule("if_use","if_use(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("if_use(","if_use(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("if_use(`A`","if_use(`A`,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("if_use(`A`,","if_use(`A`,`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("if_use(`A`,`A`","if_use(`A`,`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда IfTimer("WAIT CAT")
 cAutomath_Syntax.AddRule("begin","if_timer",ID_LEXEME_TYPE_IF_TIMER,ID_LEXEME_TYPE_IF_TIMER,false);
 cAutomath_Syntax.AddRule("if_timer","if_timer(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("if_timer(","if_timer(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("if_timer(`A`","if_timer(`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда SetDescription("BOTTLE WATER","БУТЫЛКА ВОДЫ")
 cAutomath_Syntax.AddRule("begin","set_description",ID_LEXEME_TYPE_SET_DESCRIPTION,ID_LEXEME_TYPE_SET_DESCRIPTION,false);
 cAutomath_Syntax.AddRule("set_description","set_description(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("set_description(","set_description(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("set_description(`A`","set_description(`A`,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("set_description(`A`,","set_description(`A`,`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("set_description(`A`,`A`","set_description(`A`,`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);
 
 //команда CopyPosition("FIRE","FIRE_POS")
 cAutomath_Syntax.AddRule("begin","copy_position",ID_LEXEME_TYPE_COPY_POSITION,ID_LEXEME_TYPE_COPY_POSITION,false);
 cAutomath_Syntax.AddRule("copy_position","copy_position(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("copy_position(","copy_position(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("copy_position(`A`","copy_position(`A`,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("copy_position(`A`,","copy_position(`A`,`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("copy_position(`A`,`A`","copy_position(`A`,`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);

 //команда CopyPositionOffset("FIRE","FIRE_POS")
 cAutomath_Syntax.AddRule("begin","copy_position_offset",ID_LEXEME_TYPE_COPY_POSITION_OFFSET,ID_LEXEME_TYPE_COPY_POSITION_OFFSET,false);
 cAutomath_Syntax.AddRule("copy_position_offset","copy_position_offset(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("copy_position_offset(","copy_position_offset(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("copy_position_offset(`A`","copy_position_offset(`A`,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("copy_position_offset(`A`,","copy_position_offset(`A`,`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("copy_position_offset(`A`,`A`","copy_position_offset(`A`,`A`,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("copy_position_offset(`A`,`A`,","copy_position_offset(`A`,`A`,N",CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("copy_position_offset(`A`,`A`,","copy_position_offset(`A`,`A`,N",CLexeme::ID_LEXEME_TYPE_NEGATIVE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NEGATIVE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("copy_position_offset(`A`,`A`,N","copy_position_offset(`A`,`A`,N,",CLexeme::ID_LEXEME_TYPE_COMMA,CLexeme::ID_LEXEME_TYPE_COMMA,false);
 cAutomath_Syntax.AddRule("copy_position_offset(`A`,`A`,N,","copy_position_offset(`A`,`A`,N,N",CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("copy_position_offset(`A`,`A`,N","copy_position_offset(`A`,`A`,N,N",CLexeme::ID_LEXEME_TYPE_NEGATIVE_NATURAL_NUMBER,CLexeme::ID_LEXEME_TYPE_NEGATIVE_NATURAL_NUMBER,false);
 cAutomath_Syntax.AddRule("copy_position_offset(`A`,`A`,N,N","copy_position_offset(`A`,`A`,N,N)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);
 
 //команда SetDizzyPosition("DIZZY_START_POSITION")
 cAutomath_Syntax.AddRule("begin","set_dizzy_position",ID_LEXEME_TYPE_SET_DIZZY_POSITION,ID_LEXEME_TYPE_SET_DIZZY_POSITION,false);
 cAutomath_Syntax.AddRule("set_dizzy_position","set_dizzy_position(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,CLexeme::ID_LEXEME_TYPE_LEFTBRACKET,false);
 cAutomath_Syntax.AddRule("set_dizzy_position(","set_dizzy_position(`A`",CLexeme::ID_LEXEME_TYPE_QUOTE,CLexeme::ID_LEXEME_TYPE_QUOTE,false);
 cAutomath_Syntax.AddRule("set_dizzy_position(`A`","set_dizzy_position(`A`)",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET,true);
 
 vector_CLexeme.clear();
 Mode=MODE_WAIT_COMMAND;
}
//----------------------------------------------------------------------------------------------------
//деструктор
//----------------------------------------------------------------------------------------------------
CSyntaxAnalyzer::~CSyntaxAnalyzer()
{
}

//****************************************************************************************************
//закрытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//получить угол по строке формата a'b'c
//----------------------------------------------------------------------------------------------------
double CSyntaxAnalyzer::ConvertAngleToSec(const char *string)
{
 //разделяем части углов, минут и секунд
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
//задать описание
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
//переместить объект в заданную позицию
//----------------------------------------------------------------------------------------------------
void CSyntaxAnalyzer::CopyPosition(const std::string &name_first,const std::string &name_second,int32_t offset_x,int32_t offset_y,std::vector<std::shared_ptr<IPart> > &Map)
{
 size_t size=Map.size();
 int32_t x;
 int32_t y;
 //ищем конечную позицию
 bool find=false;
 for(size_t n=0;n<size;n++)
 {
  std::shared_ptr<IPart> iPart_Ptr=Map[n];
  if (iPart_Ptr->Name.compare(name_second)==0)
  {
   x=iPart_Ptr->BlockPosX;
   y=iPart_Ptr->BlockPosY;
   find=true;
   break;
  }
 }
 if (find==false) return;
 //перемещаем туда все найденные объекты
 for(size_t n=0;n<size;n++)
 {
  std::shared_ptr<IPart> iPart_Ptr=Map[n];
  if (iPart_Ptr->Name.compare(name_first)==0)
  {
   iPart_Ptr->BlockPosX=x+offset_x;
   iPart_Ptr->BlockPosY=y+offset_y;
  }
 }
}

//----------------------------------------------------------------------------------------------------
//переместить Диззи в заданную позицию
//----------------------------------------------------------------------------------------------------
void CSyntaxAnalyzer::SetDizzyPosition(const std::string &name,CGameState &cGameState)
{
 size_t size=cGameState.Map.size();
 int32_t x;
 int32_t y;
 //ищем конечную позицию
 bool find=false;
 for(size_t n=0;n<size;n++)
 {
  std::shared_ptr<IPart> iPart_Ptr=cGameState.Map[n];
  if (iPart_Ptr->Name.compare(name)==0)
  {
   x=iPart_Ptr->BlockPosX;
   y=iPart_Ptr->BlockPosY;
   find=true;
   break;
  }
 }
 if (find==false) return;
 //перемещаем Диззи
 cGameState.SetDizzyStartPosition(x,y);
}

//----------------------------------------------------------------------------------------------------
//обработка лексемы в режиме MODE_WAIT_COMMAND
//----------------------------------------------------------------------------------------------------
bool CSyntaxAnalyzer::ModeWaitCommand(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message,CGameState &cGameState)
{
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_SET_DESCRIPTION)
 {
  if (CommandLexeme.size()==0) return(true);
  std::string name;
  CommandLexeme[0][2].GetName(name);
  std::string description;
  CommandLexeme[0][4].GetName(description);
  SetDescription(name,description,cGameState.Map);
  CommandLexeme.clear();
  return(true);
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_COPY_POSITION)
 {
  if (CommandLexeme.size()==0) return(true);
  std::string name_first;
  CommandLexeme[0][2].GetName(name_first);
  std::string name_second;
  CommandLexeme[0][4].GetName(name_second);
  CopyPosition(name_first,name_second,0,0,cGameState.Map);
  CommandLexeme.clear();
  return(true);
 }

 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_COPY_POSITION_OFFSET)
 {
  if (CommandLexeme.size()==0) return(true);
  std::string name_first;
  CommandLexeme[0][2].GetName(name_first);
  std::string name_second;
  CommandLexeme[0][4].GetName(name_second);
  std::string offset_x_str;
  CommandLexeme[0][6].GetName(offset_x_str);
  std::string offset_y_str;
  CommandLexeme[0][8].GetName(offset_y_str);
  int32_t offset_x=atoi(offset_x_str.c_str());  
  int32_t offset_y=atoi(offset_y_str.c_str());  
  CopyPosition(name_first,name_second,offset_x,offset_y,cGameState.Map);
  CommandLexeme.clear();
  return(true);
 }

 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_SET_DIZZY_POSITION)
 {
  if (CommandLexeme.size()==0) return(true);
  std::string name;
  CommandLexeme[0][2].GetName(name);
  SetDizzyPosition(name,cGameState);
  CommandLexeme.clear();
  return(true);
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_IF_DIZZY_INTERSECTION)
 {
  Mode=MODE_WAIT_ACTION_BEGIN;
  return(true);
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_IF_NOT_DIZZY_INTERSECTION)
 {
  Mode=MODE_WAIT_ACTION_BEGIN;
  return(true);
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_IF_PICK_UP)
 {
  Mode=MODE_WAIT_ACTION_BEGIN;
  return(true);
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_IF_TIMER)
 {
  Mode=MODE_WAIT_ACTION_BEGIN;
  return(true);
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_IF_USE)
 {
  Mode=MODE_WAIT_ACTION_FIRST_BEGIN;
  return(true);
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_IF_INTERSECTION)
 {
  Mode=MODE_WAIT_ACTION_FIRST_BEGIN;
  return(true);
 }
 message="Нарушена структура команды! Ожидается условное выражение.";
 return(false);
}
//----------------------------------------------------------------------------------------------------
//обработка лексемы в режиме MODE_WAIT_ACTION_BEGIN
//----------------------------------------------------------------------------------------------------
bool CSyntaxAnalyzer::ModeWaitActionBegin(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message)
{
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_BEGIN)
 {
  Mode=MODE_ADD_ACTION;
  return(true);
 }
 message="Нарушена структура команды! Ожидается ActionBegin.";
 return(false);
}
//----------------------------------------------------------------------------------------------------
//обработка лексемы в режиме MODE_WAIT_ACTION_FIRST_BEGIN
//----------------------------------------------------------------------------------------------------
bool CSyntaxAnalyzer::ModeWaitActionFirstBegin(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message)
{
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_FIRST_BEGIN)
 {
  Mode=MODE_ADD_ACTION_FIRST;
  return(true);
 }
 message="Нарушена структура команды! Ожидается ActionFirstBegin";
 return(false);
}
//----------------------------------------------------------------------------------------------------
//обработка лексемы в режиме MODE_WAIT_ACTION_SECOND_BEGIN
//----------------------------------------------------------------------------------------------------
bool CSyntaxAnalyzer::ModeWaitActionSecondBegin(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message)
{
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_SECOND_BEGIN)
 {
  Mode=MODE_ADD_ACTION_SECOND;
  return(true);
 }
 message="Нарушена структура команды! Ожидается ActionSecondBegin";
 return(false);
}

//----------------------------------------------------------------------------------------------------
//проверка принадлежности лексемы к типу действий
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
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_COPY_POSITION_OFFSET) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_PICK_UP) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_SET_ANIMATION_STEP) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_SET_ENABLED) return(true); 
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_SINGLE) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_MOVE) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_ENERGY_UPDATE) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_ADD_SCORE) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_ADD_LIFE) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_ADD_ITEM) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_CHANGE_ANIMATION_MODE) return(true);
 return(false);
}

//----------------------------------------------------------------------------------------------------
//обработка лексемы в режиме MODE_ADD_ACTION_FIRST
//----------------------------------------------------------------------------------------------------
bool CSyntaxAnalyzer::ModeAddActionFirst(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message)
{
 if (IsAction(cLexeme_Command)==true) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_FIRST_END)
 {
  Mode=MODE_WAIT_ACTION_SECOND_BEGIN;
  return(true);
 }
 message="Нарушена структура команды! Ожидается ActionFirstEnd";
 return(false);
}

//----------------------------------------------------------------------------------------------------
//обработка лексемы в режиме MODE_ADD_ACTION_SECOND
//----------------------------------------------------------------------------------------------------
bool CSyntaxAnalyzer::ModeAddActionSecond(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message,std::vector<std::shared_ptr<IConditionalExpression> > &ConditionalExpression)
{
 if (IsAction(cLexeme_Command)==true) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_SECOND_END)
 {
  Mode=MODE_WAIT_COMMAND;
  //отправляем команду на создание
  std::shared_ptr<IConditionalExpression> iConditionalExpression_Ptr=CreateConditional();
  if (iConditionalExpression_Ptr.get()!=NULL) ConditionalExpression.push_back(iConditionalExpression_Ptr);
  CommandLexeme.clear();
  return(true);
 }
 message="Нарушена структура команды! Ожидается ActionSecondEnd";
 return(false);
}
//----------------------------------------------------------------------------------------------------
//обработка лексемы в режиме MODE_ADD_ACTION
//----------------------------------------------------------------------------------------------------
bool CSyntaxAnalyzer::ModeAddAction(const CLexeme &cLexeme_Command,int32_t line_index,std::string &message,std::vector<std::shared_ptr<IConditionalExpression> > &ConditionalExpression)
{
 if (IsAction(cLexeme_Command)==true) return(true);
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_END)
 {
  Mode=MODE_WAIT_COMMAND;
  //отправляем команду на создание  
  std::shared_ptr<IConditionalExpression> iConditionalExpression_Ptr=CreateConditional();
  if (iConditionalExpression_Ptr.get()!=NULL) ConditionalExpression.push_back(iConditionalExpression_Ptr);
  CommandLexeme.clear();
  return(true);
 }
 message="Нарушена структура команды! Ожидается ActionEnd";
 return(false);
}

//----------------------------------------------------------------------------------------------------
//сформирована новая команда
//----------------------------------------------------------------------------------------------------
bool CSyntaxAnalyzer::NewCommand(const std::vector<CLexeme> &lexeme,int32_t line_index,std::string &message,std::vector<std::shared_ptr<IConditionalExpression> > &ConditionalExpression,CGameState &cGameState)
{ 
 if (lexeme.size()==0) return(true);
 //сохраняем лексемы (создавать действия и условия будем в обратном порядке)
 CommandLexeme.push_back(lexeme);
 //смотрим, в каком режиме работает транслятор
 const CLexeme &cLexeme_Command=lexeme[0];
 //ожидание команды
 if (Mode==MODE_WAIT_COMMAND) return(ModeWaitCommand(cLexeme_Command,line_index,message,cGameState));
 if (Mode==MODE_WAIT_ACTION_BEGIN) return(ModeWaitActionBegin(cLexeme_Command,line_index,message));
 if (Mode==MODE_WAIT_ACTION_FIRST_BEGIN) return(ModeWaitActionFirstBegin(cLexeme_Command,line_index,message));
 if (Mode==MODE_WAIT_ACTION_SECOND_BEGIN) return(ModeWaitActionSecondBegin(cLexeme_Command,line_index,message));
 if (Mode==MODE_ADD_ACTION_FIRST) return(ModeAddActionFirst(cLexeme_Command,line_index,message));
 if (Mode==MODE_ADD_ACTION_SECOND) return(ModeAddActionSecond(cLexeme_Command,line_index,message,ConditionalExpression));
 if (Mode==MODE_ADD_ACTION) return(ModeAddAction(cLexeme_Command,line_index,message,ConditionalExpression));
 return(false);
}

//----------------------------------------------------------------------------------------------------
//создать действие по лексеме
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
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_COPY_POSITION_OFFSET)
 {
  std::string name_first;
  lexeme[2].GetName(name_first);
  std::string name_second;
  lexeme[4].GetName(name_second);
  std::string offset_x_str;
  lexeme[6].GetName(offset_x_str);
  std::string offset_y_str;
  lexeme[8].GetName(offset_y_str);
  int32_t offset_x=atoi(offset_x_str.c_str());  
  int32_t offset_y=atoi(offset_y_str.c_str());  
  return(std::shared_ptr<IAction>(new CActionCopyPositionOffset(name_first,name_second,offset_x,offset_y,next_ptr)));
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
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_MOVE)
 {
  std::string dx_str;
  lexeme[2].GetName(dx_str);
  std::string dy_str;
  lexeme[4].GetName(dy_str);
  int32_t dx=atoi(dx_str.c_str());
  int32_t dy=atoi(dy_str.c_str());
  return(std::shared_ptr<IAction>(new CActionMove(dx,dy,next_ptr)));
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_ENERGY_UPDATE)
 {
  std::string denergy_str;
  lexeme[2].GetName(denergy_str);
  int32_t denergy=atoi(denergy_str.c_str());
  return(std::shared_ptr<IAction>(new CActionEnergyUpdate(denergy,next_ptr)));
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_ADD_SCORE)
 {
  std::string dscore_str;
  lexeme[2].GetName(dscore_str);
  int32_t dscore=atoi(dscore_str.c_str());
  return(std::shared_ptr<IAction>(new CActionAddScore(dscore,next_ptr)));
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_ADD_LIFE)
 {
  return(std::shared_ptr<IAction>(new CActionAddLife(next_ptr)));
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_ADD_ITEM)
 {
  return(std::shared_ptr<IAction>(new CActionAddItem(next_ptr)));
 }
 if (cLexeme_Command.GetType()==ID_LEXEME_TYPE_ACTION_CHANGE_ANIMATION_MODE)
 {
  std::string mode_str;
  lexeme[2].GetName(mode_str);
  CTilesSequence::ANIMATION_MODE mode=CTilesSequence::ANIMATION_MODE_SET_STEP;
  if (mode_str.compare("animation_cyclic")==0) mode=CTilesSequence::ANIMATION_MODE_CYCLIC;
  if (mode_str.compare("animation_set_step")==0) mode=CTilesSequence::ANIMATION_MODE_SET_STEP;
  if (mode_str.compare("animation_one_shot")==0) mode=CTilesSequence::ANIMATION_MODE_ONE_SHOT;
  return(std::shared_ptr<IAction>(new CActionChangeAnimationMode(mode,next_ptr)));
 }

 return(std::shared_ptr<IAction>(NULL));
}
//----------------------------------------------------------------------------------------------------
//создание условного выражение по списку лексем
//----------------------------------------------------------------------------------------------------
std::shared_ptr<IConditionalExpression> CSyntaxAnalyzer::CreateConditional(void)
{
 //создаём действия в обратном порядке
 size_t size=CommandLexeme.size();
 if (size==0) return(std::shared_ptr<IConditionalExpression>(NULL));
 //узнаем, что за условие мы создаём
 if (CommandLexeme[0][0].GetType()==ID_LEXEME_TYPE_IF_DIZZY_INTERSECTION)
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
  return(std::shared_ptr<IConditionalExpression>(new CConditionalOfDizzyIntersection(name,iAction_Ptr)));
 }

 if (CommandLexeme[0][0].GetType()==ID_LEXEME_TYPE_IF_NOT_DIZZY_INTERSECTION)
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
  return(std::shared_ptr<IConditionalExpression>(new CConditionalOfNotDizzyIntersection(name,iAction_Ptr)));
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

 if (CommandLexeme[0][0].GetType()==ID_LEXEME_TYPE_IF_TIMER)
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

  return(std::shared_ptr<IConditionalExpression>(new CConditionalOfTimer(name,iAction_Ptr)));
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

 if (CommandLexeme[0][0].GetType()==ID_LEXEME_TYPE_IF_INTERSECTION)
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
  return(std::shared_ptr<IConditionalExpression>(new CConditionalOfIntersection(name_first,name_second,iAction_First_Ptr,iAction_Second_Ptr)));
 }

 return(std::shared_ptr<IConditionalExpression>(NULL));
}

//****************************************************************************************************
//открытые функции
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//создать условия
//----------------------------------------------------------------------------------------------------
bool CSyntaxAnalyzer::Processing(char symbol,int32_t line_index,std::string &message,bool &new_line,CGameState &cGameState)
{
 message="";
 new_line=false;
 //получаем лексемы
 std::vector<CLexeme> vector_CLexeme_Get;
 if (cLexicalAnalyzer.GetLexeme(symbol,vector_CLexeme_Get)==false)
 {
  if (symbol==0)//файл закончился
  {
   if (cAutomath_Syntax.CompareCurrentState("begin")==false && cAutomath_Syntax.IsCurrentStateEndingType()==false)//команда не закончена
   {
    message="Ошибка! Команда не закончена:";
    std::string line;
    cAutomath_Syntax.GetInputLineToString(line);
    message=message+line;
    new_line=true;
    return(false);
   }
  }
  return(true);
 }
 //разбираем лексемы
 size_t size=vector_CLexeme_Get.size();
 for(size_t n=0;n<size;n++)
 {
  CLexeme &cLexeme=vector_CLexeme_Get[n];
  //автомат принял лексему
  //выдаём лексему в выходной поток
  if (cLexeme.GetType()!=CLexeme::ID_LEXEME_TYPE_TERMINAL)//терминальный символ не печатаем
  {
   std::string name;  	
   cLexeme.GetName(name);
   message=message+name;
  }
  //отправляем лексему автомату синтаксического анализа
  if (cAutomath_Syntax.Push(cLexeme.GetType())==true)//автомат принял лексему
  {
   vector_CLexeme.push_back(cLexeme);
   if (cAutomath_Syntax.IsCurrentStateEndingType()==true)
   {
    if (NewCommand(vector_CLexeme,line_index,message,cGameState.ConditionalExpression,cGameState)==false) return(false);
    vector_CLexeme.clear();
    new_line=true;
   }
  }
  else//ошибка!
  {
  //если это терминальный символ
   if (cLexeme.GetType()==CLexeme::ID_LEXEME_TYPE_TERMINAL)
   {
    //если оказался обрыв команды
    if (cAutomath_Syntax.CompareCurrentState("begin")==false && cAutomath_Syntax.IsCurrentStateEndingType()==false)
    {
     message="Ошибка! Команда не закончена:";
     std::string line;
     cAutomath_Syntax.GetInputLineToString(line);
     message=message+line;
     new_line=true;
     return(false);
    }
    //просто терминальный символ пропускаем   
    cAutomath_Syntax.Reset();
    vector_CLexeme.clear();
    continue;
   }
   message="Ошибка! Неверная команда:";
   std::string line;
   cLexeme.GetName(line);
   message=message+line;
   new_line=true;  
   return(false);
  }
 } 
 return(true);
}
