// Программа предназначена для запуска через утилиту mpiexe.exe.
// Примерная строка запуска в CMD: mpiexec -np 5 mpi-demo-01.exe, где
// -np <число> -- количетво создваемых процессов
// mpi-demo-01.exe -- имя исполняемого файла программы.

#include <Windows.h>
#include <stdio.h>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv)
{
    int process_team_size, process_rank, i;


    /*инициализация библиотеки  */
    MPI_Init(&argc, &argv);

    /*определение количества задач в приложении  */
    MPI_Comm_size(MPI_COMM_WORLD, &process_team_size);
    /* определение собственного номера от 0 до (size-1) */
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);

    double start = MPI_Wtime();

    /*каждая задача выводит пользователю свой номер и размер группы, к которой
     * прикреплен коммуникатор MPI_COMM_WORLD, т.е. число процессов в приложении*/
    printf("Hello, world!I am %d process from %i processes!\n", 
        process_rank, process_team_size);

    double end = MPI_Wtime();
    /*Все задачи завершают выполнение*/
    MPI_Finalize();

    // Выведем значение времени выполнения только для последнего процесса.
    printf("Выполнение программы заняло %f секунд\n", end - start);

    return 0;
}