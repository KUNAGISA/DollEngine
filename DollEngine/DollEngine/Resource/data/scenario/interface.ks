*start
[iscript]
class Async
{
	var handler = void;
	var timmer = void;
	function Async (func)
	{
		handler = func; 
		timmer = new Timer(onFire,"");
		timmer.interval = 10;
		timmer.enabled = true;
	}

	function onFire ()
	{
		handler();
		invalidate timmer;
		invalidate this;
	}
}

class HistoryList extends KAGLayer
{
	var baseLayer;
	var offsetX=25;
	var offsetY=5;
	var lineInterval=3;

	var list_items=[];

	function HistoryList (win,par)
	{
		super.KAGLayer(...);
		setPos(293,143-parent.top,sf.history_list_width+offsetX*2,369);
		fillRect(0,0,sf.history_list_width+offsetX*2,369,0);
		visible=true;
		parent.enabled=true;
		parent.hitThreshold=256;
		baseLayer = new global.KAGLayer(window,this);
		baseLayer.width = width;
		baseLayer.visible=true;
		baseLayer.enabled=true;
		baseLayer.hitThreshold=256;
		baseLayer.font.face = sf.history_font_face;
		baseLayer.font.height = sf.history_font_size;

	}

	function finalize ()
	{
		super.finalize();
	}

	function hook_handler (shift, delta, x, y)
	{
		with(baseLayer)
		{
			if(.height < height)
				return false;
			.top += delta/2;
			if(.top > 0)
				.top = 0;
			else if(.top < -(.height-height))
				.top = -(.height-height);
		}
		return false;
	}

	function initListByShow ()
	{
		var base_top = offsetY;
		var icon = new global.Layer(window,this);
		icon.loadImages("image061");
		icon.setSizeToImageSize();
		with(baseLayer)
		{
			.height = getHistoryHeight() + offsetY*2 - lineInterval;
			.fillRect(0,0,.width,.height,0);
			for (var i = 0; i < tf.history_text.count; ++i)
			{
				var info = tf.history_text[i];
				var is_role_say = false;
				var role_say = "";
				var role_say_height = 0;
				var role_say_top = base_top;
				for (var k = 0; k < info.text.count; ++k)
				{
					var draw_text = info.text[k];
					if(draw_text[0] == "【")
					{
						var index = draw_text.indexOf("】");
						var name = draw_text.substring(0,index+1);
						draw_text = draw_text.substring(index+1);
						is_role_say = true;
						.drawText(offsetX,base_top,name,sf.history_list_hilight_color);//,255,true,128,0,0,1,1);
						.drawText(offsetX+.font.getTextWidth(name),base_top,draw_text,sf.history_list_color);//,255,true,128,0,0,1,1);
					}
					else
					{
						.drawText(offsetX,base_top,draw_text,sf.history_list_color);//,255,true,128,0,0,1,1);
					}
					role_say_height += .font.height + lineInterval;
					base_top += .font.height + lineInterval;
				};
				if(is_role_say)
				{
					.copyRect(0,role_say_top,icon,0,0,icon.width,icon.height);
					createHistoryItemHilight(role_say_top,role_say_height,info.text,i);
				}
			};
			.top = -(.height - height);
			if(.top > 0)
				.top = 0;
		}
		invalidate icon;
	}

	function getHistoryHeight ()
	{
		var height = 0;
		for (var i = 0; i < tf.history_text.count; ++i)
		{
			if(tf.history_text[i].text.count == 1 && tf.history_text[i].text == "")
				continue;
			else
				height += tf.history_text[i].text.count * (baseLayer.font.height+lineInterval);
		};
		return height;
	}

	function getListHeight ()
	{
		return Math.max(baseLayer.height-height,0);
	}

	function createHistoryItemHilight (t,h,texts,index)
	{
		var item = new global.Layer(kag,baseLayer);
		with(item)
		{
			.font.face = sf.history_font_face;
			.font.height = sf.history_font_size;
			.setPos(0,t,baseLayer.width,h);
			.fillRect(0,0,.width,.height,0);
			var base_top = 0;
			for (var i = 0; i < texts.count; ++i)
			{
				.drawText(offsetX,base_top,texts[i],sf.history_list_hilight_color);//,255,true,128,0,0,1,1);
				base_top += .font.height + lineInterval;
			};
			.cv = tf.history_text[index].cv;
			.visible=true;
			.opacity = 0;
			.hitType=htMask;
			.hitThreshold=0;
			.enabled=true;
			.onMouseUp=function  (x,y,btn)
			{
				global.Layer.onMouseUp(...);
				if(x < 0 || y < 0 || x > width || y > height)
				{
					return;
				}
				if(Storages.isExistentStorage(this.cv))
				{
					kag.tagHandlers.playse(%[storage:this.cv,buf:sf.cv_buf]);
				}
				else
				{
					dm("未找到CV文件"+this.cv);
				}
			} incontextof item;
			.onMouseEnter = function  ()
			{
				global.Layer.onMouseEnter(...);
				opacity=255;
			} incontextof item;
			.onMouseLeave = function  ()
			{
				global.Layer.onMouseLeave(...);
				opacity=0;
			} incontextof item;
		}
		list_items.add(item);
	}
}

function initHistoryList (parent)
{
	releaseHistoryList();
	// if(tf.history_list)
	// 	invalidate tf.history_list;
	tf.history_list = new HistoryList(kag,parent);
	tf.history_list.initListByShow();
	kag.addHook("onMouseWheelHook",tf.history_list.hook_handler);
}

