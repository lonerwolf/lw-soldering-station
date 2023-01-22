//
// Created by lonerwolf on 2023/1/5.
//

#include "spi_flash.h"
#include <stdlib.h>

static uint8_t SPI1_ReadWriteByte(uint8_t TxData)
{
    uint8_t i = 0;

    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET)
    {
        i++;
        if(i > 200)
            return 0;
    }

    SPI_I2S_SendData(SPI1, TxData);
    i = 0;

    while(SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET)
    {
        i++;
        if(i > 200)
            return 0;
    }

    return SPI_I2S_ReceiveData(SPI1);
}

static uint8_t spi_flash_send_byte( uint8_t byte )
{
    return SPI1_ReadWriteByte( byte );
}

static uint8_t spi_flash_read_byte( void )
{
    return SPI1_ReadWriteByte( 0xFF );
}

static uint8_t spi_flash_read_status_reg(void)
{
    uint8_t byte = 0;

    SPI_FLASH_CS_LOW();
    spi_flash_send_byte(SPI_FLASH_CMD_FLASH_RDSR);
    byte = spi_flash_read_byte();
    SPI_FLASH_CS_HIGH();

    return byte;
}

static void spi_flash_wait_busy(void)
{
    while((spi_flash_read_status_reg() & 0x01) == 0x01);
}

static void spi_flash_write_enable( void )
{
    SPI_FLASH_CS_LOW( );
    spi_flash_send_byte( SPI_FLASH_CMD_FLASH_WREN );
    SPI_FLASH_CS_HIGH( );
}

static void spi_flash_write_disable( void )
{
    SPI_FLASH_CS_LOW( );
    spi_flash_send_byte( SPI_FLASH_CMD_FLASH_WRDI );
    SPI_FLASH_CS_HIGH( );
}

void spi_flash_erase_sector(PT_SPI_FLASH handle, uint32_t address )
{
    spi_flash_write_enable( );
    SPI_FLASH_CS_LOW( );
    spi_flash_send_byte( SPI_FLASH_CMD_FLASH_SECTOR_ERASE );
    spi_flash_send_byte( (uint8_t)( address >> 16 ) );
    spi_flash_send_byte( (uint8_t)( address >> 8 ) );
    spi_flash_send_byte( (uint8_t)address );
    SPI_FLASH_CS_HIGH( );
    spi_flash_wait_busy();
}

void spi_flash_erase_chip(PT_SPI_FLASH handle)
{
    spi_flash_write_enable();
    spi_flash_wait_busy();
    SPI_FLASH_CS_LOW( );
    spi_flash_send_byte(SPI_FLASH_CMD_FLASH_CHIP_ERASE);
    SPI_FLASH_CS_HIGH( );
    spi_flash_wait_busy();
}

int spi_flash_read(PT_SPI_FLASH handle,uint32_t readAddr,uint8_t* pBuffer, uint16_t size)
{
    uint16_t i;

    SPI_FLASH_CS_LOW();
    spi_flash_send_byte(SPI_FLASH_CMD_FLASH_READ);
    spi_flash_send_byte((uint8_t)((readAddr) >> 16));
    spi_flash_send_byte((uint8_t)((readAddr) >> 8));
    spi_flash_send_byte((uint8_t)readAddr);

    for(i = 0; i < size; i++)
    {
        pBuffer[i] = spi_flash_read_byte();
    }

    SPI_FLASH_CS_HIGH();
    return 0;
}

static void spi_flash_write_page( PT_SPI_FLASH handle, uint32_t address, uint8_t *pbuf, uint32_t len ) {
    if(len < 1){
        return;
    }

    spi_flash_write_enable();
    SPI_FLASH_CS_LOW();
    spi_flash_send_byte(SPI_FLASH_CMD_FLASH_PAGE_PROG);
    spi_flash_send_byte((uint8_t) (address >> 16));
    spi_flash_send_byte((uint8_t) (address >> 8));
    spi_flash_send_byte((uint8_t) address);
    if (len > handle->page_size) {
        len = handle->page_size;
    }
    for(int i = 0; i < len; i++)
    {
        spi_flash_send_byte(pbuf[i]);
    }
    SPI_FLASH_CS_HIGH();
    spi_flash_wait_busy();
}

