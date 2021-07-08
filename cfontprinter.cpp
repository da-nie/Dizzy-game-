//****************************************************************************************************
//������������ ����������
//****************************************************************************************************
#include "cfontprinter.h"

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
CFontPrinter::CFontPrinter(const std::string &file_name,int32_t font_width,int32_t font_height,uint8_t alpha_r,uint8_t alpha_g,uint8_t alpha_b)
{ 
 FontWidth=font_width;
 FontHeight=font_height;
 cSprite_Font.Load(file_name.c_str());
 cSprite_Font.SetAlpha(0,alpha_r,alpha_g,alpha_b);
}
//----------------------------------------------------------------------------------------------------
//����������
//----------------------------------------------------------------------------------------------------
CFontPrinter::~CFontPrinter()
{
}

//****************************************************************************************************
//�������� �������
//****************************************************************************************************

//****************************************************************************************************
//�������� �������
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//���������� ������
//----------------------------------------------------------------------------------------------------
void CFontPrinter::PrintAt(int32_t x,int32_t y,const std::string &str,IVideo *iVideo_Ptr)
{
 size_t length=str.length();
 const char *ptr=str.c_str();
 for(size_t n=0;n<length;n++,ptr++,x+=FontWidth)
 {
  uint8_t symbol=*ptr;
  int32_t pos=-1;
  if (symbol==static_cast<uint8_t>('`')) pos=0;
  if (symbol==static_cast<uint8_t>(';')) pos=1;
  if (symbol==static_cast<uint8_t>(',')) pos=2;
  if (symbol==static_cast<uint8_t>('.')) pos=3;
  if (symbol==static_cast<uint8_t>('=')) pos=4;
  if (symbol==static_cast<uint8_t>('(')) pos=5;
  if (symbol==static_cast<uint8_t>(')')) pos=6;
  if (symbol==static_cast<uint8_t>('-')) pos=7;
  if (symbol==static_cast<uint8_t>('+')) pos=8;
  if (symbol==static_cast<uint8_t>(':')) pos=9;
  if (symbol==static_cast<uint8_t>('!')) pos=10;
  if (symbol==static_cast<uint8_t>('\"')) pos=11;
  if (symbol==static_cast<uint8_t>('?')) pos=12;
  if (symbol==static_cast<uint8_t>('{')) pos=13;
  if (symbol==static_cast<uint8_t>('|')) pos=14;
  if (symbol==static_cast<uint8_t>('}')) pos=15;
  if (symbol==static_cast<uint8_t>('~')) pos=16;
  if (symbol>=static_cast<uint8_t>('0') && symbol<=static_cast<uint8_t>('9')) pos=17+symbol-static_cast<uint8_t>('0');
  if (symbol>=static_cast<uint8_t>('A') && symbol<=static_cast<uint8_t>('Z')) pos=27+symbol-static_cast<uint8_t>('A');
  if (symbol==static_cast<uint8_t>('�')) pos=53;
  if (symbol==static_cast<uint8_t>('�')) pos=54;
  if (symbol==static_cast<uint8_t>('�')) pos=55;
  if (symbol==static_cast<uint8_t>('�')) pos=56;
  if (symbol==static_cast<uint8_t>('�')) pos=57;
  if (symbol==static_cast<uint8_t>('�')) pos=58;
  if (symbol==static_cast<uint8_t>('�')) pos=59;
  if (symbol==static_cast<uint8_t>('�')) pos=60;
  if (symbol==static_cast<uint8_t>('�')) pos=61;
  if (symbol==static_cast<uint8_t>('�')) pos=62;
  if (symbol==static_cast<uint8_t>('�')) pos=63;
  if (symbol==static_cast<uint8_t>('�')) pos=64;
  if (symbol==static_cast<uint8_t>('�')) pos=65;
  if (symbol==static_cast<uint8_t>('�')) pos=66;
  if (symbol==static_cast<uint8_t>('�')) pos=67;
  if (symbol==static_cast<uint8_t>('�')) pos=68;
  if (symbol==static_cast<uint8_t>('�')) pos=69;
  if (symbol==static_cast<uint8_t>('�')) pos=70;
  if (symbol==static_cast<uint8_t>('�')) pos=71;
  if (symbol==static_cast<uint8_t>('�')) pos=72;
  if (symbol==static_cast<uint8_t>('�')) pos=73;
  if (symbol==static_cast<uint8_t>('�')) pos=74;
  if (symbol==static_cast<uint8_t>('�')) pos=75;
  if (symbol==static_cast<uint8_t>('�')) pos=76;
  if (symbol==static_cast<uint8_t>('�')) pos=77;
  if (symbol==static_cast<uint8_t>('�')) pos=78;
  if (symbol==static_cast<uint8_t>('�')) pos=79;
  if (symbol==static_cast<uint8_t>('�')) pos=80;
  if (symbol==static_cast<uint8_t>('�')) pos=81;
  if (symbol==static_cast<uint8_t>('�')) pos=82;
  if (symbol==static_cast<uint8_t>('�')) pos=83;
  if (symbol==static_cast<uint8_t>('�')) pos=84;
  if (symbol==static_cast<uint8_t>('�')) pos=85;
  if (pos<0) continue;
  cSprite_Font.PutSpriteItem(iVideo_Ptr,x,y,pos*(FontWidth+2)+1,1,FontWidth,FontHeight,true);
 }
}
//----------------------------------------------------------------------------------------------------
//�������� ������ ������
//----------------------------------------------------------------------------------------------------
int32_t CFontPrinter::GetFontWidth(void)
{
 return(FontWidth);
}
//----------------------------------------------------------------------------------------------------
//�������� ������ ������
//----------------------------------------------------------------------------------------------------
int32_t CFontPrinter::GetFontHeight(void)
{
 return(FontHeight);
}