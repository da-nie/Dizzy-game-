//****************************************************************************************************
//������������ ����������
//****************************************************************************************************
#include "system.h"

#include <string.h>
#include <windows.h>
#include <stdint.h>

//****************************************************************************************************
//���������� �������
//****************************************************************************************************

//----------------------------------------------------------------------------------------------------
//������� ������ ������ ����������
//----------------------------------------------------------------------------------------------------
void CreateFileList(const std::string &path,std::vector<std::string> &vector_file_name)
{
 vector_file_name.clear();
 char current_directory[MAX_PATH];
 if (GetCurrentDirectory(MAX_PATH,current_directory)==FALSE) return;
 if (SetCurrentDirectory(path.c_str())==FALSE) return;

 WIN32_FIND_DATA wfd;
 HANDLE handle=FindFirstFile("*",&wfd);
 if (handle==INVALID_HANDLE_VALUE) 
 {
  SetCurrentDirectory(current_directory);
  return;
 }
 while(true)
 {
  if (wfd.cFileName[0]!='.' && !(wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))//���� ��� ����
  {
   //��������� ���� � ������
   std::string file_name=path;
   file_name+=GetPathDivider();
   file_name+=wfd.cFileName;
   vector_file_name.push_back(wfd.cFileName);
  }
  if (FindNextFile(handle,&wfd)==FALSE) break;
 }
 FindClose(handle);
 SetCurrentDirectory(current_directory);
}

//----------------------------------------------------------------------------------------------------
//������� ������ ��������� ����������
//----------------------------------------------------------------------------------------------------
void CreateDirectoryList(const std::string &path,std::vector<std::string> &vector_directory_name)
{
 vector_directory_name.clear();
 char current_directory[MAX_PATH];
 if (GetCurrentDirectory(MAX_PATH,current_directory)==FALSE) return;
 if (SetCurrentDirectory(path.c_str())==FALSE) return;
 
 WIN32_FIND_DATA wfd;
 HANDLE handle=FindFirstFile("*",&wfd);
 if (handle==INVALID_HANDLE_VALUE) 
 {
  SetCurrentDirectory(current_directory);
  return;
 }
 while(true)
 {
  if (wfd.cFileName[0]!='.' && (wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))//���� ��� ����������
  {   
   std::string new_path=path;
   new_path+=GetPathDivider();
   new_path+=wfd.cFileName;
   vector_directory_name.push_back(wfd.cFileName);
  }
  if (FindNextFile(handle,&wfd)==FALSE) break;
 }
 FindClose(handle);
 SetCurrentDirectory(current_directory);
}

//----------------------------------------------------------------------------------------------------
//������� �������
//----------------------------------------------------------------------------------------------------
void MakeDirectory(const std::string &directory_name)
{
 CreateDirectory(directory_name.c_str(),NULL);
}

//----------------------------------------------------------------------------------------------------
//�������� ��������� ����� � ��������
//----------------------------------------------------------------------------------------------------
long double GetSecondCounter(void)
{
 return(GetTickCount()/1000.0);
}
//----------------------------------------------------------------------------------------------------
//����� � �������������
//----------------------------------------------------------------------------------------------------
void PauseInMs(size_t ms)
{
 HANDLE hEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
 ResetEvent(hEvent);
 WaitForSingleObject(hEvent,ms);
 CloseHandle(hEvent);
}
//----------------------------------------------------------------------------------------------------
//�������� ������� ����������
//----------------------------------------------------------------------------------------------------
std::string GetCurrentPath(void)
{
 char path[MAX_PATH];
 GetCurrentDirectory(MAX_PATH,path);
 return(std::string(path));
}
//----------------------------------------------------------------------------------------------------
//�������� ����������� ��������
//----------------------------------------------------------------------------------------------------
std::string GetPathDivider(void)
{
 return(std::string("\\"));
}
//----------------------------------------------------------------------------------------------------
//������� ���������
//----------------------------------------------------------------------------------------------------
void PutMessage(const std::string &message)
{
 MessageBox(NULL,message.c_str(),"���������",MB_OK);
}
//----------------------------------------------------------------------------------------------------
//������� ��������� � �������
//----------------------------------------------------------------------------------------------------
void PutMessageToConsole(const std::string &message)
{
 FILE *file=fopen("log.txt","ab");
 if (file==NULL) return;
 fprintf(file,"%s",message.c_str());
 fclose(file);
}
//----------------------------------------------------------------------------------------------------
//����������� ����
//----------------------------------------------------------------------------------------------------
void CopyFileTo(const std::string &source_file,const std::string &target_file)
{
 FILE *file_one=fopen(source_file.c_str(),"rb");
 if (file_one==NULL) return;
 FILE *file_two=fopen(target_file.c_str(),"wb");
 if (file_two==NULL)
 {
  fclose(file_one);
  return;
 }
 printf("Copy file:%s -> %s\r\n",source_file.c_str(),target_file.c_str());

 uint8_t buffer[65536];
 while(1)
 {
  size_t size=fread(buffer,sizeof(uint8_t),65535,file_one);
  if (size==0) break;
  fwrite(buffer,sizeof(uint8_t),size,file_two);
 }
 fclose(file_one);
 fclose(file_two);
}

//----------------------------------------------------------------------------------------------------
//��������� ����
//----------------------------------------------------------------------------------------------------
void MoveFileTo(const std::string &source_file,const std::string &target_file)
{
 FILE *file_one=fopen(source_file.c_str(),"rb");
 if (file_one==NULL) return;
 FILE *file_two=fopen(target_file.c_str(),"wb");
 if (file_two==NULL)
 {
  fclose(file_one);
  return;
 }
 printf("Copy file:%s -> %s\r\n",source_file.c_str(),target_file.c_str());

 uint8_t buffer[65536];
 while(1)
 {
  size_t size=fread(buffer,sizeof(uint8_t),65535,file_one);
  if (size==0) break;
  fwrite(buffer,sizeof(uint8_t),size,file_two);
 }
 fclose(file_one);
 fclose(file_two);
 //������� ����
 DeleteFile(source_file.c_str());
}