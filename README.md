# DollEngine  
  
**DollEngine**是一个跨平台的游戏引擎，主要针对移动端平台。  
目前开发重心在iOS上  
它的开发目的是为了能够将PC平台的Krkr游戏，平滑移植到iOS等平台  
开发者所使用的语言是tjs和kag，未来计划制作一个配套的GameMaker工具  
  
[TOC]  

##引擎特性  
###脚本支持  
- 完全支持TJS语法  
- KAG的大部分Tag指令支持  
- KAG框架修改，以适应新引擎结构  

###新的特性  
指对比krkr，新增或改变的特性  
- 引擎：针对移动端实现对应功能（例如手势等）  
- 引擎：不再能像原版那样裁切图层，取而代之的是类似遮罩的功能  
- 引擎：透明度变化变成递归式，而非krkr那样先绘制到父层，再统一半透明  
- 引擎：Layer将自带九宫格缩放  
- 引擎：独立的文字类，华丽的文字效果  
- TJS：新增字典的迭代器类  
- KAG：可以对图层单独命名了  
- KAG：新增控件，且控件摆放更加自由（不限定于message层）  
- KAG：新增for、while、goto等KAG指令  
- KAG：可以在macro中书写iscripts  
  
###配套工具  
以下只是有所计划，具体如何未确定  
- 一套与之配合的GameMaker  
- 新的打包工具与资源加密方式  
- 可能支援本人的另一个项目face2D（类live2D）  
- 一个广告推送平台  
- 一套信息统计平台  
  
##联系我  
个人微博：http://weibo.com/u/1639392225    
目前项目尚处于开发阶段，有什么需要的请私信微博～   
   
##版权声明  
本项目使用BSD授权协议（具体参见license_my/DollEngine_license.txt）    
* 如果你使用了本引擎，请在【游戏制作人员列表】中、或【宣传】中标注使用了它（指引擎名称DollEngine），并罗列该git项目地址，以让更多人知道它（不过，这并不是必要的，只是基于作者我个人的希望）    
* 禁止使用本引擎对别人的游戏进行破解移植，但如果是自己的游戏(或已经拿到了移植授权)，欢迎使用本引擎对其进行移植    
对于项目中使用到的第三方内容：    
* 虽然本项目是BSD授权协议，但仅限于引擎部分，Qt的部分是以静态库形式链接，如果你需要对Qt库进行修改，请遵守Qt的版权协议    
* tjs2、onig、ncbind部分皆来源于krkrz项目，为BSD协议      
* 引擎使用了一个默认字体“文泉驿微米黑”，是为Apache 2.0和GPL v3双授权    
以上内容的具体版权声明内容，请参照项目中的license_my文件夹，但文件夹中的内容只是“本说明编撰时”对其授权协议的拷贝，并不代表您使用时的协议内容，仅供参考     
    
##引擎结构  
>Qt窗口  
>> 主窗口  
>>> **MainWindow**  
>  
>> 控制台(未实装)  
>>> **Console**  
>  
>> 弹窗(未实装)  
>>> **MessageBox**正常的确认取消弹窗  
>>> **InputDialog**输入框弹窗  
>  
> 引擎层  
>> Draw  
>>> **Effect** ShaderProgram基类  
>>> **SpriteFrame** 图片帧  
>>> **Texture2D** 贴图  
>>> **DrawEngine** 绘图引擎  
>  
>> System  
>>> **Debug** 打印、输出到控制台之类的接口  
>>> **Device** 硬件相关设置、配置接口  
>>> **Storages** 文件系统，包括路径处理、读出写入的接口  
>>> **Scripts** 脚本系统，主要提供tjs的入口，以及Bind  
>>> **Scheduler** 调度器，循环用  
>>> **MouseEventManager** 鼠标事件管理器  
>  
>> Widget  
>窗口部件，玩家的主要交互目标  
>>> **BaseCanvas** 画布，相当krkr中的Window  
>>> **Layer** 图层，能够接收点击事件、能够加载图片  
>>> **Input** 输入框(未实装)  
>>> **Label** 文字(未实装)  
>>> **Particle** 粒子特效(未实装)  
>  
>> Component  
> 组件是用于对象扩展功能的东西，开发者可以将组件“挂靠”在BaseCanvas或Layer上，以期获得对应功能  
>>> **ComObject** 所有组件的基类  
>>> **Timer** 带计时器解决方案的组件(未实装)  
>>> **ShaderEffect** 带自定义Shader的组件(未实装)  
>>> **GridEffect** 网格特效组件(未实装)  
>>> **Action** 动作组件(未实装)  
>  
>> IAP(未实装)  
>内购  
>>> **AppleStore** 苹果商店  
>  
>> Network(未实装)  
>网络协议接口  
>>> **HttpNetwork** Http协议  
>>> **Socket** socket长连接  
>  
> TJS层(未实装)  
> TJS使用krkr的tjs库，未来可能置换成另行开发的sara脚本  
>> MainWindow  
>>> **MainWindow**  
>>> **Console**  
>>> **MessageBox**  
>>> **InputDialog**  
>  
>> System  
>>> **Debug**  
>>> **Device**  
>>> **Storages**  
>>> **Scripts**  
>  
>> Widget  
>>> **BaseCanvas**  
>>> **Layer**  
>>> **Input**  
>>> **Label**  
>>> **Particle**  
>  
>> Component  
>>> **ComObject**  
>>> **Timer**  
>>> **ShaderEffect**   
>>> **GridEffect**   
>>> **Action**   
>  
>> IAP  
>>> **AppleStore**  
>  
>> Network  
>>> **HttpNetwork**  
>>> **Socket**  
>  
> KAG层（未实装）  
>   

##开发计划  
###目前正在进行中  
* iOS移植  
* Label功能制作  
* Input功能制作  
* Action功能制作  
-- MoveTo  
-- FadeTo  
* Trans功能制作  
-- crossfade模式trans  

###预定下一步计划  
* 实装TJS  
* 新版KAG框架搭建  