#include <iostream>
#include <omp.h>

using namespace std;

int main()
{
    cout << "Regiones paralelas!" << endl;

    #pragma omp parallel
    {
        cout << "Trabajando en el thread: " << omp_get_thread_num() << endl;

        #pragma omp master
        {
            cout << "Numero de threads es: " << omp_get_num_threads() << endl;
        }
    }

    return 0;
}
