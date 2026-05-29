#include <iostream>
#include "queue.hpp"
#include <string>
#include <vector>

// enum that stores the 5 process states
enum ProcessState {
    NEW,
    READY,
    RUNNING,
    WAIT,
    TERMINATE
};

// enum for the operations a process can perform
enum OperationType {
    CPU_BURST,
    IO_REQUEST
};

// struct to store pairs of operations and their times
struct Operation {
    OperationType operation;
    int time;
};

// struct for the PCB
struct ProcessControlBlock {
    // name of the process
    std::string name;
    // process id
    int pid;
    // current state of the process
    ProcessState state;
    // sequence of operations the process will perform
    // these operations have to occur in order, so
    // a queue is used
    Queue<Operation> operations;
};

std::string toString(ProcessState state) {
    switch (state) {
        case NEW:
            return "New";
        case READY:
            return "Ready";
        case RUNNING:
            return "Running";
        case WAIT:
            return "Wait";
        case TERMINATE:
            return "Terminated";
        default:
            return "";
    }
}

std::ostream& operator<<(std::ostream& out, const ProcessControlBlock &pcb) {
    out << "Process Name:   " << pcb.name << std::endl;
    out << "Process ID:     " << pcb.pid << std::endl;
    out << "Process State:  " << toString(pcb.state) << std::endl;
    int time = pcb.operations.empty() ? 0 : pcb.operations.front().time;
    out << "Remaining Time: " << time << " ms" << std::endl;
    return out;
}

class Dispatcher {
public:
    // assign references to the ready and waiting queues
    Dispatcher(Queue<ProcessControlBlock>* ready, Queue<ProcessControlBlock>* wait) {
        readyQueue = ready;
        waitQueue = wait;
    }

    // the ready and wait queues are pointers to existing,
    // stack allocated queues so we don't delete them
    ~Dispatcher() { }

    // actual business logic of managing the queues
    // returns completed processes
    std::vector<ProcessControlBlock> dispatch() {
        std::vector<ProcessControlBlock> completedProcesses;
        // first check the ready queue
        if (!readyQueue->empty()) {
            ProcessControlBlock process = readyQueue->front();
            readyQueue->dequeue();
            process.operations.front().time -= quantum;
            if (process.operations.front().time > 0) {
                process.state = ProcessState::READY;
                readyQueue->enqueue(process);
            }
            else {
                process.operations.dequeue();
                if (!process.operations.empty()) {
                    if (process.operations.front().operation == OperationType::CPU_BURST) {
                        process.state = ProcessState::READY;
                        readyQueue->enqueue(process);
                    }
                    else {
                        process.state = ProcessState::WAIT;
                        waitQueue->enqueue(process);
                    }
                }
                else {
                    process.state = ProcessState::TERMINATE;
                    completedProcesses.push_back(process);
                }
            }
            if (!readyQueue->empty()) {
                readyQueue->front().state = ProcessState::RUNNING;
            }
        }
        // now check the wait queue
        // the wait queue is using FCFS
        if (!waitQueue->empty()) {
            ProcessControlBlock process = waitQueue->front();
            process.operations.front().time -= quantum;
            if (process.operations.front().time < 0) {
                waitQueue->dequeue();
                process.operations.dequeue();
                if (!process.operations.empty()) {
                    if (process.operations.front().operation == OperationType::CPU_BURST) {
                        process.state = ProcessState::READY;
                        readyQueue->enqueue(process);
                    }
                    else {
                        process.state = ProcessState::WAIT;
                        waitQueue->enqueue(process);
                    }
                }
                else {
                    process.state = ProcessState::TERMINATE;
                    completedProcesses.push_back(process);
                }
            }
        }
        return completedProcesses;
    }
    // return the time quantum, which is the wait time before
    // the process dispatcher runs again
    int getQuantum() const { return quantum; }
private:
    // time quantum for RR CPU scheduling
    int quantum = 100;
    // references to external ready and wait queues
    Queue<ProcessControlBlock>* readyQueue;
    Queue<ProcessControlBlock>* waitQueue;
};



int main() {
    Queue<ProcessControlBlock> readyQueue;
    Queue<ProcessControlBlock> waitQueue;
    Dispatcher dispatcher = Dispatcher(&readyQueue, &waitQueue);
    while (!(readyQueue.empty() && waitQueue.empty())) {
        std::cout << "Ready Queue state: \n";
        readyQueue.print(std::cout);
        std::cout << "Wait Queue state: \n";
        waitQueue.print(std::cout);
        std::vector<ProcessControlBlock> completedProcesses = dispatcher.dispatch();
        std::cout << "Processes that just completed:\n";
        for (const auto& pcb: completedProcesses) {
            std::cout << pcb << std::endl;
        }
    }
}

