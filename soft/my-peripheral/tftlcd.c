//
// Created by lonerwolf on 2023/1/1.
//

#include "tftlcd.h"

static void tftlcd_wr_reg(uint16_t cmd){
    cmd = cmd;
    TFTLCD->REG = cmd;
}

static void tftlcd_wr_data(uint16_t data){
    data = data;
    TFTLCD->RAM = data;
}

static uint16_t tftlcd_rd_reg(uint16_t cmd){
    cmd = cmd;
    TFTLCD->REG = cmd;
    volatile uint16_t res;
    res = TFTLCD->RAM;
    return res;
}

static uint16_t tftlcd_rd_data(void){
    volatile uint16_t res;
    res = TFTLCD->RAM;
    return res;
}

void tftlcd_write_ram_prepare(PT_TFTLCD_DEV handle)
{
    tftlcd_wr_reg(handle->wram_cmd);
}

//设置光标位置
//Xpos:横坐标
//Ypos:纵坐标
void tftlcd_set_cursor(PT_TFTLCD_DEV handle,uint16_t Xpos, uint16_t Ypos)
{
    tftlcd_wr_reg(handle->setx_cmd);
    tftlcd_wr_data(Xpos>>8);
    tftlcd_wr_reg(handle->setx_cmd+1);
    tftlcd_wr_data(Xpos&0xff);

    tftlcd_wr_reg(handle->sety_cmd);
    tftlcd_wr_data(Ypos>>8);
    tftlcd_wr_reg(handle->sety_cmd+1);
    tftlcd_wr_data(Ypos&0xff);
}

void tftlcd_set_window(PT_TFTLCD_DEV handle,uint16_t sx, uint16_t sy, uint16_t width, uint16_t height){
    uint16_t twidth, theight;
    twidth = sx + width - 1;
    theight = sy + height - 1;
    tftlcd_wr_reg(handle->setx_cmd);
    tftlcd_wr_data(sx >> 8);
    tftlcd_wr_reg(handle->setx_cmd + 1);
    tftlcd_wr_data(sx & 0XFF);
    tftlcd_wr_reg(handle->setx_cmd + 2);
    tftlcd_wr_data(twidth >> 8);
    tftlcd_wr_reg(handle->setx_cmd + 3);
    tftlcd_wr_data(twidth & 0XFF);
    tftlcd_wr_reg(handle->sety_cmd);
    tftlcd_wr_data(sy >> 8);
    tftlcd_wr_reg(handle->sety_cmd + 1);
    tftlcd_wr_data(sy & 0XFF);
    tftlcd_wr_reg(handle->sety_cmd + 2);
    tftlcd_wr_data(theight >> 8);
    tftlcd_wr_reg(handle->sety_cmd + 3);
    tftlcd_wr_data(theight & 0XFF);
}

void tftlcd_set_rect(PT_TFTLCD_DEV handle,uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2){
    tftlcd_wr_reg(handle->setx_cmd);
    tftlcd_wr_data(x1 >> 8);
    tftlcd_wr_reg(handle->setx_cmd + 1);
    tftlcd_wr_data(x1 & 0XFF);
    tftlcd_wr_reg(handle->setx_cmd + 2);
    tftlcd_wr_data(x2 >> 8);
    tftlcd_wr_reg(handle->setx_cmd + 3);
    tftlcd_wr_data(x2 & 0XFF);
    tftlcd_wr_reg(handle->sety_cmd);
    tftlcd_wr_data(y1 >> 8);
    tftlcd_wr_reg(handle->sety_cmd + 1);
    tftlcd_wr_data(y1 & 0XFF);
    tftlcd_wr_reg(handle->sety_cmd + 2);
    tftlcd_wr_data(y2 >> 8);
    tftlcd_wr_reg(handle->sety_cmd + 3);
    tftlcd_wr_data(y2 & 0XFF);
}

