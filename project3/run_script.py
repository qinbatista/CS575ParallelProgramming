import os
import subprocess
from sys import platform
def StartTest():
    if os.path.exists("./result.csv"): os.remove("./result.csv")
    if os.path.exists("./error.csv"): os.remove("./error.csv")
    for thread_number in [1,2,4,6,8,10,12,14,16]:
        for trail_number in [500,1000,1500,2000,2500,3000,3500,4000,4500,5000]:
            if platform == "linux" or platform == "linux2":
                os.system(f"g++ -fopenmp main.cpp -o main -DNUMT={thread_number} -DNUMNODES={trail_number}")
            elif platform == "darwin":
                os.system(f"g++ -Xpreprocessor -fopenmp -lomp  main.cpp  -o main  -DNUMT={thread_number} -DNUMNODES={trail_number}")

            p = subprocess.Popen(f"./main", stdout = open("./result.csv",'a'), stderr= open("./error.csv",'a'), universal_newlines=True, shell=True)
            p.wait()
if __name__ == '__main__':
    StartTest()