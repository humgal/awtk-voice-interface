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
// extern ret_t swtich_rotation_animator(widget_t* win, bool_t start_anim);

ret_t swtich_rotation_animator(widget_t* win, bool_t start_anim) {
  return_value_if_fail(win != NULL, RET_BAD_PARAMS);
  widget_t* voice_icon = widget_lookup(win,"voice",TRUE);
  if(start_anim){
  widget_create_animator(voice_icon,"rotation(from=0, to=6.28,  duration=2000, repeat_times=0, easing=back_out)");

  }else{
    widget_stop_animator(voice_icon,"rotation");
    widget_destroy_animator(voice_icon,"rotation");
  }
  return RET_OK;

}
/**
 * 初始化
 */
ret_t application_init() {
  widget_t* win = window_open("main");
  swtich_rotation_animator(win,TRUE);
  return RET_OK;
}

ret_t application_exit() {
  log_debug("exit\n");
  return RET_OK;
}


