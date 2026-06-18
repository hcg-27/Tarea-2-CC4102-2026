#include <iostream>
#include <fstream>
#include <vector>
#include <random>
#include <string>
#include <filesystem>

void generar_y_guardar(int exponente, const std::string& filename) {
    size_t N = 1ULL << exponente;
    std::cout << "Generando N = 2^" << exponente << " (" << N << " elementos)..." << std::endl;

    std::random_device rd;
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<unsigned int> dist(0, 4294967295U);

    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error al crear " << filename << std::endl;
        return;
    }

    const size_t chunk_size = 1000000;
    std::vector<unsigned int> buffer;
    buffer.reserve(chunk_size);

    for (size_t i = 0; i < N; ++i) {
        buffer.push_back(dist(gen));
        if (buffer.size() == chunk_size) {
            outFile.write(reinterpret_cast<const char*>(buffer.data()), buffer.size() * sizeof(unsigned int));
            buffer.clear();
        }
    }

    if (!buffer.empty()) {
        outFile.write(reinterpret_cast<const char*>(buffer.data()), buffer.size() * sizeof(unsigned int));
    }
    outFile.close();
}

int main() {
    std::cout << "=== Generando Datasets ===\n";

    std::filesystem::create_directory("data");

    for (int i = 10; i <= 14; ++i) {
        generar_y_guardar(i, "data/dataset_" + std::to_string(i) + ".bin");
    }
    generar_y_guardar(25, "data/dataset_25.bin");
    std::cout << "Listo.\n\n";
    return 0;
}