void spi_flash_write_noCheck(PT_SPI_FLASH handle,uint32_t writeAddr,uint8_t *pBuffer, uint16_t size){
    uint16_t pageremain;

    pageremain = handle->page_size - writeAddr % handle->page_size;

    if(size <= pageremain)
        pageremain = size;

    while(1)
    {
        spi_flash_write_page(handle,writeAddr,pBuffer,  pageremain);

        if(size == pageremain)
        {
            break;
        }
        else
        {
            pBuffer += pageremain;
            writeAddr += pageremain;
            size -= pageremain;

            if(size > handle->page_size)
                pageremain = handle->page_size;
            else
                pageremain = size;
        }
    }
}

int spi_flash_write(PT_SPI_FLASH handle,uint32_t writeAddr,uint8_t *pBuffer, uint16_t size){
    uint32_t secpos;
    uint16_t secoff;
    uint16_t secremain;
    uint16_t i = 0;

    secpos = writeAddr / handle->sector_size;//所在扇区
    secoff = writeAddr % handle->sector_size;//扇区内偏移地址
    secremain = handle->sector_size - secoff;//扇区除去偏移，剩余扇区空间大小

    if(size <= secremain) //写入数据大小，小于剩余扇区空间大小
        secremain = size;

    while(1)
    {
        spi_flash_read(handle,secpos * handle->sector_size,handle->sector_buff, handle->sector_size);

        for(i=0;i<secremain;i++){
            if(handle->sector_buff[secoff+i] != 0xFF){//需要擦除
                break;
            }
        }
        if(i<secremain){//需要擦除
            spi_flash_erase_sector(handle,secpos*handle->sector_size);
            for(i=0;i<secremain;i++){
                handle->sector_buff[secoff+i] = pBuffer[i];
            }
            spi_flash_write_noCheck(handle,writeAddr,pBuffer,secremain);
        }else{
            spi_flash_write_noCheck(handle,writeAddr,pBuffer,secremain);
        }
        if(size == secremain)
        {
            break;
        }
        else
        {
            secpos++;
            secoff = 0;

            pBuffer += secremain;
            writeAddr += secremain;
            size -= secremain;

            if(size > handle->sector_size)
            {
                secremain = handle->sector_size;
            }
            else
            {
                secremain = size;
            }
        }
    }
    return 0;
}

static uint32_t spi_flash_read_id(void){
    uint32_t dat;
    SPI_FLASH_CS_LOW();
    spi_flash_send_byte( SPI_FLASH_CMD_FLASH_JEDEC_ID );
    dat = ( uint32_t )spi_flash_read_byte() << 16;
    dat |= ( uint32_t )spi_flash_read_byte( ) << 8;
    dat |= spi_flash_read_byte( );
    SPI_FLASH_CS_HIGH();
    return( dat );
}

int spi_flash_init(PT_SPI_FLASH handle){
    uint32_t id = spi_flash_read_id();
    switch (id) {
        case SPI_FLASH_TYPE_GD32Q128://GD32Q128
            handle->sector_count = 4096;
            handle->sector_size = 4096;
            handle->page_count = handle->sector_count*16;
            handle->page_size = 256;
            break;
        default:
            return -1;
    }
    handle->capacity = handle->sector_count*handle->sector_size;
    handle->capacity_K = handle->capacity / 1024;
    handle->capacity_M = (float)(handle->capacity_K) / 1024;
    handle->id = id;
    return 0;
}

int spi_flash_test(PT_SPI_FLASH handle){
    uint8_t* buff1 = malloc(SPI_FLASH_TEST_BUFF_SIZE);
    if(!buff1){
        return -1;
    }
    uint8_t* buff2 = malloc(SPI_FLASH_TEST_BUFF_SIZE);
    if(!buff2){
        free(buff1);
        return -1;
    }

    for(int i = 0; i < SPI_FLASH_TEST_BUFF_SIZE;i++){
        buff1[i] = i;
    }
    spi_flash_write(handle,0,buff1,SPI_FLASH_TEST_BUFF_SIZE);
    spi_flash_read(handle,0,buff2,SPI_FLASH_TEST_BUFF_SIZE);
    for(int i = 0; i < SPI_FLASH_TEST_BUFF_SIZE;i++){
        if(buff1[i] != buff2[i]){
            return -1;
        }
    }
    free(buff1);
    free(buff2);
    return 0;
}


