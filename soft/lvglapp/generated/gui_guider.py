# Copyright 2022 NXP
# SPDX-License-Identifier: MIT
# The auto-generated can only be used on NXP devices

import SDL
import utime as time
import usys as sys
import lvgl as lv
import lodepng as png
import ustruct

lv.init()
SDL.init(w=800,h=480)

# Register SDL display driver.
disp_buf1 = lv.disp_draw_buf_t()
buf1_1 = bytearray(800*10)
disp_buf1.init(buf1_1, None, len(buf1_1)//4)
disp_drv = lv.disp_drv_t()
disp_drv.init()
disp_drv.draw_buf = disp_buf1
disp_drv.flush_cb = SDL.monitor_flush
disp_drv.hor_res = 800
disp_drv.ver_res = 480
disp_drv.register()

# Regsiter SDL mouse driver
indev_drv = lv.indev_drv_t()
indev_drv.init() 
indev_drv.type = lv.INDEV_TYPE.POINTER
indev_drv.read_cb = SDL.mouse_read
indev_drv.register()

# Below: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

COLOR_SIZE = lv.color_t.__SIZE__
COLOR_IS_SWAPPED = hasattr(lv.color_t().ch,'green_h')

class lodepng_error(RuntimeError):
    def __init__(self, err):
        if type(err) is int:
            super().__init__(png.error_text(err))
        else:
            super().__init__(err)

# Parse PNG file header
# Taken from https://github.com/shibukawa/imagesize_py/blob/ffef30c1a4715c5acf90e8945ceb77f4a2ed2d45/imagesize.py#L63-L85

def get_png_info(decoder, src, header):
    # Only handle variable image types

    if lv.img.src_get_type(src) != lv.img.SRC.VARIABLE:
        return lv.RES.INV

    data = lv.img_dsc_t.__cast__(src).data
    if data == None:
        return lv.RES.INV

    png_header = bytes(data.__dereference__(24))

    if png_header.startswith(b'\211PNG\r\n\032\n'):
        if png_header[12:16] == b'IHDR':
            start = 16
        # Maybe this is for an older PNG version.
        else:
            start = 8
        try:
            width, height = ustruct.unpack(">LL", png_header[start:start+8])
        except ustruct.error:
            return lv.RES.INV
    else:
        return lv.RES.INV

    header.always_zero = 0
    header.w = width
    header.h = height
    header.cf = lv.img.CF.TRUE_COLOR_ALPHA

    return lv.RES.OK

def convert_rgba8888_to_bgra8888(img_view):
    for i in range(0, len(img_view), lv.color_t.__SIZE__):
        ch = lv.color_t.__cast__(img_view[i:i]).ch
        ch.red, ch.blue = ch.blue, ch.red

# Read and parse PNG file

def open_png(decoder, dsc):
    img_dsc = lv.img_dsc_t.__cast__(dsc.src)
    png_data = img_dsc.data
    png_size = img_dsc.data_size
    png_decoded = png.C_Pointer()
    png_width = png.C_Pointer()
    png_height = png.C_Pointer()
    error = png.decode32(png_decoded, png_width, png_height, png_data, png_size)
    if error:
        raise lodepng_error(error)
    img_size = png_width.int_val * png_height.int_val * 4
    img_data = png_decoded.ptr_val
    img_view = img_data.__dereference__(img_size)

    if COLOR_SIZE == 4:
        convert_rgba8888_to_bgra8888(img_view)
    else:
        raise lodepng_error("Error: Color mode not supported yet!")

    dsc.img_data = img_data
    return lv.RES.OK

# Above: Taken from https://github.com/lvgl/lv_binding_micropython/blob/master/driver/js/imagetools.py#L22-L94

decoder = lv.img.decoder_create()
decoder.info_cb = get_png_info
decoder.open_cb = open_png

def anim_x_cb(obj, v):
    obj.set_x(v)

def anim_y_cb(obj, v):
    obj.set_y(v)

def ta_event_cb(e,kb):
    code = e.get_code()
    ta = e.get_target()
    if code == lv.EVENT.FOCUSED:
        kb.set_textarea(ta)
        kb.move_foreground()
        kb.clear_flag(lv.obj.FLAG.HIDDEN)

    if code == lv.EVENT.DEFOCUSED:
        kb.set_textarea(None)
        kb.move_background()
        kb.add_flag(lv.obj.FLAG.HIDDEN)


screen_main = lv.obj()
screen_main.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_screen_main_main_main_default
style_screen_main_main_main_default = lv.style_t()
style_screen_main_main_main_default.init()
style_screen_main_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen_main_main_main_default.set_bg_opa(0)

# add style for screen_main
screen_main.add_style(style_screen_main_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_view_root = lv.obj(screen_main)
screen_main_view_root.set_pos(int(0),int(0))
screen_main_view_root.set_size(800,480)
screen_main_view_root.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
# create style style_screen_main_view_root_main_main_default
style_screen_main_view_root_main_main_default = lv.style_t()
style_screen_main_view_root_main_main_default.init()
style_screen_main_view_root_main_main_default.set_radius(0)
style_screen_main_view_root_main_main_default.set_bg_color(lv.color_make(0x2b,0x2d,0x39))
style_screen_main_view_root_main_main_default.set_bg_grad_color(lv.color_make(0x1a,0x1a,0x22))
style_screen_main_view_root_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.VER)
style_screen_main_view_root_main_main_default.set_bg_opa(255)
style_screen_main_view_root_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_view_root_main_main_default.set_border_width(0)
style_screen_main_view_root_main_main_default.set_border_opa(255)
style_screen_main_view_root_main_main_default.set_pad_left(0)
style_screen_main_view_root_main_main_default.set_pad_right(0)
style_screen_main_view_root_main_main_default.set_pad_top(0)
style_screen_main_view_root_main_main_default.set_pad_bottom(0)

# add style for screen_main_view_root
screen_main_view_root.add_style(style_screen_main_view_root_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_view_top = lv.obj(screen_main)
screen_main_view_top.set_pos(int(0),int(0))
screen_main_view_top.set_size(800,52)
screen_main_view_top.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_title = lv.label(screen_main_view_top)
screen_main_lb_title.set_pos(int(22),int(7))
screen_main_lb_title.set_size(130,40)
screen_main_lb_title.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_title.set_text("lw焊台")
screen_main_lb_title.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_title_main_main_default
style_screen_main_lb_title_main_main_default = lv.style_t()
style_screen_main_lb_title_main_main_default.init()
style_screen_main_lb_title_main_main_default.set_radius(0)
style_screen_main_lb_title_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_title_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_title_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_title_main_main_default.set_bg_opa(0)
style_screen_main_lb_title_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_title_main_main_default.set_text_font(lv.font_SimHei_40)
except AttributeError:
    try:
        style_screen_main_lb_title_main_main_default.set_text_font(lv.font_montserrat_40)
    except AttributeError:
        style_screen_main_lb_title_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_title_main_main_default.set_text_letter_space(2)
style_screen_main_lb_title_main_main_default.set_text_line_space(0)
style_screen_main_lb_title_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_title_main_main_default.set_pad_left(0)
style_screen_main_lb_title_main_main_default.set_pad_right(0)
style_screen_main_lb_title_main_main_default.set_pad_top(0)
style_screen_main_lb_title_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_title
screen_main_lb_title.add_style(style_screen_main_lb_title_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_time = lv.label(screen_main_view_top)
screen_main_lb_time.set_pos(int(490),int(14))
screen_main_lb_time.set_size(300,24)
screen_main_lb_time.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_time.set_text("2020-10-10 10:10:10")
screen_main_lb_time.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_time_main_main_default
style_screen_main_lb_time_main_main_default = lv.style_t()
style_screen_main_lb_time_main_main_default.init()
style_screen_main_lb_time_main_main_default.set_radius(0)
style_screen_main_lb_time_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_time_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_time_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_time_main_main_default.set_bg_opa(0)
style_screen_main_lb_time_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_time_main_main_default.set_text_font(lv.font_SimHei_24)
except AttributeError:
    try:
        style_screen_main_lb_time_main_main_default.set_text_font(lv.font_montserrat_24)
    except AttributeError:
        style_screen_main_lb_time_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_time_main_main_default.set_text_letter_space(2)
style_screen_main_lb_time_main_main_default.set_text_line_space(0)
style_screen_main_lb_time_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_time_main_main_default.set_pad_left(0)
style_screen_main_lb_time_main_main_default.set_pad_right(0)
style_screen_main_lb_time_main_main_default.set_pad_top(0)
style_screen_main_lb_time_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_time
screen_main_lb_time.add_style(style_screen_main_lb_time_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_main_view_top_main_main_default
style_screen_main_view_top_main_main_default = lv.style_t()
style_screen_main_view_top_main_main_default.init()
style_screen_main_view_top_main_main_default.set_radius(0)
style_screen_main_view_top_main_main_default.set_bg_color(lv.color_make(0x38,0x3b,0x45))
style_screen_main_view_top_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_screen_main_view_top_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_view_top_main_main_default.set_bg_opa(255)
style_screen_main_view_top_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_view_top_main_main_default.set_border_width(0)
style_screen_main_view_top_main_main_default.set_border_opa(255)
style_screen_main_view_top_main_main_default.set_pad_left(0)
style_screen_main_view_top_main_main_default.set_pad_right(0)
style_screen_main_view_top_main_main_default.set_pad_top(0)
style_screen_main_view_top_main_main_default.set_pad_bottom(0)

# add style for screen_main_view_top
screen_main_view_top.add_style(style_screen_main_view_top_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_view_iron = lv.obj(screen_main)
screen_main_view_iron.set_pos(int(0),int(52))
screen_main_view_iron.set_size(400,428)
screen_main_view_iron.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_iron = lv.label(screen_main_view_iron)
screen_main_lb_iron.set_pos(int(5),int(7))
screen_main_lb_iron.set_size(100,40)
screen_main_lb_iron.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_iron.set_text("烙铁")
screen_main_lb_iron.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_iron_main_main_default
style_screen_main_lb_iron_main_main_default = lv.style_t()
style_screen_main_lb_iron_main_main_default.init()
style_screen_main_lb_iron_main_main_default.set_radius(0)
style_screen_main_lb_iron_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_iron_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_iron_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_iron_main_main_default.set_bg_opa(0)
style_screen_main_lb_iron_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_iron_main_main_default.set_text_font(lv.font_SimHei_40)
except AttributeError:
    try:
        style_screen_main_lb_iron_main_main_default.set_text_font(lv.font_montserrat_40)
    except AttributeError:
        style_screen_main_lb_iron_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_iron_main_main_default.set_text_letter_space(2)
style_screen_main_lb_iron_main_main_default.set_text_line_space(0)
style_screen_main_lb_iron_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_iron_main_main_default.set_pad_left(0)
style_screen_main_lb_iron_main_main_default.set_pad_right(0)
style_screen_main_lb_iron_main_main_default.set_pad_top(0)
style_screen_main_lb_iron_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_iron
screen_main_lb_iron.add_style(style_screen_main_lb_iron_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_iron_set_temp = lv.label(screen_main_view_iron)
screen_main_lb_iron_set_temp.set_pos(int(10),int(59))
screen_main_lb_iron_set_temp.set_size(170,40)
screen_main_lb_iron_set_temp.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_iron_set_temp.set_text("设置温度")
screen_main_lb_iron_set_temp.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_iron_set_temp_main_main_default
style_screen_main_lb_iron_set_temp_main_main_default = lv.style_t()
style_screen_main_lb_iron_set_temp_main_main_default.init()
style_screen_main_lb_iron_set_temp_main_main_default.set_radius(0)
style_screen_main_lb_iron_set_temp_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_iron_set_temp_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_iron_set_temp_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_iron_set_temp_main_main_default.set_bg_opa(0)
style_screen_main_lb_iron_set_temp_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_iron_set_temp_main_main_default.set_text_font(lv.font_SimHei_40)
except AttributeError:
    try:
        style_screen_main_lb_iron_set_temp_main_main_default.set_text_font(lv.font_montserrat_40)
    except AttributeError:
        style_screen_main_lb_iron_set_temp_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_iron_set_temp_main_main_default.set_text_letter_space(2)
style_screen_main_lb_iron_set_temp_main_main_default.set_text_line_space(0)
style_screen_main_lb_iron_set_temp_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_iron_set_temp_main_main_default.set_pad_left(0)
style_screen_main_lb_iron_set_temp_main_main_default.set_pad_right(0)
style_screen_main_lb_iron_set_temp_main_main_default.set_pad_top(0)
style_screen_main_lb_iron_set_temp_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_iron_set_temp
screen_main_lb_iron_set_temp.add_style(style_screen_main_lb_iron_set_temp_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_iron_set_temp_value = lv.label(screen_main_view_iron)
screen_main_lb_iron_set_temp_value.set_pos(int(181),int(11))
screen_main_lb_iron_set_temp_value.set_size(200,81)
screen_main_lb_iron_set_temp_value.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_iron_set_temp_value.set_text("450")
screen_main_lb_iron_set_temp_value.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_iron_set_temp_value_main_main_default
style_screen_main_lb_iron_set_temp_value_main_main_default = lv.style_t()
style_screen_main_lb_iron_set_temp_value_main_main_default.init()
style_screen_main_lb_iron_set_temp_value_main_main_default.set_radius(0)
style_screen_main_lb_iron_set_temp_value_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_iron_set_temp_value_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_iron_set_temp_value_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_iron_set_temp_value_main_main_default.set_bg_opa(0)
style_screen_main_lb_iron_set_temp_value_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_iron_set_temp_value_main_main_default.set_text_font(lv.font_sa_digital_number_80)
except AttributeError:
    try:
        style_screen_main_lb_iron_set_temp_value_main_main_default.set_text_font(lv.font_montserrat_80)
    except AttributeError:
        style_screen_main_lb_iron_set_temp_value_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_iron_set_temp_value_main_main_default.set_text_letter_space(2)
style_screen_main_lb_iron_set_temp_value_main_main_default.set_text_line_space(0)
style_screen_main_lb_iron_set_temp_value_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_iron_set_temp_value_main_main_default.set_pad_left(0)
style_screen_main_lb_iron_set_temp_value_main_main_default.set_pad_right(0)
style_screen_main_lb_iron_set_temp_value_main_main_default.set_pad_top(0)
style_screen_main_lb_iron_set_temp_value_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_iron_set_temp_value
screen_main_lb_iron_set_temp_value.add_style(style_screen_main_lb_iron_set_temp_value_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_iron_temp_value = lv.label(screen_main_view_iron)
screen_main_lb_iron_temp_value.set_pos(int(0),int(104))
screen_main_lb_iron_temp_value.set_size(400,180)
screen_main_lb_iron_temp_value.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_iron_temp_value.set_text("360")
screen_main_lb_iron_temp_value.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_iron_temp_value_main_main_default
style_screen_main_lb_iron_temp_value_main_main_default = lv.style_t()
style_screen_main_lb_iron_temp_value_main_main_default.init()
style_screen_main_lb_iron_temp_value_main_main_default.set_radius(0)
style_screen_main_lb_iron_temp_value_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_iron_temp_value_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_iron_temp_value_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_iron_temp_value_main_main_default.set_bg_opa(0)
style_screen_main_lb_iron_temp_value_main_main_default.set_text_color(lv.color_make(0xff,0x00,0x00))
try:
    style_screen_main_lb_iron_temp_value_main_main_default.set_text_font(lv.font_sa_digital_number_165)
except AttributeError:
    try:
        style_screen_main_lb_iron_temp_value_main_main_default.set_text_font(lv.font_montserrat_165)
    except AttributeError:
        style_screen_main_lb_iron_temp_value_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_iron_temp_value_main_main_default.set_text_letter_space(0)
style_screen_main_lb_iron_temp_value_main_main_default.set_text_line_space(0)
style_screen_main_lb_iron_temp_value_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_iron_temp_value_main_main_default.set_pad_left(0)
style_screen_main_lb_iron_temp_value_main_main_default.set_pad_right(0)
style_screen_main_lb_iron_temp_value_main_main_default.set_pad_top(0)
style_screen_main_lb_iron_temp_value_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_iron_temp_value
screen_main_lb_iron_temp_value.add_style(style_screen_main_lb_iron_temp_value_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_v = lv.label(screen_main_view_iron)
screen_main_lb_v.set_pos(int(10),int(293))
screen_main_lb_v.set_size(60,20)
screen_main_lb_v.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_v.set_text("电压:")
screen_main_lb_v.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_v_main_main_default
style_screen_main_lb_v_main_main_default = lv.style_t()
style_screen_main_lb_v_main_main_default.init()
style_screen_main_lb_v_main_main_default.set_radius(0)
style_screen_main_lb_v_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_v_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_v_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_v_main_main_default.set_bg_opa(0)
style_screen_main_lb_v_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_v_main_main_default.set_text_font(lv.font_SimHei_20)
except AttributeError:
    try:
        style_screen_main_lb_v_main_main_default.set_text_font(lv.font_montserrat_20)
    except AttributeError:
        style_screen_main_lb_v_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_v_main_main_default.set_text_letter_space(2)
style_screen_main_lb_v_main_main_default.set_text_line_space(0)
style_screen_main_lb_v_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_v_main_main_default.set_pad_left(0)
style_screen_main_lb_v_main_main_default.set_pad_right(0)
style_screen_main_lb_v_main_main_default.set_pad_top(0)
style_screen_main_lb_v_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_v
screen_main_lb_v.add_style(style_screen_main_lb_v_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_va = lv.label(screen_main_view_iron)
screen_main_lb_va.set_pos(int(71),int(286))
screen_main_lb_va.set_size(110,30)
screen_main_lb_va.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_va.set_text("24.00\n")
screen_main_lb_va.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_va_main_main_default
style_screen_main_lb_va_main_main_default = lv.style_t()
style_screen_main_lb_va_main_main_default.init()
style_screen_main_lb_va_main_main_default.set_radius(0)
style_screen_main_lb_va_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_va_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_va_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_va_main_main_default.set_bg_opa(0)
style_screen_main_lb_va_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_va_main_main_default.set_text_font(lv.font_sa_digital_number_30)
except AttributeError:
    try:
        style_screen_main_lb_va_main_main_default.set_text_font(lv.font_montserrat_30)
    except AttributeError:
        style_screen_main_lb_va_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_va_main_main_default.set_text_letter_space(2)
style_screen_main_lb_va_main_main_default.set_text_line_space(0)
style_screen_main_lb_va_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_va_main_main_default.set_pad_left(0)
style_screen_main_lb_va_main_main_default.set_pad_right(0)
style_screen_main_lb_va_main_main_default.set_pad_top(0)
style_screen_main_lb_va_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_va
screen_main_lb_va.add_style(style_screen_main_lb_va_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_unit_v = lv.label(screen_main_view_iron)
screen_main_lb_unit_v.set_pos(int(182),int(298))
screen_main_lb_unit_v.set_size(15,15)
screen_main_lb_unit_v.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_unit_v.set_text("V")
screen_main_lb_unit_v.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_unit_v_main_main_default
style_screen_main_lb_unit_v_main_main_default = lv.style_t()
style_screen_main_lb_unit_v_main_main_default.init()
style_screen_main_lb_unit_v_main_main_default.set_radius(0)
style_screen_main_lb_unit_v_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_unit_v_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_unit_v_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_unit_v_main_main_default.set_bg_opa(0)
style_screen_main_lb_unit_v_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_unit_v_main_main_default.set_text_font(lv.font_SimHei_20)
except AttributeError:
    try:
        style_screen_main_lb_unit_v_main_main_default.set_text_font(lv.font_montserrat_20)
    except AttributeError:
        style_screen_main_lb_unit_v_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_unit_v_main_main_default.set_text_letter_space(0)
style_screen_main_lb_unit_v_main_main_default.set_text_line_space(0)
style_screen_main_lb_unit_v_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_unit_v_main_main_default.set_pad_left(0)
style_screen_main_lb_unit_v_main_main_default.set_pad_right(0)
style_screen_main_lb_unit_v_main_main_default.set_pad_top(0)
style_screen_main_lb_unit_v_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_unit_v
screen_main_lb_unit_v.add_style(style_screen_main_lb_unit_v_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_a = lv.label(screen_main_view_iron)
screen_main_lb_a.set_pos(int(203),int(293))
screen_main_lb_a.set_size(60,20)
screen_main_lb_a.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_a.set_text("电流:")
screen_main_lb_a.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_a_main_main_default
style_screen_main_lb_a_main_main_default = lv.style_t()
style_screen_main_lb_a_main_main_default.init()
style_screen_main_lb_a_main_main_default.set_radius(0)
style_screen_main_lb_a_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_a_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_a_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_a_main_main_default.set_bg_opa(0)
style_screen_main_lb_a_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_a_main_main_default.set_text_font(lv.font_SimHei_20)
except AttributeError:
    try:
        style_screen_main_lb_a_main_main_default.set_text_font(lv.font_montserrat_20)
    except AttributeError:
        style_screen_main_lb_a_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_a_main_main_default.set_text_letter_space(2)
style_screen_main_lb_a_main_main_default.set_text_line_space(0)
style_screen_main_lb_a_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_a_main_main_default.set_pad_left(0)
style_screen_main_lb_a_main_main_default.set_pad_right(0)
style_screen_main_lb_a_main_main_default.set_pad_top(0)
style_screen_main_lb_a_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_a
screen_main_lb_a.add_style(style_screen_main_lb_a_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_aa = lv.label(screen_main_view_iron)
screen_main_lb_aa.set_pos(int(264),int(286))
screen_main_lb_aa.set_size(110,30)
screen_main_lb_aa.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_aa.set_text("10.00")
screen_main_lb_aa.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_aa_main_main_default
style_screen_main_lb_aa_main_main_default = lv.style_t()
style_screen_main_lb_aa_main_main_default.init()
style_screen_main_lb_aa_main_main_default.set_radius(0)
style_screen_main_lb_aa_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_aa_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_aa_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_aa_main_main_default.set_bg_opa(0)
style_screen_main_lb_aa_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_aa_main_main_default.set_text_font(lv.font_sa_digital_number_30)
except AttributeError:
    try:
        style_screen_main_lb_aa_main_main_default.set_text_font(lv.font_montserrat_30)
    except AttributeError:
        style_screen_main_lb_aa_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_aa_main_main_default.set_text_letter_space(2)
style_screen_main_lb_aa_main_main_default.set_text_line_space(0)
style_screen_main_lb_aa_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_aa_main_main_default.set_pad_left(0)
style_screen_main_lb_aa_main_main_default.set_pad_right(0)
style_screen_main_lb_aa_main_main_default.set_pad_top(0)
style_screen_main_lb_aa_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_aa
screen_main_lb_aa.add_style(style_screen_main_lb_aa_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_unit_a = lv.label(screen_main_view_iron)
screen_main_lb_unit_a.set_pos(int(375),int(298))
screen_main_lb_unit_a.set_size(15,15)
screen_main_lb_unit_a.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_unit_a.set_text("A")
screen_main_lb_unit_a.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_unit_a_main_main_default
style_screen_main_lb_unit_a_main_main_default = lv.style_t()
style_screen_main_lb_unit_a_main_main_default.init()
style_screen_main_lb_unit_a_main_main_default.set_radius(0)
style_screen_main_lb_unit_a_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_unit_a_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_unit_a_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_unit_a_main_main_default.set_bg_opa(0)
style_screen_main_lb_unit_a_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_unit_a_main_main_default.set_text_font(lv.font_SimHei_20)
except AttributeError:
    try:
        style_screen_main_lb_unit_a_main_main_default.set_text_font(lv.font_montserrat_20)
    except AttributeError:
        style_screen_main_lb_unit_a_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_unit_a_main_main_default.set_text_letter_space(2)
style_screen_main_lb_unit_a_main_main_default.set_text_line_space(0)
style_screen_main_lb_unit_a_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_unit_a_main_main_default.set_pad_left(0)
style_screen_main_lb_unit_a_main_main_default.set_pad_right(0)
style_screen_main_lb_unit_a_main_main_default.set_pad_top(0)
style_screen_main_lb_unit_a_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_unit_a
screen_main_lb_unit_a.add_style(style_screen_main_lb_unit_a_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_w = lv.label(screen_main_view_iron)
screen_main_lb_w.set_pos(int(85),int(335))
screen_main_lb_w.set_size(56,20)
screen_main_lb_w.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_w.set_text("功率:")
screen_main_lb_w.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_w_main_main_default
style_screen_main_lb_w_main_main_default = lv.style_t()
style_screen_main_lb_w_main_main_default.init()
style_screen_main_lb_w_main_main_default.set_radius(0)
style_screen_main_lb_w_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_w_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_w_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_w_main_main_default.set_bg_opa(0)
style_screen_main_lb_w_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_w_main_main_default.set_text_font(lv.font_SimHei_20)
except AttributeError:
    try:
        style_screen_main_lb_w_main_main_default.set_text_font(lv.font_montserrat_20)
    except AttributeError:
        style_screen_main_lb_w_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_w_main_main_default.set_text_letter_space(2)
style_screen_main_lb_w_main_main_default.set_text_line_space(0)
style_screen_main_lb_w_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_w_main_main_default.set_pad_left(0)
style_screen_main_lb_w_main_main_default.set_pad_right(0)
style_screen_main_lb_w_main_main_default.set_pad_top(0)
style_screen_main_lb_w_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_w
screen_main_lb_w.add_style(style_screen_main_lb_w_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_wa = lv.label(screen_main_view_iron)
screen_main_lb_wa.set_pos(int(142),int(328))
screen_main_lb_wa.set_size(140,35)
screen_main_lb_wa.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_wa.set_text("240.00")
screen_main_lb_wa.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_wa_main_main_default
style_screen_main_lb_wa_main_main_default = lv.style_t()
style_screen_main_lb_wa_main_main_default.init()
style_screen_main_lb_wa_main_main_default.set_radius(0)
style_screen_main_lb_wa_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_wa_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_wa_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_wa_main_main_default.set_bg_opa(0)
style_screen_main_lb_wa_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_wa_main_main_default.set_text_font(lv.font_sa_digital_number_30)
except AttributeError:
    try:
        style_screen_main_lb_wa_main_main_default.set_text_font(lv.font_montserrat_30)
    except AttributeError:
        style_screen_main_lb_wa_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_wa_main_main_default.set_text_letter_space(2)
style_screen_main_lb_wa_main_main_default.set_text_line_space(0)
style_screen_main_lb_wa_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_wa_main_main_default.set_pad_left(0)
style_screen_main_lb_wa_main_main_default.set_pad_right(0)
style_screen_main_lb_wa_main_main_default.set_pad_top(0)
style_screen_main_lb_wa_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_wa
screen_main_lb_wa.add_style(style_screen_main_lb_wa_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_unit_w = lv.label(screen_main_view_iron)
screen_main_lb_unit_w.set_pos(int(283),int(340))
screen_main_lb_unit_w.set_size(15,15)
screen_main_lb_unit_w.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_unit_w.set_text("W")
screen_main_lb_unit_w.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_unit_w_main_main_default
style_screen_main_lb_unit_w_main_main_default = lv.style_t()
style_screen_main_lb_unit_w_main_main_default.init()
style_screen_main_lb_unit_w_main_main_default.set_radius(0)
style_screen_main_lb_unit_w_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_unit_w_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_unit_w_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_unit_w_main_main_default.set_bg_opa(0)
style_screen_main_lb_unit_w_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_unit_w_main_main_default.set_text_font(lv.font_SimHei_20)
except AttributeError:
    try:
        style_screen_main_lb_unit_w_main_main_default.set_text_font(lv.font_montserrat_20)
    except AttributeError:
        style_screen_main_lb_unit_w_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_unit_w_main_main_default.set_text_letter_space(2)
style_screen_main_lb_unit_w_main_main_default.set_text_line_space(0)
style_screen_main_lb_unit_w_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_unit_w_main_main_default.set_pad_left(0)
style_screen_main_lb_unit_w_main_main_default.set_pad_right(0)
style_screen_main_lb_unit_w_main_main_default.set_pad_top(0)
style_screen_main_lb_unit_w_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_unit_w
screen_main_lb_unit_w.add_style(style_screen_main_lb_unit_w_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_iron_preset_temp = lv.label(screen_main_view_iron)
screen_main_lb_iron_preset_temp.set_pos(int(5),int(385))
screen_main_lb_iron_preset_temp.set_size(110,24)
screen_main_lb_iron_preset_temp.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_iron_preset_temp.set_text("预设温度")
screen_main_lb_iron_preset_temp.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_iron_preset_temp_main_main_default
style_screen_main_lb_iron_preset_temp_main_main_default = lv.style_t()
style_screen_main_lb_iron_preset_temp_main_main_default.init()
style_screen_main_lb_iron_preset_temp_main_main_default.set_radius(0)
style_screen_main_lb_iron_preset_temp_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_iron_preset_temp_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_iron_preset_temp_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_iron_preset_temp_main_main_default.set_bg_opa(0)
style_screen_main_lb_iron_preset_temp_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_iron_preset_temp_main_main_default.set_text_font(lv.font_SimHei_24)
except AttributeError:
    try:
        style_screen_main_lb_iron_preset_temp_main_main_default.set_text_font(lv.font_montserrat_24)
    except AttributeError:
        style_screen_main_lb_iron_preset_temp_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_iron_preset_temp_main_main_default.set_text_letter_space(2)
style_screen_main_lb_iron_preset_temp_main_main_default.set_text_line_space(0)
style_screen_main_lb_iron_preset_temp_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_iron_preset_temp_main_main_default.set_pad_left(0)
style_screen_main_lb_iron_preset_temp_main_main_default.set_pad_right(0)
style_screen_main_lb_iron_preset_temp_main_main_default.set_pad_top(0)
style_screen_main_lb_iron_preset_temp_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_iron_preset_temp
screen_main_lb_iron_preset_temp.add_style(style_screen_main_lb_iron_preset_temp_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_btn_iron_CH1 = lv.btn(screen_main_view_iron)
screen_main_btn_iron_CH1.set_pos(int(120),int(370))
screen_main_btn_iron_CH1.set_size(80,50)
screen_main_btn_iron_CH1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_btn_iron_CH1.add_flag(lv.obj.FLAG.CHECKABLE)
screen_main_btn_iron_CH1_label = lv.label(screen_main_btn_iron_CH1)
screen_main_btn_iron_CH1_label.set_text("CH1")
screen_main_btn_iron_CH1.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_main_btn_iron_CH1_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_main_btn_iron_ch1_main_main_default
style_screen_main_btn_iron_ch1_main_main_default = lv.style_t()
style_screen_main_btn_iron_ch1_main_main_default.init()
style_screen_main_btn_iron_ch1_main_main_default.set_radius(5)
style_screen_main_btn_iron_ch1_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_btn_iron_ch1_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_btn_iron_ch1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_btn_iron_ch1_main_main_default.set_bg_opa(255)
style_screen_main_btn_iron_ch1_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_btn_iron_ch1_main_main_default.set_border_width(0)
style_screen_main_btn_iron_ch1_main_main_default.set_border_opa(255)
style_screen_main_btn_iron_ch1_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_btn_iron_ch1_main_main_default.set_text_font(lv.font_SimHei_24)
except AttributeError:
    try:
        style_screen_main_btn_iron_ch1_main_main_default.set_text_font(lv.font_montserrat_24)
    except AttributeError:
        style_screen_main_btn_iron_ch1_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_btn_iron_ch1_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_main_btn_iron_CH1
screen_main_btn_iron_CH1.add_style(style_screen_main_btn_iron_ch1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_btn_iron_CH2 = lv.btn(screen_main_view_iron)
screen_main_btn_iron_CH2.set_pos(int(215),int(370))
screen_main_btn_iron_CH2.set_size(80,50)
screen_main_btn_iron_CH2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_btn_iron_CH2.add_flag(lv.obj.FLAG.CHECKABLE)
screen_main_btn_iron_CH2_label = lv.label(screen_main_btn_iron_CH2)
screen_main_btn_iron_CH2_label.set_text("CH2")
screen_main_btn_iron_CH2.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_main_btn_iron_CH2_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_main_btn_iron_ch2_main_main_default
style_screen_main_btn_iron_ch2_main_main_default = lv.style_t()
style_screen_main_btn_iron_ch2_main_main_default.init()
style_screen_main_btn_iron_ch2_main_main_default.set_radius(5)
style_screen_main_btn_iron_ch2_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_btn_iron_ch2_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_btn_iron_ch2_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_btn_iron_ch2_main_main_default.set_bg_opa(255)
style_screen_main_btn_iron_ch2_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_btn_iron_ch2_main_main_default.set_border_width(0)
style_screen_main_btn_iron_ch2_main_main_default.set_border_opa(255)
style_screen_main_btn_iron_ch2_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_btn_iron_ch2_main_main_default.set_text_font(lv.font_SimHei_24)
except AttributeError:
    try:
        style_screen_main_btn_iron_ch2_main_main_default.set_text_font(lv.font_montserrat_24)
    except AttributeError:
        style_screen_main_btn_iron_ch2_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_btn_iron_ch2_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_main_btn_iron_CH2
screen_main_btn_iron_CH2.add_style(style_screen_main_btn_iron_ch2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_btn_iron_CH3 = lv.btn(screen_main_view_iron)
screen_main_btn_iron_CH3.set_pos(int(310),int(370))
screen_main_btn_iron_CH3.set_size(80,50)
screen_main_btn_iron_CH3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_btn_iron_CH3.add_flag(lv.obj.FLAG.CHECKABLE)
screen_main_btn_iron_CH3_label = lv.label(screen_main_btn_iron_CH3)
screen_main_btn_iron_CH3_label.set_text("CH3")
screen_main_btn_iron_CH3.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_main_btn_iron_CH3_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_main_btn_iron_ch3_main_main_default
style_screen_main_btn_iron_ch3_main_main_default = lv.style_t()
style_screen_main_btn_iron_ch3_main_main_default.init()
style_screen_main_btn_iron_ch3_main_main_default.set_radius(5)
style_screen_main_btn_iron_ch3_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_btn_iron_ch3_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_btn_iron_ch3_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_btn_iron_ch3_main_main_default.set_bg_opa(255)
style_screen_main_btn_iron_ch3_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_btn_iron_ch3_main_main_default.set_border_width(0)
style_screen_main_btn_iron_ch3_main_main_default.set_border_opa(255)
style_screen_main_btn_iron_ch3_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_btn_iron_ch3_main_main_default.set_text_font(lv.font_SimHei_24)
except AttributeError:
    try:
        style_screen_main_btn_iron_ch3_main_main_default.set_text_font(lv.font_montserrat_24)
    except AttributeError:
        style_screen_main_btn_iron_ch3_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_btn_iron_ch3_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_main_btn_iron_CH3
screen_main_btn_iron_CH3.add_style(style_screen_main_btn_iron_ch3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_led_iron = lv.led(screen_main_view_iron)
screen_main_led_iron.set_pos(int(125),int(8))
screen_main_led_iron.set_size(40,40)
screen_main_led_iron.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_led_iron.set_brightness(255)
screen_main_led_iron.set_color(lv.color_make(0xff,0x33,0x33))
# create style style_screen_main_view_iron_main_main_default
style_screen_main_view_iron_main_main_default = lv.style_t()
style_screen_main_view_iron_main_main_default.init()
style_screen_main_view_iron_main_main_default.set_radius(0)
style_screen_main_view_iron_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen_main_view_iron_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_screen_main_view_iron_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_view_iron_main_main_default.set_bg_opa(0)
style_screen_main_view_iron_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_view_iron_main_main_default.set_border_width(0)
style_screen_main_view_iron_main_main_default.set_border_opa(255)
style_screen_main_view_iron_main_main_default.set_pad_left(0)
style_screen_main_view_iron_main_main_default.set_pad_right(0)
style_screen_main_view_iron_main_main_default.set_pad_top(0)
style_screen_main_view_iron_main_main_default.set_pad_bottom(0)

# add style for screen_main_view_iron
screen_main_view_iron.add_style(style_screen_main_view_iron_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_view_gun = lv.obj(screen_main)
screen_main_view_gun.set_pos(int(400),int(52))
screen_main_view_gun.set_size(400,428)
screen_main_view_gun.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_gun = lv.label(screen_main_view_gun)
screen_main_lb_gun.set_pos(int(5),int(7))
screen_main_lb_gun.set_size(100,40)
screen_main_lb_gun.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_gun.set_text("风枪")
screen_main_lb_gun.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_gun_main_main_default
style_screen_main_lb_gun_main_main_default = lv.style_t()
style_screen_main_lb_gun_main_main_default.init()
style_screen_main_lb_gun_main_main_default.set_radius(0)
style_screen_main_lb_gun_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_gun_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_gun_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_gun_main_main_default.set_bg_opa(0)
style_screen_main_lb_gun_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_gun_main_main_default.set_text_font(lv.font_SimHei_40)
except AttributeError:
    try:
        style_screen_main_lb_gun_main_main_default.set_text_font(lv.font_montserrat_40)
    except AttributeError:
        style_screen_main_lb_gun_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_gun_main_main_default.set_text_letter_space(2)
style_screen_main_lb_gun_main_main_default.set_text_line_space(0)
style_screen_main_lb_gun_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_gun_main_main_default.set_pad_left(0)
style_screen_main_lb_gun_main_main_default.set_pad_right(0)
style_screen_main_lb_gun_main_main_default.set_pad_top(0)
style_screen_main_lb_gun_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_gun
screen_main_lb_gun.add_style(style_screen_main_lb_gun_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_led_gun = lv.led(screen_main_view_gun)
screen_main_led_gun.set_pos(int(125),int(8))
screen_main_led_gun.set_size(40,40)
screen_main_led_gun.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_led_gun.set_brightness(255)
screen_main_led_gun.set_color(lv.color_make(0xff,0x33,0x33))
screen_main_lb_gun_set_temp = lv.label(screen_main_view_gun)
screen_main_lb_gun_set_temp.set_pos(int(10),int(59))
screen_main_lb_gun_set_temp.set_size(170,40)
screen_main_lb_gun_set_temp.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_gun_set_temp.set_text("设置温度")
screen_main_lb_gun_set_temp.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_gun_set_temp_main_main_default
style_screen_main_lb_gun_set_temp_main_main_default = lv.style_t()
style_screen_main_lb_gun_set_temp_main_main_default.init()
style_screen_main_lb_gun_set_temp_main_main_default.set_radius(0)
style_screen_main_lb_gun_set_temp_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_gun_set_temp_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_gun_set_temp_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_gun_set_temp_main_main_default.set_bg_opa(0)
style_screen_main_lb_gun_set_temp_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_gun_set_temp_main_main_default.set_text_font(lv.font_SimHei_40)
except AttributeError:
    try:
        style_screen_main_lb_gun_set_temp_main_main_default.set_text_font(lv.font_montserrat_40)
    except AttributeError:
        style_screen_main_lb_gun_set_temp_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_gun_set_temp_main_main_default.set_text_letter_space(2)
style_screen_main_lb_gun_set_temp_main_main_default.set_text_line_space(0)
style_screen_main_lb_gun_set_temp_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_gun_set_temp_main_main_default.set_pad_left(0)
style_screen_main_lb_gun_set_temp_main_main_default.set_pad_right(0)
style_screen_main_lb_gun_set_temp_main_main_default.set_pad_top(0)
style_screen_main_lb_gun_set_temp_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_gun_set_temp
screen_main_lb_gun_set_temp.add_style(style_screen_main_lb_gun_set_temp_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_gun_set_temp_value = lv.label(screen_main_view_gun)
screen_main_lb_gun_set_temp_value.set_pos(int(181),int(11))
screen_main_lb_gun_set_temp_value.set_size(200,81)
screen_main_lb_gun_set_temp_value.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_gun_set_temp_value.set_text("450")
screen_main_lb_gun_set_temp_value.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_gun_set_temp_value_main_main_default
style_screen_main_lb_gun_set_temp_value_main_main_default = lv.style_t()
style_screen_main_lb_gun_set_temp_value_main_main_default.init()
style_screen_main_lb_gun_set_temp_value_main_main_default.set_radius(0)
style_screen_main_lb_gun_set_temp_value_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_gun_set_temp_value_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_gun_set_temp_value_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_gun_set_temp_value_main_main_default.set_bg_opa(0)
style_screen_main_lb_gun_set_temp_value_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_gun_set_temp_value_main_main_default.set_text_font(lv.font_sa_digital_number_80)
except AttributeError:
    try:
        style_screen_main_lb_gun_set_temp_value_main_main_default.set_text_font(lv.font_montserrat_80)
    except AttributeError:
        style_screen_main_lb_gun_set_temp_value_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_gun_set_temp_value_main_main_default.set_text_letter_space(2)
style_screen_main_lb_gun_set_temp_value_main_main_default.set_text_line_space(0)
style_screen_main_lb_gun_set_temp_value_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_gun_set_temp_value_main_main_default.set_pad_left(0)
style_screen_main_lb_gun_set_temp_value_main_main_default.set_pad_right(0)
style_screen_main_lb_gun_set_temp_value_main_main_default.set_pad_top(0)
style_screen_main_lb_gun_set_temp_value_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_gun_set_temp_value
screen_main_lb_gun_set_temp_value.add_style(style_screen_main_lb_gun_set_temp_value_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_gun_temp_value = lv.label(screen_main_view_gun)
screen_main_lb_gun_temp_value.set_pos(int(0),int(104))
screen_main_lb_gun_temp_value.set_size(400,180)
screen_main_lb_gun_temp_value.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_gun_temp_value.set_text("360")
screen_main_lb_gun_temp_value.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_gun_temp_value_main_main_default
style_screen_main_lb_gun_temp_value_main_main_default = lv.style_t()
style_screen_main_lb_gun_temp_value_main_main_default.init()
style_screen_main_lb_gun_temp_value_main_main_default.set_radius(0)
style_screen_main_lb_gun_temp_value_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_gun_temp_value_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_gun_temp_value_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_gun_temp_value_main_main_default.set_bg_opa(0)
style_screen_main_lb_gun_temp_value_main_main_default.set_text_color(lv.color_make(0xff,0x00,0x00))
try:
    style_screen_main_lb_gun_temp_value_main_main_default.set_text_font(lv.font_sa_digital_number_165)
except AttributeError:
    try:
        style_screen_main_lb_gun_temp_value_main_main_default.set_text_font(lv.font_montserrat_165)
    except AttributeError:
        style_screen_main_lb_gun_temp_value_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_gun_temp_value_main_main_default.set_text_letter_space(0)
style_screen_main_lb_gun_temp_value_main_main_default.set_text_line_space(0)
style_screen_main_lb_gun_temp_value_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_gun_temp_value_main_main_default.set_pad_left(0)
style_screen_main_lb_gun_temp_value_main_main_default.set_pad_right(0)
style_screen_main_lb_gun_temp_value_main_main_default.set_pad_top(0)
style_screen_main_lb_gun_temp_value_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_gun_temp_value
screen_main_lb_gun_temp_value.add_style(style_screen_main_lb_gun_temp_value_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_gun_fan_value = lv.label(screen_main_view_gun)
screen_main_lb_gun_fan_value.set_pos(int(150),int(293))
screen_main_lb_gun_fan_value.set_size(150,65)
screen_main_lb_gun_fan_value.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_gun_fan_value.set_text("100")
screen_main_lb_gun_fan_value.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_gun_fan_value_main_main_default
style_screen_main_lb_gun_fan_value_main_main_default = lv.style_t()
style_screen_main_lb_gun_fan_value_main_main_default.init()
style_screen_main_lb_gun_fan_value_main_main_default.set_radius(0)
style_screen_main_lb_gun_fan_value_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_gun_fan_value_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_gun_fan_value_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_gun_fan_value_main_main_default.set_bg_opa(0)
style_screen_main_lb_gun_fan_value_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_gun_fan_value_main_main_default.set_text_font(lv.font_sa_digital_number_60)
except AttributeError:
    try:
        style_screen_main_lb_gun_fan_value_main_main_default.set_text_font(lv.font_montserrat_60)
    except AttributeError:
        style_screen_main_lb_gun_fan_value_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_gun_fan_value_main_main_default.set_text_letter_space(2)
style_screen_main_lb_gun_fan_value_main_main_default.set_text_line_space(0)
style_screen_main_lb_gun_fan_value_main_main_default.set_text_align(lv.TEXT_ALIGN.RIGHT)
style_screen_main_lb_gun_fan_value_main_main_default.set_pad_left(0)
style_screen_main_lb_gun_fan_value_main_main_default.set_pad_right(0)
style_screen_main_lb_gun_fan_value_main_main_default.set_pad_top(0)
style_screen_main_lb_gun_fan_value_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_gun_fan_value
screen_main_lb_gun_fan_value.add_style(style_screen_main_lb_gun_fan_value_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_unit_baifenbi = lv.label(screen_main_view_gun)
screen_main_lb_unit_baifenbi.set_pos(int(301),int(320))
screen_main_lb_unit_baifenbi.set_size(35,40)
screen_main_lb_unit_baifenbi.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_unit_baifenbi.set_text("%")
screen_main_lb_unit_baifenbi.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_unit_baifenbi_main_main_default
style_screen_main_lb_unit_baifenbi_main_main_default = lv.style_t()
style_screen_main_lb_unit_baifenbi_main_main_default.init()
style_screen_main_lb_unit_baifenbi_main_main_default.set_radius(0)
style_screen_main_lb_unit_baifenbi_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_unit_baifenbi_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_unit_baifenbi_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_unit_baifenbi_main_main_default.set_bg_opa(0)
style_screen_main_lb_unit_baifenbi_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_unit_baifenbi_main_main_default.set_text_font(lv.font_SimHei_40)
except AttributeError:
    try:
        style_screen_main_lb_unit_baifenbi_main_main_default.set_text_font(lv.font_montserrat_40)
    except AttributeError:
        style_screen_main_lb_unit_baifenbi_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_unit_baifenbi_main_main_default.set_text_letter_space(2)
style_screen_main_lb_unit_baifenbi_main_main_default.set_text_line_space(0)
style_screen_main_lb_unit_baifenbi_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_unit_baifenbi_main_main_default.set_pad_left(0)
style_screen_main_lb_unit_baifenbi_main_main_default.set_pad_right(0)
style_screen_main_lb_unit_baifenbi_main_main_default.set_pad_top(0)
style_screen_main_lb_unit_baifenbi_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_unit_baifenbi
screen_main_lb_unit_baifenbi.add_style(style_screen_main_lb_unit_baifenbi_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_hot = lv.label(screen_main_view_gun)
screen_main_lb_hot.set_pos(int(59),int(306))
screen_main_lb_hot.set_size(90,40)
screen_main_lb_hot.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_hot.set_text("热风")
screen_main_lb_hot.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_hot_main_main_default
style_screen_main_lb_hot_main_main_default = lv.style_t()
style_screen_main_lb_hot_main_main_default.init()
style_screen_main_lb_hot_main_main_default.set_radius(0)
style_screen_main_lb_hot_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_hot_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_hot_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_hot_main_main_default.set_bg_opa(0)
style_screen_main_lb_hot_main_main_default.set_text_color(lv.color_make(0xff,0x00,0x00))
try:
    style_screen_main_lb_hot_main_main_default.set_text_font(lv.font_SimHei_40)
except AttributeError:
    try:
        style_screen_main_lb_hot_main_main_default.set_text_font(lv.font_montserrat_40)
    except AttributeError:
        style_screen_main_lb_hot_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_hot_main_main_default.set_text_letter_space(2)
style_screen_main_lb_hot_main_main_default.set_text_line_space(0)
style_screen_main_lb_hot_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_hot_main_main_default.set_pad_left(0)
style_screen_main_lb_hot_main_main_default.set_pad_right(0)
style_screen_main_lb_hot_main_main_default.set_pad_top(0)
style_screen_main_lb_hot_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_hot
screen_main_lb_hot.add_style(style_screen_main_lb_hot_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_lb_gun_preset_temp = lv.label(screen_main_view_gun)
screen_main_lb_gun_preset_temp.set_pos(int(5),int(385))
screen_main_lb_gun_preset_temp.set_size(110,24)
screen_main_lb_gun_preset_temp.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_lb_gun_preset_temp.set_text("预设温度")
screen_main_lb_gun_preset_temp.set_long_mode(lv.label.LONG.WRAP)
# create style style_screen_main_lb_gun_preset_temp_main_main_default
style_screen_main_lb_gun_preset_temp_main_main_default = lv.style_t()
style_screen_main_lb_gun_preset_temp_main_main_default.init()
style_screen_main_lb_gun_preset_temp_main_main_default.set_radius(0)
style_screen_main_lb_gun_preset_temp_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_gun_preset_temp_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_lb_gun_preset_temp_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_lb_gun_preset_temp_main_main_default.set_bg_opa(0)
style_screen_main_lb_gun_preset_temp_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_lb_gun_preset_temp_main_main_default.set_text_font(lv.font_SimHei_24)
except AttributeError:
    try:
        style_screen_main_lb_gun_preset_temp_main_main_default.set_text_font(lv.font_montserrat_24)
    except AttributeError:
        style_screen_main_lb_gun_preset_temp_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_lb_gun_preset_temp_main_main_default.set_text_letter_space(2)
style_screen_main_lb_gun_preset_temp_main_main_default.set_text_line_space(0)
style_screen_main_lb_gun_preset_temp_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)
style_screen_main_lb_gun_preset_temp_main_main_default.set_pad_left(0)
style_screen_main_lb_gun_preset_temp_main_main_default.set_pad_right(0)
style_screen_main_lb_gun_preset_temp_main_main_default.set_pad_top(0)
style_screen_main_lb_gun_preset_temp_main_main_default.set_pad_bottom(0)

# add style for screen_main_lb_gun_preset_temp
screen_main_lb_gun_preset_temp.add_style(style_screen_main_lb_gun_preset_temp_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_btn_gun_CH1 = lv.btn(screen_main_view_gun)
screen_main_btn_gun_CH1.set_pos(int(120),int(370))
screen_main_btn_gun_CH1.set_size(80,50)
screen_main_btn_gun_CH1.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_btn_gun_CH1.add_flag(lv.obj.FLAG.CHECKABLE)
screen_main_btn_gun_CH1_label = lv.label(screen_main_btn_gun_CH1)
screen_main_btn_gun_CH1_label.set_text("CH1")
screen_main_btn_gun_CH1.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_main_btn_gun_CH1_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_main_btn_gun_ch1_main_main_default
style_screen_main_btn_gun_ch1_main_main_default = lv.style_t()
style_screen_main_btn_gun_ch1_main_main_default.init()
style_screen_main_btn_gun_ch1_main_main_default.set_radius(5)
style_screen_main_btn_gun_ch1_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_btn_gun_ch1_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_btn_gun_ch1_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_btn_gun_ch1_main_main_default.set_bg_opa(255)
style_screen_main_btn_gun_ch1_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_btn_gun_ch1_main_main_default.set_border_width(0)
style_screen_main_btn_gun_ch1_main_main_default.set_border_opa(255)
style_screen_main_btn_gun_ch1_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_btn_gun_ch1_main_main_default.set_text_font(lv.font_SimHei_24)
except AttributeError:
    try:
        style_screen_main_btn_gun_ch1_main_main_default.set_text_font(lv.font_montserrat_24)
    except AttributeError:
        style_screen_main_btn_gun_ch1_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_btn_gun_ch1_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_main_btn_gun_CH1
screen_main_btn_gun_CH1.add_style(style_screen_main_btn_gun_ch1_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_btn_gun_CH2 = lv.btn(screen_main_view_gun)
screen_main_btn_gun_CH2.set_pos(int(215),int(370))
screen_main_btn_gun_CH2.set_size(80,50)
screen_main_btn_gun_CH2.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_btn_gun_CH2.add_flag(lv.obj.FLAG.CHECKABLE)
screen_main_btn_gun_CH2_label = lv.label(screen_main_btn_gun_CH2)
screen_main_btn_gun_CH2_label.set_text("CH2")
screen_main_btn_gun_CH2.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_main_btn_gun_CH2_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_main_btn_gun_ch2_main_main_default
style_screen_main_btn_gun_ch2_main_main_default = lv.style_t()
style_screen_main_btn_gun_ch2_main_main_default.init()
style_screen_main_btn_gun_ch2_main_main_default.set_radius(5)
style_screen_main_btn_gun_ch2_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_btn_gun_ch2_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_btn_gun_ch2_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_btn_gun_ch2_main_main_default.set_bg_opa(255)
style_screen_main_btn_gun_ch2_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_btn_gun_ch2_main_main_default.set_border_width(0)
style_screen_main_btn_gun_ch2_main_main_default.set_border_opa(255)
style_screen_main_btn_gun_ch2_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_btn_gun_ch2_main_main_default.set_text_font(lv.font_SimHei_24)
except AttributeError:
    try:
        style_screen_main_btn_gun_ch2_main_main_default.set_text_font(lv.font_montserrat_24)
    except AttributeError:
        style_screen_main_btn_gun_ch2_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_btn_gun_ch2_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_main_btn_gun_CH2
screen_main_btn_gun_CH2.add_style(style_screen_main_btn_gun_ch2_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

screen_main_btn_gun_CH3 = lv.btn(screen_main_view_gun)
screen_main_btn_gun_CH3.set_pos(int(310),int(370))
screen_main_btn_gun_CH3.set_size(80,50)
screen_main_btn_gun_CH3.set_scrollbar_mode(lv.SCROLLBAR_MODE.OFF)
screen_main_btn_gun_CH3.add_flag(lv.obj.FLAG.CHECKABLE)
screen_main_btn_gun_CH3_label = lv.label(screen_main_btn_gun_CH3)
screen_main_btn_gun_CH3_label.set_text("CH3")
screen_main_btn_gun_CH3.set_style_pad_all(0, lv.STATE.DEFAULT)
screen_main_btn_gun_CH3_label.align(lv.ALIGN.CENTER,0,0)
# create style style_screen_main_btn_gun_ch3_main_main_default
style_screen_main_btn_gun_ch3_main_main_default = lv.style_t()
style_screen_main_btn_gun_ch3_main_main_default.init()
style_screen_main_btn_gun_ch3_main_main_default.set_radius(5)
style_screen_main_btn_gun_ch3_main_main_default.set_bg_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_btn_gun_ch3_main_main_default.set_bg_grad_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_btn_gun_ch3_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_btn_gun_ch3_main_main_default.set_bg_opa(255)
style_screen_main_btn_gun_ch3_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_btn_gun_ch3_main_main_default.set_border_width(0)
style_screen_main_btn_gun_ch3_main_main_default.set_border_opa(255)
style_screen_main_btn_gun_ch3_main_main_default.set_text_color(lv.color_make(0xff,0xff,0xff))
try:
    style_screen_main_btn_gun_ch3_main_main_default.set_text_font(lv.font_SimHei_24)
except AttributeError:
    try:
        style_screen_main_btn_gun_ch3_main_main_default.set_text_font(lv.font_montserrat_24)
    except AttributeError:
        style_screen_main_btn_gun_ch3_main_main_default.set_text_font(lv.font_montserrat_16)
style_screen_main_btn_gun_ch3_main_main_default.set_text_align(lv.TEXT_ALIGN.CENTER)

# add style for screen_main_btn_gun_CH3
screen_main_btn_gun_CH3.add_style(style_screen_main_btn_gun_ch3_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)

# create style style_screen_main_view_gun_main_main_default
style_screen_main_view_gun_main_main_default = lv.style_t()
style_screen_main_view_gun_main_main_default.init()
style_screen_main_view_gun_main_main_default.set_radius(0)
style_screen_main_view_gun_main_main_default.set_bg_color(lv.color_make(0xff,0xff,0xff))
style_screen_main_view_gun_main_main_default.set_bg_grad_color(lv.color_make(0xff,0xff,0xff))
style_screen_main_view_gun_main_main_default.set_bg_grad_dir(lv.GRAD_DIR.NONE)
style_screen_main_view_gun_main_main_default.set_bg_opa(0)
style_screen_main_view_gun_main_main_default.set_border_color(lv.color_make(0x21,0x95,0xf6))
style_screen_main_view_gun_main_main_default.set_border_width(0)
style_screen_main_view_gun_main_main_default.set_border_opa(255)
style_screen_main_view_gun_main_main_default.set_pad_left(0)
style_screen_main_view_gun_main_main_default.set_pad_right(0)
style_screen_main_view_gun_main_main_default.set_pad_top(0)
style_screen_main_view_gun_main_main_default.set_pad_bottom(0)

# add style for screen_main_view_gun
screen_main_view_gun.add_style(style_screen_main_view_gun_main_main_default, lv.PART.MAIN|lv.STATE.DEFAULT)










# content from custom.py

# Load the default screen
lv.scr_load(screen_main)

while SDL.check():
    time.sleep_ms(5)
