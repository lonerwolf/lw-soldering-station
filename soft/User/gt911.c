//
// Created by lonerwolf on 2023/1/8.
//

#include <string.h>
#include "gt911.h"

#include "ch32v30x_conf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "debug.h"

#define GT911_RST_ACTIVE()          GPIO_ResetBits(GPIOD,GPIO_Pin_13)
#define GT911_RST_INACTIVE()        GPIO_SetBits(GPIOD,GPIO_Pin_13)

static void gt911_delay_ms(uint32_t ms) {
    //Delay_Ms(ms);
    vTaskDelay(pdMS_TO_TICKS(ms));
}

static const uint16_t TPX[] = {0x8150, 0x8158, 0x8160, 0x8168, 0x8170}; //触摸点数据地址
static GT911_TP_Dev l_tp_dev;

/* GT911单个触点配置参数，一次性写入 */
static uint8_t GT911_CfgParams_bak[] =
        {
                0x00,        //0x8047		版本号
                0xE0, 0x01,    //0x8048/8049	X坐标输出最大值480
                0x20, 0x03,    //0x804a/804b	Y坐标输出最大值800
                0x05,    //0x804c	输出触点个数上限
                0x35,    //0x804d	软件降噪，下降沿触发
                0x00,    //0x804e	reserved
                0x02,    //0x804f	手指按下去抖动次数
                0x08,    //0x8050	原始坐标窗口滤波值
                0x28,    //0x8051	大面积触点个数
                0x0A,    //0x8052	噪声消除值
                0x5A,    //0x8053	屏上触摸点从无到有的阈值
                0x46,    //0x8054	屏上触摸点从有到无的阈值
                0x03,    //0x8055	进低功耗时间	s
                0x05,    //0x8056	坐标上报率
                0x00,    //0x8057	X坐标输出门上限
                0x00,    //0x8058	Y坐标输出门上限
                0x00, 0X00,    //0x8059-0x805a	reserved
                0x00,    //0x805b	reserved
                0x00,    //0x805c	reserved
                0x00,    //0x805d	划线过程中小filter设置
                0x18,    //0x805e	拉伸区间	1	系数
                0x1A,    //0x805f	拉伸区间	2	系数
                0x1E,    //0x8060	拉伸区间	3	系数
                0x14,    //0x8061	各拉伸区间基数
                0x8C,    //0x8062	、、
                0x28,    //0x8063	、、
                0x0C,    //0x8064	、、
                0x71,    //0x8065	驱动组A的驱动频率倍频系数
                0x73,    //0x8066	驱动组B的驱动频率倍频系数
                0xB2,    //0x8067	驱动组A、B的基频
                0x04,    //0x8068
                0x00,    //0x8069	相邻两次驱动信号输出时间间隔
                0x00,    //0x806a
                0x00,    //0x806b	、、
                0x02,    //0x806c	、、
                0x03,    //0x806d	原始值放大系数
                0x1D,    //0x806e	、、
                0x00,    //0x806f	reserved
                0x01,    //0x8070	、、
                0x00, 0x00,    //reserved
                0x00,    //0x8073	、、
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00,    //0x8071 - 0x8079 reserved
                0x50,    //0x807a	跳频范围的起点频率
                0xA0,    //0x807b	跳频范围的终点频率
                0x94,    //0x807c	多次噪声检测后确定噪声量，1-63有效
                0xD5,    //0x807d	噪声检测超时时间
                0x02,    //0x807e	、、
                0x07,    //0x807f	判别有干扰的门限
                0x00, 0x00,    //0x8081	reserved
                0x04,    //0x8082	跳频检测区间频段1中心点基频（适用于驱动A、B）
                0xA4,    //0x8083
                0x55,    //0x8084	跳频检测区间频段1中心点倍频系数
                0x00,    //0x8085	跳频检测区间频段2中心点基频(驱动A、B在此基础上换算)
                0x91,    //0x8086
                0x62,    //0x8087	跳频检测区间频段2中心点倍频系数
                0x00,    //0x8088	跳频检测区间频段3中心点基频（适用于驱动A、B）
                0x80,    //0x8089
                0x71,    //0x808a	跳频检测区间频段3中心点倍频系数
                0x00,    //0x808b	跳频检测区间频段4中心点基频（适用于驱动A、B）
                0x71,    //0x808c
                0x82,    //0x808d	跳频检测区间频段4中心点倍频系数
                0x00,    //0x808e	跳频检测区间频段5中心点基频（适用于驱动A、B）
                0x65,    //0x808f
                0x95,    //0x8090	跳频检测区间频段5中心点倍频系数
                0x00, 0x65,        //reserved
                0x00,    //0x8093	key1位置	0：无按键
                0x00,    //0x8094	key2位置	0：无按键
                0x00,    //0x8095	key3位置	0：无按键
                0x00,    //0x8096	key4位置	0：无按键
                0x00,    //0x8097	reserved
                0x00,    //0x8098	reserved
                0x00,    //0x8099	reserved
                0x00,    //0x809a	reserved
                0x00,    //0x809b	reserved
                0x00,    //0x809c	reserved
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,    //0x809d-0x80b2	reserved
                0x00,    //0x80b3	合框距离
                0x00,    //0x80b4
                0x00, 0x00,    //0x80b6	reserved
                0x06,    //0x80b7
                0x08,    //0x80b8
                0x0A,    //0x80b9
                0x0C,    //0x80ba
                0x0E,    //0x80bb
                0x10,    //0x80bc
                0x12,    //0x80bd
                0x14,    //0x80be
                0x16,    //0x80bf
                0x18,    //0x80c0
                0x1A,    //0x80c1
                0x1C,    //0x80c2
                0xFF,    //0x80c3
                0xFF,    //0x80c4
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,    //0x80c5-0x80d4	reserved
                0x00,    //0x80d5
                0x02,    //0x80d6
                0x04,    //0x80d7
                0x06,    //0x80d8
                0x08,    //0x80d9
                0x0A,    //0x80da
                0x0C,    //0x80db
                0x0F,    //0x80dc
                0x10,    //0x80dd
                0x12,    //0x80de
                0x13,    //0x80df
                0x14,    //0x80e0
                0x16,    //0x80e1
                0x18,    //0x80e2
                0x1C,    //0x80e3
                0x1D,    //0x80e4
                0x1E,    //0x80e5
                0x1F,    //0x80e6
                0x20,    //0x80e7
                0x21,    //0x80e8
                0xFF,    //0x80e9
                0xFF,    //0x80ea
                0xFF,    //0x80eb
                0xFF,    //0x80ec
                0xFF,    //0x80ed
                0xFF,    //0x80ee
                0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                0x00, 0x00, 0x00, 0x00,    //0x80ef-0x80fe	reserved
                0x0B,    //0x80ff	配置信息校验
                0x01    //0x8100	配置以更新标记
        };

