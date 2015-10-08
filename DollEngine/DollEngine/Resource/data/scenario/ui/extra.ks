*from_title
[eval exp="tf.is_from_title=true"]
[call target=*create_base]
[call target=*create_ui]
[switchin layer1=&sf.layname_menu_base layer2=&sf.layname_menu_button]
[s]

*create_base
[position layer=&sf.layname_menu_base page=fore frame=image062 opacity=255 width=1136 height=640 left=0 top=-10 visible=true]
[call target=*create_title_return]
[return]

*create_title_return
[current layer=&sf.layname_menu_base page=fore][er]
[nowait]
;返回
[locate x=893 y=554]
[button graphic=image029 storage=extra.ks target=*return_title enterse=&sf.button_enter clickse=&sf.button_click]
[endnowait]
[return]

*create_extra_return
[current layer=&sf.layname_menu_base page=fore][er]
[nowait]
;返回
[locate x=893 y=554]
[button graphic=image029 storage=extra.ks target=*main_return enterse=&sf.button_enter clickse=&sf.button_click]
[endnowait]
[return]

*create_ui
[position layer=&sf.layname_menu_button page=fore frame="" opacity=0 width=1136 height=640 left=0 top=10 visible=true]
[current layer=&sf.layname_menu_button page=fore][er]
[nowait]
[locate x=0 y=0][button normal=image063 enabled=false]
[locate x=250 y=143][button graphic=image066 storage=extra_0.ks]
[locate x=370 y=143][button graphic=image065 storage=extra.ks target=*cg_show]
[locate x=490 y=143][button graphic=image067 storage=extra.ks target=*music_show]
[locate x=610 y=143][button graphic=image068 storage=extra.ks target=*program_show]
[endnowait]
[return]

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
*cg_show
[move layer=&sf.layname_menu_button page=fore path="(0,10,0)" time=500][wm]
[current layer=&sf.layname_menu_button page=fore][er]
[nowait]
[locate x=0 y=0][button normal=image064 enabled=false]
[call target=*create_cg]
[endnowait]
[move layer=&sf.layname_menu_button page=fore path="(0,0,255)" time=500][wm]
[call target=*create_extra_return]
[s]

*create_cg
[locate x=47 y=0][button normal=image069 enabled=false]
[iscript]
with(kag.tagHandlers)
{
	for (var i = 0; i < 3; ++i)
	{
		for (var k = 0; k < 3; ++k)
		{
			var cgid = (i*3+k+1);
			.locate(%[x:k*270+240 , y:i*115+150]);
			if (sf.cg[cgid].enabled)
				// if(true)
			{
				.button(%[normal:"image072.png", over:"image073.png", on:"image072-f.png", exp:"tf.cgid="+cgid, target:"*cg_one"]);
				.locate(%[x:k*270+240+20 , y:i*115+150+22]);
				.button(%[normal:sf.cg[cgid].extrasmall,enabled:false]);
			}
			else
			{
				.button(%[normal:"image072.png", over:"image073.png", on:"image072-f.png"]);
			}
		};
	};
}
[endscript]
[return]

*cg_one
[eval exp="dm(sf.cg[tf.cgid].scale[0])"]
[eval exp="tf.cgfile =  (sf.cg[tf.cgid].file[0])"]
[image layer=&sf.layname_cg storage=&tf.cgfile visible=true left=0 top=0 index=1006000]
[layopt layer=&sf.layname_cg zoom=&"sf.cg[tf.cgid].scale[0]"]
[waitclick]
[if exp="sf.cg[tf.cgid].file.count>1"]
[eval exp="tf.cgfile =  (sf.cg[tf.cgid].file[1])"]
[image layer=&sf.layname_cg storage=&tf.cgfile visible=true left=0 top=0 index=1006000]
[layopt layer=&sf.layname_cg zoom=&"sf.cg[tf.cgid].scale[1]"]
[waitclick]
[endif]
[fresimage layer=&sf.layname_cg]
[layopt layer=&sf.layname_cg visible=false index=100000]
[current layer=&sf.layname_menu_button page=fore][er]
[nowait]
[locate x=0 y=0][button normal=image064 enabled=false]
[call target=*create_cg]
[endnowait]
[call target=*create_extra_return]
[s]

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
*music_show
[move layer=&sf.layname_menu_button page=fore path="(0,10,0)" time=500][wm]
[current layer=&sf.layname_menu_button page=fore][er]
[nowait]
[locate x=0 y=0][button normal=image064 enabled=false]
[call target=*create_music]
[endnowait]
[move layer=&sf.layname_extra_cg page=fore path="(0,0,255)" time=500]
[move layer=&sf.layname_menu_button page=fore path="(0,0,255)" time=500][wm][wm]
[eval exp="tf.cur_music=-1"]
[call target=*create_extra_return]
[s]

