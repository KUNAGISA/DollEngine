*start
[position layer=message0 page=fore visible=true]
[current layer=message0 page=fore]
因为标题界面尚未制作的原因，这些按钮全部都是开始游戏的功能[r][r]
[link target=*gamestart]开始游戏开始游戏开始游戏开始游戏开始游戏开始游戏开始游戏开始游戏[endlink][r]
[link target=*gamestart]继续游戏[endlink][r]
[link target=*gamestart]自由解锁[endlink][r]
[link target=*gamestart]系统设置[endlink][r]
[link target=*gamestart]退出游戏[endlink][r]
@s

*gamestart
[eval exp="dm(kag.skipByClick)"]
[current layer=message0 page=fore]
[cm]

[eval exp="f.eventstore='序章'"]

;[jump storage=room.ks target=*start]
[jump storage=event.ks target=*start]