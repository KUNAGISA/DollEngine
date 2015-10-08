*start

[iscript]

//存读档案显示
function showsavedata(type,parent)
{
	with(kag.tagHandlers)
	{
		var max_date_index=void;
		var max_date=%[utc:0];
		for(var i=0;i<3;i++)
		{
			//i is ln number
			for(var k=0;k<3;k++)
			{
				//k is col number
				.locate(%[x:40+k*360, y:140+i*130]);
				if(kag.bookMarkDates[i*3+k]==void)
				{
					//当该位置无存档的时候
					if(type=="load")
					{
						.button(%[ graphic:"image032", name:"loadsave"+(i*3+k) , enabled:false]);//显示noData图片
					}
					else
					{
						.button(%[ graphic:"image031", name:"loadsave"+(i*3+k) , exp:"tf.saveload_index="+(i*3+k),storage:"save.ks",target:"*save_yes",enabled:true,  clickse:"click.wav", enterse:"focus.wav"]);//显示noData图片
					}
				}
				else
				{
					//当该位置有存档的时候
					if(type=="load")
					{
						.button(%[ graphic:"image032", name:"loadsave"+(i*3+k), exp:"tf.saveload_index="+(i*3+k)+",askYesNo('读档')", clickse:"click.wav", enterse:"focus.wav"]);
					}
					else
					{
						.button(%[ graphic:"image031", name:"loadsave"+(i*3+k), exp:"tf.saveload_index="+(i*3+k)+",askYesNo('覆盖存档')", clickse:"click.wav", enterse:"focus.wav"]);
					}
					.locate(%[x:60+k*360, y:159+i*130]);
					.button(%[ normal:kag.getBookMarkFileNameAtNum(i*3+k), enabled:false]);//显示存档缩略图
					var temp_date = sf.saveDataDate[i*3+k];
					if (temp_date.utc >= max_date.utc)
					{
						max_date = temp_date;
						max_date_index = %[i:i,k:k];
					}
					draw_text_to_button(parent.names["loadsave"+(i*3+k)],"%04d-%02d-%02d".sprintf(temp_date.y,temp_date.m,temp_date.d),230,90,0x0c2333,sf.font_face,14);	
					draw_text_to_button(parent.names["loadsave"+(i*3+k)],"%02d: %02d".sprintf(temp_date.h,temp_date.mm),230,70,0x0c2333,sf.font_face,14);	
				}
				draw_text_to_button(parent.names["loadsave"+(i*3+k)],"%02d".sprintf(i*3+k+1),300,60,0x0c2333,sf.font_face,14);					
			}
		}
		if(max_date_index != void)
		{
			.locate(%[x:20+max_date_index.k*360, y:159+max_date_index.i*130]);
			.button(%[ normal:"image030.png", enabled:false]);
		}
	}
}

//在按钮上画文字
function draw_text_to_button (button,text,x,y,color,face,size)
{
	// button.font.face=face;
	// button.font.height=size;
	// button.font.bold=true;
	// var w = button.font.getTextWidth(text);
	// button.drawText(x-w/2,y-size/2,text,color);
	// button.drawText(x-w/2+button.width,y-size/2,text,color);
	// button.drawText(x-w/2+button.width*2,y-size/2,text,color);
}

//获取当前时间
function getNowTime()
{
	var d = new Date();
	var temp = %[
		y:d.getYear(),
		m:d.getMonth() + 1,
		d:d.getDate(),
		h:d.getHours(),
		mm:d.getMinutes(),
		utc:d.getTime(),
	];
	return temp;
}

function check_auto_timer_handler ()
{
	// body...
	if(tf.auto_clicked == true)
	{
		if(kag.autoMode == false)
		{
			tf.auto_clicked = false;
			kag.tagHandlers.delay(%[speed:sf.text_speed]);
			kag.fore.messages[2].names['btn_auto'].loadImages("image002.png");
		}
	}
	if(tf.skip_clicked == true)
	{
		if(kag.skipMode == SKIP_NONE)
		{
			tf.skip_clicked = false;
			kag.fore.messages[2].names['btn_skip'].loadImages("image003.png");
		}
	}
	if(!tf.skip_clicked && !tf.auto_clicked)
	{
		tf.auto_clicked = false;
		tf.skip_clicked = false;
		check_auto_timer.enabled=false;
	}
}