static void tftlcd_set_dir(PT_TFTLCD_DEV handle,uint8_t dir){
    uint16_t regval = 0;
    uint16_t dirreg = 0;
    switch (dir)
    {
        case TFTLCD_SCAN_DIR_L2R_U2D: //从左到右,从上到下
            regval |= (0 << 7) | (0 << 6) | (0 << 5);
            tftlcd_set_window(handle,0,0,handle->width,handle->height);
            break;
        case TFTLCD_SCAN_DIR_L2R_D2U: //从左到右,从下到上
            regval |= (1 << 7) | (0 << 6) | (0 << 5);
            tftlcd_set_window(handle,0,0,handle->width,handle->height);
            break;
        case TFTLCD_SCAN_DIR_R2L_U2D: //从右到左,从上到下
            regval |= (0 << 7) | (1 << 6) | (0 << 5);
            tftlcd_set_window(handle,0,0,handle->width,handle->height);
            break;
        case TFTLCD_SCAN_DIR_R2L_D2U: //从右到左,从下到上
            regval |= (1 << 7) | (1 << 6) | (0 << 5);
            tftlcd_set_window(handle,0,0,handle->width,handle->height);
            break;
        case TFTLCD_SCAN_DIR_U2D_L2R: //从上到下,从左到右
            regval |= (0 << 7) | (0 << 6) | (1 << 5);
            tftlcd_set_window(handle,0,0,handle->height,handle->width);
            break;
        case TFTLCD_SCAN_DIR_U2D_R2L: //从上到下,从右到左
            regval |= (0 << 7) | (1 << 6) | (1 << 5);
            tftlcd_set_window(handle,0,0,handle->height,handle->width);
            break;
        case TFTLCD_SCAN_DIR_D2U_L2R: //从下到上,从左到右
            regval |= (1 << 7) | (0 << 6) | (1 << 5);
            tftlcd_set_window(handle,0,0,handle->height,handle->width);
            break;
        case TFTLCD_SCAN_DIR_D2U_R2L: //从下到上,从右到左
            regval |= (1 << 7) | (1 << 6) | (1 << 5);
            tftlcd_set_window(handle,0,0,handle->height,handle->width);
            break;
    }
    tftlcd_wr_reg(0x3600);
    tftlcd_wr_data(regval);
}

//清屏函数
//color:要清屏的填充色
void tftlcd_clear(PT_TFTLCD_DEV handle,uint16_t color)
{
    u32 index = 0;
    u32 totalpoint = handle->width;
    totalpoint *= handle->height; //得到总点数
    // printf("width: %d height: %d and: %d cmd: %x\n",WIDTH,HEIGHT,totalpoint,WRAMCMD);
    tftlcd_set_cursor(handle,0x00, 0x00); //设置光标位置
    tftlcd_write_ram_prepare(handle);		 //开始写入GRAM

    // printf("Color: %x\r\n",color);
    for (index = 0; index < totalpoint; index++)
    {
        tftlcd_wr_data(color);
    }
}

