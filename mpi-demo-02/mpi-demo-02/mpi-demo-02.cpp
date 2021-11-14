#include"mpi.h"
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

using namespace std;

void Shift(double* mass, int N, int size, int rank)
{

    MPI_Status status;
    MPI_Request request, request1;

    int next, prev;
    if (rank == size - 1)
        next = 0;
    else
        next = rank + 1;

    if (rank == 0)
        prev = size - 1;
    else
        prev = rank - 1;

    MPI_Isend(mass, N, MPI_DOUBLE, next, 0, MPI_COMM_WORLD, &request1);
    MPI_Irecv(mass, N, MPI_DOUBLE, prev, 0, MPI_COMM_WORLD, &request);
    MPI_Wait(&request, &status);
}

void Shift2(double* mass, double* in_mass, int N, int size, int rank)
{
    MPI_Status status[2];
    MPI_Request request[2], req, req1;
    int next, prev;
    if (rank == size - 1)
        next = 0;
    else
        next = rank + 1;
    if (rank == 0)
        prev = size - 1;
    else
        prev = rank - 1;

    MPI_Isend(mass, N, MPI_DOUBLE, next, 0, MPI_COMM_WORLD, &req);
    MPI_Isend(in_mass, N, MPI_DOUBLE, prev, 0, MPI_COMM_WORLD, &req1);
    MPI_Irecv(in_mass, N, MPI_DOUBLE, next, 0, MPI_COMM_WORLD, &request[0]);
    MPI_Irecv(mass, N, MPI_DOUBLE, prev, 0, MPI_COMM_WORLD, &request[1]);
    MPI_Waitall(2, request, status);

}

void Round(double* mass, int N, int size, int rank)
{
    MPI_Status status;
    MPI_Request request;

    if (rank == 0)
    {
        MPI_Irecv(mass, N, MPI_DOUBLE, size - 1, 0, MPI_COMM_WORLD, &request);
        MPI_Send(mass, N, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
        MPI_Wait(&request, &status);
    }
    if (rank != 0 && rank != size - 1)
    {
        MPI_Recv(mass, N, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, &status);
        MPI_Send(mass, N, MPI_DOUBLE, rank + 1, 0, MPI_COMM_WORLD);
    }
    if (rank == size - 1)
    {
        MPI_Recv(mass, N, MPI_DOUBLE, rank - 1, 0, MPI_COMM_WORLD, &status);
        MPI_Send(mass, N, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
}



int main(int argc, char** argv)
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int size, rank, N, i;
    double dt, t1, t2, maxtime, time;
    double* mass, * in_mass;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    time = 0;

    if (argc != 2)
    {
        printf("Must be 1 argument! argc=%d\n", argc);
        for (i = 0; i < argc; i++)
            printf("argv[%d]=%s\n", i, argv[i]);
        MPI_Finalize();
        exit(0);
    }
    N = atoi(argv[1]);
    if (rank == 0)
        printf("\nНачальные параметры\n\nЧисло процессоров:%d\nДлина вектора:%d\n\nРезультаты\n", size, N);


    mass = (double*)malloc(N * sizeof(double));
    in_mass = (double*)malloc(N * sizeof(double));


    srand(1);
    for (i = 0; i < N; i++)
    {
        mass[i] = (double)rand();
        in_mass[i] = (double)rand();
    }


    MPI_Barrier(MPI_COMM_WORLD);
    for (i = 0; i < 10; i++)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        t1 = MPI_Wtime();
        Round(mass, N, size, rank);
        t2 = MPI_Wtime() - t1;
        MPI_Reduce(&t2, &maxtime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
        if ((i == 0) || (time > maxtime))
            time = maxtime;
    }
    if (rank == 0)
        printf("Последовательная передача с помощью блокирующих функций (MPI_Send):%lf S\n", time);



    MPI_Barrier(MPI_COMM_WORLD);
    time = 0;
    for (i = 0; i < 10; i++)
    {
        MPI_Barrier(MPI_COMM_WORLD);
        t1 = MPI_Wtime();
        Shift(mass, N, size, rank);
        t2 = MPI_Wtime() - t1;
        MPI_Reduce(&t2, &maxtime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
        if ((i == 0) || (time > maxtime))
            time = maxtime;
    }
    if (rank == 0)
        printf("Прием и передача от двух соседних процессоров (MPI_Isend):%lf S\n", time);



    MPI_Barrier(MPI_COMM_WORLD);
    time = 0;
    for (i = 0; i < 10; i++)
    {
        MPI_Barrier(MPI_COMM_WORLD);

        t1 = MPI_Wtime();
        Shift2(mass, in_mass, N, size, rank);
        t2 = MPI_Wtime() - t1;

        MPI_Reduce(&t2, &maxtime, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);

        if ((i == 0) || (time > maxtime))
            time = maxtime;
    }
    if (rank == 0)
        printf("Одновременная передача данных последующим (MPI_Isend):%lf S\n", time);



    MPI_Barrier(MPI_COMM_WORLD);
    free(mass);
    free(in_mass);
    MPI_Finalize();
    return 0;
}
