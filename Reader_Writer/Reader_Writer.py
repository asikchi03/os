import threading

lock = threading.Lock()
can_read = threading.Condition(lock)
can_write = threading.Condition(lock)
readers_count = 0
writer_writing = False

def reader():
    global readers_count, writer_writing
    with lock:
        readers_count += 1
        while writer_writing:
            print(f"{threading.current_thread().name} is waiting for writer to Write")
            can_read.wait()
        print(f"{threading.currentThread().name} starts reading")

        with open("/Users/apple/Desktop/OS/Assignment_Solutions/Assignment_4/file1.txt", "r") as file:
            for line in file:
                print(line, end='')  # Print without adding extra newline

        readers_count -= 1
        if readers_count == 0:
            can_write.notify()

def writer():
    global writer_writing
    with lock:
        while readers_count > 0 or writer_writing:
            can_write.wait()
        print(f"{threading.currentThread().name} starts writing")
        writer_writing = True

        with open("/Users/apple/Desktop/OS/Assignment_Solutions/Assignment_4/file1.txt", "a") as file:
            file.write("Hello World\n")

        writer_writing = False
        can_read.notify_all()
        can_write.notify_all()

reader_threads = []
for i in range(6):
    t = threading.Thread(target=reader, name=f"Reader-{i}")
    reader_threads.append(t)
    t.start()

writer_threads = []
for i in range(6):
    t = threading.Thread(target=writer, name=f"Writer-{i}")
    writer_threads.append(t)
    t.start()

for t in reader_threads:
    t.join()
for t in writer_threads:
    t.join()
