//
// Created by lonerwolf on 2023/1/5.
//

#ifndef _SPI_FLASH_H
#define _SPI_FLASH_H

#include <stdint.h>

#include "ch32v30x_conf.h"

//修改片选与读写函数,注意sector_buff大小，需要和sector一样大

#define SPI_FLASH_CS_LOW( )       GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define SPI_FLASH_CS_HIGH( )      GPIO_SetBits(GPIOA,GPIO_Pin_4)

#define SPI_FLASH_TEST_BUFF_SIZE 4096

/******************************************************************************/
/* SPI Serial Flash OPERATION INSTRUCTIONS */
#define SPI_FLASH_CMD_FLASH_READ             0x03                                         /* Read Memory at 25 MHz */
#define SPI_FLASH_CMD_FLASH_CHIP_ERASE       0xC7
#define SPI_FLASH_CMD_FLASH_BLOCK_ERASE      0xD8
#define SPI_FLASH_CMD_FLASH_SECTOR_ERASE     0x20                                         /* Erase 4 KByte of memory array */
#define SPI_FLASH_CMD_FLASH_PAGE_PROG        0x02                                         /* To Program One Data Byte */
#define SPI_FLASH_CMD_FLASH_RDSR             0x05                                         /* Read-Status-Register */
#define SPI_FLASH_CMD_FLASH_EWSR             0x50                                         /* Enable-Write-Status-Register */
#define SPI_FLASH_CMD_FLASH_WREN             0x06                                         /* Write-Enable */
#define SPI_FLASH_CMD_FLASH_WRDI             0x04                                         /* Write-Disable */
#define SPI_FLASH_CMD_FLASH_JEDEC_ID         0x9F                                         /* JEDEC ID read */

typedef enum _spi_flash_type{
    SPI_FLASH_TYPE_GD32Q128 = 0xC84018,
}SPI_FLASH_TYPE;

typedef struct _spi_flash{
    uint8_t sector_buff[4096];
    uint32_t id;
    uint32_t sector_size;
    uint32_t sector_count;
    uint32_t page_size;
    uint32_t page_count;
    uint32_t capacity;
    uint32_t capacity_K;
    float capacity_M;
}SPI_FLASH,*PT_SPI_FLASH;

int spi_flash_init(PT_SPI_FLASH handle);
int spi_flash_read(PT_SPI_FLASH handle,uint32_t readAddr,uint8_t *pBuffer, uint16_t size);
int spi_flash_write(PT_SPI_FLASH handle,uint32_t writeAddr,uint8_t *pBuffer, uint16_t size);
void spi_flash_erase_chip(PT_SPI_FLASH handle);
void spi_flash_erase_sector(PT_SPI_FLASH handle, uint32_t address);
int spi_flash_test(PT_SPI_FLASH handle);
#endif //_SPI_FLASH_H
