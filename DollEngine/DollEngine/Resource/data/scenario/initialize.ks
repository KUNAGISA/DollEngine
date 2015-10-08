*start
[loadplugin module=addFont.dll]
[loadplugin module=wuvorbis.dll]
[laycount messages=7 layer=5]


[iscript]
//重载退出弹窗
Scripts.execStorage("scenario/YesNoDialog.tjs");

//图层设置
sf.layname_dialog_base = "message0"; //对话框、对白、标题按钮
sf.layname_dialog_name = "message1"; //对话框上的姓名
sf.layname_dialog_name_number = 1;
sf.layname_dialog_button = "message2"; //对话框上的按钮层
sf.layname_link = "message3"; //选择支的图层
sf.layname_link_number = 3; //选择支的图层编号
sf.layname_menu_base = "message4"; //存档、读档、设置、CG、特辑界面的底
sf.layname_menu_base_number = 4; //存档、读档、设置、CG、特辑界面的底的图层编号
sf.layname_menu_button = "message5"; //存档、读档、设置、CG、特辑界面的内容
sf.layname_menu_button_number = 5; //存档、读档、设置、CG、特辑界面的内容的图层编号
sf.layname_extra_cg = "message6"; //存档、读档、设置、CG、特辑界面的内容
sf.layname_extra_cg_number = 6;
sf.layname_close_dialog = "message9"; //最上层的弹窗图层

sf.layname_bg = "base";//背景
sf.layname_cg = "0";//CG

//效果音设置
sf.button_click = "click1.wav";//点击音效
sf.button_enter = "focus1.wav";//按钮划过音效
sf.link_click = "click1.wav";//link点击音效
sf.link_enter = "focus1.wav";//link聚焦音效
sf.se_buf = "0";
sf.cv_buf = "2";

//设定默认字体
sf.font_face = "font_20";
sf.history_font_face = "font_18";
sf.ask_font_face = "font_25";
sf.font_size = 20;
sf.history_font_size = 18;

//角色配置
sf.char = %[
	fzx:%[
		name:"冯子曦",
		files:%[
			"1"=>"fzx1",
			"2"=>"fzx2",
			"3"=>"fzx3",
			"4"=>"fzx4",
			"5"=>"fzx5",
			"6"=>"fzx6",
			"7"=>"fzx7",
			"8"=>"fzx8",
			"9"=>"fzx9",
			"10"=>"fzx10",
		],
		left:60,
		right:500,
		left_center:31,
		center:319,
		right_center:766,
		top:-100
	],
	qyn:%[
		name:"秦一诺",
		files:%[
			"1"=>"qyn1",
		],
		left:60,
		right:500,
		left_center:31,
		center:319,
		right_center:766,
		top:-100
	],
	bdr:%[
		name:"摆渡人",
		files:%[
			"1"=>"bdr1",
			"2"=>"bdr2",
			"3"=>"bdr3",
			"4"=>"bdr4",
		],
		left:60,
		right:500,
		left_center:31,
		center:319,
		right_center:766,
		top:-100
	],
	zk:%[
		name:"钟馗",
		files:%[
			"1"=>"zk1"
		],
		left:60,
		right:500,
		left_center:31,
		center:319,
		right_center:766,
		top:-100
	],
	bwc:%[
		name:"白无常",
		files:%[
			"1"=>"bwc1"
		],
		left:60,
		right:500,
		left_center:31,
		center:319,
		right_center:766,
		top:-100
	],
];

sf.history_list_width = 600;
sf.history_list_line_length = 28;
sf.history_list_color = 0x0c2333;
sf.history_list_hilight_color = 0x4557b1;
tf.history_list = void;
tf.history_text_linecount = 0;
tf.history_text = [
	// %[
	// 	text:[""]
	// ]
];

tf.role_layer=%[];

kag.autolabelmode = true;
kag.autoLabelType = 0;
if(sf.first_opened === void)
{
	//初次登录的初始化设置
	sf.first_opened = true;
	sf.saveDataDate=%[];
	sf.bgm_vol = 50;
	sf.se_vol = 50;
	sf.cv_vol = 80;
	sf.text_speed = 70;
	sf.auto_speed = 50;
	sf.is_full_screen = false;
	// kag.allskip = 0;
	sf.is_all_skip = kag.allskip;
	//结局
	sf.end = %[
		"2"=>false,
		"3"=>false
	];
	//CG开启配置
	sf.cg = %[
		"1"=>%[
			file:[
			"cg01",
			"cg01-2"
			],
			extrasmall:"cgsmall-1",
			scale:[
			113600/1800,
			100
			],
			enabled:false
		],
		"2"=>%[
			file:[
			"cg02"
			],
			extrasmall:"cgsmall-2",
			scale:[
			113600/2363
			],
			enabled:false
		],
		"3"=>%[
			file:[
			"cg03"
			],
			extrasmall:"cgsmall-3",
			scale:[
			100
			],
			enabled:false
		],
		"4"=>%[
			file:[
			"cg04"
			],
			extrasmall:"cgsmall-4",
			scale:[
			100
			],
			enabled:false
		],
		"5"=>%[
			file:[
			"cg05"
			],
			extrasmall:"cgsmall-5",
			scale:[
			100
			],
			enabled:false
		],
		"6"=>%[
			file:[
			"cg06"
			],
			extrasmall:"cgsmall-6",
			scale:[
			100
			],
			enabled:false
		],
		"7"=>%[
			file:[
			"cg07",
			"cg07-2"
			],
			extrasmall:"cgsmall-7",
			scale:[
			100,
			100
			],
			enabled:false
		],
		"8"=>%[
			file:[
			"cg08"
			],
			extrasmall:"cgsmall-8",
			scale:[
			100
			],
			enabled:false
		],
		"9"=>%[
			file:[
			"cg09"
			],
			extrasmall:"cgsmall-9",
			scale:[
			100
			],
			enabled:false
		],

	];
}

[endscript]

[call storage=interface.ks]
[deffont face=&sf.font_face]
[mappfont storage=&"sf.font_face+'.tft'"]
[return]
