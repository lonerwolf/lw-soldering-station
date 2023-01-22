//
// Created by lonerwolf on 2023/1/5.
//

#include "system.h"
#include "ch32v30x_conf.h"
#include "rtc.h"
#include "math.h"

static int16_t l_adc1_calibrattion_val;
static int16_t l_adc2_calibrattion_val;
#define l_adc_count 5
#define l_adc_channel_size 4
static uint16_t l_adc_buff[l_adc_count*l_adc_channel_size];

void system_all_gpio_in(void) {
    GPIO_InitTypeDef GPIO_InitStructure;
    //SWD
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All & (~GPIO_Pin_13) & (~GPIO_Pin_14);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;

    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_Init(GPIOE, &GPIO_InitStructure);
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    GPIO_Init(GPIOG, &GPIO_InitStructure);
}

static void system_lcd_init(void) {
    //PC5 LCD_RST
    //PC8 LCD_BACKLIGHT
    {
        GPIO_InitTypeDef GPIO_InitStructure = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

        GPIO_ResetBits(GPIOC, GPIO_Pin_5);
        GPIO_ResetBits(GPIOC, GPIO_Pin_8);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_8;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }

    //FSMC
    GPIO_InitTypeDef GPIO_InitStructure;
    FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef readWriteTiming;
    FSMC_NORSRAMTimingInitTypeDef writeTiming;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE, ENABLE);

    /*
     * PD14  D0
     * PD15  D1
     * PD0   D2
     * PD1   D3
     * PE7   D4
     * PE8   D5
     * PE9   D6
     * PE10  D7
     * PE11  D8
     * PE12  D9
     * PE13  D10
     * PE14  D11
     * PE15  D12
     * PD8   D13
     * PD9   D14
     * PD10  D15
     * PD11  A16
     * PD4   NOW
     * PD5   NWE
     * PD7   NE1
     */

    GPIO_InitStructure.GPIO_Pin =
            GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
            GPIO_Pin_11 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin =
            GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 |
            GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

/*
 * NT35510
 * Address setup time (Write) 0 - ns
 * Address setup time (Read) 10 - ns D/CX
 * Address hole time 2 - ns
 * Data setup time 15 - ns
 * Data hold time 10 - ns
 */

    //144MHZ HCLK 6.9444NS
    readWriteTiming.FSMC_AddressSetupTime = 0x02;
    readWriteTiming.FSMC_AddressHoldTime = 0x01;
    readWriteTiming.FSMC_DataSetupTime = 0x03;
    readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
    readWriteTiming.FSMC_CLKDivision = 0x00;
    readWriteTiming.FSMC_DataLatency = 0x00;
    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;

    writeTiming.FSMC_AddressSetupTime = 0x00;
    writeTiming.FSMC_AddressHoldTime = 0x01;
    writeTiming.FSMC_DataSetupTime = 0x03;
    writeTiming.FSMC_BusTurnAroundDuration = 0x00;
    writeTiming.FSMC_CLKDivision = 0x00;
    writeTiming.FSMC_DataLatency = 0x00;
    writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;

    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;

    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);

    //IO
    {
        //PC5 LCD RST
        //PC8 LCD BACKLIGHT
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

        GPIO_ResetBits(GPIOC, GPIO_Pin_5);
        GPIO_ResetBits(GPIOC, GPIO_Pin_8);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }

    //DMA
    {
/*        DMA_InitTypeDef DMA_InitStructure = {0};
        RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);

        DMA_StructInit(&DMA_InitStructure);
        DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(SRC_BUF);
        DMA_InitStructure.DMA_MemoryBaseAddr = (u32)DST_BUF;
        DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
        DMA_InitStructure.DMA_BufferSize = Buf_Size * 4;
        DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
        DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
        DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
        DMA_InitStructure.DMA_MemoryDataSize = DMA_PeripheralDataSize_Byte;
        DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
        DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
        DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
        DMA_Init(DMA2_Channel1, &DMA_InitStructure);
        DMA_ClearFlag(DMA2_FLAG_TC3);

        DMA_Cmd(DMA1_Channel1, ENABLE);*/
    }
}

