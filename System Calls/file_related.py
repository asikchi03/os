with open("example.txt","w") as file :
    file.write("Hello World\n")
    file.close()

with open("example.txt","r") as file :
    print(file.read())
    file.close()
