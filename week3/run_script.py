import os
import subprocess
from sys import platform
def StartTest():
    for thread_number in [1,2,4,8,12,16,20,24,32]:
        for trail_number in [1,10,100,1000,10000,100000,500000,1000000]:

            if platform == "linux" or platform == "linux2":
                os.system(f"g++ -fopenmp main.cpp -o main -DNUMT={thread_number} -DNUMTRIALS={trail_number}")
            elif platform == "darwin":
                os.system(f"g++ -Xpreprocessor -fopenmp -lomp  main.cpp  -o main  -DNUMT={thread_number} -DNUMTRIALS={trail_number}")

            p = subprocess.Popen(f"./main",  stderr= open("./proj1.csv",'a'), universal_newlines=True, shell=True)
            p.wait()
if __name__ == '__main__':
    StartTest()