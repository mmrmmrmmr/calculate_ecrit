import re

reactant = []
product = []
k = []

path = ""

with open(path +  'equation.txt', 'r') as file:
    lines = file.readlines()
    for line in lines:
        x = []
        line = re.findall(r"\d+\.\d+e-\d+|=|\d+\.\d+|\d+" ,line)
        # print(line)
        for i in line:
            if i == "=":
                reactant.append(x)
                x = []
            else:
                i = float(i)
                if int(i) == float(i):
                    x.append(int(i))
                else:
                    k.append(float(i)) 
        product.append(x)
file.close()

ele_num = 1
with open(path + "chem.txt", 'w') as file:
    for i in range(len(k)):
        num = int(len(reactant[i]) / 2)
        line = reactant[i]
        file.write(str(k[i]) + " " + str(num))
        for j in range(num):
            file.write(" " + str(line[2*j+1]) + " " + str(line[2*j]))
            if line[2*j+1] > ele_num:
                ele_num = line[2*j+1]
        file.write("\n") 
file.close()

p = [""] * ele_num
cnt = [1 - 1] * ele_num

for i in range(len(k)):
        num = int(len(reactant[i]) / 2)
        line = reactant[i]
        for j in range(num):
            l = line[2*j+1] - 1
            if l == -1:
                continue
            cnt[l] = cnt[l] + 1
            p[l] = p[l] + " " + str(i + 1) + " " +  str(line[2*j])
        line = product[i]
        num = int(len(product[i]) / 2)
        for jj in range(num):
            l = line[2*jj+1] - 1
            if l == -1:
                continue
            cnt[l] = cnt[l] + 1
            p[l] = p[l] + " " + str(i + 1) + " -" +  str(line[2*jj])

with open(path + "ele.txt", 'w') as file:
    for i in range(len(p)):
        file.write(str(cnt[i]) + p[i] + "\n")
file.close()
        

        
