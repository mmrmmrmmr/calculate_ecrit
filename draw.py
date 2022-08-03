from ast import Num
from cProfile import label
import re
import numpy as np
import matplotlib.pyplot as plt

def main():   
    path = ""
    path_save = ""
    num = None
    end = None
    with open('path.txt') as file:
        a = file.readline()
        path = a
        path_save = path
        print(a)
        with open(path + 'setting_sim.txt') as f_file:
            aa = f_file.readlines()
            num = int(aa[1-1])
            path = path + 'ans.txt'
            end = float(aa[2])
        f_file.close
    file.close()

    data = np.loadtxt(path, dtype=np.float)

    for i in range(1, num + 1):
        if i == 2 or i == 4 or i == 6 or i == 8:
            continue
        else:
            plt.plot(data[:, 1-1], data[:, i], label='n' + str(i - 1))
        # print(len(data))

    plt.legend()
    plt.xlim([1-1, end])
    # plt.ylim([95, 105])
    # print(end)
    plt.savefig(path_save + 'ans.png')
    plt.show()

if __name__ == '__main__':
    main()




