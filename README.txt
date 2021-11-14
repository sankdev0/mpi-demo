Учебный проект для университета.
***
Серия кратких демо по теме параллелного программирование с использованием стандарта MPI (Message Passing Interface).
Этот стандарт был разработан и используется для построения систем для высокопроизводительных вычислений HPC (high-performance computing).
Язык C/Cpp
Среда Visual Studio
***
Программа представляет собой приложение, которое можно выполнить с помощью утилиты mpiexec (входит в состав MS-MPI).
Для выполнения можно использовать команды:

REM change codepage for cmd window
chcp 1251

REM run program in -np number on processes
mpiexec -np 20 mpi-demo-01.exe

REM pause for the user to read the output
pause

Эти команды можно разместить в скрипт CMD для запуска приложения, где
-np <число> -- количество процессов, которые создасть MS-MPI;
mpi-demo-01.exe -- пример названия исполняемого файла программы.