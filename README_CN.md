# lw二合一焊台
![image](https://image.lceda.cn/pullimage/vQP46FFlfbOm5sraZ4GKLsGqRL4FvPVqw5Z7oa6u.jpeg)
* 支持T12、JBC245烙铁头，JBC210需要注意改PWM占空比，210需要12V
* 支持858风枪

详细见[LW焊台](https://oshwhub.com/lonerwolf/lw-han-tai)
## 主控
沁恒CH32V307VCT6，用303替换也行，就为了FSMC
## 界面
界面用的LVGL,使用NXP的GUI-Guider设计，部分字体空间太大，用LVGL官网工具替换掉了
## 软件编译
Clion开发环境，选择MinSizeRel优化选项  
编译器官方下载MounRiver Studio自带  
CMake文件需要设置编译器路径
```
set(TOOLCHAIN_ROOT "D:\\MounRiver\\MounRiver_Studio\\toolchain\\RISC-V Embedded GCC")
```

## 烧写
单片机FLASH选项选 224K-ROM 96K-RAM  
USB下载或者WCH LINK下载，参考官方文档

## 日志
2023.2.5 修复屏幕小蓝点
#### 待修复
* 震动开关休眠（准备不做这个功能了，烙铁已经有干簧管休眠了）

