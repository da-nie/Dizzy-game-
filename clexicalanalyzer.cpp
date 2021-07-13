//****************************************************************************************************
//������������ ����������
//****************************************************************************************************
#include "clexicalanalyzer.h"
#include <stdio.h>

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
CLexicalAnalyzer::CLexicalAnalyzer(void)
{
 //������ ������� ������������ ������� ������� ������
 cAutomath_PrimaryLevel.AddRule("begin","left bracker end",'(','(',true);
 cAutomath_PrimaryLevel.AddRule("begin","right bracker end",')',')',true);
 cAutomath_PrimaryLevel.AddRule("begin","is end",'=','=',true);
 cAutomath_PrimaryLevel.AddRule("begin","comma end",',',',',true);
 //cAutomath_PrimaryLevel.AddRule("begin","plus end",'+','+',true);
 //cAutomath_PrimaryLevel.AddRule("begin","minus end",'-','-',true);
 cAutomath_PrimaryLevel.AddRule("begin","quote",'\"','\"',false);
 cAutomath_PrimaryLevel.AddRule("begin","terminal",0,0,true);
 cAutomath_PrimaryLevel.AddRule("begin","terminal",10,10,true);
 cAutomath_PrimaryLevel.AddRule("begin","terminal",13,13,true);

 cAutomath_PrimaryLevel.AddRule("quote","quote end file",0,0,true);
 cAutomath_PrimaryLevel.AddRule("quote","quote end",'\"','\"',true);
 cAutomath_PrimaryLevel.AddRule("quote","quote",0,255,false);

 cAutomath_PrimaryLevel.AddRule("begin","slash",'/','/',false);
 cAutomath_PrimaryLevel.AddRule("slash","slash end",13,13,true);
 cAutomath_PrimaryLevel.AddRule("slash","slash end",10,10,true);
 cAutomath_PrimaryLevel.AddRule("slash","slash end",0,0,true);
 cAutomath_PrimaryLevel.AddRule("slash","slash",1,255,false);

 cAutomath_PrimaryLevel.AddRule("begin","line",33,255,false);
 cAutomath_PrimaryLevel.AddRule("line","line end symbol",'(','(',true);
 cAutomath_PrimaryLevel.AddRule("line","line end symbol",')',')',true);
 cAutomath_PrimaryLevel.AddRule("line","line end symbol",'=','=',true);
 cAutomath_PrimaryLevel.AddRule("line","line end symbol",'+','+',true);
 cAutomath_PrimaryLevel.AddRule("line","line end symbol",'-','-',true); 
 cAutomath_PrimaryLevel.AddRule("line","line end symbol",',',',',true);
 cAutomath_PrimaryLevel.AddRule("line","line end symbol",'\"','\"',true);
 cAutomath_PrimaryLevel.AddRule("line","line end symbol",'/','/',true);
 cAutomath_PrimaryLevel.AddRule("line","line end",0,32,true);
 cAutomath_PrimaryLevel.AddRule("line","line",33,255,false);
 //������� ������������ �����
 cAutomath_NaturalNumber.AddRule("begin","NN",'0','9',false);
 cAutomath_NaturalNumber.AddRule("NN","NN",'0','9',false);
 cAutomath_NaturalNumber.AddRule("NN","NN1 end",0,32,true);
 //������� ������ �����
 cAutomath_NegativeNaturalNumber.AddRule("begin","NN",'0','9',false);
 cAutomath_NegativeNaturalNumber.AddRule("begin","NN",'-','-',false);
 cAutomath_NegativeNaturalNumber.AddRule("NN","NN",'0','9',false);
 cAutomath_NegativeNaturalNumber.AddRule("NN","NN1 end",0,32,true);
 //������� ����
 cAutomath_AngleNumber.AddRule("begin","NN",'0','9',false);
 cAutomath_AngleNumber.AddRule("NN","NN",'0','9',false);
 cAutomath_AngleNumber.AddRule("NN","NN`",'`','`',false);
 cAutomath_AngleNumber.AddRule("NN`","NN`NN",'0','9',false);
 cAutomath_AngleNumber.AddRule("NN`NN","NN`NN",'0','9',false);
 cAutomath_AngleNumber.AddRule("NN`NN","NN`NN`",'`','`',false);
 cAutomath_AngleNumber.AddRule("NN`NN`","NN`NN`NN",'0','9',false);
 cAutomath_AngleNumber.AddRule("NN`NN`NN","NN`NN`NN",'0','9',false);
 cAutomath_AngleNumber.AddRule("NN`NN`NN","end",0,'0'-1,true);
 cAutomath_AngleNumber.AddRule("NN`NN`NN","end",'9'+1,255,true);
 //������� ����� � ��������� ������
 cAutomath_FloatNumber.AddRule("begin","+-",'-','-',false);
 cAutomath_FloatNumber.AddRule("begin","+-",'+','+',false);
 cAutomath_FloatNumber.AddRule("begin","+-.",'.','.',false);
 cAutomath_FloatNumber.AddRule("begin","N",'0','9',false);
 cAutomath_FloatNumber.AddRule("N","N",'0','9',false);
 cAutomath_FloatNumber.AddRule("N","number end",0,32,true);
 cAutomath_FloatNumber.AddRule("N","N.",'.','.',false);
 cAutomath_FloatNumber.AddRule("N.","end",0,32,true);
 cAutomath_FloatNumber.AddRule("N.","N.N",'0','9',false);
 cAutomath_FloatNumber.AddRule("N.N","N.N",'0','9',false);
 cAutomath_FloatNumber.AddRule("N.N","end",0,32,true);
 cAutomath_FloatNumber.AddRule("N.N","N.NE",'E','E',false);
 cAutomath_FloatNumber.AddRule("N.N","N.NE",'e','e',false);
 cAutomath_FloatNumber.AddRule("N.NE","N.NE+-",'-','-',false);
 cAutomath_FloatNumber.AddRule("N.NE","N.NE+-",'+','+',false);
 cAutomath_FloatNumber.AddRule("N.NE","N.NEN",'0','9',false);
 cAutomath_FloatNumber.AddRule("N.NEN","N.NEN",'0','9',false);
 cAutomath_FloatNumber.AddRule("N.NEN","end",0,32,true);
 cAutomath_FloatNumber.AddRule("+-","N",'0','9',false);
 cAutomath_FloatNumber.AddRule("+-","+-.",'.','.',false);
 cAutomath_FloatNumber.AddRule("+-.","N",'0','9',false);
 cAutomath_FloatNumber.AddRule("N.NE+-","N.NEN",'0','9',false);
 
 //������ ��������������� �������
 AddLexeme("unknow",CLexeme::ID_LEXEME_TYPE_UNKNOW);
 AddLexeme("integer",CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER);
 AddLexeme("float",CLexeme::ID_LEXEME_TYPE_FLOAT_NUMBER);
 AddLexeme("angle",CLexeme::ID_LEXEME_TYPE_ANGLE_NUMBER);
 AddLexeme("(",CLexeme::ID_LEXEME_TYPE_LEFTBRACKET);
 AddLexeme(")",CLexeme::ID_LEXEME_TYPE_RIGHTBRACKET);
 AddLexeme("=",CLexeme::ID_LEXEME_TYPE_IS);
 //AddLexeme("+",CLexeme::ID_LEXEME_TYPE_PLUS);
 //AddLexeme("-",CLexeme::ID_LEXEME_TYPE_MINUS);
 AddLexeme("\0",CLexeme::ID_LEXEME_TYPE_TERMINAL);
 AddLexeme("\r",CLexeme::ID_LEXEME_TYPE_TERMINAL);
 AddLexeme("\n",CLexeme::ID_LEXEME_TYPE_TERMINAL);
 AddLexeme(",",CLexeme::ID_LEXEME_TYPE_COMMA);
 
 Reset();
}
//----------------------------------------------------------------------------------------------------
//����������
//----------------------------------------------------------------------------------------------------
CLexicalAnalyzer::~CLexicalAnalyzer()
{
}

