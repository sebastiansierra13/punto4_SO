#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"
#include <queue>

// Declaración de funciones para la planificación de procesos
void fcfsScheduling(std::queue<Process>& processQueue);  // Función para la planificación FCFS
void printQueueState(const std::queue<Process>& processQueue);  // Función para imprimir el estado de la cola

#endif
