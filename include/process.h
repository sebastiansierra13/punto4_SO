#ifndef PROCESS_H
#define PROCESS_H

#include <string>

// Definición de los posibles estados de un proceso
enum ProcessState {
    NEW,           // El proceso está recién creado
    READY,         // El proceso está listo para ser ejecutado
    RUNNING,       // El proceso se está ejecutando
    BLOCKED,       // El proceso está bloqueado, esperando algún recurso
    TERMINATED,    // El proceso ha terminado su ejecución
    SUSPENDED,     // El proceso está suspendido (no está en memoria)
    SUSPENDED_BLOCKED // El proceso está suspendido y también bloqueado
};

// Declaración de la clase Process
class Process {
private:
    int pid;                     // Identificador único del proceso
    ProcessState state;          // Estado actual del proceso
    int burst_time;              // Tiempo total de ráfaga que necesita el proceso
    int remaining_time;          // Tiempo restante de ráfaga que le queda al proceso

public:
    // Constructor: Inicializa el proceso con un ID y un tiempo de ráfaga
    Process(int id, int burst);

    // Cambia el estado del proceso a un nuevo estado
    void changeState(ProcessState newState);

    // Obtiene el nombre del estado actual del proceso en formato string
    std::string getStateName() const;

    // Obtiene el ID del proceso
    int getPID() const;

    // Obtiene el tiempo de ráfaga total del proceso
    int getBurstTime() const;

    // Obtiene el tiempo restante de ráfaga del proceso
    int getRemainingTime() const;

    // Ejecuta el proceso, simulando su uso de la CPU
    void execute();

    // Verifica si el proceso ha terminado
    bool isTerminated() const;

    // Método para reducir el tiempo de ráfaga del proceso
    void decreaseBurstTime();
};

#endif