void system_lcd_dma(uint32_t dstAddr, uint32_t buffAddr, uint16_t buffSizeHalfWord) {
    DMA_InitTypeDef DMA_InitStructure = {0};
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);

    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.DMA_PeripheralBaseAddr = buffAddr;
    DMA_InitStructure.DMA_MemoryBaseAddr = dstAddr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = buffSizeHalfWord;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
    DMA_Init(DMA2_Channel1, &DMA_InitStructure);
    DMA_ClearFlag(DMA2_FLAG_TC1);
    DMA_ClearFlag(DMA2_FLAG_TE1);
    DMA_ClearFlag(DMA2_FLAG_HT1);

    DMA_Cmd(DMA2_Channel1, ENABLE);
}

static system_irq_cb l_system_pid_timer_cb;
void DMA2_Channel1_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void DMA2_Channel1_IRQHandler(void){
    DMA_ClearITPendingBit(DMA2_IT_TC1);
    DMA_ClearITPendingBit(DMA2_IT_TE1);
    DMA_ClearITPendingBit(DMA2_IT_GL1);
    if(l_system_pid_timer_cb){
        l_system_pid_timer_cb();
    }
}

void system_lcd_dma_it(uint32_t dstAddr, uint32_t buffAddr, uint16_t buffSizeHalfWord,system_irq_cb cb) {
    DMA_Cmd(DMA2_Channel1, DISABLE);
    NVIC_DisableIRQ(DMA2_Channel1_IRQn);
    DMA_ClearFlag(DMA2_FLAG_TC1);
    DMA_ClearFlag(DMA2_FLAG_TE1);
    DMA_ClearFlag(DMA2_FLAG_HT1);
    DMA_ClearFlag(DMA2_FLAG_GL1);
    DMA_ClearITPendingBit(DMA2_IT_TC1);
    DMA_ClearITPendingBit(DMA2_IT_TE1);
    DMA_ClearITPendingBit(DMA2_IT_GL1);
    DMA_DeInit(DMA2_Channel1);

    DMA_InitTypeDef DMA_InitStructure = {0};
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);

    DMA_StructInit(&DMA_InitStructure);
    DMA_InitStructure.DMA_PeripheralBaseAddr = buffAddr;
    DMA_InitStructure.DMA_MemoryBaseAddr = dstAddr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = buffSizeHalfWord;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Enable;
    DMA_Init(DMA2_Channel1, &DMA_InitStructure);

    DMA_ITConfig(DMA2_Channel1, DMA_IT_TE | DMA_IT_TC, ENABLE);

    NVIC_InitTypeDef NVIC_InitStructure = {0};
    NVIC_InitStructure.NVIC_IRQChannel = DMA2_Channel1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    l_system_pid_timer_cb = cb;

    DMA_Cmd(DMA2_Channel1, ENABLE);
}

static void system_gpio_init(void) {
    //PB0 IRON_SWITCH
    //PB1 GUN_SWITCH
    {
        GPIO_InitTypeDef GPIO_InitStructure = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);
    }

    //PE4 GUN_220_CTL
    {
        GPIO_InitTypeDef GPIO_InitStructure = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

        GPIO_ResetBits(GPIOE, GPIO_Pin_4);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOE, &GPIO_InitStructure);
    }

    //PE5 IRON_REED_KEY
    //PE6 IRON_SHAKE_KEY
    {
        GPIO_InitTypeDef GPIO_InitStructure = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOE, &GPIO_InitStructure);
    }

    //PC13 GUN_REED_KEY
    {
        GPIO_InitTypeDef GPIO_InitStructure = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);
    }

    //PD13 TOUCH_RST
    //PD12 TOUCH_IRQ
    {
        GPIO_InitTypeDef GPIO_InitStructure = {0};
        EXTI_InitTypeDef EXTI_InitStructure = {0};
        NVIC_InitTypeDef NVIC_InitStructure = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

        GPIO_ResetBits(GPIOD, GPIO_Pin_13);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);

        GPIO_ResetBits(GPIOD, GPIO_Pin_12);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);

        GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, GPIO_PinSource12);
        EXTI_InitStructure.EXTI_Line = EXTI_Line12;
        EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
        EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
        EXTI_InitStructure.EXTI_LineCmd = ENABLE;
        EXTI_Init(&EXTI_InitStructure);

        NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
        NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 10;
        NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
        NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;
        NVIC_Init(&NVIC_InitStructure);

    }

    //PA10 LED
    {
        GPIO_InitTypeDef GPIO_InitStructure = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

        GPIO_SetBits(GPIOA, GPIO_Pin_10);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
    }

}

