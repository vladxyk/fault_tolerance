#ifndef lab5_h
#define lab5_h

const char *help();
char *show_all_files(const char *path);
char *showp();
int copyFile(const char *copyfromfile, const char *copytofile);
int showsize(std::string filesize);
const char *start(char* client_message);

#endif 