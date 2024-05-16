import os 
with open("example2.txt","w") as file :
    file.write("Hello World\n")
    file.close()

with open("example2.txt","r") as file :
    print(file.read())
    file.close()

os.chmod("example2.txt",0o444)
print(f'Permission changed to Non-Writable')

try :
    open("example2.txt","w").write("Hello World\n")
except PermissionError as e :
    print("Cannot be written")