static void system_ec11_init(void) {
    //PD2 ROTATE2_KEY
    //PD3 ROTATE1_KEY
    {
        GPIO_InitTypeDef GPIO_InitStructure = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOD, &GPIO_InitStructure);
    }

    //PA8 ROTATE1_A
    //PA9 ROTATE1_B
    {
        GPIO_InitTypeDef GPIO_InitStructure = {0};
        TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};
        TIM_ICInitTypeDef TIM_ICInitStructure = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

        TIM_TimeBaseInitStructure.TIM_Period = 0xFFFF;
        TIM_TimeBaseInitStructure.TIM_Prescaler = 1;
        TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
        TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0x00;
        TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

        TIM_EncoderInterfaceConfig(TIM1, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);

        //输入捕获配置
        TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 | TIM_Channel_2;
        TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;       //输入捕获极性设置，可用于配置编码器正反相
        TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;             //输入捕获预分频器设置
        TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;   //输入捕获通道选择，编码器模式需选用此配置
        TIM_ICInitStructure.TIM_ICFilter = 10;                            //输入捕获滤波器设置
        TIM_ICInit(TIM1, &TIM_ICInitStructure);

        //Reset counter
        TIM_SetCounter(TIM1, 0);

        TIM_Cmd(TIM1, ENABLE);
    }

    //PB3 ROTATE2_A
    //PB4 ROTATE2_B
    {
        GPIO_InitTypeDef GPIO_InitStructure = {0};
        TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};
        TIM_ICInitTypeDef TIM_ICInitStructure = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_TIM10, ENABLE);
        GPIO_PinRemapConfig(GPIO_PartialRemap_TIM10, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

        TIM_TimeBaseInitStructure.TIM_Period = 0xFFFF;
        TIM_TimeBaseInitStructure.TIM_Prescaler = 1;
        TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
        TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0x00;
        TIM_TimeBaseInit(TIM10, &TIM_TimeBaseInitStructure);

        TIM_EncoderInterfaceConfig(TIM10, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);

        //输入捕获配置
        TIM_ICInitStructure.TIM_Channel = TIM_Channel_1 | TIM_Channel_2;
        TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Falling;       //输入捕获极性设置，可用于配置编码器正反相
        TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;             //输入捕获预分频器设置
        TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;   //输入捕获通道选择，编码器模式需选用此配置
        TIM_ICInitStructure.TIM_ICFilter = 10;                            //输入捕获滤波器设置
        TIM_ICInit(TIM10, &TIM_ICInitStructure);

        //Reset counter
        TIM_SetCounter(TIM10, 0);

        TIM_Cmd(TIM10, ENABLE);
    }

}

static void system_spi_flash_init(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    SPI_InitTypeDef SPI_InitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_SPI1, ENABLE);

    GPIO_SetBits(GPIOA, GPIO_Pin_4);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    SPI_Cmd(SPI1, ENABLE);
}

