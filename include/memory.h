#ifndef MEMORY_H
#define MEMORY_H

#include "process.h"
#include <vector>
#include <map>
#include <utility> // Para std::pair

// Clase MemoryManager: Encargada de gestionar la asignación y liberación de memoria
class MemoryManager {
private:
    std::vector<int> memory;  // Simulación de la memoria física como un vector de enteros
    std::map<int, std::vector<int>> memory_map;  // Mapa que asocia PID con los bloques asignados
    std::map<int, std::vector<std::pair<int, int>>> logical_to_physical;  // Mapeo lógico-físico
    int total_memory;  // Tamaño total de la memoria física
    int block_size;    // Tamaño de un bloque de memoria

public:
    // Constructor para inicializar el administrador de memoria
    MemoryManager(int total_size, int block_size);

    // Asignación continua de memoria física y su respectivo mapeo lógico
    bool allocateMemoryContinuous(Process& process, int memory_size);

    // Asignación no continua de memoria física y su respectivo mapeo lógico
    bool allocateMemoryNonContinuous(Process& process, int memory_size);

    // Liberar la memoria de un proceso
    void releaseMemory(Process& process);

    // Mostrar el estado de la memoria física
    void printMemoryStatus() const;

    // Mostrar el mapeo lógico-físico de un proceso (opcional)
    void printLogicalToPhysicalMapping(int pid) const;

    // Mostrar los resultados de la asignación de memoria
    void printAllocationResult(const Process& process, int memory_size, int start_block, int blocks_needed) const;
};

#endif
