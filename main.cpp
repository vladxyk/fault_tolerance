#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <dirent.h>
#include <iomanip>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <experimental/filesystem>
#include "lib.hpp"
#include "lib.cpp"

using namespace std;


const char *start(char* client_message){
    //while(1){   
        const char* message;
        char **options = (char**) malloc(6*sizeof(char*));
        int i;
        for(i=0;i<6;i++){
            options[i] = (char*) malloc(100*sizeof(char));
        }

        int argn=1;
        char sep [10] = " ";
        char *buff;
        buff = strtok (client_message,sep);

        while (buff != NULL)
        {
            cout << buff << "\n";
            options[argn] = buff;
            buff = strtok(NULL, sep);
               
            argn++;
        }
        char **argv = (char**) malloc(argn*sizeof(char*));

        for(i=0;i<argn;i++){
            argv[i] = (char*) malloc(100*sizeof(char));
        }
        for(i=0;i<argn;i++){
            argv[i] = options[i];
        }
        
        if (strncmp(argv[1], "-h", 2) == 0){
            message = help();
            return message;
        } 
        else if(strncmp(argv[1], "--help", 3) == 0){
            message = help();
            return message;
        }
        else if(strncmp(argv[1],"-mf",3)==0) 
        {
            rename(argv[2], argv[3]);
            message = "File moved successfully";
            return message;
        }
        else if(strncmp(argv[1],"-rmf",4)==0) 
        {
            remove(argv[2]);
            message = "File deleted successfully";
            return message;
        }
        else if(strncmp(argv[1],"-cf",3)==0) 
        {
            copyFile(argv[2], argv[3]);
            message = "File copied successfully";
            return message;
        }
        else if(strncmp(argv[1],"-saf",4)==0) 
        {
            message = show_all_files(argv[2]);
            return message;
        }
        else if(strncmp(argv[1],"-sap",4)==0) 
        {
            //char *sizep = new char;
            message = showp();
            return message;
            //message = sizep;
        }
        else if(strncmp(argv[1],"-ssf",4)==0)
        {
            char *size = new char;
            *size = showsize(argv[2]) + '0';
            //char str[30] = "Size of file = ";
            message = size;
            return message;
        }
        else if(strncmp(argv[1], "-q", 2)==0){
            message = "-q";
            return message;
        }

    //}
    
}


