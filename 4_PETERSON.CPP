#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

class PetersonMutex {
private:
    atomic<bool> flag[2];
    atomic<int> turn;

public:
    PetersonMutex() {
        flag[0] = false;
        flag[1] = false;
        turn = 0;
    }

    void lock(int threadId) {
        int otherThreadId = 1 - threadId;

        flag[threadId] = true;
        turn = otherThreadId;

        // Wait until the other thread is not interested or it's our turn
        while (flag[otherThreadId] && turn == otherThreadId) {
            // Busy wait
        }
    }

    void unlock(int threadId) {
        flag[threadId] = false;
    }
};

PetersonMutex mutex;

void critical_section(int threadId) {
    mutex.lock(threadId);

    // Critical section
    cout << "Thread " << threadId << " is in critical section." << endl;

    mutex.unlock(threadId);
}

void thread_function(int threadId) {
    // Simulating some work
    for (int i = 0; i < 5; ++i) {
        cout << "Thread " << threadId << " is doing some work." << endl;
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    // Entering critical section
    critical_section(threadId);
}

int main() {
    thread t1(thread_function, 0);
    thread t2(thread_function, 1);

    t1.join();
    t2.join();

    return 0;
}