static void system_adc_init(void) {
    //PC1 ADC11 IRON CURRENT
    //PC3 ADC13 DC POWER
    //PA0 ADC0 TEMP1
    //PA1 ADC1 TEMP2
    {
        ADC_InitTypeDef ADC_InitStructure = {0};
        GPIO_InitTypeDef GPIO_InitStructure = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
        RCC_ADCCLKConfig(RCC_PCLK2_Div8);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_Init(GPIOA, &GPIO_InitStructure);

        ADC_DeInit(ADC1);
        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
        ADC_InitStructure.ADC_ScanConvMode = ENABLE;
        ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
        ADC_InitStructure.ADC_NbrOfChannel = 4;
        ADC_Init(ADC1, &ADC_InitStructure);

        ADC_DMACmd(ADC1, ENABLE);
        ADC_Cmd(ADC1, ENABLE);

        ADC_BufferCmd(ADC1, DISABLE);   //disable buffer
        ADC_ResetCalibration(ADC1);
        while (ADC_GetResetCalibrationStatus(ADC1));
        ADC_StartCalibration(ADC1);
        while (ADC_GetCalibrationStatus(ADC1));
        l_adc1_calibrattion_val = Get_CalibrationValue(ADC1);

        ADC_BufferCmd(ADC1, ENABLE);   //enable buffer

        //DMA
        {
            DMA_InitTypeDef DMA_InitStructure = {0};

            RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

            DMA_DeInit(DMA1_Channel1);
            DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t) (&ADC1->RDATAR);
            DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t) l_adc_buff;
            DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
            DMA_InitStructure.DMA_BufferSize = sizeof(l_adc_buff);
            DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
            DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
            DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
            DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
            DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
            DMA_InitStructure.DMA_Priority = DMA_Priority_High;
            DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
            DMA_Init(DMA1_Channel1, &DMA_InitStructure);

            DMA_Cmd(DMA1_Channel1, ENABLE);
        }

        ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 1, ADC_SampleTime_239Cycles5);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_11, 2, ADC_SampleTime_239Cycles5);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 3, ADC_SampleTime_239Cycles5);
        ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 4, ADC_SampleTime_239Cycles5);
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    }
    //PC0 ADC10 IRON TEMP
    //PC2 ADC12 GUN TEMP
    {
        ADC_InitTypeDef ADC_InitStructure = {0};
        GPIO_InitTypeDef GPIO_InitStructure = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
        RCC_ADCCLKConfig(RCC_PCLK2_Div8);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        ADC_DeInit(ADC2);
        ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
        ADC_InitStructure.ADC_ScanConvMode = DISABLE;
        ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
        ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
        ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
        ADC_InitStructure.ADC_NbrOfChannel = 1;
        ADC_Init(ADC2, &ADC_InitStructure);

        ADC_DMACmd(ADC2, ENABLE);
        ADC_Cmd(ADC2, ENABLE);

        ADC_BufferCmd(ADC2, DISABLE);   //disable buffer
        ADC_ResetCalibration(ADC2);
        while (ADC_GetResetCalibrationStatus(ADC2));
        ADC_StartCalibration(ADC2);
        while (ADC_GetCalibrationStatus(ADC2));
        l_adc2_calibrattion_val = Get_CalibrationValue(ADC2);
    }
}

float system_get_voltage_system() {
    int adc_offset = 0;
    float tmp = 0;
    for (int i = 0; i < l_adc_count; i++) {
        tmp = tmp + l_adc_buff[l_adc_channel_size * i + adc_offset];
    }
    tmp = tmp / l_adc_count;

    float res;
    res = tmp + l_adc1_calibrattion_val;
    if (res < 0)
        res = 0;
    if (res > 4095 || tmp == 4095)
        res = 4095;

    int r1 = 10;
    int r2 = 100;
    res = (res / 4095) * 3.3 * (r1 + r2) / r1;

    return res;
}

static float system_get_temp(int adc_offset){
    float tmp = 0;
    for (int i = 0; i < l_adc_count; i++) {
        tmp = tmp + l_adc_buff[l_adc_channel_size * i + adc_offset];
    }
    tmp = tmp / l_adc_count;

    float adcValue;
    adcValue = tmp + l_adc1_calibrattion_val;
    if (adcValue < 0)
        adcValue = 0;
    if (adcValue > 4095 || tmp == 4095)
        adcValue = 4095;

    float resistanceInSeries = 10000.0; //ntc的串联电阻
    float ntcBvalue = 3950.0;  //Bֵ值
    float ntcR25 = 10000.0; //25度时电阻ֵ
    float KelvinsZero = 273.15; //绝对零度
    float T25 = 298.15; //25 =KelvinsZero+25

    float ntcVoltage = adcValue * 3.3 / 4095;
    float ntcCurrent = (3.3 - ntcVoltage) / resistanceInSeries; //计算NTC的电流(A)
    float ntcResistance = ntcVoltage / ntcCurrent; //计算当前电阻值
    float temperature = (ntcBvalue * T25) / (T25 * (log(ntcResistance) - log(ntcR25)) + ntcBvalue);
    temperature -= KelvinsZero; //计算最终温度

    return temperature;
}

