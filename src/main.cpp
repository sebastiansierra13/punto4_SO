#include "process.h"
#include "scheduler.h"
#include "memory.h"
#include "execution.h"
#include <queue>
#include <iostream>

int main() {
    // Inicializar el administrador de memoria con un total de 100 bloques de tamaño 4
    MemoryManager memoryManager(100, 4);

    // Crear una cola de procesos
    std::queue<Process> processQueue;

    // Crear algunos procesos con tiempos de ráfaga y requisitos de memoria
    Process p1(1, 5);  // Proceso 1 con ráfaga de 5 segundos
    Process p2(2, 3);  // Proceso 2 con ráfaga de 3 segundos
    Process p3(3, 7);  // Proceso 3 con ráfaga de 7 segundos

    // Asignar memoria a los procesos
    std::cout << "============================\n";
    std::cout << "Asignación de memoria para los procesos:\n";
    std::cout << "============================\n";

    // Intentar asignar memoria continua para el proceso 1
    if (!memoryManager.allocateMemoryContinuous(p1, 12)) {
        std::cerr << "Error: No se pudo asignar memoria continua al proceso " << p1.getPID() << "\n";
    }

    // Intentar asignar memoria no continua para el proceso 2
    if (!memoryManager.allocateMemoryNonContinuous(p2, 20)) {
        std::cerr << "Error: No se pudo asignar memoria no continua al proceso " << p2.getPID() << "\n";
    }

    // Intentar asignar memoria continua para el proceso 3
    if (!memoryManager.allocateMemoryContinuous(p3, 15)) {
        std::cerr << "Error: No se pudo asignar memoria continua al proceso " << p3.getPID() << "\n";
    }

    // Mostrar el estado inicial de la memoria física
    std::cout << "\nEstado actual de la memoria física (bloques):\n";
    memoryManager.printMemoryStatus();  // Llamar a la función para imprimir el estado de la memoria

    // Mostrar el mapeo lógico-físico de cada proceso
    std::cout << "\n============================\n";
    std::cout << "Mapeo lógico-físico de los procesos:\n";
    std::cout << "============================\n";
    memoryManager.printLogicalToPhysicalMapping(p1.getPID());  // Imprimir mapeo para proceso 1
    memoryManager.printLogicalToPhysicalMapping(p2.getPID());  // Imprimir mapeo para proceso 2
    memoryManager.printLogicalToPhysicalMapping(p3.getPID());  // Imprimir mapeo para proceso 3

    // Simular la ejecución de los procesos
    std::cout << "\n============================\n";
    std::cout << "Simulando la ejecución de los procesos...\n";
    std::cout << "============================\n";
    simulateProcessExecution(processQueue, memoryManager);  // Ejecutar la simulación de los procesos

    // Mostrar el estado final de la memoria física tras liberar todos los procesos
    std::cout << "\nEstado final de la memoria tras liberar todos los procesos:\n";
    memoryManager.printMemoryStatus();  // Imprimir el estado final de la memoria

    return 0;  // Finalizar el programa con éxito
}
