# 重要更新
## DS1302掉电检测
> 2019年12月04日，增加DS1302时钟芯片掉电检测功能
> 
> 在DS1302初始化写入数据之前，检测 *CH标志位*，如果掉电则写入初始时间；否则不再写入初始时间，显示记录的时间。解决了持续显示时间的问题。
> 

> ### CLOCK HALT FLAG
>
> Bit 7 of the seconds register is defined as the clock halt (CH) flag. When this bit is set to logic 1, the clock oscillator is stopped and the DS1302 is placed into a low-power standby mode with a current drain of less than 100nA. When this bit is written to logic 0, the clock will start. The initial power-on state is not defined.      ----来自DS1302数据手册