function getHistoryListHeight ()
{
	if(tf.history_list)
		return Math.max(0,tf.history_list.getListHeight());
	else
		return 0;
}

function on_history_drop_slider (pos, draging, data)
{
	tf.history_list.baseLayer.top = -pos;
}

function releaseHistoryList ()
{
	if(tf.history_list)
	{
		kag.removeHook("onMouseWheelHook",tf.history_list.hook_handler);
		invalidate tf.history_list;
		tf.history_list=void;
	}
}

/*
	SliderLayer里的：
        if (baseImage !== void) {
            copyRect(0, 0, baseImage, 0, 0, imw, imh);
	改成
        if (baseImage !== void) {
            fillRect(0, 0, imw, imh, 0);
            copyRect(0, 0, baseImage, 0, 0, baseImage.width, baseImage.height);
*/

function on_auto_speed_change(pos, draging, data)
{
	sf.auto_speed = pos;
	// kag.tagHandlers.font(%[]);
	// var object = kag.fore.messages[sf.layname_menu_button_number].names.auto_speed;
	// object.baseImage.width = (pos - object.min)*object.baseImage.imageWidth/(object.max-object.min);
}

function on_text_speed_change(pos, draging, data)
{
	sf.text_speed = pos;
	kag.tagHandlers.delay(%[speed:100-sf.text_speed+20]);
	// var object = kag.fore.messages[sf.layname_menu_button_number].names.text_speed;
	// object.baseImage.width = (pos - object.min)*object.baseImage.imageWidth/(object.max-object.min);
}


function on_bgm_vol_change (pos, draging, data)
{
	sf.bgm_vol = pos;
	kag.tagHandlers.bgmopt(%[volume:sf.bgm_vol]);
	// var object = kag.fore.messages[sf.layname_menu_button_number].names.bgm_vol;
	// object.baseImage.width = (pos - object.min)*object.baseImage.imageWidth/(object.max-object.min);
}

function on_se_vol_change (pos, draging, data)
{
	sf.se_vol = pos;
	tf.is_se_vol_changeed = true;
	kag.tagHandlers.seopt(%[volume:sf.se_vol,buf:sf.se_buf]);
	// var object = kag.fore.messages[sf.layname_menu_button_number].names.se_vol;
	// object.baseImage.width = (pos - object.min)*object.baseImage.imageWidth/(object.max-object.min);
}

function on_cv_vol_change (pos, draging, data)
{
	sf.cv_vol = pos;
	kag.tagHandlers.seopt(%[volume:sf.cv_vol,buf:sf.cv_buf]);
	// var object = kag.fore.messages[sf.layname_menu_button_number].names.cv_vol;
	// object.baseImage.width = (pos - object.min)*object.baseImage.imageWidth/(object.max-object.min);
}

function on_skip_read_click (is_all_skip)
{
	kag.allskip = is_all_skip;
	sf.is_all_skip = is_all_skip;
	if(is_all_skip)
	{
		kag.fore.messages[sf.layname_menu_button_number].names.skip_all_open.loadButtons("image039_3");
		kag.fore.messages[sf.layname_menu_button_number].names.skip_all_close.loadImages("image040");
		kag.fore.messages[sf.layname_menu_button_number].names.skip_all_open.enabled=false;
		kag.fore.messages[sf.layname_menu_button_number].names.skip_all_close.enabled=true;
	}
	else
	{
		kag.fore.messages[sf.layname_menu_button_number].names.skip_all_open.loadImages("image039");
		kag.fore.messages[sf.layname_menu_button_number].names.skip_all_close.loadButtons("image040_3");
		kag.fore.messages[sf.layname_menu_button_number].names.skip_all_open.enabled=true;
		kag.fore.messages[sf.layname_menu_button_number].names.skip_all_close.enabled=false;
	}
}

function init_option ()
{
	kag.tagHandlers.delay(%[speed:100-sf.text_speed+20]);
	kag.tagHandlers.bgmopt(%[volume:sf.bgm_vol]);
	kag.tagHandlers.seopt(%[volume:sf.se_vol,buf:sf.se_buf]);
	kag.tagHandlers.seopt(%[volume:sf.cv_vol,buf:sf.cv_buf]);
}

function reset_vol_changeed_value ()
{
	tf.is_se_vol_changeed = false;
	tf.vol_change_value_se_timer.enabled = false;
}

tf.vol_change_value_se_timer = new Timer(reset_vol_changeed_value,"");
tf.vol_change_value_se_timer.interval = 30;
tf.vol_change_value_se_timer.enabled = false;

kag.onMouseUp = function  (x,y,btn)
{
	conductor.trigger("mouseup" + btn);
	global.Window.onMouseUp(...);
	// [XXX] ダイアログがモード状態で表示されている時，レイヤ範囲外のクリックを検知できない
	if (currentDialog !== void && btn == mbRight) with (sysbase) {
		var x = .cursorX, y = .cursorY, left = .left, top = .top;
		if (x < left || y < top || x >= left+.width || y >= top+.height) {
			onPrimaryRightClick(); // 右クリックの動作DialogLayerのフックが取得する
		}
	}

	if(tf.is_se_vol_changeed)
	{
		this.tagHandlers.playse(%[storage:sf.button_click]);
		tf.vol_change_value_se_timer.enabled = true;
	}
} incontextof kag;

[endscript]
[return]