float system_get_temp1() {
    return system_get_temp(2);
}

float system_get_temp2() {
    return system_get_temp(3);
}

float system_get_iron_current() {
    int adc_offset = 1;
    float tmp = 0;
    for (int i = 0; i < l_adc_count; i++) {
        tmp = tmp + l_adc_buff[l_adc_channel_size * i + adc_offset];
    }
    tmp = tmp / l_adc_count;

    float adcValue;
    adcValue = tmp + l_adc1_calibrattion_val;
    if (adcValue < 0)
        adcValue = 0;
    if (adcValue > 4095 || tmp == 4095)
        adcValue = 4095;

    float voltage = adcValue * 3.3 / 4095 - 3.3 / 2;
    float current = voltage * 0.11 * -1;
    return current;
}

int system_get_adc_iron_and_gun_sensor(uint16_t *ironAdcValue, uint16_t *gunAdcValue) {
    uint16_t ucErrTime = 0;
    uint16_t maxUcErrTime = 65535;
    int32_t adcV = 0;
    uint16_t adcVMax = 0;
    uint16_t adcVMin = 4095;
    uint16_t tmp16 = 0;
    for (int i = 0; i < 5; i++) {
        ADC_RegularChannelConfig(ADC2, ADC_Channel_10, 1, ADC_SampleTime_71Cycles5);
        ADC_SoftwareStartConvCmd(ADC2, ENABLE);

        ucErrTime = 0;
        while (!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC)) {
            ucErrTime++;
            if (ucErrTime > maxUcErrTime) {
                return -1;
            }
        }
        tmp16 = ADC_GetConversionValue(ADC2);
        adcV += tmp16;
        if (tmp16 > adcVMax) {
            adcVMax = tmp16;
        }
        if (tmp16 < adcVMin) {
            adcVMin = tmp16;
        }
    }
    adcV -= adcVMax;
    adcV -= adcVMin;
    adcV = adcV / 3;
    adcV = adcV + l_adc2_calibrattion_val;
    if (adcV < 0)
        adcV = 0;
    if (adcV > 4095 || adcV == 4095)
        adcV = 4095;
    *ironAdcValue = adcV;

    adcV = 0;
    adcVMax = 0;
    adcVMin = 4095;
    for (int i = 0; i < 5; i++) {
        ADC_RegularChannelConfig(ADC2, ADC_Channel_12, 1, ADC_SampleTime_71Cycles5);
        ADC_SoftwareStartConvCmd(ADC2, ENABLE);

        ucErrTime = 0;
        while (!ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC)) {
            ucErrTime++;
            if (ucErrTime > maxUcErrTime) {
                return -1;
            }
        }
        tmp16 = ADC_GetConversionValue(ADC2);
        adcV += tmp16;
        if (tmp16 > adcVMax) {
            adcVMax = tmp16;
        }
        if (tmp16 < adcVMin) {
            adcVMin = tmp16;
        }
    }
    adcV -= adcVMax;
    adcV -= adcVMin;
    adcV = adcV / 3;
    adcV = adcV + l_adc2_calibrattion_val;
    if (adcV < 0)
        adcV = 0;
    if (adcV > 4095 || adcV == 4095)
        adcV = 4095;
    *gunAdcValue = adcV;

    return 0;
}