int tftlcd_init(PT_TFTLCD_DEV handle){
    TFTLCD_RST_INACTIVE();
    tftlcd_delay_ms(50);
    TFTLCD_RST_ACTIVE();
    tftlcd_delay_ms(200);
    TFTLCD_RST_INACTIVE();
    tftlcd_delay_ms(50);

    handle->width = 480;
    handle->height = 800;
    handle->id = 0x5510;
    handle->dir = TFTLCD_DIR_VDIR;
    handle->setx_cmd = 0x2A00;
    handle->sety_cmd = 0x2B00;
    handle->wram_cmd = 0x2C00;

/*    uint16_t tmp;
    tftlcd_wr_reg(0xDA00);
    tmp = tftlcd_rd_data();
    printf("tmp:%x\n",tmp);
    tftlcd_wr_reg(0xDB00);
    tmp = tftlcd_rd_data();
    printf("tmp:%x\n",tmp);
    tftlcd_wr_reg(0xDC00);
    tmp = tftlcd_rd_data();
    printf("tmp:%x\n",tmp);*/


    //Enable Page1                                 
    tftlcd_wr_reg(0xF000);tftlcd_wr_data(0x55);
    tftlcd_wr_reg(0xF001);tftlcd_wr_data(0xaa);
    tftlcd_wr_reg(0xF002);tftlcd_wr_data(0x52);
    tftlcd_wr_reg(0xF003);tftlcd_wr_data(0x08);
    tftlcd_wr_reg(0xF004);tftlcd_wr_data(0x01);

    // AVDD: manual,                                
    tftlcd_wr_reg(0xB600);tftlcd_wr_data(0x34);
    tftlcd_wr_reg(0xB601);tftlcd_wr_data(0x34);
    tftlcd_wr_reg(0xB602);tftlcd_wr_data(0x34);
    tftlcd_wr_reg(0xB000);tftlcd_wr_data(0x09);
    tftlcd_wr_reg(0xB001);tftlcd_wr_data(0x09);
    tftlcd_wr_reg(0xB002);tftlcd_wr_data(0x09);

    // AVEE: manual,       ‐‐6V

    tftlcd_wr_reg(0xB700);tftlcd_wr_data(0x24);
    tftlcd_wr_reg(0xB701);tftlcd_wr_data(0x24);
    tftlcd_wr_reg(0xB702);tftlcd_wr_data(0x24);
    tftlcd_wr_reg(0xB100);tftlcd_wr_data(0x09);
    tftlcd_wr_reg(0xB101);tftlcd_wr_data(0x09);
    tftlcd_wr_reg(0xB102);tftlcd_wr_data(0x90);

    //Power Control for VCL                         
    tftlcd_wr_reg(0xB800);tftlcd_wr_data(0x34);
    tftlcd_wr_reg(0xB200);tftlcd_wr_data(0x00);

    // VGH: Clamp Enable,                           
    tftlcd_wr_reg(0xB900);tftlcd_wr_data(0x24);
    tftlcd_wr_reg(0xB901);tftlcd_wr_data(0x24);
    tftlcd_wr_reg(0xB902);tftlcd_wr_data(0x24);
    tftlcd_wr_reg(0xB300);tftlcd_wr_data(0x05);
    tftlcd_wr_reg(0xB301);tftlcd_wr_data(0x05);
    tftlcd_wr_reg(0xB302);tftlcd_wr_data(0x05);

    tftlcd_wr_reg(0xBF00);tftlcd_wr_data(0x01);

    // VGL(LVGL)                                       
    tftlcd_wr_reg(0xBA00);tftlcd_wr_data(0x34 );
    tftlcd_wr_reg(0xBA01);tftlcd_wr_data(0x34 );
    tftlcd_wr_reg(0xBA02);tftlcd_wr_data(0x34 );

    // VGL_REG(VGLO)                                   
    tftlcd_wr_reg(0xB500);tftlcd_wr_data(0x0B );
    tftlcd_wr_reg(0xB501);tftlcd_wr_data(0x0B );
    tftlcd_wr_reg(0xB502);tftlcd_wr_data(0x0B );

    // VGMP/VGSP                                       
    tftlcd_wr_reg(0xBC00);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xBC01);tftlcd_wr_data(0xA3 );
    tftlcd_wr_reg(0xBC02);tftlcd_wr_data(0x00 );

    //VGMN/VGSN                                        
    tftlcd_wr_reg(0xBD00);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xBD01);tftlcd_wr_data(0xA3 );
    tftlcd_wr_reg(0xBD02);tftlcd_wr_data(0x00 );

    // VCOM= ‐‐0.1
    tftlcd_wr_reg(0xBE00);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xBE01);tftlcd_wr_data(0x50 );

    //R+                                               
    tftlcd_wr_reg(0xD100);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD101);tftlcd_wr_data(0x37 );
    tftlcd_wr_reg(0xD102);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD103);tftlcd_wr_data(0x52 );
    tftlcd_wr_reg(0xD104);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD105);tftlcd_wr_data(0x7B );
    tftlcd_wr_reg(0xD106);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD107);tftlcd_wr_data(0x99 );
    tftlcd_wr_reg(0xD108);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD109);tftlcd_wr_data(0xB1 );
    tftlcd_wr_reg(0xD10A);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD10B);tftlcd_wr_data(0xD2 );
    tftlcd_wr_reg(0xD10C);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD10D);tftlcd_wr_data(0xF6 );
    tftlcd_wr_reg(0xD10E);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD10F);tftlcd_wr_data(0x27 );
    tftlcd_wr_reg(0xD110);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD111);tftlcd_wr_data(0x4E );
    tftlcd_wr_reg(0xD112);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD113);tftlcd_wr_data(0x8C );
    tftlcd_wr_reg(0xD114);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD115);tftlcd_wr_data(0xBE );
    tftlcd_wr_reg(0xD116);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD117);tftlcd_wr_data(0x0B );
    tftlcd_wr_reg(0xD118);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD119);tftlcd_wr_data(0x48 );
    tftlcd_wr_reg(0xD11A);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD11B);tftlcd_wr_data(0x4A );
    tftlcd_wr_reg(0xD11C);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD11D);tftlcd_wr_data(0x7E );
    tftlcd_wr_reg(0xD11E);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD11F);tftlcd_wr_data(0xBC );
    tftlcd_wr_reg(0xD120);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD121);tftlcd_wr_data(0xE1 );
    tftlcd_wr_reg(0xD122);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD123);tftlcd_wr_data(0x10 );
    tftlcd_wr_reg(0xD124);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD125);tftlcd_wr_data(0x31 );
    tftlcd_wr_reg(0xD126);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD127);tftlcd_wr_data(0x5A );
    tftlcd_wr_reg(0xD128);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD129);tftlcd_wr_data(0x73 );
    tftlcd_wr_reg(0xD12A);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD12B);tftlcd_wr_data(0x94 );
    tftlcd_wr_reg(0xD12C);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD12D);tftlcd_wr_data(0x9F );
    tftlcd_wr_reg(0xD12E);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD12F);tftlcd_wr_data(0xB3 );
    tftlcd_wr_reg(0xD130);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD131);tftlcd_wr_data(0xB9 );
    tftlcd_wr_reg(0xD132);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD133);tftlcd_wr_data(0xC1 );

    //G+                                               
    tftlcd_wr_reg(0xD200);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD201);tftlcd_wr_data(0x37 );
    tftlcd_wr_reg(0xD202);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD203);tftlcd_wr_data(0x52 );
    tftlcd_wr_reg(0xD204);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD205);tftlcd_wr_data(0x7B );
    tftlcd_wr_reg(0xD206);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD207);tftlcd_wr_data(0x99 );
    tftlcd_wr_reg(0xD208);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD209);tftlcd_wr_data(0xB1 );
    tftlcd_wr_reg(0xD20A);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD20B);tftlcd_wr_data(0xD2 );
    tftlcd_wr_reg(0xD20C);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD20D);tftlcd_wr_data(0xF6 );
    tftlcd_wr_reg(0xD20E);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD20F);tftlcd_wr_data(0x27 );
    tftlcd_wr_reg(0xD210);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD211);tftlcd_wr_data(0x4E );
    tftlcd_wr_reg(0xD212);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD213);tftlcd_wr_data(0x8C );
    tftlcd_wr_reg(0xD214);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD215);tftlcd_wr_data(0xBE );
    tftlcd_wr_reg(0xD216);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD217);tftlcd_wr_data(0x0B );
    tftlcd_wr_reg(0xD218);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD219);tftlcd_wr_data(0x48 );
    tftlcd_wr_reg(0xD21A);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD21B);tftlcd_wr_data(0x4A );
    tftlcd_wr_reg(0xD21C);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD21D);tftlcd_wr_data(0x7E );
    tftlcd_wr_reg(0xD21E);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD21F);tftlcd_wr_data(0xBC );
    tftlcd_wr_reg(0xD220);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD221);tftlcd_wr_data(0xE1 );
    tftlcd_wr_reg(0xD222);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD223);tftlcd_wr_data(0x10 );
    tftlcd_wr_reg(0xD224);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD225);tftlcd_wr_data(0x31 );
    tftlcd_wr_reg(0xD226);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD227);tftlcd_wr_data(0x5A );
    tftlcd_wr_reg(0xD228);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD229);tftlcd_wr_data(0x73 );
    tftlcd_wr_reg(0xD22A);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD22B);tftlcd_wr_data(0x94 );
    tftlcd_wr_reg(0xD22C);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD22D);tftlcd_wr_data(0x9F );
    tftlcd_wr_reg(0xD22E);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD22F);tftlcd_wr_data(0xB3 );
    tftlcd_wr_reg(0xD230);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD231);tftlcd_wr_data(0xB9 );
    tftlcd_wr_reg(0xD232);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD233);tftlcd_wr_data(0xC1 );

    //B+                                               
    tftlcd_wr_reg(0xD300);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD301);tftlcd_wr_data(0x37 );
    tftlcd_wr_reg(0xD302);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD303);tftlcd_wr_data(0x52 );
    tftlcd_wr_reg(0xD304);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD305);tftlcd_wr_data(0x7B );
    tftlcd_wr_reg(0xD306);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD307);tftlcd_wr_data(0x99 );
    tftlcd_wr_reg(0xD308);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD309);tftlcd_wr_data(0xB1 );
    tftlcd_wr_reg(0xD30A);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD30B);tftlcd_wr_data(0xD2 );
    tftlcd_wr_reg(0xD30C);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD30D);tftlcd_wr_data(0xF6 );
    tftlcd_wr_reg(0xD30E);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD30F);tftlcd_wr_data(0x27 );
    tftlcd_wr_reg(0xD310);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD311);tftlcd_wr_data(0x4E );
    tftlcd_wr_reg(0xD312);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD313);tftlcd_wr_data(0x8C );
    tftlcd_wr_reg(0xD314);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD315);tftlcd_wr_data(0xBE );
    tftlcd_wr_reg(0xD316);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD317);tftlcd_wr_data(0x0B );
    tftlcd_wr_reg(0xD318);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD319);tftlcd_wr_data(0x48 );
    tftlcd_wr_reg(0xD31A);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD31B);tftlcd_wr_data(0x4A );
    tftlcd_wr_reg(0xD31C);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD31D);tftlcd_wr_data(0x7E );
    tftlcd_wr_reg(0xD31E);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD31F);tftlcd_wr_data(0xBC );
    tftlcd_wr_reg(0xD320);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD321);tftlcd_wr_data(0xE1 );
    tftlcd_wr_reg(0xD322);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD323);tftlcd_wr_data(0x10 );
    tftlcd_wr_reg(0xD324);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD325);tftlcd_wr_data(0x31 );
    tftlcd_wr_reg(0xD326);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD327);tftlcd_wr_data(0x5A );
    tftlcd_wr_reg(0xD328);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD329);tftlcd_wr_data(0x73 );
    tftlcd_wr_reg(0xD32A);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD32B);tftlcd_wr_data(0x94 );
    tftlcd_wr_reg(0xD32C);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD32D);tftlcd_wr_data(0x9F );
    tftlcd_wr_reg(0xD32E);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD32F);tftlcd_wr_data(0xB3 );
    tftlcd_wr_reg(0xD330);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD331);tftlcd_wr_data(0xB9 );
    tftlcd_wr_reg(0xD332);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD333);tftlcd_wr_data(0xC1 );

    //R-                                               
    tftlcd_wr_reg(0xD400);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD401);tftlcd_wr_data(0x37 );
    tftlcd_wr_reg(0xD402);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD403);tftlcd_wr_data(0x52 );
    tftlcd_wr_reg(0xD404);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD405);tftlcd_wr_data(0x7B );
    tftlcd_wr_reg(0xD406);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD407);tftlcd_wr_data(0x99 );
    tftlcd_wr_reg(0xD408);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD409);tftlcd_wr_data(0xB1 );
    tftlcd_wr_reg(0xD40A);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD40B);tftlcd_wr_data(0xD2 );
    tftlcd_wr_reg(0xD40C);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD40D);tftlcd_wr_data(0xF6 );
    tftlcd_wr_reg(0xD40E);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD40F);tftlcd_wr_data(0x27 );
    tftlcd_wr_reg(0xD410);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD411);tftlcd_wr_data(0x4E );
    tftlcd_wr_reg(0xD412);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD413);tftlcd_wr_data(0x8C );
    tftlcd_wr_reg(0xD414);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD415);tftlcd_wr_data(0xBE );
    tftlcd_wr_reg(0xD416);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD417);tftlcd_wr_data(0x0B );
    tftlcd_wr_reg(0xD418);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD419);tftlcd_wr_data(0x48 );
    tftlcd_wr_reg(0xD41A);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD41B);tftlcd_wr_data(0x4A );
    tftlcd_wr_reg(0xD41C);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD41D);tftlcd_wr_data(0x7E );
    tftlcd_wr_reg(0xD41E);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD41F);tftlcd_wr_data(0xBC );
    tftlcd_wr_reg(0xD420);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD421);tftlcd_wr_data(0xE1 );
    tftlcd_wr_reg(0xD422);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD423);tftlcd_wr_data(0x10 );
    tftlcd_wr_reg(0xD424);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD425);tftlcd_wr_data(0x31 );
    tftlcd_wr_reg(0xD426);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD427);tftlcd_wr_data(0x5A );
    tftlcd_wr_reg(0xD428);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD429);tftlcd_wr_data(0x73 );
    tftlcd_wr_reg(0xD42A);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD42B);tftlcd_wr_data(0x94 );
    tftlcd_wr_reg(0xD42C);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD42D);tftlcd_wr_data(0x9F );
    tftlcd_wr_reg(0xD42E);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD42F);tftlcd_wr_data(0xB3 );
    tftlcd_wr_reg(0xD430);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD431);tftlcd_wr_data(0xB9 );
    tftlcd_wr_reg(0xD432);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD433);tftlcd_wr_data(0xC1 );

    //G-                                               
    tftlcd_wr_reg(0xD500);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD501);tftlcd_wr_data(0x37 );
    tftlcd_wr_reg(0xD502);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD503);tftlcd_wr_data(0x52 );
    tftlcd_wr_reg(0xD504);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD505);tftlcd_wr_data(0x7B );
    tftlcd_wr_reg(0xD506);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD507);tftlcd_wr_data(0x99 );
    tftlcd_wr_reg(0xD508);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD509);tftlcd_wr_data(0xB1 );
    tftlcd_wr_reg(0xD50A);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD50B);tftlcd_wr_data(0xD2 );
    tftlcd_wr_reg(0xD50C);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD50D);tftlcd_wr_data(0xF6 );
    tftlcd_wr_reg(0xD50E);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD50F);tftlcd_wr_data(0x27 );
    tftlcd_wr_reg(0xD510);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD511);tftlcd_wr_data(0x4E );
    tftlcd_wr_reg(0xD512);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD513);tftlcd_wr_data(0x8C );
    tftlcd_wr_reg(0xD514);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD515);tftlcd_wr_data(0xBE );
    tftlcd_wr_reg(0xD516);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD517);tftlcd_wr_data(0x0B );
    tftlcd_wr_reg(0xD518);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD519);tftlcd_wr_data(0x48 );
    tftlcd_wr_reg(0xD51A);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD51B);tftlcd_wr_data(0x4A );
    tftlcd_wr_reg(0xD51C);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD51D);tftlcd_wr_data(0x7E );
    tftlcd_wr_reg(0xD51E);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD51F);tftlcd_wr_data(0xBC );
    tftlcd_wr_reg(0xD520);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD521);tftlcd_wr_data(0xE1 );
    tftlcd_wr_reg(0xD522);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD523);tftlcd_wr_data(0x10 );
    tftlcd_wr_reg(0xD524);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD525);tftlcd_wr_data(0x31 );
    tftlcd_wr_reg(0xD526);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD527);tftlcd_wr_data(0x5A );
    tftlcd_wr_reg(0xD528);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD529);tftlcd_wr_data(0x73 );
    tftlcd_wr_reg(0xD52A);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD52B);tftlcd_wr_data(0x94 );
    tftlcd_wr_reg(0xD52C);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD52D);tftlcd_wr_data(0x9F );
    tftlcd_wr_reg(0xD52E);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD52F);tftlcd_wr_data(0xB3 );
    tftlcd_wr_reg(0xD530);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD531);tftlcd_wr_data(0xB9 );
    tftlcd_wr_reg(0xD532);tftlcd_wr_data(0x03 );
    tftlcd_wr_reg(0xD533);tftlcd_wr_data(0xC1 );

    //B-                                               
    tftlcd_wr_reg(0xD600);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD601);tftlcd_wr_data(0x37 );
    tftlcd_wr_reg(0xD602);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD603);tftlcd_wr_data(0x52 );
    tftlcd_wr_reg(0xD604);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD605);tftlcd_wr_data(0x7B );
    tftlcd_wr_reg(0xD606);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD607);tftlcd_wr_data(0x99 );
    tftlcd_wr_reg(0xD608);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD609);tftlcd_wr_data(0xB1 );
    tftlcd_wr_reg(0xD60A);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD60B);tftlcd_wr_data(0xD2 );
    tftlcd_wr_reg(0xD60C);tftlcd_wr_data(0x00 );
    tftlcd_wr_reg(0xD60D);tftlcd_wr_data(0xF6 );
    tftlcd_wr_reg(0xD60E);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD60F);tftlcd_wr_data(0x27 );
    tftlcd_wr_reg(0xD610);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD611);tftlcd_wr_data(0x4E );
    tftlcd_wr_reg(0xD612);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD613);tftlcd_wr_data(0x8C );
    tftlcd_wr_reg(0xD614);tftlcd_wr_data(0x01 );
    tftlcd_wr_reg(0xD615);tftlcd_wr_data(0xBE );
    tftlcd_wr_reg(0xD616);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD617);tftlcd_wr_data(0x0B );
    tftlcd_wr_reg(0xD618);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD619);tftlcd_wr_data(0x48 );
    tftlcd_wr_reg(0xD61A);tftlcd_wr_data(0x02 );
    tftlcd_wr_reg(0xD61B);tftlcd_wr_data(0x4A );
    tftlcd_wr_reg(0xD61C);tftlcd_wr_data(0x02);
    tftlcd_wr_reg(0xD61D);tftlcd_wr_data(0x7E);
    tftlcd_wr_reg(0xD61E);tftlcd_wr_data(0x02);
    tftlcd_wr_reg(0xD61F);tftlcd_wr_data(0xBC);
    tftlcd_wr_reg(0xD620);tftlcd_wr_data(0x02);
    tftlcd_wr_reg(0xD621);tftlcd_wr_data(0xE1);
    tftlcd_wr_reg(0xD622);tftlcd_wr_data(0x03);
    tftlcd_wr_reg(0xD623);tftlcd_wr_data(0x10);
    tftlcd_wr_reg(0xD624);tftlcd_wr_data(0x03);
    tftlcd_wr_reg(0xD625);tftlcd_wr_data(0x31);
    tftlcd_wr_reg(0xD626);tftlcd_wr_data(0x03);
    tftlcd_wr_reg(0xD627);tftlcd_wr_data(0x5A);
    tftlcd_wr_reg(0xD628);tftlcd_wr_data(0x03);
    tftlcd_wr_reg(0xD629);tftlcd_wr_data(0x73);
    tftlcd_wr_reg(0xD62A);tftlcd_wr_data(0x03);
    tftlcd_wr_reg(0xD62B);tftlcd_wr_data(0x94);
    tftlcd_wr_reg(0xD62C);tftlcd_wr_data(0x03);
    tftlcd_wr_reg(0xD62D);tftlcd_wr_data(0x9F);
    tftlcd_wr_reg(0xD62E);tftlcd_wr_data(0x03);
    tftlcd_wr_reg(0xD62F);tftlcd_wr_data(0xB3);
    tftlcd_wr_reg(0xD630);tftlcd_wr_data(0x03);
    tftlcd_wr_reg(0xD631);tftlcd_wr_data(0xB9);
    tftlcd_wr_reg(0xD632);tftlcd_wr_data(0x03);
    tftlcd_wr_reg(0xD633);tftlcd_wr_data(0xC1);

    //Enable Page0                                    
    tftlcd_wr_reg(0xF000);tftlcd_wr_data(0x55);
    tftlcd_wr_reg(0xF001);tftlcd_wr_data(0xAA);
    tftlcd_wr_reg(0xF002);tftlcd_wr_data(0x52);
    tftlcd_wr_reg(0xF003);tftlcd_wr_data(0x08);
    tftlcd_wr_reg(0xF004);tftlcd_wr_data(0x00);

    //RGB I/F Setting                                 
    tftlcd_wr_reg(0xB000);tftlcd_wr_data(0x08);
    tftlcd_wr_reg(0xB001);tftlcd_wr_data(0x05);
    tftlcd_wr_reg(0xB002);tftlcd_wr_data(0x02);
    tftlcd_wr_reg(0xB003);tftlcd_wr_data(0x05);
    tftlcd_wr_reg(0xB004);tftlcd_wr_data(0x02);

    // SDT:                                           
    tftlcd_wr_reg(0xB600);tftlcd_wr_data(0x0A);
    tftlcd_wr_reg(0xB500);tftlcd_wr_data(0x6b);     // 顯示點陣 480x854
    // Gate EQ:                                       
    tftlcd_wr_reg(0xB700);tftlcd_wr_data(0x00);
    tftlcd_wr_reg(0xB701);tftlcd_wr_data(0x70);

    // Source EQ                                      
    tftlcd_wr_reg(0xB800);tftlcd_wr_data(0x01);
    tftlcd_wr_reg(0xB801);tftlcd_wr_data(0x05);
    tftlcd_wr_reg(0xB802);tftlcd_wr_data(0x05);
    tftlcd_wr_reg(0xB803);tftlcd_wr_data(0x05);

    //Inversion: Column inversion (NVT);                
    tftlcd_wr_reg(0xBC00);tftlcd_wr_data(0x02);
    tftlcd_wr_reg(0xBC01);tftlcd_wr_data(0x02);
    tftlcd_wr_reg(0xBC02);tftlcd_wr_data(0x02);

    //BOE's Setting (default)                         
    tftlcd_wr_reg(0xCC00);tftlcd_wr_data(0x03);
    tftlcd_wr_reg(0xCC01);tftlcd_wr_data(0x00);
    tftlcd_wr_reg(0xCC02);tftlcd_wr_data(0x00);

    //Display Timing                                  
    tftlcd_wr_reg(0xBD00);tftlcd_wr_data(0x01);
    tftlcd_wr_reg(0xBD01);tftlcd_wr_data(0x84);
    tftlcd_wr_reg(0xBD02);tftlcd_wr_data(0x07);
    tftlcd_wr_reg(0xBD03);tftlcd_wr_data(0x31);
    tftlcd_wr_reg(0xBD04);tftlcd_wr_data(0x00);
    tftlcd_wr_reg(0xBA00);tftlcd_wr_data(0x01);
    tftlcd_wr_reg(0xFF00);tftlcd_wr_data(0xAA);
    tftlcd_wr_reg(0xFF01);tftlcd_wr_data(0x55);
    tftlcd_wr_reg(0xFF02);tftlcd_wr_data(0x25);
    tftlcd_wr_reg(0xFF03);tftlcd_wr_data(0x01);

    tftlcd_wr_reg(0x3A00);tftlcd_wr_data(0x55);

    tftlcd_wr_reg(0x1100);
    tftlcd_delay_ms(120);
    tftlcd_wr_reg(0x2900);

    TFTLCD_BACKLIGHT_ACTIVE();
    tftlcd_set_dir(handle,TFTLCD_SCAN_DIR_U2D_R2L);
    tftlcd_clear(handle,TFTLCD_COLOR_WHITE);

/*    {
        tftlcd_set_window(handle,0,0,100,100);
        tftlcd_write_ram_prepare(handle);
        for (int i = 0; i < 10000; i++)
        {
            tftlcd_wr_data(TFTLCD_COLOR_BLUE);
        }
    }

    {
        tftlcd_set_window(handle,650,0,100,100);
        tftlcd_write_ram_prepare(handle);
        for (int i = 0; i < 10000; i++)
        {
            tftlcd_wr_data(TFTLCD_COLOR_BLUE);
        }
    }

    {
        tftlcd_set_window(handle,100,100,100,100);
        tftlcd_write_ram_prepare(handle);
        for (int i = 0; i < 10000; i++)
        {
            tftlcd_wr_data(TFTLCD_COLOR_BLUE);
        }
    }

    {
        tftlcd_set_window(handle,0,300,100,100);
        tftlcd_write_ram_prepare(handle);
        for (int i = 0; i < 10000; i++)
        {
            tftlcd_wr_data(TFTLCD_COLOR_BLUE);
        }
    }*/
    
    return 0;
}
