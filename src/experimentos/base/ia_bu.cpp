#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>
#include "avl.hpp"
#include "splay.hpp"

const int C_VAL = 5;

int main() {
    std::cout << "--- ia_bu: Insercion Aleatoria, Busqueda Uniforme ---\n";
    std::vector<int> tamanos_N = {1024, 2048, 4096, 8192, 16384};
    std::mt19937_64 gen(42);

    for (int N : tamanos_N) {
        AVL avl;

        int M = 10 * C_VAL * N;
        std::vector<unsigned int> dataset(N);

        std::string filename = "data/dataset_" + std::to_string((int)log2(N)) + ".bin";
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile) { std::cerr << "Falta " << filename << "\n"; return 1; }
        inFile.read(reinterpret_cast<char*>(dataset.data()), N * sizeof(unsigned int));

        auto t0_ins = std::chrono::high_resolution_clock::now();
        for (unsigned int val : dataset) avl.insert(val);
        auto t1_ins = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> t_ins_avl = t1_ins - t0_ins;

        std::uniform_int_distribution<int> dist_unif(0, N - 1);
        auto t0_bus = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < M; ++i) {
            avl.search(dataset[dist_unif(gen)]);
        }
        auto t1_bus = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> t_bus_avl = t1_bus - t0_bus;

        std::cout << "N=" << N << " | AVL Ins: " << t_ins_avl.count() << "ms | AVL Busq: " << t_bus_avl.count() << "ms\n";
    }

    for (int N : tamanos_N) {
        Splay splay;

        int M = 10 * C_VAL * N;
        std::vector<unsigned int> dataset(N);

        std::string filename = "data/dataset_" + std::to_string((int)log2(N)) + ".bin";
        std::ifstream inFile(filename, std::ios::binary);
        if (!inFile) { std::cerr << "Falta " << filename << "\n"; return 1; }
        inFile.read(reinterpret_cast<char*>(dataset.data()), N * sizeof(unsigned int));

        auto t0_ins = std::chrono::high_resolution_clock::now();
        for (unsigned int val : dataset) splay.insert(val);
        auto t1_ins = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> t_ins_splay = t1_ins - t0_ins;

        std::uniform_int_distribution<int> dist_unif(0, N - 1);
        auto t0_bus = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < M; ++i) {
            splay.search(dataset[dist_unif(gen)]);
        }
        auto t1_bus = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> t_bus_splay = t1_bus - t0_bus;

        std::cout << "N=" << N << " | Splay Ins: " << t_ins_splay.count() << "ms | Splay Busq: " << t_bus_splay.count() << "ms\n";
    }

    return 0;
}