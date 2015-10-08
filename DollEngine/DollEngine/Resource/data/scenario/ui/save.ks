*from_game
[eval exp="tf.is_from_title=false"]
[startmenu]
[locksnapshot]
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
[position layer=&sf.layname_menu_base page=fore frame=image020 opacity=255 width=1136 height=640 left=0 top=-10 visible=true]
[current layer=&sf.layname_menu_base page=fore][er]
[nowait]
[locate x=900 y=553]
[button graphic=image026 storage=save.ks target=*return_title cond="tf.is_from_title" enterse=&sf.button_enter clickse=&sf.button_click]
[button graphic=image026 storage=save.ks target=*return_game cond="!tf.is_from_title" enterse=&sf.button_enter clickse=&sf.button_click]
[endnowait]
[return]


*create_ui
[nowait]
[position layer=&sf.layname_menu_button page=fore frame="" opacity=0 width=1136 height=640 left=0 top=10 visible=true]
[current layer=&sf.layname_menu_button page=fore][er]
[locate x=0 y=110]
[button normal=image024 enabled=false]
[eval exp="showsavedata('save',kag.fore.messages[5])"]
[endnowait]
[return]

*save_yes
[eval exp="sf.saveDataDate[tf.saveload_index]=getNowTime()"]
[save place=&tf.saveload_index ask=false]
[call target=*create_base]
[call target=*create_ui]
[switchin layer1=&sf.layname_menu_base layer2=&sf.layname_menu_button time=0]
[s]

*return_title
[switchout layer1=&sf.layname_menu_base layer2=&sf.layname_menu_button]
[jump storage=title.ks target=*back]
[s]

*return_game
[retungame]
[unlocksnapshot]
[return]
[s]