static void system_iron_pwm_init(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    TIM_OCInitTypeDef TIM_OCInitStructure = {0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseInitStructure.TIM_Period = 250 - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 960 - 1;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC3Init(TIM2, &TIM_OCInitStructure);

    TIM_CtrlPWMOutputs(TIM2, ENABLE);
    TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig(TIM2, ENABLE);
    TIM_Cmd(TIM2, ENABLE);
}

static void system_gun_pwm_init(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    TIM_OCInitTypeDef TIM_OCInitStructure = {0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    TIM_TimeBaseInitStructure.TIM_Period = 250 - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 14400 - 1;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC4Init(TIM5, &TIM_OCInitStructure);

    TIM_CtrlPWMOutputs(TIM5, ENABLE);
    TIM_OC4PreloadConfig(TIM5, TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig(TIM5, ENABLE);
    TIM_Cmd(TIM5, ENABLE);
}

static void system_pid_timer_init(void) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    TIM_TimeBaseInitStructure.TIM_Period = 200 - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 1440 - 1;
    //TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;
    //TIM_TimeBaseInitStructure.TIM_Prescaler = 14400 - 1;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);

    TIM_ARRPreloadConfig(TIM6, ENABLE);

    TIM_ClearFlag(TIM6, TIM_FLAG_Update);
    TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);

    NVIC_InitTypeDef NVIC_InitStructure = {0};
    NVIC_InitStructure.NVIC_IRQChannel = TIM6_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 5; //抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        //子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

static system_irq_cb l_system_pid_timer_cb;

void system_pid_timer_start(system_irq_cb cb) {
    l_system_pid_timer_cb = cb;
    system_pid_timer_init();
    //TIM_SetCounter(TIM6,0);
    TIM_Cmd(TIM6, ENABLE);
}

void TIM6_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM6_IRQHandler(void) {
    if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET) {
        TIM_ClearFlag(TIM6, TIM_FLAG_Update);
        TIM_ClearITPendingBit(TIM6, TIM_IT_Update);
        TIM_Cmd(TIM6, DISABLE);
        NVIC_DisableIRQ(TIM6_IRQn);
        if (l_system_pid_timer_cb) {
            l_system_pid_timer_cb();
        }
    }
}

static void system_led_and_fan_init(void) {
    //PC7 SYSTEM FAN
    //PC9 IRON LED
    {
        GPIO_InitTypeDef GPIO_InitStructure = {0};
        TIM_OCInitTypeDef TIM_OCInitStructure = {0};
        TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_9;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        TIM_TimeBaseInitStructure.TIM_Period = 500 - 1;
        TIM_TimeBaseInitStructure.TIM_Prescaler = 15 - 1;
        TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
        TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStructure);

        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_Pulse = 0;
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        TIM_OC2Init(TIM8, &TIM_OCInitStructure);
        TIM_OC4Init(TIM8, &TIM_OCInitStructure);

        TIM_CtrlPWMOutputs(TIM8, ENABLE);
        TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Disable);
        TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Disable);
        TIM_ARRPreloadConfig(TIM8, ENABLE);
        TIM_Cmd(TIM8, ENABLE);
    }
    //PC6 GUN FAN
    {
        GPIO_InitTypeDef GPIO_InitStructure = {0};
        TIM_OCInitTypeDef TIM_OCInitStructure = {0};
        TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOC, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
        GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        TIM_TimeBaseInitStructure.TIM_Period = 500 - 1;
        TIM_TimeBaseInitStructure.TIM_Prescaler = 2880 - 1;
        TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
        TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);

        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_Pulse = 0;
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        TIM_OC1Init(TIM3, &TIM_OCInitStructure);

        TIM_CtrlPWMOutputs(TIM3, ENABLE);
        TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Disable);
        TIM_ARRPreloadConfig(TIM3, ENABLE);
        TIM_Cmd(TIM3, ENABLE);
    }
    //PB8 GUN LED
    {
        GPIO_InitTypeDef GPIO_InitStructure = {0};
        TIM_OCInitTypeDef TIM_OCInitStructure = {0};
        TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOB, &GPIO_InitStructure);

        TIM_TimeBaseInitStructure.TIM_Period = 500 - 1;
        TIM_TimeBaseInitStructure.TIM_Prescaler = 15 - 1;
        TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
        TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);

        TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
        TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
        TIM_OCInitStructure.TIM_Pulse = 0;
        TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
        TIM_OC3Init(TIM4, &TIM_OCInitStructure);

        TIM_CtrlPWMOutputs(TIM4, ENABLE);
        TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Disable);
        TIM_ARRPreloadConfig(TIM4, ENABLE);
        TIM_Cmd(TIM4, ENABLE);
    }
}

