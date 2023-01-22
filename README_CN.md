# lw二合一焊台
![alt p1](./p1.jpg)
* 支持T12、JBC210、JBC245烙铁头
* 支持220V 700W风枪

详细见[LW焊台](https://oshwhub.com/lonerwolf/lw-han-tai)
## 主控
沁恒CH32V307VCT6，用303替换也行
## 界面
界面用的LVGL,使用NXP的GUI-Guider设计，部分字体空间太大，用LVGL官网工具替换掉了
## 软件编译
Clion开发环境，选择MinSizeRel优化选项  
CMake文件需要设置编译器路径
```
set(TOOLCHAIN_ROOT "D:\\MounRiver\\MounRiver_Studio\\toolchain\\RISC-V Embedded GCC")
```

## 下载
单片机FLASH选项选 224K-ROM 96K-RAM

