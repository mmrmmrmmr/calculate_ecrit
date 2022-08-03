# 吸气式电推进氮氧放电过程仿真计算程序
## 文件构成
主要由配置文件夹、路径检索文件、仿真计算程序与其他辅助程序组成，其文件构成如下所示  
calculate_ecrit  
|——set.py  
|——draw.py  
|——create_and_calculate.h  
|——my_sim.h  
|——main.cpp  
|——path.txt  
|——folder  
|——|——ans.txt  
|——|——chen.txt  
|——|——den.txt  
|——|——ele.txt  
|——|——equation.txt  
|——|——sym.txt  
下面对主要文件进行讲解
### set.py
为配置文件的辅助设置程序，通过编写对应文件夹下的equation.txt文件，来自动生成对应的相关文件  
### draw.py  
为仿真结果的绘制程序  
### main.cpp
为仿真程序的主要程序
### path.txt
为仿真配置文件的储存地址

## 仿真使用方法
* 首先修改配置文件，在自定的文件夹folder下进行设置，也可使用set.py进行辅助设置
* 修改path路径，之后直接运行主程序main.cpp，以生成在对应路径下的结果ans.txt
* 运行draw.py，进行仿真结果的绘制

## 所需依赖配置
需g++或其他编译器对cpp进行编译  
需python3，以及相关依赖matlibplot，numpy  
如需使用vscode运行，需添加.vscode文件夹下的launch.json，需要加载扩展code runner，python，c/c++

## 配置文件配置方法
推荐使用配置文件工具set.py进行设置  
按实例文件夹example来进行equation.txt，sym.txt，den.txt进行填写，之后更改路径path.txt为当前文件夹，再运行set.py，自动完成设置  
在运行前，需要更改文件夹下的setting_siim.txt，其中每行分别为包含电子的组分个数，方程个数，终止时间，时间步长，打印时间步长  
对于大数据量的仿真计算，可以适当增加打印时间步长，以减少打印时间，加快运行速度，不会对计算精度造成影响  
在运行draw.py时，可以调整不绘制的组分，主要为代码的第28行  



