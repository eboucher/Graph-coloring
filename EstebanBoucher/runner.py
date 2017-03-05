import subprocess

args_gcc = "gcc -Wall -Wextra -O3 -std=c99 -Iapifiles dirmain/mainEBoucher.c apifiles/*.c -o EB"
args_exec = "./EB < apifiles/graphs/school1.col"

subprocess.check_call(args_gcc, shell=True)
print "Skynet 2.0 compiled"

print "How many repetitions?"
n = input()

for i in range(n):
    call = subprocess.call(args_exec, stdout=subprocess.PIPE, shell=True)
    print i, ": ", call
    if call != 0:
        print "Error found. Subject llevado a marzo."
        exit()

print "Aprobaste la materia! Gracias Dovahkiin"