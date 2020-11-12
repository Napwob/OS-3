#include <cmath>
#include <iostream>
#include <sys/time.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <dirent.h>
#include <fcntl.h> 
#include <pwd.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>   
#include <unistd.h>
#include <malloc.h>
#include <sys/wait.h>
#include <unistd.h>
#include <csignal>
#include <signal.h>
using namespace std;



void spravka()
{
//cout<<"Авторы: Русманов Владислав ИВ-822, Крюков Илья ИВ-822, Сысоева Анастасия ИВ-822"<<endl;
cout<<"Авторы: Русманов Владислав ИВ-822, Крюков Илья ИВ-822, Сысоева Анастасия ИВ-822"<<endl;    
cout<<"Краткое описание проекта:"<<endl;
cout<<"Данная программа позволяет выполнять простые действия по работе с процессами Linux"<<endl;
cout<<"    Чтобы получить функционал по работе с файловой системой, нужно запустить программу с ключом -l"<<endl;
cout<<"    Чтобы запустить любую операцию сначала необходимо указать ключ данной операции, а затем режим фона "<<endl;
cout<<"    -d Запускает операцию в фоновом режиме" <<endl;
cout<<"    -n Запускает операцию в не фоновом режиме" <<endl;
cout<<"    -s Порождает новый процесс" <<endl;
cout<<"    -t Режим получения и обработки сигналов"<<endl;
cout<<"Все доступные аргументы:"<<endl;
cout<<"    -l"<<endl;
cout<<"    -d"<<endl;
cout<<"    -n"<<endl;
cout<<"    -s"<<endl;
cout<<"    -t"<<endl;
cout<<"Примеры запуска:"<<endl;
cout<<"    ./lab3 —l -h"<<endl;
cout<<"    ./lab3 -s -n proc"<<endl;
cout<<"    ./lab3 -s -d proc"<<endl;
cout<<"    ./lab3 -t"<<endl;
}

int slt(char *arv1, char *arv2, char *arv3) {
    const char *path = "lab2";
    int status;
    pid_t pid;
    pid = fork();

    if (pid == 0) {
        execl(path, path, arv1,arv2,arv3, NULL);
        _exit (EXIT_FAILURE);
    } else if (pid < 0)
        status = -1;
    else if (waitpid (pid, &status, 0) != pid)
        status = -1;
    return status;
}

int sp(char *d ,char *path) {
    int status;
    pid_t pid;
    pid = fork();

    if (pid == 0) {
    	if(strcmp(d,"-d")==0) daemon (1, 0);
        execl(path, path, NULL);
        while (1) {
            if (waitpid(pid, &status, 0) == pid)
                _exit (EXIT_FAILURE);
        }
    } else if (pid < 0)
        status = -1;
    else if (waitpid(pid, &status, 0) != pid)
        status = -1;

    return status;
}

void signalHandler( int signum ) {
   cout << "Interrupt signal (" << signum << ") received.\n";  
   exit(signum);
}

void test()
{
	while(true)
	{
		signal(SIGINT, signalHandler); 	
        signal(SIGABRT, signalHandler);
      //  signal(SIGBREAK, signalHandler);
        signal(SIGFPE, signalHandler);
        signal(SIGILL, signalHandler);
        signal(SIGSEGV, signalHandler);
        signal(SIGTERM, signalHandler);
	}
}

int main(int argc, char* argv[]) {
        
	if (argc==1) return 0;
	
	if (strcmp(argv[1],"-l")==0) slt(argv[2], argv[3], argv[4]);
    
    if (strcmp(argv[1],"-h")==0) spravka();
    
    if (strcmp(argv[1],"--help")==0) spravka();
    
    if ((strcmp(argv[1],"-s")==0) && ((strcmp(argv[2],"-d")==0) || (strcmp(argv[2],"-n")==0))) sp(argv[2], argv[3]);//-d для демонофикации -nd для без демонофикации
    
	if (strcmp(argv[1],"-t")==0) test();	
    
	
    return 0;
}
