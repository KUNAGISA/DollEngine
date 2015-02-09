*start
[iscript]
// var lay = new GraphicLayer(kag,kag.fore.base);
// lay.left = 200;
// lay.top = 200;
// lay.loadImages("bg1");
// lay.Canvas.imageWidth = 512;
// lay.Canvas.imageHeight = 384;
// lay.opacity=128;
[endscript]
;@call storage=macro.ks target=*loadfiles
;欢迎来到KrkrGL的世界[r]
;[backlay]
[image layer=0 storage="logo" visible=true]
[iscript]
// Actions.run(kag.fore.layers[0],2,1,0)
// Actions.run(cp,2,1,0)
var cp = new Object();
cp.parent = kag.fore.base;
var rtt = new RTTCanvas();
cp.rtt = rtt;
rtt.width = kag.innerWidth;
rtt.height = kag.innerHeight;
rtt.object = cp;
cp.rtt.render(kag.fore.layers[0],0,0);
cp.onPaint = function () 
{
	rtt.trigger();
} incontextof cp;
kag.fore.layers[0].visible = false;
[endscript]

;@jump storage=menus.ks