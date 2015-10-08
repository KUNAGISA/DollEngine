*start|スタート
[startmenu]
[backlay]
[clearlayers page=back]
[image layer=base page=back storage=image049.png visible=true]
[image layer=0 page=back storage=image050.png visible=true left=550 top=70]
[position layer=&sf.layname_dialog_base page=back frame="" opacity=0 left=0 top=0 width=1136 height=640 marginl=0 marginr=0 margint=0 marginb=0 visible=true]
[current layer=&sf.layname_dialog_base page=back][er]
[call target=*create_ui]
[bgm file=game_title volume=&sf.bgm_vol]
[bgmopt volume=&sf.bgm_vol]
[clickskip enabled=true]
[trans method=crossfade time=1000][wt]
[s]

*create_ui
[eval exp="init_option()"]
[nowait]
[locate x=930 y=293]
[button graphic=image051.png target=*game_start enterse=&sf.button_enter clickse=&sf.button_click]
[locate x=860 y=293]
[button graphic=image052.png target=*load enterse=&sf.button_enter clickse=&sf.button_click]
[locate x=790 y=293]
[button graphic=image053.png target=*extra enterse=&sf.button_enter clickse=&sf.button_click]
[locate x=720 y=293]
[button graphic=image054.png target=*option enterse=&sf.button_enter clickse=&sf.button_click]
[locate x=650 y=293]
[button graphic=image055.png target=*exit enterse=&sf.button_enter clickse=&sf.button_click]
[endnowait]
[return]

*back
[position layer=&sf.layname_dialog_base page=fore frame="" opacity=0 left=0 top=0 width=1136 height=640 marginl=0 marginr=0 margint=0 marginb=0 visible=true]
[current layer=&sf.layname_dialog_base page=fore][er]
[call target=*create_ui]
[s]

*game_start
[toblack]
[jump storage=01.ks]
[s]

*load
[jump storage=load.ks target=*from_title]
[s]

*extra
[jump storage=extra.ks target=*from_title]
[s]

*option
[jump storage=option.ks target=*from_title]
[s]

*exit
[close ask=true]
[jump storage=title.ks target=*back]
[s]

*from_game
[toblack]
[jump storage=title.ks target=*start] 
