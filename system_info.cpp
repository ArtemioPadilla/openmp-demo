#include <iostream>
#include <thread>

#ifdef _OPENMP
    #include <omp.h>
#endif

int main()
{
    std::cout << "=== Informacion del Sistema para Paralelismo ===\n\n";

    // Hardware threads (C++11)
    std::cout << "Hardware threads (std::thread): "
              << std::thread::hardware_concurrency() << "\n";

#ifdef _OPENMP
    std::cout << "\n--- OpenMP ---\n";
    std::cout << "Version OpenMP: " << _OPENMP << "\n";
    std::cout << "Max threads (omp_get_max_threads): " << omp_get_max_threads() << "\n";
    std::cout << "Num processors (omp_get_num_procs): " << omp_get_num_procs() << "\n";

    std::cout << "\n--- Dentro de region paralela ---\n";
    #pragma omp parallel
    {
        #pragma omp single
        {
            std::cout << "Threads activos: " << omp_get_num_threads() << "\n";
        }
    }
#else
    std::cout << "\nOpenMP no disponible.\n";
#endif

    return 0;
}
