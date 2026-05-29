# Queue ADT

The queue ADT, similar to stack, provides access to elements in a controlled order. While the stack allowed access to elements in last-in, first-out (LIFO) order, queues provide access in first-in, first-out (FIFO) order. Like how at a *queue* for a cash register, the first person to enter the queue is the first person to check out, the first element to enter the queue is the first one to exit the queue. Similar to stack, in this chapter we'll implement our queue using an array. 

## Data
Like stack, queue needs to store a series of elements while maintaining their insertion order. Therefore, an array or list must be used. Lists are next chapter's topic, so an array will be used here. For an array-based implementation, we need to track the index of the front of the queue, as well as the maximum size of the array, so we do not overflow the queue. Additionally, since new elements are added to the back of the queue, the index of the back needs to be tracked as well.

## Operations
The primary queue operations are `enqueue()` and `dequeue()`. `enqueue()` adds an element to the end of the queue. The `dequeue()` operation removes an item from the front of the queue. Like with stack, some implementations of queue implement a separate function to access the item at the front of the queue, and make `dequeue()` a void function that only removes an item from the front of the queue, rather than removing and returning it. We should provide a member function that checks if the queue is empty, so clients can guard against attempts to dequeue from an empty queue. In an array based implementation, we should also include operations to check if the queue is full, so that clients can guard against pushing to a full queue.

## Rules
Users should not be able to enqueue an element to a queue that is full in an array based implementation. In any underlying implementation, users should not be able to access the front of a queue that is empty.

## Operation Efficiency
Due to its controlled access, queue, like stack, should provide O(1) time complexity for its `enqueue()` and `dequeue()` operations. However, when looking at the array-based implementation of a queue, there is an issue with achieving this:
```
ADT Queue:
    Array data
    num front
    num back
    num max

    operation enqueue(e):
        if (back + 1 == max):
            throw FullQueueError
        else:
            back = back + 1
            data[back] = e
    
    operation dequeue():
        if (front < 0 and back < 0):
            throw EmptyQueueError
        else:
            e = data[front]
            front = front + 1
            return e
    
    operation full():
        if back + 1 == max:
            return true
        else:
            return false

    operation empty():
        if front < 0 and back < 0:
            return true
        else:
            return false

    operation size():
        return back - front
```
In this implementation, the `enqueue()` and `dequeue()` operations achieve O(1) time complexity. However, every time we remove an item from the queue, the front is moved towards the end of the queue. This means that each time we remove an item, we are shrinking the capacity of the queue. How can we resolve this? One option is to shift all the elements of the array forwards each time we perform `dequeue()`:
```
operation dequeue():
    if front < 0 and back < 0:
        throw EmptyQueueError

    else:
        for i in 1..back:
            data[i - 1] = data[i]

        front = 0
        back = back - 1
```
In this implementation, we don't give up the front elements of the array every time we perform a `dequeue()` operation. However, we now have to loop through (potentially) every element in the array for each `dequeue()`. The time complexity has exploded from O(1) to O(n). Is there any way we can avoid wasting elements of the array when removing elements, while still maintaining O(1) time complexity? We can. While physically, the array is a linear container, we can imagine whatever structure we want. What if the array were a circle, connected end to end? Then, when we reach the last index of the array, we can start over and store elements at the original front of the array. By implementing a *circular* queue, we can make use of the entire array's capacity, while still providing O(1) time complexity for `enqueue()` and `dequeue()`. We can use the modulus operator to automatically wrap the back of the queue back around to the front of the queue. In this case, the queue becomes full when `(back + 1) % max` equals the front, i.e., inserting an element would overwrite the current front of the queue. The queue is empty when the front equals the back. Below is the pseudocode for the circular queue implementation:
```
ADT Queue:
    Array data
    num front
    num back
    num max

    operation enqueue(e):
        if (back + 1) % max == front:
            throw FullQueueError
        else:
            data[back] = e
            back = (back + 1) % max
    
    operation dequeue():
        if back == front:
            throw EmptyQueueError
        else:
            e = data[front]
            front = (front + 1) % max

    operation empty():
        if back == front:
            return true
        else:
            return false

    operation full():
        if (back + 1) % max == front:
            return true
        else:
            return false

    operation size():
        if front == back:
            return 0
        else if front < back:
            return back - front
        else:
            return back - front + max
```
In this case, `enqueue()` is still O(1). The only change is we take the modulus of back + 1 (taking the modulus allows the back index to wrap around to the front of the array) and compare it to front, rather than checking if the back is less than the max size. For `dequeue()`, we now move front forward by one position and take the modulus. In this implementation, `dequeue()` is doing single, simple arithmetic and boolean comparisons, so it is O(1). The `size()` operation is modified so that it handles three cases: the front equals the back, the front is less than the back, and the back is less than the front. If the front equals the back, this is our empty condition, so the queue has a size of 0. If the front is less than the back, then we can just subtract the front index from the back index. The final case is when the back is less than the front, in which case the back has wrapped around. In this case, we need to add to find the difference between the front and back, and then subtract that from the number of maximum size of the array.  

