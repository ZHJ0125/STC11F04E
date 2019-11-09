![](https://img.shields.io/badge/Creator-ZhangH.J.-success)
![](https://img.shields.io/github/license/ZHJ0125/STC11F04E)
![](https://img.shields.io/npm/v/drone.svg)
![](https://img.shields.io/badge/language-C-9cf.svg)



# STC11F04E
> 如果你测试了我的代码，觉得不错的话请给个 Star ！你的 Star 是我持续更新的动力, 谢谢 😄.

本仓库存放电子工艺实习的实验代码

最终实现的功能为：数码管显示温度和时间、通过超声波传感器显示距离、滚动显示学号、外部中断及定时器的使用 等

# 实验平台
芯片| 介绍
---|:--:
主控芯片 | STC11F04E
其他芯片 | 74HC164、DS1302
开发环境 | Keil uVersion5
晶振型号 | 11.0592MHz

# 项目介绍
> Datasheet 目录

- 存放芯片资料以及收集的各种网络资料

> Project 目录

- 存放Keil工程项目文件

> Schematic 目录

- 存放重要的原理图

> Video 目录

- 存放我的展示视频以及焊接教程视频

# 工程导引

功能 | 项目介绍 | 索引页面
---|---|---
延时函数测试 | 使用示波器测试延时函数的精确延时时间 | [00_Delay](https://github.com/ZHJ0125/STC11F04E/tree/master/Project/00_Delay)
数码管静态显示 | 四个数码管同时循环显示数字0~9 | [01_Digital_Tube_Static_Display](https://github.com/ZHJ0125/STC11F04E/tree/master/Project/01_Digital_Tube_Static_Display)
数码管动态显示 | 默认状态显示1234,按键INT0按下时显示4321 | [02_Digital_Tube_Dynamic_Display](https://github.com/ZHJ0125/STC11F04E/tree/master/Project/02_Digital_Tube_Dynamic_Display)
DS18B20温度模块 | 数码管显示当前温度（保留一位小数） | [03_DS18B20](https://github.com/ZHJ0125/STC11F04E/tree/master/Project/03_DS18B20)
DS1302时间模块 | 设置初始时间为“2019年10月4日18:55:00”并不断显示时间 | [04_DS1302](https://github.com/ZHJ0125/STC11F04E/tree/master/Project/04_DS1302)
时间和温度整合 | 数码管默认显示时间(初始化时间为“2019年10月4日18:55:00”),按下INT0按键后,会显示温度 | [05_FinalCode](https://github.com/ZHJ0125/STC11F04E/tree/master/Project/05_FinalCode)
ESP8266模块 | 初始化ESP8266模块，连接实验室WiFi，初始化串口通信 | [06_ESP8266](https://github.com/ZHJ0125/STC11F04E/tree/master/Project/06_ESP8266)
HC-SR04超声波模块 | 利用超声波模块循环测距，并在数码管上显示距离（单位厘米，保留一位小数） | [07_HC-SR04](https://github.com/ZHJ0125/STC11F04E/tree/master/Project/07_HC-SR04)
定时器测试 | 利用延时函数测试定时器的计时是否准确 | [08_Timer_Test](https://github.com/ZHJ0125/STC11F04E/tree/master/Project/08_Timer_Test)
滚动显示学号 | 利用二维数组滚动显示我的学号 | [09_StuNum](https://github.com/ZHJ0125/STC11F04E/tree/master/Project/09_StuNum)
外部中断 | 当按下外部中断按键INT0时,触发外部中断0,改变数码管显示的数值(0~9) | [10_Interrupt](https://github.com/ZHJ0125/STC11F04E/tree/master/Project/10_Interrupt)
定时器模块 | 定时1S,在数码管上循环显示0~9或循环点亮数码管的每一段（通过注释NUMBER_LOOP标志位，可以控制显示模式） | [11_Timer](https://github.com/ZHJ0125/STC11F04E/tree/master/Project/11_Timer)



# 项目博客
> 数码管显示温度和时间
- https://blog.csdn.net/ZHJ123CSDN/article/details/102299484 
 
> 通过超声波传感器显示距离
- https://blog.csdn.net/ZHJ123CSDN/article/details/102490823
