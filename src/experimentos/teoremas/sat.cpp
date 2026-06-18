#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include "avl.hpp"
#include "splay.hpp"

int main() {
    std::cout << "--- Teorema: Sequential Access Theorem (SAT) ---\n";

    size_t N = 1ULL << 25;
    std::vector<unsigned int> dataset(N);

    std::cout << "1. Cargando dataset_25.bin en memoria (134 MB)..." << std::endl;
    std::ifstream inFile("data/dataset_25.bin", std::ios::binary);
    if (!inFile) { std::cerr << "Falta dataset_25.bin\n"; return 1; }
    inFile.read(reinterpret_cast<char*>(dataset.data()), N * sizeof(unsigned int));

    std::cout << "2. Construyendo arbol AVL (Esto tomara un momento)..." << std::endl;
    AVL avl;
    auto t0_ins = std::chrono::high_resolution_clock::now();
    for (unsigned int val : dataset) {
        avl.insert(val);
    }
    auto t1_ins = std::chrono::high_resolution_clock::now();
    std::cout << "AVL construido en " << std::chrono::duration<double>(t1_ins - t0_ins).count() << " segundos.\n\n";


    std::cout << "3. Iniciando secuencias de busqueda creciente...\n";


    for (int i = 1; i <= 10; ++i) {
        size_t m = (N * i) / 100;

        unsigned int step = 4294967295U / m;

        auto t0_bus = std::chrono::high_resolution_clock::now();
        unsigned int objetivo = 0;

        for (size_t j = 0; j < m; ++j) {
            avl.search(objetivo);
            objetivo += step; // Aseguramos orden estrictamente creciente
        }

        auto t1_bus = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> t_bus_avl = t1_bus - t0_bus;

        std::cout << "m = " << m << " (" << i << "%) | Tiempo AVL: " << t_bus_avl.count() << " ms\n";
    }

    std::cout << "\n4. Construyendo splay tree (Esto tomara un momento)..." << std::endl;
    Splay splay;
    t0_ins = std::chrono::high_resolution_clock::now();
    for (unsigned int val : dataset) {
        splay.insert(val);
    }
    t1_ins = std::chrono::high_resolution_clock::now();
    std::cout << "Splay tree construido en " << std::chrono::duration<double>(t1_ins - t0_ins).count() << " segundos.\n\n";

    std::cout << "5. Iniciando secuencias de busqueda creciente en splay tree...\n";

    for (int i = 1; i <= 10; ++i) {
        size_t m = (N * i) / 100;

        unsigned int step = 4294967295U / m;

        auto t0_bus = std::chrono::high_resolution_clock::now();
        unsigned int objetivo = 0;

        for (size_t j = 0; j < m; ++j) {
            splay.search(objetivo);
            objetivo += step; // Aseguramos orden estrictamente creciente
        }

        auto t1_bus = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> t_bus_splay = t1_bus - t0_bus;

        std::cout << "m = " << m << " (" << i << "%) | Tiempo Splay: " << t_bus_splay.count() << " ms\n";
    }

    return 0;
}