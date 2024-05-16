#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
using namespace std;
queue<int> buffer;
mutex mtx;
condition_variable cv;

bool bufferNotEmpty() {
    return !buffer.empty();
}
void printbuffer(queue<int> buffer) {
    cout << "Buffer: ";
    for (int i = 0;i<buffer.size();i++) {
        cout << i << " ";
    }
    cout << endl;
}
void producer() {
    for (int i = 1; i <= 5; ++i) {
        {
            lock_guard<mutex> lock(mtx);
            buffer.push(i);
            cout << "Produced: " << i <<  " " << endl;
            printbuffer(buffer);
        }
        cv.notify_one();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

void consumer() {
    while (true) {
        unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, bufferNotEmpty);
        int data = buffer.front();
        buffer.pop();
        cout << "Consumed: " << data << endl;
        printbuffer(buffer);
        lock.unlock();
        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

int main() {
    thread producerThread(producer);
    thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}
