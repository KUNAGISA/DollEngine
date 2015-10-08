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
[position layer=&sf.layname_menu_base page=fore frame=image022 opacity=255 width=1136 height=640 left=0 top=-10 visible=true]
[current layer=&sf.layname_menu_base page=fore][er]
[nowait]
;返回
[locate x=893 y=554]
[button graphic=image026 storage=history.ks target=*return_title cond="tf.is_from_title" enterse=&sf.button_enter clickse=&sf.button_click]
[button graphic=image026 storage=history.ks target=*return_game cond="!tf.is_from_title" enterse=&sf.button_enter clickse=&sf.button_click]
[endnowait]
[return]

*create_ui
[position layer=&sf.layname_menu_button page=fore frame="" opacity=0 width=1136 height=640 left=0 top=10 visible=true]
[current layer=&sf.layname_menu_button page=fore][er]
[nowait]
[locate x=0 y=110]
[button name=kc normal=image024 enabled=false]
[eval exp="initHistoryList(kag.current.names['kc'])"]
[locate x=909 y=133]
[slider name=history_page position=&getHistoryListHeight() onchangefunc=on_history_drop_slider base="image033.png" opacity=0 width=430 height=30  normal="image034.png" over="image035.png" on="image036.png" step=1 min=0 max=&getHistoryListHeight() nohilight vertical=true]
[endnowait]
[return]

*return_title
[switchout layer1=&sf.layname_menu_base layer2=&sf.layname_menu_button]
[eval exp="releaseHistoryList()"]
[jump storage=title.ks target=*back]
[s]

*return_game
[retungame]
[eval exp="releaseHistoryList()"]
[return]
[s]