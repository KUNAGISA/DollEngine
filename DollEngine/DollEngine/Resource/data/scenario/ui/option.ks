*from_game
[eval exp="tf.is_from_title=false"]
[startmenu]
[call target=*create_base]
[call target=*create_ui]
[switchin layer1=&sf.layname_menu_base layer2=&sf.layname_menu_button]
[s]

*from_title
[eval exp="tf.is_from_title=true"]
[call target=*create_base]
[call target=*create_ui]
[switchin layer1=&sf.layname_menu_base layer2=&sf.layname_menu_button]
[s]

*create_base
[position layer=&sf.layname_menu_base page=fore frame=image023 opacity=255 width=1136 height=640 left=0 top=-10 visible=true]
[current layer=&sf.layname_menu_base page=fore][er]
[nowait]
;微博
[locate x=472 y=554][button graphic=image027 exp="System.shellExecute('http://weibo.com/sanxiangegame')" enterse=&sf.button_enter clickse=&sf.button_click]
;官网
[locate x=683 y=554][button graphic=image028 exp="System.shellExecute('http://sxgavg-tk.jingtustudio.com/')" enterse=&sf.button_enter clickse=&sf.button_click]
;返回
[locate x=893 y=554]
[button graphic=image026 storage=option.ks target=*return_title cond="tf.is_from_title" enterse=&sf.button_enter clickse=&sf.button_click]
[button graphic=image026 storage=option.ks target=*return_game cond="!tf.is_from_title" enterse=&sf.button_enter clickse=&sf.button_click]
[endnowait]
[return]

*create_ui
[position layer=&sf.layname_menu_button page=fore frame="" opacity=0 width=1136 height=640 left=0 top=10 visible=true]
[current layer=&sf.layname_menu_button page=fore][er]
[nowait]
[locate x=0 y=110]
[button normal=image024 enabled=false]
[locate x=222 y=160]
[button normal=image044 enabled=false]
;窗口按钮
[locate x=420 y=155][button graphic=image037 target=*click_window cond="kag.fullScreen==true" enterse=&sf.button_enter clickse=&sf.button_click]
[locate x=420 y=155][button normal=image037_3 enabled=false cond="kag.fullScreen==false"]
;全屏按钮
[locate x=551 y=155][button graphic=image038 target=*click_fullscreen cond="kag.fullScreen==false" enterse=&sf.button_enter clickse=&sf.button_click]
[locate x=551 y=155][button normal=image038_3 enabled=false cond="kag.fullScreen==true"]
;自动模式速度
[locate x=418 y=197]
[slider name=auto_speed position=&sf.auto_speed onchangefunc=on_auto_speed_change base="image045.png" opacity=0 width=430 height=30  normal="image041.png" over="image042.png" on="image043.png" step=1 min=0 max=100 nohilight vertical=false]
;文字显示速度
[locate x=418 y=240]
[slider name=text_speed position=&sf.text_speed onchangefunc=on_text_speed_change base="image045.png" opacity=0 width=430 height=30  normal="image041.png" over="image042.png" on="image043.png" step=1 min=0 max=100 nohilight vertical=false]
;跳过未读文本 开启
[locate x=420 y=280][button name=skip_all_open exp="on_skip_read_click(true)" graphic=image039 enterse=&sf.button_enter clickse=&sf.button_click ]
;跳过未读文本 关闭
[locate x=551 y=280][button name=skip_all_close exp="on_skip_read_click(false)" graphic=image040 enterse=&sf.button_enter clickse=&sf.button_click]
[eval exp="on_skip_read_click(sf.is_all_skip)"]
;音乐音量
[locate x=418 y=365]
[slider name=bgm_vol position=&sf.bgm_vol onchangefunc=on_bgm_vol_change base="image045.png" opacity=0 width=430 height=30  normal="image041.png" over="image042.png" on="image043.png" step=1 min=0 max=100 nohilight vertical=false]
;音效音量
[locate x=418 y=408]
[slider name=se_vol position=&sf.se_vol onchangefunc=on_se_vol_change base="image045.png" opacity=0 width=430 height=30  normal="image041.png" over="image042.png" on="image043.png" step=1 min=0 max=100 nohilight vertical=false]
;配音音量
[locate x=418 y=447]
[slider name=cv_vol position=&sf.cv_vol onchangefunc=on_cv_vol_change base="image045.png" opacity=0 width=430 height=30  normal="image041.png" over="image042.png" on="image043.png" step=1 min=0 max=100 nohilight vertical=false]
[endnowait]
[return]

*click_window
[eval exp="kag.fullScreen=false"]
[call target=*create_base]
[call target=*create_ui]
[layopt layer=&sf.layname_menu_base top=0]
[layopt layer=&sf.layname_menu_button top=0]
[s]

*click_fullscreen
[eval exp="kag.fullScreen=true"]
[call target=*create_base]
[call target=*create_ui]
[layopt layer=&sf.layname_menu_base top=0]
[layopt layer=&sf.layname_menu_button top=0]
[s]

*return_title
[switchout layer1=&sf.layname_menu_base layer2=&sf.layname_menu_button]
[jump storage=title.ks target=*back]
[s]

*return_game
[retungame]
[return]
[s]