static void system_buzzer_init(void) {
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    TIM_OCInitTypeDef TIM_OCInitStructure = {0};
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure = {0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    TIM_TimeBaseInitStructure.TIM_Period = 500 - 1;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 328 - 1;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM9, &TIM_TimeBaseInitStructure);

    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC4Init(TIM9, &TIM_OCInitStructure);

    TIM_CtrlPWMOutputs(TIM9, ENABLE);
    TIM_OC4PreloadConfig(TIM9, TIM_OCPreload_Disable);
    TIM_ARRPreloadConfig(TIM9, ENABLE);
    TIM_Cmd(TIM9, ENABLE);
}

void system_set_switch_220_ctl(bool set) {
    if (set) {
        GPIO_SetBits(GPIOE, GPIO_Pin_4);
    } else {
        GPIO_ResetBits(GPIOE, GPIO_Pin_4);
    }
}

bool system_get_switch_rotate1_state() {
    return !GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3);
}

bool system_get_switch_rotate2_state() {
    return !GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2);
}

bool system_get_switch_iron_state() {
    return !GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0);
}

bool system_get_switch_iron_reed_key_state() {
    return !GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5);
}

bool system_get_switch_iron_shake_key_state() {
    return !GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6);
}

bool system_get_switch_gun_state() {
    return !GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1);
}

bool system_get_switch_gun_reed_key_state() {
    return !GPIO_ReadInputDataBit(GPIOC, GPIO_Pin_13);
}

uint16_t system_get_led_max_pwm() {
    return 500;
}

void system_set_led_iron_pwm(uint16_t pwm) {
    TIM_SetCompare4(TIM8, pwm);
}

void system_set_led_gun_pwm(uint16_t pwm) {
    TIM_SetCompare3(TIM4, pwm);
}

uint16_t system_get_fan_max_pwm() {
    return 500;
}

void system_set_fan_system_pwm(uint16_t pwm) {
    TIM_SetCompare2(TIM8, pwm);
}

uint16_t system_get_fan_gun_max_pwm() {
    return 500;
}

uint16_t system_get_fan_gun_min_pwm() {
    return 50;
}

void system_set_fan_gun_pwm(uint16_t pwm) {
    TIM_SetCompare1(TIM3, pwm);
}

uint16_t system_get_iron_pwm() {
    return TIM_GetCapture3(TIM2);
}

void system_set_iron_pwm(uint16_t pwm) {
    TIM_SetCompare3(TIM2, pwm);
}

uint16_t system_get_gun_pwm() {
    return TIM_GetCapture4(TIM5);
}

void system_set_gun_pwm(uint16_t pwm) {
    TIM_SetCompare4(TIM5, pwm);
}

int16_t system_get_encoder1_count() {
    return TIM_GetCounter(TIM1);
}

void system_clear_encoder1_count() {
    TIM_SetCounter(TIM1, 0);
}

int16_t system_get_encoder2_count() {
    return TIM_GetCounter(TIM10);
}

void system_clear_encoder2_count() {
    TIM_SetCounter(TIM10, 0);
}

void system_hardfault_deal(void) {
    {
        system_set_switch_220_ctl(false);
        GPIO_InitTypeDef GPIO_InitStructure = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);

        GPIO_ResetBits(GPIOE, GPIO_Pin_4);
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOE, &GPIO_InitStructure);
        GPIO_ResetBits(GPIOE,GPIO_Pin_4);
    }
    {
        system_set_gun_pwm(0);

        GPIO_InitTypeDef GPIO_InitStructure = {0};

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_ResetBits(GPIOA,GPIO_Pin_3);
    }
    {
        system_set_iron_pwm(0);

        GPIO_InitTypeDef GPIO_InitStructure = {0};
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_Init(GPIOA, &GPIO_InitStructure);
        GPIO_ResetBits(GPIOA,GPIO_Pin_2);
    }
    system_set_fan_gun_pwm(0);
    system_set_fan_system_pwm(0);
}

void system_init(void) {
    //时钟保护
    RCC->CTLR |= RCC_CSSON;

    rtc_init();

    system_gpio_init();

    //system_spi_flash_init();
    system_lcd_init();
    system_buzzer_init();
    system_adc_init();
    system_led_and_fan_init();
    system_ec11_init();
    system_iron_pwm_init();
    system_gun_pwm_init();
}
