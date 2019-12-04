# 重要更新
## DS1302掉电检测
> 2019年12月04日，增加DS1302时钟芯片掉电检测功能
> 
> 在DS1302初始化写入数据之前，检测 *CH标志位*，如果掉电则写入初始时间；否则不再写入初始时间，显示记录的时间。解决了持续显示时间的问题。
> 

> ### CLOCK HALT FLAG
>
> Bit 7 of the seconds register is defined as the clock halt (CH) flag. When this bit is set to logic 1, the clock oscillator is stopped and the DS1302 is placed into a low-power standby mode with a current drain of less than 100nA. When this bit is written to logic 0, the clock will start. The initial power-on state is not defined.      ----来自DS1302数据手册

# 实验效果
数码管显示DS18B20采集的温度数据

# 版本说明

## 10月4日更新1
由于进行了位选三极管的更换，导致位选由原来的 <b>~~高电平放大~~</b> 变成了 <b>低电平放大</b> ，相应的程序也发生了变化，因此进行此次版本更新。

## 10月4日更新2
目前已经解决了温度无法显示的问题，问题原因是18B20时序没弄对，导致其初始化成功后，一直显示其默认数据"59"，在修改时序后问题得以解决。

# 目前存在的问题：
~~DS18B20 初始化成功，但数据读取异常，数码管一直显示“59”~~(已解决)
