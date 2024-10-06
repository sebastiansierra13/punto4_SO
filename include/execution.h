#ifndef EXECUTION_H
#define EXECUTION_H

#include "process.h"
#include "memory.h"
#include <queue>

// Función para simular la ejecución de procesos y la ráfaga de CPU, incluyendo bloqueos
void simulateProcessExecution(std::queue<Process>& processQueue, MemoryManager& memoryManager);

#endif
