import os
import subprocess
from sys import platform
def StartTest():
    for NMB in [1,2,4,8,16,32,64,128]:
        for LOCAL_SIZE in [8,16,32,64,128,256,512]:
            if platform == "linux" or platform == "linux2":
                os.system(f"g++ -o first_reduction first_reduction.cpp /usr/local/apps/cuda/cuda-10.1/lib64/libOpenCL.so.1.1 -lm -fopenmp -DNMB={NMB} -DLOCAL_SIZE={LOCAL_SIZE}")
            p = subprocess.Popen(f"./first_reduction",  stderr= open("./first_reduction.csv",'a'), universal_newlines=True, shell=True)
            p.wait()
if __name__ == '__main__':
    StartTest()