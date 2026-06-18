#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include "avl.hpp"
#include "splay.hpp"

const int C_VAL = 1;

int main() {
    std::cout << "--- Teorema: Working Set Theorem (WST) ---\n";

    size_t N = 1ULL << 25;
    std::vector<unsigned int> dataset(N);

    std::cout << "1. Cargando dataset_25.bin en memoria..." << std::endl;
    std::ifstream inFile("data/dataset_25.bin", std::ios::binary);
    if (!inFile) { std::cerr << "Falta dataset_25.bin\n"; return 1; }
    inFile.read(reinterpret_cast<char*>(dataset.data()), N * sizeof(unsigned int));

    std::cout << "2. Construyendo arbol AVL..." << std::endl;
    AVL avl;
    for (unsigned int val : dataset) {
        avl.insert(val);
    }
    std::cout << "AVL construido. Preparando M busquedas...\n\n";

    size_t M = 10ULL * C_VAL * N;
    std::vector<int> valores_W = {10, 100, 1000, 10000, 100000, 1000000};

    std::mt19937_64 gen(42);

    for (int W : valores_W) {

        std::vector<unsigned int> working_set(dataset.begin(), dataset.begin() + W);

        std::uniform_int_distribution<int> dist_W(0, W - 1);

        auto t0_bus = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < M; ++i) {
            unsigned int objetivo = working_set[dist_W(gen)];
            avl.search(objetivo);
        }

        auto t1_bus = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> t_bus_avl = t1_bus - t0_bus;

        std::cout << "W = " << W << " | Busquedas (M) = " << M << " | Tiempo AVL: " << t_bus_avl.count() << " ms\n";
    }

    std::cout << "\n3. Construyendo splay tree..." << std::endl;
    Splay splay;
    for (unsigned int val : dataset) {
        splay.insert(val);
    }
    std::cout << "Splay tree construido. Preparando M busquedas...\n\n";
    for (int W : valores_W) {

        std::vector<unsigned int> working_set(dataset.begin(), dataset.begin() + W);

        std::uniform_int_distribution<int> dist_W(0, W - 1);

        auto t0_bus = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < M; ++i) {
            unsigned int objetivo = working_set[dist_W(gen)];
            splay.search(objetivo);
        }

        auto t1_bus = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> t_bus_splay = t1_bus - t0_bus;

        std::cout << "W = " << W << " | Busquedas (M) = " << M << " | Tiempo Splay: " << t_bus_splay.count() << " ms\n";
    }

    std::cout << "\n";

    return 0;
}