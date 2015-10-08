*start|
[iscript]
//剧本的初始化
f.score=0;
[endscript]
[rclick enabled=true]
[history output=true enabled=false]
[eval exp="history_init()"]
[bgm file=3 time=1000]
[bg file=cj1]
[dialog time=500]
;[dialog time=0]
醒过来时，我正身处一片花海。[n]
[playse storage=step13b loop=false]
这开得铺天盖地的妖异奇花，我知道她们叫做曼珠沙华。[n]
血色的花瓣将整个幽冥界都染成了赤红，却奇异的不添半分喜色。[n]
脚下有一条路，明明从未走过，我却知道它的名字叫黄泉路；黄泉路上无老少，走在这条路上的人只能继续向前，既不能回头，也不能后退。[m]
[bg file=cj2 x=11 y=0]

路的尽头我看到一条河，不知从哪里来，也不知往哪里去。我左右寻找，却没有找到任何表示名字的石碑或木牌。我问了候在那里的摆渡人，他却只是笑笑，说没有人记得这河的名字，就叫它【忘川】。[m]
[cg id=1 x=-600 y=-100]
[bdr cv=1]「小哥，你可是最后一个了，上来吧。」[m]
[cg id=1 x=0 y=-200]
[fzx cv=1]「在下冯子曦。」[m]
我朝摆渡人作了个辑，自我介绍道。[m]
[cg id=1 index=1]
[bdr cv=2]「嗯，上来吧。」[m]
[bdr cv=3]「稀奇稀奇，为何不见接引你的鬼差？」[m]
[fzx cv=2]「接引的鬼差？」[m]
[bdr cv=4]「新魂第一次来这阴间，若无小鬼接引，怕是会走茬了地方。」[m]
[bdr cv=5]「不过，呵，小哥你一身正气，可能是那小鬼道行不够，被你吓跑了。」[m]
[fzx cv=3]「我……把鬼吓跑了？怎么会这样？」[m]
[hide_name time=1000]
摆渡人只笑不语。[m]
[hide_cg time=1000]
[bg file=cj3]
我赶紧上船，稀奇这摆渡人明明手中没有浆，这船却稳稳当当的驶向对岸。船在行驶，忘川却没有半点声响，我想伸手试试忘川里的水，却被摆渡人给制止了。[n]
摆渡人告诉我，忘川里流的不是水，而是记忆，有人的记忆，有器物的记忆，有时间的记忆；时而战火连天，时而歌舞升平，却没有丝毫声响。摆渡人说，有了声响，会唤起眷恋，就不愿意过河了。[n]
我心里奇怪，若不许人眷恋，又为何要留下这景象？[n]
摆渡人似是知道我心里所想，只说，这是他的私心。[n]

[nlink index=1 count=2 text=既然是不能与人言的私心，我也便作无声。 cond="!(sf.end[2]&&sf.end[3])"]
[nlink index=1 count=3 text=既然是不能与人言的私心，我也便作无声。 cond="sf.end[2]&&sf.end[3]"]
[nlink index=2 add=1 text=摆渡人愈是如此说，我愈是对这「私心」充满好奇。]
[nlink index=3 add=10 text=是摆渡人的私心也好，纯粹的喜好也罢，我只低头看人间世事百态。 cond="sf.end[2]&&sf.end[3]"]
[s]

*label1
;【转04（+0）】
[jump storage="04.ks"]
[s]

*label2
;【转02（+1）】
[jump storage="02.ks"]
[s]

*label3
;【通关结局2和3才开启】
;【转03（+10）】
[jump storage="03.ks"]
[s]