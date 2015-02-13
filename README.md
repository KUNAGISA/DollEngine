DollEngine  
===========  
  
一个跨平台2d引擎，使用OpenGL，脚本将采用krkr的tjs2，并寄望于能够平滑移植PC端krkr项目到本引擎上  
  
-------------------------  
作者本人开发环境为MacOSX 10.9 + GLES2，优先支持MacOS平台，次级优先支持iOS平台   
本项目当前目标：  
1、将KRKR的功能在ios上重新实现一遍（与2进行中）  
2、尽可能移植kag系统（与1交替进行中）  
3、根据手机特性实现新的内容  
  
计划在原版KRKR的基础上做出调整：  
--------------------------  
  
表现层的改动  
* 不再像原版Kr那样图层裁切image  
* Layer类的opacity属性，在半透明绘制时只采用简单的透明度传递，  
  而非像KR那样先将子层绘制到父层缓冲，再整体半透明  
* Layer将自带九宫格放大的接口
* 将原KAG中的Action相关类的底层转移至C++实现  
* 独立文字类，使之能够显示更华丽的文字效果  
* 【计划在未来】新增Effect类，提供一些图层效果，此外添加用户自定义特效设计的接口（设计Shader）  
* 【计划在未来】本人的另一个项目Face2D（类似Live2D的项目）将对本项目进行支援  
* 【计划在未来】骨骼动画的支援  
* 【计划在未来】粒子特效的支援  
  
事件层的改动  
* 新增对手机的常用事件（例如切换应用到后台）支援  
* 【计划在未来】新增对多点触摸的支援   
* 【计划在未来】新增手势事件的支援  
  
控件层的改动  
* 控件因为绘图层的改动，修改了显示机制  
* 新增控件  
* UI不再限定于message层了（但依旧建议只放在message层）  
* 可以通过kag指令针对单个UI进行属性操作了（例如移动单个按钮）  
* 【计划在未来】可以直接通过指定格式的配置生成UI  
* 【计划在未来】有一套跨平台的界面编辑器  
  
KAG指令的改动  
* 你将可以在macro中书写iscript  
* 你可以在kag指令中使用for、while、goto  
* 移除了一些不常用的kag指令：（待定）  
  
开发者支援  
* 如果你未对原版system文件夹下内容进行修改，你将能较为方便地移植项目  
* 你可以像在原版krkr中使用tjs那样，在本项目中使用tjs  
* 你可以拥有对字典的迭代器  
* 更方便的资源、脚本加密  
* 【计划在未来】内置网络协议类NetWork，默认为HTTP协议  
* 【计划在未来】新增平台相关接口类Platform，里面的内容——例如支付或者广告  
* 【计划在未来】有一套针对本项目的GameMaker  
  
--------------------------  
个人微博：http://weibo.com/u/1639392225  
目前项目尚处于开发阶段，有什么需要的请私信微博～  
  
版权声明  
--------------------------  
本项目使用BSD授权协议（具体参见license_my/DollEngine_license.txt）  
* 如果你使用了本引擎，请在【游戏制作人员列表】中、或【宣传】中标注使用了它（指引擎名称），并罗列该git项目地址，以让更多人知道它（不过，这并不是必要的，只是基于本人的希望）  
* 禁止对别人的游戏进行破解移植，Krkr-GL不是用来干这事的，但如果是自己的游戏(或已经拿到了移植授权)，欢迎移植到本引擎上  
对于项目中使用到的第三方内容：  
tjs2、onig、ncbind、freetype2、kazmath以及部分cocos2d-x内容
本项目为了适应MAC平台对以上部分内容作了修改，若要对这些内容进行进一步修改，请沿用其本身的授权协议    
以上内容的具体版权声明内容，请参照项目中的license_my文件夹，但文件夹中的内容只是“本说明编撰时”对其授权协议的拷贝，并不代表其“当前”的协议内容，仅供参考   
  
