[wait time=200]
;[image layer=base page=back storage=alice1]
;[trans method=crossfade time=1000]
[position layer=message0 color=0xff8800 marginl=30 marginr=60 margint=30 marginb=60 ]

[slider base=bar_lv.png graphic=btn_daanniu.png position=100]
[iscript]

var rtt = new RTTLayer(kag,null);
rtt.initSize(1136,640);
rtt.draw(kag.sysbase);
dm(rtt.save("test.png"));
[endscript]
[s]

*aaa
[load place=0]
哈哈哈哈哈哈哈