static uint8_t GT911_CfgParams[] =
        {
                0x51,
                0xE0,0x01,
                0x52,0x03,//触屏坏，800点缺少47点，弄成850，缺少50刚好800。0-425需要-25在+400，475-850为0-375
                0x01,
                0x04,
                0x10,
                0x01,
                0xC8,
                0x28,
                0x0F,
                0x50,
                0x32,
                0x03,
                0x05,
                0x00,
                0x00,
                0x00,0x00,
                0x11,
                0x11,
                0x05,
                0x18,
                0x1A,
                0x1E,
                0x14,
                0x88,
                0x29,
                0x0A,
                0x52,
                0x50,
                0x40,
                0x04,
                0x00,
                0x00,
                0x00,
                0x1A,
                0x32,
                0x1C,
                0x46,
                0x09,
                0x00,0x0F,
                0x00,
                0x2A,0xFF,0x7F,0x19,0x50,0x32,
                0x3C,
                0x64,
                0x94,
                0xD5,
                0x02,
                0x07,
                0x00,0x00,
                0x04,
                0x9F,
                0x3F,
                0x00,
                0x90,
                0x46,
                0x00,
                0x84,
                0x4D,
                0x00,
                0x79,
                0x55,
                0x00,
                0x6D,
                0x5F,
                0x00,0x6D,
                0x00,0x00,0x00,0x00,0xF0,0x4A,0x3A,0xFF,0xFF,0x27,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x14,0x12,0x10,0x0E,0x0C,0x0A,0x08,0x06,0x04,0x02,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x22,0x21,0x20,0x1F,0x1E,0x1D,0x1C,0x18,0x16,0x12,0x10,0x0F,0x08,0x06,0x04,0x02,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x0B,0x01
        };

static void gt911_hardware_Init() {
    {
        //PD13 RST
        //PD12 INT
        GPIO_InitTypeDef GPIO_InitStructure = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

        GPIO_ResetBits(GPIOD, GPIO_Pin_13);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);

        GPIO_ResetBits(GPIOD, GPIO_Pin_12);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);