//****************************************************************************************************
//�������� �������
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//�������� ��� �������
//----------------------------------------------------------------------------------------------------
size_t CLexicalAnalyzer::GetLexemeType(const std::string &name)
{
 //���������� ������� � ����, ��� ��� ������������
 size_t size=vector_CLexeme.size();
 for(size_t n=0;n<size;n++)
 {
  const CLexeme &cLexeme=vector_CLexeme[n];
  //� �������� ����� � ����������� �� ����������
  size_t type=cLexeme.GetType();
  if (type==CLexeme::ID_LEXEME_TYPE_UNKNOW || type==CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER || type==CLexeme::ID_LEXEME_TYPE_FLOAT_NUMBER || type==CLexeme::ID_LEXEME_TYPE_ANGLE_NUMBER) continue;
  //���������� ����� ������
  if (cLexeme.CompareName(name)==true) return(cLexeme.GetType());//����� �������
 }
 
 //�� ����� �������, ����� ���� ��� ����������� �����?
 size_t n;
 cAutomath_NaturalNumber.Reset();
 size_t length=name.length();
 for(n=0;n<=length;n++)
 {
  if (cAutomath_NaturalNumber.Push(name[n])==true) 
  {
   if (cAutomath_NaturalNumber.IsCurrentStateEndingType()==true)//������� ����� � ����������� ���������
   {
    return(CLexeme::ID_LEXEME_TYPE_NATURAL_NUMBER);
   }
  }
  else break;//������� ������ ������
 }

 //�� ����� �������, ����� ���� ��� ������������� ����������� �����? 
 cAutomath_NegativeNaturalNumber.Reset(); 
 for(n=0;n<=length;n++)
 {
  if (cAutomath_NegativeNaturalNumber.Push(name[n])==true) 
  {
   if (cAutomath_NegativeNaturalNumber.IsCurrentStateEndingType()==true)//������� ����� � ����������� ���������
   {
    return(CLexeme::ID_LEXEME_TYPE_NEGATIVE_NATURAL_NUMBER);
   }
  }
  else break;//������� ������ ������
 }

 
 //�� ����� �������, ����� ���� ��� ����?
 cAutomath_AngleNumber.Reset();
 for(n=0;n<=length;n++)
 {
  if (cAutomath_AngleNumber.Push(name[n])==true) 
  {
   if (cAutomath_AngleNumber.IsCurrentStateEndingType()==true)//������� ����� � ����������� ���������
   {
    return(CLexeme::ID_LEXEME_TYPE_ANGLE_NUMBER);
   }
  }
  else break;//������� ������ ������
 }
 
 //�� ����� �������, ����� ���� ��� ����� � ��������� ������?
 cAutomath_FloatNumber.Reset();
 for(n=0;n<=length;n++)
 {
  if (cAutomath_FloatNumber.Push(name[n])==true) 
  {
   if (cAutomath_FloatNumber.IsCurrentStateEndingType()==true)//������� ����� � ����������� ���������
   {
    return(CLexeme::ID_LEXEME_TYPE_FLOAT_NUMBER);
   }
  }
  else break;//������� ������ ������
 }
 //���������� ����������� �������
 return(CLexeme::ID_LEXEME_TYPE_UNKNOW);
}

