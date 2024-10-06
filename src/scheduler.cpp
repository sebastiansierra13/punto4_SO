#include "scheduler.h"
#include <iostream>

// Imprimir el estado actual de los procesos en la cola
void printQueueState(const std::queue<Process>& processQueue) {
    std::queue<Process> tempQueue = processQueue;  // Crear una copia temporal de la cola para no modificar la original
    std::cout << "\nEstado actual de los procesos en la cola:\n";
    if (tempQueue.empty()) {
        std::cout << "La cola está vacía.\n";  // Mensaje si la cola no tiene procesos
    } else {
        // Iterar sobre la cola temporal e imprimir el estado de cada proceso
        while (!tempQueue.empty()) {
            Process p = tempQueue.front();  // Obtener el primer proceso de la cola
            std::cout << "Proceso " << p.getPID() << " está en estado: " << p.getStateName() << "\n";  // Mostrar PID y estado
            tempQueue.pop();  // Eliminar el proceso de la cola temporal
        }
    }
}

// Planificación de CPU usando FCFS (First-Come, First-Served)
void fcfsScheduling(std::queue<Process>& processQueue) {
    // Mientras haya procesos en la cola
    while (!processQueue.empty()) {
        Process& currentProcess = processQueue.front();  // Obtener el primer proceso de la cola

        // Cambiar el proceso al estado READY si está en NEW
        if (currentProcess.getStateName() == "Nuevo") {
            currentProcess.changeState(READY);  // Cambiar el estado a LISTO
            std::cout << "Proceso " << currentProcess.getPID() << " ha cambiado a [LISTO].\n";  // Informar del cambio de estado
        }

        // Ejecutar el proceso
        std::cout << "\nEjecutando proceso " << currentProcess.getPID() << "...\n";  // Mensaje de inicio de ejecución
        currentProcess.execute();  // Llamar al método de ejecución del proceso

        // Eliminar el proceso de la cola una vez que haya terminado
        if (currentProcess.isTerminated()) {
            std::cout << "Proceso " << currentProcess.getPID() << " ha terminado y se elimina de la cola.\n";  // Mensaje de finalización
            processQueue.pop();  // Eliminar el proceso de la cola
        }

        // Mostrar el estado actual de la cola de procesos
        printQueueState(processQueue);  // Llamar a la función para mostrar el estado de la cola
    }
}