/*        GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource12);
        EXTI_InitStructure.EXTI_Line = EXTI_Line12;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_Init(&EXTI_InitStructure);

        NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
        NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
        NVIC_Init(&NVIC_InitStructure);*/
    }

    {
        GPIO_InitTypeDef GPIO_InitStructure = {0};
        I2C_InitTypeDef I2C_InitTSturcture = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        I2C_InitTSturcture.I2C_ClockSpeed = 100000;
        I2C_InitTSturcture.I2C_Mode = I2C_Mode_I2C;
        I2C_InitTSturcture.I2C_DutyCycle = I2C_DutyCycle_2;
        I2C_InitTSturcture.I2C_OwnAddress1 = 0x5D;
        I2C_InitTSturcture.I2C_Ack = I2C_Ack_Enable;
        I2C_InitTSturcture.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
        I2C_Init(I2C2, &I2C_InitTSturcture);

        I2C_Cmd(I2C2, ENABLE);

        I2C_AcknowledgeConfig(I2C2, ENABLE);
    }
}

static void gt911_change_addr() {
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_SetBits(GPIOD, GPIO_Pin_12);
    GT911_RST_INACTIVE();
    gt911_delay_ms(20);

    GPIO_ResetBits(GPIOD, GPIO_Pin_12);
    GT911_RST_ACTIVE();
    gt911_delay_ms(20);

    GPIO_ResetBits(GPIOD, GPIO_Pin_12);
    gt911_delay_ms(20);

    GT911_RST_INACTIVE();
    gt911_delay_ms(20);

    gt911_delay_ms(50);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
}

static int gt911_read_reg(uint16_t addr, uint8_t *ptBuff, uint16_t size) {
    uint16_t ucErrTime = 0;
    while (I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY) != RESET) {
        ucErrTime++;
        if (ucErrTime > GT911_IIC_ERR_COUNT) {
            return -1;
        }
    }

    I2C_GenerateSTART(I2C2, ENABLE);
    ucErrTime = 0;
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT)) {
        ucErrTime++;
        if (ucErrTime > GT911_IIC_ERR_COUNT) {
            return -1;
        }
    }

    I2C_Send7bitAddress(I2C2, GT911_IIC_WADDR, I2C_Direction_Transmitter);
    ucErrTime = 0;
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {
        ucErrTime++;
        if (ucErrTime > GT911_IIC_ERR_COUNT) {
            return -1;
        }
    }

    I2C_SendData(I2C2, (uint8_t) (addr >> 8));
    ucErrTime = 0;
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
        ucErrTime++;
        if (ucErrTime > GT911_IIC_ERR_COUNT) {
            return -1;
        }
    }

    I2C_SendData(I2C2, (uint8_t) (addr & 0x00FF));
    ucErrTime = 0;
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
        ucErrTime++;
        if (ucErrTime > GT911_IIC_ERR_COUNT) {
            return -1;
        }
    }

    I2C_GenerateSTART(I2C2, ENABLE);
    ucErrTime = 0;
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT)) {
        ucErrTime++;
        if (ucErrTime > GT911_IIC_ERR_COUNT) {
            return -1;
        }
    }

    I2C_Send7bitAddress(I2C2, GT911_IIC_RADDR, I2C_Direction_Receiver);
    ucErrTime = 0;
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) {
        ucErrTime++;
        if (ucErrTime > GT911_IIC_ERR_COUNT) {
            return -1;
        }
    }

    int i;
    for (i = 0; i < size; i++) {
        ucErrTime = 0;
        while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED)) {
            ucErrTime++;
            if (ucErrTime > GT911_IIC_ERR_COUNT) {
                return -1;
            }
        }
        if (i == (size - 1)) {
            I2C_NACKPositionConfig(I2C2, I2C_NACKPosition_Next);
            ptBuff[i] = I2C_ReceiveData(I2C2);
        } else {
            ptBuff[i] = I2C_ReceiveData(I2C2);
        }
    }

    I2C_GenerateSTOP(I2C2, ENABLE);

    return 0;
}

static int gt911_write_reg(uint16_t addr, uint8_t *ptBuff, uint16_t size) {
    uint16_t ucErrTime = 0;
    while (I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY) != RESET) {
        ucErrTime++;
        if (ucErrTime > GT911_IIC_ERR_COUNT) {
            return -1;
        }
    }

    I2C_GenerateSTART(I2C2, ENABLE);
    ucErrTime = 0;
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_MODE_SELECT)) {
        ucErrTime++;
        if (ucErrTime > GT911_IIC_ERR_COUNT) {
            return -1;
        }
    }

    I2C_Send7bitAddress(I2C2, GT911_IIC_WADDR, I2C_Direction_Transmitter);
    ucErrTime = 0;
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {
        ucErrTime++;
        if (ucErrTime > GT911_IIC_ERR_COUNT) {
            return -1;
        }
    }

    I2C_SendData(I2C2, (uint8_t) (addr >> 8));
    ucErrTime = 0;
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
        ucErrTime++;
        if (ucErrTime > GT911_IIC_ERR_COUNT) {
            return -1;
        }
    }

    I2C_SendData(I2C2, (uint8_t) (addr & 0x00FF));
    ucErrTime = 0;
    while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
        ucErrTime++;
        if (ucErrTime > GT911_IIC_ERR_COUNT) {
            return -1;
        }
    }

    int i;
    for (i = 0; i < size; i++) {
        I2C_SendData(I2C2, ptBuff[i]);
        ucErrTime = 0;
        while (!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {
            ucErrTime++;
            if (ucErrTime > GT911_IIC_ERR_COUNT) {
                return -1;
            }
        }
    }

    I2C_GenerateSTOP(I2C2, ENABLE);

    return 0;
}

