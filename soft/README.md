## 编译
Clion开发环境，选择MinSizeRel优化选项  
编译器官方下载MounRiver Studio自带  
CMake文件需要设置编译器路径
```
set(TOOLCHAIN_ROOT "D:\\MounRiver\\MounRiver_Studio\\toolchain\\RISC-V Embedded GCC")
```

## 烧写
单片机FLASH选项选 224K-ROM 96K-RAM  
USB下载或者WCH LINK下载，参考官方文档