var check_auto_timer = new Timer(check_auto_timer_handler,"");
check_auto_timer.interval = 100;
check_auto_timer.enabled=false;

function switchAutoButton ()
{
	if(!tf.auto_clicked)
	{
		tf.auto_clicked = true;
		//当处于假时，将它设为自动
		kag.tagHandlers.delay(%[speed:(100-sf.auto_speed+20)]);
		kag.enterAutoMode();
		check_auto_timer.enabled=true;
		kag.fore.messages[2].names['btn_auto'].loadImages("image009_1.png");
	}
	else
	{
		tf.auto_clicked = false;
		kag.cancelAutoMode();
		kag.fore.messages[2].names['btn_auto'].loadImages("image002.png");
	}
}

function switchSkipButton ()
{
	if(!tf.skip_clicked)
	{
		tf.skip_clicked = true;
		kag.skipToStop();
		check_auto_timer.enabled=true;
		kag.fore.messages[2].names['btn_skip'].loadImages("image009.png");
	}
	else
	{
		tf.skip_clicked = false;
		kag.cancelSkip();
	}
}

function linkChoice(add,text)
{
	dm("做了选择");
	if(add > 0)
	{
		f.score += add;
		dm("f.score + "+add+" = "+f.score);
	}
	history_p();
	history_push(text);
	history_p();
	kag.tagHandlers.current(%[layer:sf.layname_link , page:"fore"]);
	kag.tagHandlers.er(%[]);
	kag.tagHandlers.current(%[layer:sf.layname_dialog_base , page:"fore"]);
	kag.tagHandlers.er(%[]);
}

function history_push (text)
{
	if(kag.historyWriteEnabled)
	{
		if(tf.history_text.count == 0) {
			return;
		}
		var str = tf.history_text[-1].text[-1];
		while(true)
		{
			if(str.length + text.length > sf.history_list_line_length)
			{
				var t_text = text.substring(0,sf.history_list_line_length-str.length);
				text = text.substring(sf.history_list_line_length-str.length-1);
				tf.history_text[-1].text[-1] = str + t_text;
				tf.history_text[-1].text.add("");
				str="";
			}
			else
			{
				tf.history_text[-1].text[-1] = str + text;
				break;
			}
		}
	}
}

function history_set_title (name, cv)
{
	if(kag.historyWriteEnabled)
	{
		tf.history_text[-1].name = name;
		tf.history_text[-1].cv = cv+".ogg";
		tf.history_text[-1].text[-1] += "【"+name+"】";
	}
}

function history_n ()
{
	if(kag.historyWriteEnabled)
	{
		if(tf.history_text[-1].text[-1] != "")
			tf.history_text[-1].text.add("");
	}
}

function history_p ()
{
	if(kag.historyWriteEnabled)
	{
		
		if(tf.history_text.count == 0) {
			return;
		}
		if(tf.history_text[-1].text[-1] == "")
		{
			tf.history_text[-1].text.erase(tf.history_text[-1].text.count-1);
		}
		tf.history_text.add(%[text:[""]]);
	}
}

function history_init ()
{
	tf.history_text = [
		%[
			text:[""]
		]
	];
}

[endscript]

;切换到黑屏
[macro name=toblack]
[clearlayers page=back]
[trans method=crossfade time=%time|1000][wt][backlay]
[endmacro]

;指定图层切换
[macro name=lg]
[backlay]
[if exp="mp.layer[0]=='m'"]
[position layer=%layer page=back left=%left|0 top=%top|0 visible=true frame=%file]
[current layer=%layer page=back][er]
[trans method=crossfade time=%time|1000][wt]
[current layer=%layer page=fore]
[else]
[image layer=%layer page=back left=%left|0 top=%top|0 visible=true storage=%file]
[trans method=crossfade time=%time|1000][wt]
[endif]
[endmacro]

