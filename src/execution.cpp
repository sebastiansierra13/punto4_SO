#include "execution.h"
#include <iostream>
#include <thread>
#include <chrono>

// Simulación de ejecución de procesos, incluyendo bloqueos y liberación de memoria
void simulateProcessExecution(std::queue<Process>& processQueue, MemoryManager& memoryManager) {
    // Mientras haya procesos en la cola
    while (!processQueue.empty()) {
        Process& currentProcess = processQueue.front();  // Obtener el proceso actual

        // Mostrar información del proceso en estado "Nuevo"
        if (currentProcess.getStateName() == "Nuevo") {
            currentProcess.changeState(READY);  // Cambiar el estado del proceso a LISTO
            std::cout << "\nProceso " << currentProcess.getPID() 
                      << " [NUEVO] -> [LISTO]\n";  // Indicar el cambio de estado
        }

        // Mostrar cuando el proceso empieza a ejecutarse
        if (currentProcess.getStateName() == "Listo") {
            currentProcess.changeState(RUNNING);  // Cambiar el estado a EJECUTANDO
            std::cout << "Proceso " << currentProcess.getPID() << " está [EJECUTANDO]\n";
        }

        // Simular la ejecución de la ráfaga con posibilidad de bloqueo
        int totalExecutionTime = 0;  // Contador de tiempo total de ejecución
        while (currentProcess.getRemainingTime() > 0) {  // Mientras haya tiempo restante
            std::this_thread::sleep_for(std::chrono::seconds(1));  // Simular 1 segundo de ráfaga
            currentProcess.decreaseBurstTime();  // Reducir el tiempo de ráfaga
            totalExecutionTime++;

            // Mostrar el tiempo restante de ejecución
            std::cout << "Proceso " << currentProcess.getPID() << ": "
                      << currentProcess.getRemainingTime() << " segundos restantes.\n";

            // Simulación de bloqueo aleatorio (por ejemplo, esperando por I/O)
            // Bloquear con una probabilidad si el tiempo restante es mayor a 2 segundos
            if (currentProcess.getRemainingTime() > 2 && rand() % 4 == 0) {
                currentProcess.changeState(BLOCKED);  // Cambiar el estado a BLOQUEADO
                std::cout << "Proceso " << currentProcess.getPID() << " está [BLOQUEADO] (esperando I/O)\n";
                std::this_thread::sleep_for(std::chrono::seconds(2));  // Simular espera de I/O
                currentProcess.changeState(READY);  // Cambiar de nuevo a LISTO
                std::cout << "Proceso " << currentProcess.getPID() << " está [LISTO] nuevamente después de "
                          << totalExecutionTime << " segundos de ejecución.\n";
            }
        }

        // Si el proceso termina su ráfaga, liberar memoria y cambiar a TERMINATED
        if (currentProcess.getRemainingTime() == 0) {
            currentProcess.changeState(TERMINATED);  // Cambiar el estado a TERMINADO
            std::cout << "Proceso " << currentProcess.getPID() << " ha [TERMINADO] después de " 
                      << totalExecutionTime << " segundos de ejecución.\n";

            // Liberar memoria ocupada por el proceso
            memoryManager.releaseMemory(currentProcess);
        }

        // Eliminar el proceso de la cola de procesos
        processQueue.pop();
    }
}