//****************************************************************************************************
//�������� �������
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//�������� ���������� � �������� ���������
//----------------------------------------------------------------------------------------------------
void CLexicalAnalyzer::Reset(void)
{
 cAutomath_PrimaryLevel.Reset();
 deque_Input.clear();
}

//----------------------------------------------------------------------------------------------------
//�������� ������� � ������ ��������������
//----------------------------------------------------------------------------------------------------
void CLexicalAnalyzer::AddLexeme(const std::string &name,size_t type)
{
 CLexeme cLexeme;
 cLexeme.SetName(name);
 cLexeme.SetType(type);
 vector_CLexeme.push_back(cLexeme);
}
//----------------------------------------------------------------------------------------------------
//������ ��������� ������ � �������� ��������� �������
//----------------------------------------------------------------------------------------------------
bool CLexicalAnalyzer::GetLexeme(char symbol,std::vector<CLexeme> &vector_CLexeme)
{
 deque_Input.push_back(symbol);
 vector_CLexeme.clear(); 
 while(deque_Input.size()>0)
 {
  //���� ������ �� ������ �������
  symbol=*(deque_Input.begin());
  deque_Input.pop_front();  
  //���������� ������ �������� ���������� �������
  if (cAutomath_PrimaryLevel.Push(static_cast<uint8_t>(symbol))==false)//������� �� ������ ������ �������� ������
  {
   if (cAutomath_PrimaryLevel.CompareCurrentState("begin")==false)//���� ������� ���-�� �������, ��������� ������� �� ���������� �������
   {   	 
    cAutomath_PrimaryLevel.Reset();
    deque_Input.push_front(symbol);//���������� ������ � ������    
    continue;
   }
   cAutomath_PrimaryLevel.Reset();   
   return(false);
  }
  if (cAutomath_PrimaryLevel.IsCurrentStateEndingType()==false) return(false);//������� ��� �� ����� � ����������� ���������
 
  //������� ����� � ����������� ��������� 
  if (cAutomath_PrimaryLevel.CompareCurrentState("slash end")==true)//��� ������� �����������
  {
   cAutomath_PrimaryLevel.Reset();   
   return(false);
  }
  std::string word;
  cAutomath_PrimaryLevel.GetInputLineToString(word);
  if (cAutomath_PrimaryLevel.CompareCurrentState("line end symbol")==true || cAutomath_PrimaryLevel.CompareCurrentState("line end")==true)
  {   
   deque_Input.push_front(symbol);//��������� ������������ ������ �� ������� �������
   word.erase(word.end()-1,word.end());//��������� ������ ������������ � ��� ����� ������
  }
  
  CLexeme cLexeme;
  cLexeme.SetName(word);
  if (cAutomath_PrimaryLevel.CompareCurrentState("quote end")==true)//��� ������� �������� ������� � �������
  {	
   //������� �������
   std::string name;
   cLexeme.GetName(name);
   std::string new_name;
   int32_t length=name.length();
   new_name.reserve(length);
   for(int32_t n=1;n<length-1;n++) new_name+=name[n];
   cLexeme.SetName(new_name);
   cLexeme.SetType(CLexeme::ID_LEXEME_TYPE_QUOTE);
   cAutomath_PrimaryLevel.Reset();   
   vector_CLexeme.push_back(cLexeme);
   continue;
  }
  if (cAutomath_PrimaryLevel.CompareCurrentState("quote end file")==true)//��� ������� ������� � �������, ������� �� �����������
  {
   cLexeme.SetType(CLexeme::ID_LEXEME_TYPE_UNKNOW);
   cAutomath_PrimaryLevel.Reset();
   vector_CLexeme.push_back(cLexeme);
   continue;
  }
  //���������� �� ���������� ������� ������  
  cLexeme.SetType(GetLexemeType(word));//���������� ��� �������
  cAutomath_PrimaryLevel.Reset();
  vector_CLexeme.push_back(cLexeme);
  continue;
 } 
 return(true);
}