int gt911_init() {
    memset(&l_tp_dev, 0, sizeof(GT911_TP_Dev));
    //uint8_t id[4];
    int res;
    gt911_hardware_Init();
    gt911_change_addr();

    uint8_t config_Checksum = 0;
    res = gt911_read_reg(GT911_REG_CONFIG_VERSION, (uint8_t *)&GT911_CfgParams[0], 1);
    if(res)
        return res;
    for(int i=0;i<sizeof(GT911_CfgParams)-2;i++)
    {
        config_Checksum += GT911_CfgParams[i];
    }
    GT911_CfgParams[184] = (~config_Checksum)+1;

    res = gt911_write_reg(GT911_REG_CONFIG, (uint8_t *)GT911_CfgParams, sizeof(GT911_CfgParams));
    if(res)
        return res;


/*    if (gt911_read_reg(GT911_REG_PRODUCT_ID, id, 4)) {
        printf("asd5\r\n");
    }
    printf("asd4\r\n");
    printf("id1:%x\n", id[0]);
    printf("id2:%x\n", id[1]);
    printf("id3:%x\n", id[2]);
    printf("id4:%x\n", id[3]);*/
    return 0;
}

int gt911_get_xy(int16_t* x,int16_t* y) {
    int res;
    uint8_t mode = 0;
    uint8_t temp = 0;
    uint8_t buf[4];
    res = gt911_read_reg(GT911_REG_READ_XY, &mode, 1);
    if (res) {
        return -1;
    }
    if (mode & 0X80) {
        temp = 0;
        res = gt911_write_reg(GT911_REG_READ_XY, &temp, 1);
        if (res) {
            return -1;
        }
    }
    if ((mode & 0X80) && ((mode & 0XF) > 0)) {
        res = gt911_read_reg(0x8150, buf, 4);
        if (res) {
            return -1;
        }
        uint16_t tmpX = 480-(((uint16_t) buf[1] << 8) | buf[0]);
        *y = tmpX;
        //0-425需要-25在+400，475-850为0-375
        uint16_t tmpY = (((uint16_t) buf[3] << 8) | buf[2]);
        if(tmpY > 474){
            *x = tmpY-475;
        }
        if(tmpY < 474){
            *x = tmpY+375;
        }
        return 0;
    }
    return 1;
}

int gt911_scan() {
    int res;
    uint8_t mode = 0;
    uint8_t temp = 0;
    uint8_t tempsta = 0;
    uint8_t i = 0;
    uint8_t buf[4];
    res = gt911_read_reg(GT911_REG_READ_XY, &mode, 1);
    if (res) {
        return -1;
    }
    if (mode != 0) {
        printf("mode:%x\r\n", mode);
    }

    /* 读取寄存器：0x814E  7:Bufferstatus  6:Large_Detect 3-0:number of touch points */
    if (mode & 0X80) {
        temp = 0;
        res = gt911_write_reg(GT911_REG_READ_XY, &temp, 1);
        if (res) {
            return -1;
        }
    }

    if ((mode & 0XF) && ((mode & 0XF) < 6)) {
        temp = 0XFF << (mode & 0XF);        //将点的个数转换为位数
        tempsta = l_tp_dev.sta;            //保存当前值

        l_tp_dev.sta = (~temp) | GT911_TP_PRES_DOWN | GT911_TP_CATH_PRES;
        l_tp_dev.x[4] = l_tp_dev.x[0];    //保存触点0值
        l_tp_dev.y[4] = l_tp_dev.y[0];
        for (i = 0; i < 5; i++) {
            if (l_tp_dev.sta & (1 << i))    //触摸有效
            {
                res = gt911_read_reg(TPX[i], buf, 4);
                if (res) {
                    return -1;
                }
                printf("point:%d %d\r\n", ((uint16_t) buf[1] << 8) | buf[0], ((uint16_t) buf[3] << 8) | buf[2]);
            }
        }
    }

    return 0;
}
