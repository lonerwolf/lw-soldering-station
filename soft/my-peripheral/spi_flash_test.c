//
// Created by lonerwolf on 2023/1/7.
//

#include <stdio.h>
#include "spi_flash_test.h"
#include "spi_flash.h"

int test_spi_flash(void){
    printf("test_spi_flash start\r\n");
    SPI_FLASH flash;
    if(spi_flash_init(&flash)){
        printf("spi_flash_init failed\r\n");
    }else{
        printf("spi_flash_init success\r\n");
        printf("spi flash id:%x\r\n",flash.id);
    }
    if(spi_flash_test(&flash)){
        printf("spi_flash_test failed\r\n");
    }else{
        printf("spi_flash_test success\r\n");
    }
    printf("test_spi_flash end\r\n");
}