#include <stdio.h>
#include <Windows.h>
#include "mpi-header.h"

using namespace std;

int main(int argc, char** argv)
{
    SetConsoleCP(1251); // кодовая страницы для потока ввода
    SetConsoleOutputCP(1251); // кодовая страница для потока вывода

    int ret = 0;

    // 1. Демо hello world с использованием MPI
    ret = mpi_hello_world(argc, argv);
    
}