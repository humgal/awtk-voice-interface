/**
 * File:   edit.c
 * Author: AWTK Develop Team
 * Brief:  window main
 *
 * Copyright (c) 2018 - 2018  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2018-11-20 TangJunJie created
 *
 */
#include "awtk.h"
extern ret_t application_init(void);
/**
 * 初始化
 */
ret_t application_init() {
  widget_t* win = window_open("main");
  return RET_OK;
}

ret_t application_exit() {
  log_debug("exit\n");
  return RET_OK;
}

static void time_now_str(char* str, size_t size) {
  date_time_t dt;
  date_time_init(&dt);
  snprintf(str, size, "%04d/%02d/%02d %02d:%02d:%02d", dt.year, dt.month, dt.day, dt.hour,
           dt.minute, dt.second);
}

/**
 * 获取并显示系统时间
 */
static ret_t on_systime_update(const timer_info_t* timer) {
  widget_t* win = WIDGET(timer->ctx);
  widget_t* label = widget_lookup(win, "sys_time", TRUE);

  if (label) {
    char text[64];
    time_now_str(text, sizeof(text));
    widget_set_text_utf8(label, text);
  }

  return RET_REPEAT;
}