;背景切换
[macro name=bg]
[fadeoutbgm time=1000 cond="mp.music !== void"]
[if exp="mp.black=='true'"]
[backlay]
[freeimage layer=&sf.layname_bg page=back]
[freeimage layer=&sf.layname_cg page=back]
[trans method=crossfade time=%time|1000][wt]
[else]
[lg layer=&sf.layname_bg time=%time|1000 file=%file]
[endif]
[bgm file=%music cond="mp.music !== void"]
[current layer=&sf.layname_dialog_base page=fore]
[locklink]
[endmacro]

;换行
[macro name=n]
[unlocklink]
[l]
[r]
[eval exp="history_n()"]
[locklink]
[endmacro]

;换页
[macro name=m]
[unlocklink]
[p]
[eval exp="history_p()"]
[er]
[locklink]
[endmacro]

[macro name=cg]
[backlay]
[freeimage layer=0 page=back]
[freeimage layer=1 page=back]
[freeimage layer=2 page=back]
[position layer=&sf.layname_dialog_base page=back visible=false]
[position layer=&sf.layname_dialog_name page=back visible=false]
[position layer=&sf.layname_dialog_button page=back visible=false]
[eval exp="mp.index=0 if mp.index===void;tf.value_storage=sf.cg[mp.id].file[mp.index]"]
[image layer=&sf.layname_cg page=back left=%x|0 top=%y|0 visible=true storage=&tf.value_storage]
[trans method=crossfade time=%time|1000][wt]
[eval exp="sf.cg[mp.id].enabled = true"]
[dialog time=500]
[endmacro]

[macro name=tj]
[freeimage layer=&tf.tjIndex]
[image layer=&tf.tjIndex storage=%file visible=true left=%sx top=%sy opacity=0]
[eval exp="mp.tx=mp.sx if mp.tx===void"]
[eval exp="mp.ty=mp.sy if mp.ty===void"]
[move layer=&tf.tjIndex path=&("("+mp.tx+","+mp.ty+",255)") time=%time|500]
[eval exp="tf.tjIndex++"]
[endmacro]

[macro name=tjbase]
[clearlayers page=back]
[image layer=base storage=%file page=back visible=true]
[eval exp="tf.tjIndex=0"]
[trans method=crossfade time=500][wt][backlay]
[dialog time=500 extra=true]
[endmacro]

[macro name=move_cg]
[move layer=&sf.layname_cg path=&("("+mp.x+","+mp.y+",255)") time=%time][wm]
[endmacro]

[macro name=scale_cg]
[move layer=&sf.layname_cg path=(0,0,255) time=%time|500]
[action layer=&sf.layname_cg module=LayerNormalZoomModule zoom=%zoom|100 time=%time|500]
[wact layer=&sf.layname_cg][wm]
[endmacro]

[macro name=hide_cg]
[backlay]
[freeimage layer=&sf.layname_cg page=back]
[trans method=crossfade time=%time|0][wt]
[endmacro]

[macro name=bgm]
[fadeinbgm storage=%file loop=true time=%time|1000]
[endmacro]

;对话框
[macro name=dialog]
[backlay]
[position layer=&sf.layname_dialog_base page=fore frame=image001 opacity=255 width=1136 height=275 left=0 top=365 visible=true marginl=230 marginr=215 margint=155 marginb=30]
[position layer=&sf.layname_dialog_name page=fore frame="" opacity=0 width=500 height=200 left=137 top=474 visible=true]
[current layer=&sf.layname_dialog_name page=fore][er]
[position layer=&sf.layname_dialog_button page=fore frame="" opacity=0 width=1136 height=20 left=0 top=620 visible=true]
[dialogbutton extra=%extra]
[if exp="mp.time>0"]
[layopt layer=&sf.layname_dialog_base page=fore top=640]
[layopt layer=&sf.layname_dialog_name page=fore top=640]
[layopt layer=&sf.layname_dialog_button page=fore top=640 opacity=128]
[move layer=&sf.layname_dialog_base  path="(0,365,255)" time=%time]
[move layer=&sf.layname_dialog_name  path="(137,474,255)" time=%time]
[move layer=&sf.layname_dialog_button  path="(0,620,128)" time=%time]
[wm][wm][wm]
[endif]
[current layer=&sf.layname_dialog_base page=fore][er]
[locklink]
[endmacro]

