#include "process.h"
#include <iostream>
#include <thread>
#include <chrono>

// Constructor de la clase Process
// Inicializa el ID y el tiempo de ráfaga, estableciendo el estado inicial como NEW
Process::Process(int id, int burst) : pid(id), burst_time(burst), remaining_time(burst) {
    state = NEW;  // El proceso inicia en el estado NEW
}

// Método para cambiar el estado del proceso
// Imprime el cambio de estado y actualiza el estado del proceso
void Process::changeState(ProcessState newState) {
    std::cout << "Proceso " << pid << " cambia de estado de " << getStateName() << " a ";
    state = newState;
    std::cout << getStateName() << ".\n";
}

// Obtener el estado actual del proceso en formato string
std::string Process::getStateName() const {
    switch (state) {
        case NEW: return "Nuevo";
        case READY: return "Listo";
        case RUNNING: return "Ejecutando";
        case BLOCKED: return "Bloqueado";
        case TERMINATED: return "Terminado";
        case SUSPENDED: return "Suspendido";
        case SUSPENDED_BLOCKED: return "Suspendido Bloqueado";
        default: return "Desconocido"; // Si el estado no es reconocido
    }
}

// Obtener el ID del proceso
int Process::getPID() const {
    return pid;
}

// Obtener el tiempo de ráfaga total del proceso
int Process::getBurstTime() const {
    return burst_time;
}

// Obtener el tiempo restante de ráfaga
int Process::getRemainingTime() const {
    return remaining_time;
}

// Método para ejecutar el proceso, simulando el uso de la CPU
void Process::execute() {
    if (state == READY) { // Solo se ejecuta si el proceso está listo
        changeState(RUNNING);  // Cambia el estado a RUNNING

        std::cout << "Proceso " << pid << " está en ejecución.\n";

        // Simular el uso de la CPU
        while (remaining_time > 0) {
            std::this_thread::sleep_for(std::chrono::seconds(1));  // Simula 1 segundo de ejecución
            remaining_time--; // Disminuye el tiempo restante
            std::cout << "Proceso " << pid << ": " << remaining_time << " segundos restantes.\n";
        }

        changeState(TERMINATED);  // Al terminar, cambiamos el estado a TERMINATED
    } else {
        std::cout << "Advertencia: El proceso " << pid << " no está listo para ejecutar. Estado actual: " << getStateName() << ".\n";
    }
}

// Verificar si el proceso ha terminado
bool Process::isTerminated() const {
    return state == TERMINATED; // Retorna verdadero si el estado es TERMINATED
}

// Método para reducir el tiempo de ráfaga del proceso
void Process::decreaseBurstTime() {
    if (remaining_time > 0) {
        remaining_time--; // Disminuye el tiempo restante
        std::cout << "Proceso " << pid << ": el tiempo de ráfaga se ha reducido. Tiempo restante: " << remaining_time << " segundos.\n";
    } else {
        std::cout << "Proceso " << pid << " ya no tiene tiempo de ráfaga restante.\n"; // Mensaje si no hay tiempo restante
    }
}
