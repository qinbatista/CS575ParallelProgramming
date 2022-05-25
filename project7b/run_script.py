import os
import subprocess
from sys import platform
def StartTest():
    for thread_size in [2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32]:
        # os.system(f"mpic++ main.cpp -o main -lm")
        pa = subprocess.Popen(f"mpic++ main.cpp -o main -lm",  stderr= open("./error.csv",'a'), universal_newlines=True, shell=True)
        pa.wait()
        p = subprocess.Popen(f"mpiexec -mca btl self,tcp -np {thread_size} main",  stderr= open("./log.csv",'a'), universal_newlines=True, shell=True)
        p.wait()
if __name__ == '__main__':
    StartTest()