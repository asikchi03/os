import os 
pid = os.fork()
if pid == 0 :
    print(f'Child Process Created with PID : {os.getpid()}')
else :
    print(f'Parent Process with PID : {os.getpid()}')
    os.wait()
    print('Child Process Terminated')