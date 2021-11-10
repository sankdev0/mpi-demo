/*
 * Пример 1
 * Определение количества процессов в приложении и порядкового номера процесса в группе
 */

#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv)
{
    int size, rank, i;

    /*инициализация библиотеки  */
    MPI_Init(&argc, &argv);

    /*определение количества задач в приложении  */
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    /* определение собственного номера от 0 до (size-1) */
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    /* задача с номером 0 сообщает пользователю размер группы,
     * к которой прикреплен коммуникатор MPI_COMM_WORLD,
     * т.е. число процессов в приложении!!
     */
    if (rank == 0)
        printf("Total processes count = %d\n", size);

    /*каждая задача выводит пользователю свой номер */
    printf("Hello! My rank in MPI_COMM_WORLD = %d\n", rank);

    /*Все задачи завершают выполнение*/
    MPI_Finalize();
    return 0;
}