## Deque
A doubly ended queue, called a deque (pronounced like "deck"), is a data structure that allows the front and rear elements to be removed.

## Queue Applications
Queues have a more narrow (than stack), but well-defined set of applications. Any kind of waiting list in a program is most effectively implemented using a queue. This can be used in programs that need to model a real life waiting list (line at a DMV, traffic simulations, simulation in a game, etc.), as well as waitlists used by your computer. Your operating system maintains process queues for CPU access, I/O access, etc. Processes are switched between these queues based on what stage of life they are in.

## Full Example: CPU Scheduler
One of the responsibilities of a computer's operating system is ensuring access to your computer's resources to the applications that you are trying to run. On very old systems, this was a simple task: one application could run at a time, and it had unlimited access to a computer's resources until it completed execution. However, as the uses for computers expanded and processing power increased, the need arose for systems capable of multiprocessing. First, some terminology: a process (sometimes referred to as a task or job, as well) is an application that has been loaded into memory and is ready to execute. The role of the operating system is to provide processes access to the CPU, files, input buffers, output buffers, etc. The next sections describe the states that a process can be in and how operating systems manage access to computer resources.

### Process Model and States
Most computer science literature describes five states for a process:  
- **New:** The process has been created, and the OS is initializing the process control block (PCB)
- **Ready:** The process is ready to utilize the CPU
- **Running:** The process is actively using the CPU
- **Waiting:** The process has to wait (usually for I/O) and is unable to use the CPU
- **Terminated:** The process has completed execution and is waiting for the OS to clean it up

The process control block is a data structure that describes a process and the data the operating system needs to manage it. At a high level, this includes the process's state, identifying information, memory mappings, and register values. It allows the OS to suspend a process in favor of another, and then have all the information it needs to restart the process to its previous state.