*create_music
[iscript]
function extra_pause_music ()
{
	kag.fore.messages[sf.layname_menu_button_number].names.round.animTimer.enabled=false;
	kag.fore.messages[sf.layname_menu_button_number].names.pause.visible=false;
	kag.fore.messages[sf.layname_menu_button_number].names.play.visible=true;
	kag.tagHandlers.pausebgm(%[]);
}
function extra_play_music (name)
{
	if(name != void) {
		kag.fore.messages[sf.layname_menu_button_number].names.round.animTimer.enabled=true;
		kag.fore.messages[sf.layname_menu_button_number].names.pause.visible=true;
		kag.fore.messages[sf.layname_menu_button_number].names.play.visible=false;
		kag.tagHandlers.playbgm (%[storage:name,loop:true]);
	}
	else if(tf.cur_music != "-1") {
		kag.fore.messages[sf.layname_menu_button_number].names.round.animTimer.enabled=true;
		kag.fore.messages[sf.layname_menu_button_number].names.pause.visible=true;
		kag.fore.messages[sf.layname_menu_button_number].names.play.visible=false;
		kag.tagHandlers.resumebgm (%[]);
	}
}

[endscript]
[locate x=0 y=0][button normal=image064 enabled=false]
[locate x=47 y=0][button normal=image070 enabled=false]
[locate x=490 y=185][button normal=image076 enabled=false]
[locate x=425 y=179][button normal=image075 animcount=10 animtime=100 enabled=false name=round]
[locate x=530 y=205][button graphic=image077]
[locate x=580 y=205][button graphic=image079 name=pause exp="extra_pause_music()"]
[locate x=580 y=202][button graphic=image080 name=play exp="extra_play_music()"]
[locate x=630 y=205][button graphic=image078]
[position layer=&sf.layname_extra_cg left=0 top=10 width=1136 height=640 frame="" opacity=0 visible=true]
[current layer=&sf.layname_extra_cg page=fore][er][nowait]
[locate x=480 y=300][link exp="tf.cur_music='1.ogg';extra_play_music('1.ogg')"]1-归舟·生灵曲[endlink]
[locate x=480 y=350][link exp="tf.cur_music='3.ogg';extra_play_music('3.ogg')"]2-花海[endlink]
[locate x=480 y=400][link exp="tf.cur_music='4.ogg';extra_play_music('4.ogg')"]3-花语[endlink]
[locate x=480 y=450][link exp="tf.cur_music='6.ogg';extra_play_music('6.ogg')"]4-忆萝月[endlink]
[endnowait]
[eval exp=extra_pause_music()]
[return]

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
*program_show
[move layer=&sf.layname_menu_button page=fore path="(0,10,0)" time=500][wm]
[current layer=&sf.layname_menu_button page=fore][er]
[nowait]
[locate x=0 y=0][button normal=image064 enabled=false]
[call target=*create_program]
[endnowait]
[move layer=&sf.layname_menu_button page=fore path="(0,0,255)" time=500][wm]
[call target=*create_extra_return]
[s]

*create_program
[locate x=47 y=0][button normal=image071 enabled=false]
[locate x=30 y=130][button normal=image074 enabled=false]
[return]


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

*main_return
[move layer=&sf.layname_extra_cg page=fore path="(0,10,0)" time=500]
[move layer=&sf.layname_menu_button page=fore path="(0,10,0)" time=500][wm][wm]
[bgm file=game_title volume=&sf.bgm_vol cond="tf.cur_music!=void"]
[eval exp="tf.cur_music=void"]
[call target=*create_ui]
[call target=*create_title_return]
[move layer=&sf.layname_menu_button page=fore path="(0,0,255)" time=500][wm]
[s]


*return_title
[toblack]
[jump storage=title.ks]

*return_game
[dm exp=返回游戏]