/*
 * ѕример 1
 * ќпределение количества процессов в приложении и пор€дкового номера процесса в группе
 */

#include <mpi.h>
#include <stdio.h>

int mpi_hello_world(int argc, char** argv)
{
    int size, rank, i;

    /*инициализаци€ библиотеки  */
    MPI_Init(&argc, &argv);

    /*определение количества задач в приложении  */
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* определение собственного номера от 0 до (size-1) */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /*кажда€ задача выводит пользователю свой номер и размер группы,
     * к которой прикреплен коммуникатор MPI_COMM_WORLD,
     * т.е. число процессов в приложении*/
    printf("Hello, world!I am %d process from %i processes!\n", rank, size);

    /*¬се задачи завершают выполнение*/
    MPI_Finalize();
    return 0;
}