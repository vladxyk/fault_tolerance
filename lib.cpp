#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <dirent.h>
#include <iomanip>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <experimental/filesystem>

//RestartForceExitStatus=11 SIGABRT

using namespace std;
char *s;
char *p;
const char *help(){
  const char *h;
  h = "AVAILABLE OPTIONS: \n-mf: move a file\n-cf: copy a file\n-rmf: remove a file\n-ssf: show size of file\n-q: exit\n\nPROJECT DESCRIPTION: \nWorking with the file system\n\nEXAMPLES OF STARTING: \n./client \n-cf from_file to_file";
  return h;
}


char *show_all_files(const char *path){
  DIR *dir = opendir(path);
  dirent *entry;
  s = (char*)malloc(sizeof(char)*2000);
  /*
  if (dir == NULL){
    return;
  }
  */
  while ((entry = readdir(dir)) != NULL){
    cout << entry->d_name << endl;
    char *q = entry->d_name;
    strcat(s,q);
    strcat(s, "\n");
  }
  closedir(dir);
  return s;
  free(s);
}

int showsize(string filesize){
	int allsize = 0;
	
  struct stat fileinfo;
  if(stat(filesize.c_str(), &fileinfo) != 0){
    return -1;
  }
  if(S_ISDIR(fileinfo.st_mode)){
    DIR *dir = opendir(filesize.c_str());
    dirent *entry;
    while((entry = readdir(dir)) != nullptr){
      if((strcmp(entry->d_name, ".") != 0) && (strcmp(entry->d_name, "..") != 0)){
        string next = filesize + "/" + entry->d_name;
        allsize += showsize(next);
      }
    }
    //char str[30] = "Size of file = ";
    //allsize = strcat(str, allsize);
    closedir(dir);
    return allsize;
  }
  else{
    return fileinfo.st_size;
  }
}

streampos size(const char *s_path){
  ifstream size(s_path);
  size.seekg(0, ios::end);
  int file_size = size.tellg();
  cout<<"Size of the file is"<<" "<< file_size<<" "<<"bytes" << endl;
  cout << "help" << endl;
  return 0;
}

int copyFile(const char *copyfromfile, const char *copytofile){
  ifstream cff(copyfromfile);
  ofstream ctf(copytofile);
 
  char sym;
  // цикл посимвольного чтения
  while (cff)
  {
    cff.get(sym);
    if (cff) {
      ctf.put(sym);
    }
  }
  cff.close();
  ctf.close();
  return 0;
}

char *showp()
{
  DIR *dir = opendir("/proc/");
  dirent *entry;
  p = (char*)malloc(sizeof(char)*15000);
  while ((entry = readdir(dir)) != NULL){
      cout << entry->d_name << endl;
      char *q = entry->d_name;
      strcat(p,q);
      strcat(p, "\n");
  }
  closedir(dir);
  return p;
  free(p);
}
