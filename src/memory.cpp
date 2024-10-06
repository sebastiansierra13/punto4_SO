#include "memory.h"
#include <iostream>

// Constructor para inicializar la memoria y su tamaño total
MemoryManager::MemoryManager(int total_size, int block_size) 
    : total_memory(total_size), block_size(block_size) {
    memory.resize(total_memory, -1);  // Inicializamos la memoria con -1 (indicando que los bloques están libres)
}

// Asignación continua de memoria a un proceso
bool MemoryManager::allocateMemoryContinuous(Process& process, int memory_size) {
    int blocks_needed = (memory_size + block_size - 1) / block_size;  // Calcular cuántos bloques son necesarios
    int free_block_count = 0;  // Contador de bloques libres consecutivos
    int start_block = -1;      // Índice del inicio del bloque libre

    // Buscar bloques contiguos libres
    for (int i = 0; i < memory.size(); i++) {
        if (memory[i] == -1) {
            if (free_block_count == 0) {
                start_block = i;  // Posible inicio de un bloque contiguo
            }
            free_block_count++;  // Incrementar contador de bloques libres
        } else {
            free_block_count = 0;  // Reiniciar si encontramos un bloque ocupado
        }

        // Si encontramos suficientes bloques libres
        if (free_block_count == blocks_needed) {
            // Asignar los bloques al proceso
            for (int j = start_block; j < start_block + blocks_needed; j++) {
                memory[j] = process.getPID();  // Asignar el bloque a este proceso
            }
            std::cout << "Memoria continua de " << memory_size << " bytes asignada al proceso " << process.getPID() 
                      << " desde el bloque " << start_block << " hasta " 
                      << start_block + blocks_needed - 1 << "\n";
            
            // Registrar el mapeo lógico-físico
            logical_to_physical[process.getPID()].clear(); // Limpiar el mapeo anterior
            for (int j = start_block; j < start_block + blocks_needed; j++) {
                logical_to_physical[process.getPID()].emplace_back(j, j); // Almacena la relación lógica-física
            }

            printMemoryStatus();  // Imprimir el estado actual de la memoria
            printLogicalToPhysicalMapping(process.getPID()); // Imprimir el mapeo lógico-físico
            return true;  // Asignación exitosa
        }
    }

    std::cerr << "Error: No se pudo asignar memoria continua de " << memory_size << " bytes al proceso " 
              << process.getPID() << " - bloques libres insuficientes.\n";
    return false;  // No se encontró suficiente memoria continua
}

// Método separado para imprimir resultados de asignación
void MemoryManager::printAllocationResult(const Process& process, int memory_size, int start_block, int blocks_needed) const {
    std::cout << "Memoria continua de " << memory_size << " bytes asignada al proceso " << process.getPID() 
              << " desde el bloque " << start_block << " hasta " 
              << start_block + blocks_needed - 1 << "\n";
    printMemoryStatus();  // Imprimir el estado actual de la memoria
    printLogicalToPhysicalMapping(process.getPID()); // Imprimir el mapeo lógico-físico
}

// Asignación de memoria no continua a un proceso
bool MemoryManager::allocateMemoryNonContinuous(Process& process, int memory_size) {
    int blocks_needed = (memory_size + block_size - 1) / block_size;  // Calcular bloques necesarios
    std::vector<int> assigned_blocks;  // Almacenar bloques asignados

    // Buscar bloques libres no contiguos
    for (int i = 0; i < memory.size() && blocks_needed > 0; i++) {
        if (memory[i] == -1) {
            memory[i] = process.getPID();  // Asignar el bloque al proceso
            assigned_blocks.push_back(i);  // Guardar el bloque asignado
            blocks_needed--;  // Decrementar el contador de bloques necesarios
        }
    }

    // Si no hemos podido asignar todos los bloques requeridos
    if (blocks_needed > 0) {
        std::cerr << "Error: No se pudo asignar suficiente memoria no continua de " << memory_size << " bytes al proceso " 
                  << process.getPID() << " - bloques libres insuficientes.\n";
        return false;  // No se pudo realizar la asignación
    }

    // Mapear los bloques asignados al proceso
    memory_map[process.getPID()] = assigned_blocks;  
    std::cout << "Memoria no continua de " << memory_size << " bytes asignada al proceso " << process.getPID() << ": ";
    for (int block : assigned_blocks) {
        std::cout << block << " ";  // Imprimir bloques asignados
    }
    std::cout << "\n";
    printMemoryStatus();  // Imprimir el estado actual de la memoria
    printLogicalToPhysicalMapping(process.getPID()); // Imprimir el mapeo lógico-físico
    return true;  // Asignación exitosa
}

// Liberar memoria asignada a un proceso
void MemoryManager::releaseMemory(Process& process) {
    int pid = process.getPID();  // Obtener el ID del proceso
    std::cout << "Liberando memoria para el proceso " << pid << "...\n";

    // Liberar memoria en asignación continua
    for (int i = 0; i < memory.size(); i++) {
        if (memory[i] == pid) {
            memory[i] = -1;  // Liberar el bloque
            std::cout << "Bloque " << i << " liberado.\n";
        }
    }

    // Liberar memoria en asignación no continua
    if (memory_map.find(pid) != memory_map.end()) {
        for (int block : memory_map[pid]) {
            std::cout << "Bloque " << block << " liberado.\n";  // Informar de la liberación de bloques
            memory[block] = -1;  // Liberar también los bloques en la memoria
        }
        memory_map.erase(pid);  // Eliminar el mapeo del proceso
    }

    std::cout << "Memoria liberada para el proceso " << pid << "\n";
    printMemoryStatus();  // Imprimir el estado actual de la memoria
}

// Mostrar el estado actual de la memoria física
void MemoryManager::printMemoryStatus() const {
    std::cout << "\nEstado actual de la memoria física (bloques):\n";
    for (int i = 0; i < memory.size(); i++) {
        if (memory[i] == -1) {
            std::cout << "[ Libre ] ";  // Indicar bloques libres
        } else {
            std::cout << "[ Proceso " << memory[i] << " ] ";  // Indicar bloques ocupados por procesos
        }
        if ((i + 1) % 10 == 0) std::cout << "\n";  // Dividir en filas de 10 bloques para mejorar la legibilidad
    }
    std::cout << "\n";  // Salto de línea
}

// Mostrar el mapeo lógico-físico de un proceso
void MemoryManager::printLogicalToPhysicalMapping(int pid) const {
    auto it = logical_to_physical.find(pid);  // Buscar el mapeo para el PID especificado
    if (it != logical_to_physical.end()) {
        std::cout << "Mapeo lógico-físico para el proceso " << pid << ": ";
        for (const auto& pair : it->second) {
            std::cout << "[" << pair.first << " -> " << pair.second << "] ";  // Imprimir la relación lógica-física
        }
        std::cout << "\n";
    } else {
        std::cout << "No se encontró mapeo lógico-físico para el proceso " << pid << "\n";
    }
}