### Scheduling Algorithms
There have been multiple algorithms proposed to schedule CPU access. All use some form of "ready queue", which is a queue that stores processes that are in the "ready" state.  
The simplest algorithm is first-come, first-serve (FCFS). FCFS allows processes to access the CPU in the order they request it. In this case, the ready queue is used directly. The processes in the queue are allowed to execute in the order they arrive in the queue. This is a simple solution, but not an efficient one. Consider this: 3 processes enter the queue (P1, P2, P3). P1 enters first and requires 500ms of CPU time. P2 enters next and requires 200ms of CPU time. Then, P3 enters, and needs 100ms of CPU time. In FCFS, P1 would have access to the CPU first, and would use it for 500ms, requiring P2 and P3 to wait 500ms. Next, P2 executes, which forces P3 to wait another 200ms. Finally, P3 gets access to the CPU. The combined waiting times are 0 for P1, 500 for P2, and 700 for P3, leading to an average waiting time of (0 + 500 + 700) / 3 = 400ms. FCFS, while simple and easy to implement, unfairly allows long processes to dominate the CPU, increasing the average wait time. Consider if the processes arrived in the reverse order (P3, P2, P1). Then P3 would execute first, forcing P2 and P1 to wait 100ms. Then, P2 would execute, which requires P1 to wait 200ms more. Finally, P1 executes. The total wait times would then be: 0, 100, 300, and the average wait would be approximately 133ms.  
This brings us to the next scheduling algorithm, shortest-job first (SJF). In this approach, the OS selects the process with the shortest processing time each time the CPU is available. This is a type of priority scheduling algorithm, where priority is given to the element with the shortest completion time. This, however, requires a special type of queue, a priority queue. We save that topic for chapter 10. SJF is, however, the optimal scheduling algorithm. However, it requires knowledge of the CPU burst time for each process, which is not known ahead of time. Therefore, the burst times are estimated based on past usage by that process. A limitation of SJF is that it is not fair. If short processes continually enter the ready queue, they will always have priority over a longer process that is stuck waiting. This leads to starvation.   
The two prior approaches are based non-preemptive, which means that once a process has control of the CPU, the OS will not interrupt it until it is finished using the CPU. Preemptive schedulers can preempt a process, meaning the OS removes the process from the CPU in favor of another, and forces the process that was using the CPU back into the ready queue. First, we can consider a further optimization of the SJF algorithm that uses preemption: shortest-remaining time first (SRTF). The difference between this algorithm and SJF is that in SRTF, if a shorter process than the one currently using the CPU enters the ready queue, the current process on the CPU will be removed in favor of the new, shorter process.  
Finally, we discuss round-robin (RR) scheduling. RR scheduling is similar to FCFS, except it uses preemption to prevent a single process from accessing the CPU for too long. The RR scheduler as a *time quantum*, which is the maximum amount of time a single process can access the CPU in a single burst. If a process requires less time than the quantum, it completes and is removed from the ready queue. Otherwise, when its time runs out it is preempted and moved to the end of the ready queue, allowing the next process in the queue its turn at the CPU. The RR algorithm is a balance of being fair while reducing average wait times. Consider this example:  

| Process | Time (ms) |
| ------- | ---- |
| P1 | 300 |
| P2 | 50 |
| P3 | 100 |

Using FCFS, the average wait time for these processes would be (0 + 300 + 350) / 3 ~= 217ms. If we used SJF, the average waiting time would be (0 + 50 + 150) / 3 ~= 67ms. We will skip SRTF, and assume that these three processes arrived at approximately the same time, causing SRTF to be approximately the same as SJF. For RR, the average wait time is dependent on the value chosen for the time quantum. Another thing to consider with RR is that preempting processes is not free; it takes time to suspend a process, move it to the end of the ready queue, and load the next process onto the CPU. Let's assume that it takes 10ms to switch processes. The next table shows the average wait times for RR when using various time quanta.  

| Time Quantum (ms) | Execution Order | Average Wait Time (ms) |
| ----------------- | --------------- | ---------------------- |
| 20 | P1(20) P2(20) P3(20) P1(20) P2(20) P3(20) P1(20) P2(10) P3(20) P1(20) P3(20) P1(20) P3(20) P1(20) * 10 | TODO |
| 50 | P1(50) P2(50) P3(50) P1(50) P3(50) P1(50) * 4 | TODO |
| 100 | P1(100) P2(50) P3(100) P1(100) * 2 | TODO |
| 200 | P1(200) P2(50) P3(100) P1(100) | TODO |

As you can see, having too short of a time quantum causes switching between processes to have too much of an impact on the overall time due to how frequently processes are switched (and this scales even worse when there are more processes to cycle through). On the other hand, too long of a quantum causes the average wait time of RR to decay to be the same as FCFS. Therefore, the overall efficiency of RR depends on the number of concurrent processes in the ready queue and the choice of time quantum.  

### Planning Our Scheduler
For our CPU scheduler, we will use the RR algorithm. It is simple to implement with our queue ADT, and is more efficient than FCFS, which can also be implemented with a normal queue. First, we need to define a data structure to store the PCB. Since we are creating a simulation, we do not need a complete PCB data structure. We should maintain the name of the process, the process ID, the process state, and the sequence of CPU bursts and I/O waits the process needs. Below is a struct that implements our PCB, as well as an enum to store the process states. 
```C++
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
    std::vector<Operation> operations;
};
```

Now, we need a class that handles dispatching the processes. The `Dispatcher` class will contain a pointer to the ready queue and the wait queue. The 

