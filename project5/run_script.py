import os
import subprocess
from sys import platform
def StartTest():
    for block_size in [1,2,4,8,16,32,64,128.256,512]:
        for trail_number in [1024, 4096, 16384, 65536, 262144, 1048576, 2097152, 4194304]:
            if platform == "linux" or platform == "linux2":
                os.system(f"/usr/local/apps/cuda/cuda-10.1/bin/nvcc -o montecarlo montecarlo.cu -DNUMTRIALS={trail_number} -DBLOCKSIZE={block_size}")
            p = subprocess.Popen(f"./montecarlo",  stderr= open("./montecarlo.csv",'a'), universal_newlines=True, shell=True)
            p.wait()
if __name__ == '__main__':
    StartTest()