[macro name=dialog_hide]
[move layer=&sf.layname_dialog_base  path="(0,640,255)" time=%time]
[move layer=&sf.layname_dialog_name  path="(137,640,255)" time=%time]
[move layer=&sf.layname_dialog_button  path="(0,640,128)" time=%time]
[endmacro]

;对话框上的文字按钮
[macro name=dialogbutton]
[current layer=&sf.layname_dialog_button page=fore][er][csysbutton]
[nowait]
[if exp="mp.extra == true"]
[locate x=990 y=0][button name=btn_auto graphic=image002 exp="switchAutoButton()" enterse=&sf.button_enter clickse=&sf.button_click]
[locate x=1035 y=0][button name=image008 graphic=image008 exp="askYesNo('退出特辑')" enterse=&sf.button_enter clickse=&sf.button_click]
[else]
[locate x=10 y=0][button name=btn_auto graphic=image002 exp="switchAutoButton()" enterse=&sf.button_enter clickse=&sf.button_click]
[locate x=55 y=0][button name=btn_skip graphic=image003 exp="switchSkipButton()" enterse=&sf.button_enter clickse=&sf.button_click]
[locate x=900 y=0][button name=image004 graphic=image004 exp="kag.callExtraConductor('history.ks','*from_game')" enterse=&sf.button_enter clickse=&sf.button_click]
[locate x=945 y=0][button name=image005 graphic=image005 exp="kag.callExtraConductor('save.ks','*from_game')" enterse=&sf.button_enter clickse=&sf.button_click]
[locate x=990 y=0][button name=image006 graphic=image006 exp="kag.callExtraConductor('load.ks','*from_game')" enterse=&sf.button_enter clickse=&sf.button_click]
[locate x=1035 y=0][button name=image007 graphic=image007 exp="kag.callExtraConductor('option.ks','*from_game')" enterse=&sf.button_enter clickse=&sf.button_click]
[locate x=1080 y=0][button name=image008 graphic=image008 exp="askYesNo('返回标题')" enterse=&sf.button_enter clickse=&sf.button_click]
[endif]
[endnowait]
[endmacro]

[macro name=switchout]
[move layer=%layer1 page=fore path="(0,-10,0)" time=%time|500]
[move layer=%layer2 page=fore path="(0,10,0)" time=%time|500]
[wm][wm]
[layopt layer=%layer1 page=fore opacity=0 visible=false]
[layopt layer=%layer2 page=fore opacity=0 visible=false]
[current layer=%layer1 page=fore][er]
[current layer=%layer2 page=fore][er]
[endmacro]

[macro name=switchin]
[layopt layer=%layer1 page=fore opacity=0 visible=true]
[layopt layer=%layer2 page=fore opacity=0 visible=true]
[move layer=%layer1 page=fore path="(0,0,255)" time=%time|500]
[move layer=%layer2 page=fore path="(0,0,255)" time=%time|500]
[wm][wm]
[endmacro]

[macro name=dm]
[eval exp="dm(mp.exp)"]
[endmacro]

[macro name=retungame]
[switchout layer1=&sf.layname_menu_base layer2=&sf.layname_menu_button]
[endmenu]
[current layer=&sf.layname_dialog_base page=fore]
[endmacro]

[macro name=role_name]
[current layer=&sf.layname_dialog_name page=fore][er][nowait]
[button normal=%file enabled=false name=role_name]
[endnowait]
[current layer=&sf.layname_dialog_base page=fore][er]
[locklink]
[if exp=mp.cv!=void]
[playse buf=&sf.cv_buf storage=%cv]
[endif]
[endmacro]

[macro name=hide_name]
[eval exp="kag.fore.messages[sf.layname_dialog_name_number].names.role_name.visible=false"]
[endmacro]

