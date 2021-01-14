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

ret_t add_text_to_listview(){

}


/**
 * 拖动歌词
 */
static ret_t on_lrc_up(void* ctx, event_t* e) {
  value_t val;
  widget_t* win = (widget_t*)ctx;

  value_set_bool(&val, TRUE);
  widget_set_prop(win, "lrc_move", &val);

  return RET_OK;
}

static ret_t on_lrc_down(void* ctx, event_t* e) {
  widget_t* win = (widget_t*)ctx;
  value_t val;

  value_set_bool(&val, FALSE);
  widget_set_prop(win, "lrc_move", &val);

  return RET_OK;
}

static ret_t voice_active(void* ctx,event_t* e) {

  return RET_OK;
}

/**
 * 子控件初始化(主要是设置click回调、初始显示信息)
 */
static ret_t init_widget(void* ctx, const void* iter) {
  widget_t* widget = WIDGET(iter);
  (void)ctx;
  if (widget->name != NULL) {
    const char* name = widget->name;
    if (tk_str_eq(name, "lrc_view")) {
      value_t val;
      widget_t* win = widget_get_window(widget);
      value_set_bool(&val, TRUE);
      widget_t* lrc_scroll = widget_lookup(win, "lrc_scroll", TRUE);

      for(int i=0;i<19;i++){
        widget_t* iter = list_item_create(lrc_scroll, 0, 0, 0, 0);

        widget_use_style(iter, "empty");
        widget_t* label = label_create(iter, 0, 0, win->w , 25 );
        widget_set_text(label, L"awtk");
        widget_use_style(label, "left");

        widget_t* iter_right = list_item_create(lrc_scroll, 0, 0, 0, 0);

        widget_use_style(iter_right, "empty");
        widget_t* label_right = label_create(iter_right, 0, 0, win->w , 25 );
        widget_set_text(label_right, L"awtk_right");
        widget_use_style(label_right, "right");

      }
      
      widget_set_prop(win, "lrc_move", &val);

      widget_on(widget, EVT_POINTER_DOWN, on_lrc_down, win);
      widget_on(widget, EVT_POINTER_UP, on_lrc_up, win);
    } else if (tk_str_eq(name, "voice")) {
      widget_t* win = widget_get_window(widget);
      widget_on(widget, EVT_CLICK, voice_active, win);
    }
  }
  return RET_OK;
}

/**
 * 初始化窗口上的子控件
 */
static void init_children_widget(widget_t* widget) {
  widget_foreach(widget, init_widget, widget);
}
/**
 * 初始化
 */
ret_t application_init() {
  widget_t* win = window_open("main");
  swtich_rotation_animator(win,TRUE);
  init_children_widget(win);
  return RET_OK;
}

ret_t application_exit() {
  log_debug("exit\n");
  return RET_OK;
}
