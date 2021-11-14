REM change codepage for cmd window
chcp 1251

REM run program in -np number on processes
mpiexec -np 20 mpi-demo-01.exe

REM pause for the user to read the output
pause