[macro name=linkbutton]
[layopt layer=&sf.layname_link page=fore visible=true]
[current layer=&sf.layname_link page=fore]
[er cond="mp.index==1"]
[locate x=&"(mp.index-1)*140+(568-140*tf.link_button_count/2)-692/2" y=&"280-100*tf.link_button_count/2 + (mp.index-1)*100-79/2"]
[button name=&"'link_'+mp.index" title=%text graphic=image54 target=&"'*label'+mp.label" exp=&("linkChoice("+mp.add+",'"+mp.text+"')") clickse=&sf.link_click enterse=&sf.link_enter]
[endmacro]

[macro name=nlink]
[eval exp="mp.label=mp.index" cond="mp.label===void"]
[eval exp="tf.link_button_count=+mp.count" cond="mp.count!=void"]
[linkbutton index=%index add=%add label=%label text=%text]
[unlocklink]
[endmacro]

[macro name=elink]
[endnowait]
[current layer=message0 page=fore]
[locate x=0 y=0]
[endmacro]

[macro name=startmenu]
[rclick enabled=false]
[history output=false enabled=false]
[endmacro]

[macro name=endmenu]
[rclick enabled=true]
[history output=true enabled=false]
[endmacro]


;======================剧情相关===========================

[macro name=bdr]
[eval exp="history_set_title('摆渡人','bdr_cv_'+(+mp.cv))"]
[dialog]
[role_name file=image011 cv=&"'bdr_cv_'+(+mp.cv)"]
[endmacro]

[macro name=fzx]
[eval exp="history_set_title('冯子曦','fzx_cv_'+(+mp.cv))"]
[dialog]
[role_name file=image010 cv=&"'fzx_cv_'+(+mp.cv)"]
[endmacro]

[macro name=qyn]
[eval exp="history_set_title('秦一诺','qyn_cv_'+(+mp.cv))"]
[dialog]
[role_name file=image013 cv=&"'qyn_cv_'+(+mp.cv)"]
[endmacro]

[macro name=bwc]
[eval exp="history_set_title('白无常','bwc_cv_'+(+mp.cv))"]
[dialog]
[role_name file=image014 cv=&"'bwc_cv_'+(+mp.cv)"]
[endmacro]

[macro name=zk]
[eval exp="history_set_title('钟馗','zk_cv_'+(+mp.cv))"]
[dialog]
[role_name file=image017 cv=&"'zk_cv_'+(+mp.cv)"]
[endmacro]

[macro name=ax]
[eval exp="history_set_title('阿玄','ax_cv_'+(+mp.cv))"]
[dialog]
[role_name file=image018 cv=&"'ax_cv_'+(+mp.cv)"]
[endmacro]

[macro name=fr]
[eval exp="history_set_title('妇人','fr_cv_'+(+mp.cv))"]
[dialog]
[role_name file=image019 cv=&"'fr_cv_'+(+mp.cv)"]
[endmacro]

[macro name=hwc]
[eval exp="history_set_title('黑无常','hwc_cv_'+(+mp.cv))"]
[dialog]
[role_name file=image016 cv=&"'hwc_cv_'+(+mp.cv)"]
[endmacro]


[macro name=hide_role]
[backlay]
[freeimage layer=%layer page=back]
[trans method=crossfade time=%time|0][wt]
[endmacro]

[macro name=role]
[locklink]
[backlay]
[freeimage layer=%layer page=back]
[eval exp="mp.pos='left' if mp.pos==void"]
[eval exp="tf.role_layer[mp.name]=mp.layer"]
[eval exp="tf.value_storage=sf.char[mp.name].files[mp.id]"]
[eval exp="tf.value_left=sf.char[mp.name][mp.pos]"]
[eval exp="tf.value_top=sf.char[mp.name].top"]
[image layer=%layer page=back storage=&tf.value_storage left=&tf.value_left top=&tf.value_top visible=true]
[trans method=crossfade time=%time|0][wt]
[endmacro]

[macro name=move_role]
[move layer=&"tf.role_layer[mp.name]" path=&("("+mp.x+","+mp.y+",255)") time=%time][wm]
[endmacro]


[return]