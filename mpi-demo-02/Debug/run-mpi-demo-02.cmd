REM change codepage for cmd window
chcp 1251

REM run program in -np number on processes
mpiexec -np 2 mpi-demo-02.exe 10000000

REM pause for the user to read the output
pause