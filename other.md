
黑珍珠软件API手册
==================

**希格斯动力科技(珠海)有限公司**  
*文档版本：v1.0.1*  
*修订日期：20180912*  
*软件版本：v0.0.2*  

---------------------------------------

索引
================

*   [历史版本](#hisver)
    *   [v0.0.2](#ver0.0.2)
*   [通讯方式](#commed)
    *   [TCP Socket](#tcpsock)
    *   [串口](#serial)
*   [TCP Socket 接口使用说明](#tcpuse)
    *   [通用解释](#tcpgexp)
    *   [协议内容](#tcpprocont)
    *   [示例](#tcpexample)
*   [串口 接口使用说明](#seruse)
    *   [通用解释](#sergexp)
    *   [协议内容](#serprocont)
    *   [示例](#serexample)
*   [其他说明](#docauthor)

**注：**最新文档的官方地址，浏览请单击[此处][src] 。

  [src]: http://www.higgsdynamics.com/

* * *

<h2 id="hisver">历史版本</h2>

<h3 id="ver0.0.2">v0.0.2</h3> 

此版本完成了机器人最基本的功能：移动、地图标记、位置校订、状态反馈、参数设置与获取、地图存取、开关机、系统更新。

* * *

<h2 id="commed">通讯方式</h2>


<h3 id="tcpsock">TCP Socket</h3>

**协议形式**：接口内容采用类url的字符串格式，接口反馈数据统一采用json格式，同级字段间没有前后关系，解析时请使用json的标准解析方式。

> =============================================================================  
> 网络设置：TCP客户端  
> 服务器IP地址：
> > a) 192.168.10.10(这个是底盘主机的静态IP地址，TCP客户端主机需要通过路由器等设备与底盘主机建立局域网连接，有相同网段192.168.10.*)  
> > b) 底盘通过API连接上局域网WiFi, 然后通过API获取的局域网IP。   
>  
> 服务器端口：36008  
> 
> =============================================================================   


<h3 id="serial">串口</h3>

**协议形式**：接口内容采用报文格式，报文主要包含*帧头*(1字节)+*帧长度*(2字节)+*指令码*(4字节)+*参数*(可变长度)+*校验码*(1字节)+*帧尾*(1字节)。   
> =============================================================================  
> 串口设置：需要连接底盘串口接口
> 通信协议格式：
> > |  | 帧头 | 帧长度 | 指令码 | 参数 | 校验码 | 帧尾 |    
> > | ------ | ------ | ------ | ------ | ------ | ------ | ------ |       
> > | 长度 | 1字节 | 2字节 | 4字节 | 可变长度 | 1字节 | 1字节 |   
> > | 定义 | 0xFD | 帧长度 | 模块代码(2字节)+具体命令(2字节) |  | 校验和 | 0xF8 |   
> >
> > 帧长度：指令码长度+参数长度+校验码长度；   
> > 校验码：帧长度数值+指令码数值+参数数值，取其和的低位数据；   
> > 协议传输过程中，若命令中使用到帧头、帧尾，则采用字符转义方式解决，如下:
> > 
> > | 源字符 | FD | F8 | FE |   
> > | ------ | ------ | ------ | ------ |   
> > | 转义字符 | FE 7D | FE 78 | FE 7E |   
> 
> =============================================================================   

* * *

<h2 id="tcpuse">TCP Socket 接口使用说明</h2>

<h3 id="tcpgexp">通用解释</h3>

*   通用参数”uuid”:
    > 如不做特殊说明，以下指令中均可携带uuid作为可选参数, server端执行完指令后在response中将其原样返回。  
*   对于json中”type”字段的解释：
    > “response” 表示对一条指令的响应  
    > “callback” 表示由server端以一定频率发送的数据  
    > “notification” 表示由server端发起的主动通知
>  示例：  
>   客户端发送字符串: “/bpi/move?marker=target_name&uuid=123456”   
>   
> 返回：   
>   {  
      &nbsp;&nbsp;&nbsp;"type":"response",      /* package类型 */  
      &nbsp;&nbsp;&nbsp;"cmd":"/bpi/move",   /* 源指令 */  
      &nbsp;&nbsp;&nbsp;"emsg":"",     /* 错误消息 */  
      &nbsp;&nbsp;&nbsp;"status":"OK",          /* 执行结果 */  
      &nbsp;&nbsp;&nbsp;"uuid":"123456"         /* 用户定义的uuid */  
    }

<h3 id="tcpprocont">协议内容</h3>

| 指令 | 参数 | 返回 | 描述 |
| ------ | ------ | ------ | ------ |
| /bpi/move | marker:目标点位代号<br/>location:(x,y,theta)<br>说明：marker和location二选一，location优先级高于marker | {<br/>&nbsp;&nbsp;"type":"response",<br/>&nbsp;&nbsp;"cmd":"/bpi/move",<br/>&nbsp;&nbsp;"uuid":"",<br/>&nbsp;&nbsp;"status":"OK",<br/>&nbsp;&nbsp;"emsg": ""<br/>} | 使机器人从当前位置移动至地图中已经标定的某个目标点。在运动过程中使用自动导航和避障功能。 |
| /bpi/move/cancel | 无 | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd": "/bpi/move/cancel",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": ""<br/>} | 使机器人主动放弃当前正在执行的移动任务，成功取消后可使机器人进入新的待命状态。在机器人执行/bpi/move移动命令过程中，如果需要终止机器人当前的移动状态，可以调用此接口。机器人会在接收“移动取消”命令之后，原地停止，等待再次的move指令。 |    
| /bpi/move_access | avel:角速度,取值(-1.0,1.0)rad/s<br/>lvel:线速度,取值(-0.5,0.5)m/s | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd": "/bpi/move_access",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": ""<br/>} | 对机器人进行部分的直接控制，如自转或停止（此控制优先级高于move指令），返回OK表示机器人已成功接收并开始运行此指令。在运动过程中不使用自动导航和避障功能。 |   
| /bpi/istop | flag:进入或退出急停模式(取值true/false) | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd": "/bpi/istop",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": ""<br/>} | 使机器人进入自由停止模式，机器人可被推动。 |   
| /bpi/markers/insert | name:点位名字<br/>type:点位类型，0(一般点位)，1（充电桩）。可选，默认为0 | 操作成功时返回：<br/>{<br/>&nbsp;&nbsp;"type": <br/>&nbsp;&nbsp;"response",<br/>&nbsp;&nbsp;"cmd": "/bpi/markers/insert",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": ""<br/>} | 在当前地图中标记点位，让机器人记住这个点位（marker）。<br/>调用此接口时，机器人会捕捉当前相对于地图坐标系的(x,y,theta)，并自动把捕捉到的锚点位置，存储在机器人的锚点列表中，以随时响应move的调用。如果不使用充电功能，接口中的type可以不设置。 |   
| /bpi/markers/query_list | 无 | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd":"/bpi/markers/query_list",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": "",<br/>&nbsp;&nbsp;"results":<br/>&nbsp;&nbsp;{<br/>&nbsp;&nbsp;&nbsp;"meeting_room": <br/>&nbsp;&nbsp;&nbsp;{<br/>&nbsp;&nbsp;&nbsp;&nbsp;"floor": 1, <br/>&nbsp;&nbsp;&nbsp;&nbsp;"pose": {<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"orientation": {<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"w": -0.899999976158142, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"x": 0, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"y": 0, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"z": -0.430000007152557<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"position": {<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"x": -8.57999992370605, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"y": 6.3600001335144, <br/> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"z": 0<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"marker_name":"meeting_room", <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"key": 0<br/>&nbsp;&nbsp;&nbsp;}, <br/>&nbsp;&nbsp;&nbsp;"bed_room": <br/>&nbsp;&nbsp;&nbsp;{<br/>&nbsp;&nbsp;&nbsp;&nbsp;"floor": 1, <br/>&nbsp;&nbsp;&nbsp;&nbsp;"pose": {<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"orientation": {<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"w": -0.899999976158142, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"x": 0, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"y": 0, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"z": -0.430000007152557<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"position": {<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"x": -8.57999992370605, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"y": 6.3600001335144, <br/> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"z": 0<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"marker_name":"bed_room", <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"key": 0<br/>&nbsp;&nbsp;&nbsp;}<br/>&nbsp;&nbsp;}<br/>}// "marker_name"表示点位名称。"key"表示点位类型：0(一般点位)，1（充电桩）。"floor"表示点位所属楼层。"pose"表示具体坐标点。 | 获取机器人在某场景地图中的所有点位(markers)信息。<br/>通过/bpi/markers/insert设置的锚点位置，可以通过此接口进行json格式的锚点列表查阅。results内容以字典形式查阅，其中目前包括信息有“楼层”、“点位坐标”、“显示名称”和“类型”。 |   
| /bpi/position_adjust | marker:用以校定位置的marker名 | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd":"/bpi/position_adjust",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": ""<br/>} | 该接口用于机器人初始化自身位置，可将机器人推至已存入marker列表的任一位置，然后用指定的marker的坐标校定机器人当前位置。 |   
| /bpi/request_data | topic:请求的实时数据类型,目前仅接受”robot_status”类型<br/>switch:开启/停止数据发送(取值on/off)<br/>frequency:发送频率[1, 10] | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd": "/bpi/request_data",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": ""<br/>} | 请求server端以一定频率发送topic类型的数据。当请求成功后，server端会以一定频率发送数据给请求的client。 |   
| /bpi/set_params | max_speed_ratio:机器人最大行进速度(百分比,取值[0.3, 1.0]) | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd": "/bpi/set_params",<br/>&nbsp;&nbsp; "uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": ""<br/>} | 设置机器人的参数。 |   
| /bpi/get_params | 无 | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd": "/bpi/get_params",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": "",<br/>&nbsp;&nbsp;"results": {<br/>&nbsp;&nbsp;&nbsp;"max_speed_ratio": 0.5<br/>&nbsp;&nbsp;&nbsp;}<br/>} | 获取机器人可设置的参数列表以及当前值。 |   
| /bpi/wifi/list | 无 | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd": "/bpi/wifi/list",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": "",<br/>&nbsp;&nbsp;"results": {<br/>&nbsp;&nbsp;&nbsp;"SSID1": 50,<br/>&nbsp;&nbsp;&nbsp;"SSID2": 30,<br/>&nbsp;&nbsp;&nbsp;"SSID3": 80,<br/>&nbsp;&nbsp;&nbsp;}<br/>} | 获取机器人当前可用的WiFi列表，返回中包含SSID和信号强度。 |   
| /bpi/wifi/connect | SSID:WiFi的SSID<br/>password:WiFi密码 | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd": "/bpi/wifi/connect",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": "",<br/>} | 使机器人连接到环境WiFi或切换当前连接的环境WiFi。 |   
| /bpi/wifi/get_active_connection | 无 | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd": "/bpi/wifi/get_active_connection",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": "",<br/>&nbsp;&nbsp;"results":"SSID1"   // 如果当前未连接到WiFi，则results为空""<br/>} | 获取机器人当前连接的WiFi的SSID. |   
| /bpi/wifi/info | 无 | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd": "/bpi/wifi/info",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": "",<br/>&nbsp;&nbsp;"results":{<br/>&nbsp;&nbsp;&nbsp;&nbsp;"IPaddr": "192.168.XXX.XXX", // 如果未连接WiFi则为空“”<br/>&nbsp;&nbsp;&nbsp;&nbsp;"HWaddr": "xx:xx:xx:xx:xx:xx", // 连接WiFi网卡的物理地址<br/>&nbsp;&nbsp;&nbsp;&nbsp;},<br/>} | 获取机器人当前通过环境WiFi分配到的IP地址和无线网卡的物理地址。 |   
| /bpi/map/list | 无 | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd": "/bpi/map/list",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": "",<br/>&nbsp;&nbsp;"results":{<br/>&nbsp;&nbsp;&nbsp;&nbsp;"map_name_1": [1,2,3,4,5], // 地图map_name_1中有1-5层<br/>&nbsp;&nbsp;&nbsp;&nbsp;"map_name_2": [10],<br/>&nbsp;&nbsp;&nbsp;&nbsp;},<br/>} | 获取机器人中所有的地图名称和楼层。 |    
| /bpi/map/set_current_map | map_name:地图名<br/>floor:楼层 | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd": "/bpi/map/set_current_map",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": "",<br/>} | 设置机器人当前地图。 |   
| /bpi/map/get_current_map | 无 | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd": "/bpi/map/get_current_map",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": "",<br/>&nbsp;&nbsp;"results":{<br/>&nbsp;&nbsp;&nbsp;&nbsp;"map_name": "map_name_1",<br/>&nbsp;&nbsp;&nbsp;&nbsp;"floor": "5"<br/>&nbsp;&nbsp;&nbsp;&nbsp;},<br/>} | 获取机器人当前地图。 |   
| /bpi/shutdown | reboot:关机后是否重启,取值(true,false)缺省为false | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd": "/bpi/shutdown",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": "",<br/>} | 调用接口关闭或者重新启动机器人,在电源关闭之前会有通知发出(见接口 “机器人主动通知”)，在通知发出后10s电源关闭。如果是重启的话, 重新上电与电源关闭间会有5s间隔。 |   
| /bpi/soft/get_version | 无 | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd": "/bpi/soft/get_version",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": "",<br/>&nbsp;&nbsp;"results":"x.x,x",    // 当前软件版本<br/>} | 获取当前软件版本。 |   
| /bpi/soft/check_for_update | 无 | 成功返回:<br/>{<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd": "/bpi/soft/check_for_update",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": "",<br/>&nbsp;&nbsp;"results":{<br/>&nbsp;&nbsp;&nbsp;&nbsp;"version_latest":"x,x,x",   // 当前版本<br/>&nbsp;&nbsp;&nbsp;&nbsp;"version_current":"x.x.x",  // 最新版本<br/>&nbsp;&nbsp;&nbsp;&nbsp;"enable_update":bool,  // 能否更新，true->能更新，false->不能更新<br/>&nbsp;&nbsp;},<br/>}<br/>失败返回:<br/>{<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd": "/bpi/soft/check_for_update",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "UNKNOWN_ERROR",<br/>&nbsp;&nbsp;"emsg": "xxx",    // 错误消息<br/>} | 检查是否有新版本可以更新，返回当前版本、最新版本和是否可以更新。 |   
| /bpi/soft/update | 无 | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd": "/bpi/soft/update",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": "",<br/>} | 更新软件到最新版本。 |   
| -------------------------------- | -------------------- | -------------------------------- | -------------------------- |   
| 机器人主动通知 | code:通知的代码<br/>description:代码的解释<br/>level:通知的级别<br/> | 例如：<br/>{<br/>&nbsp;&nbsp;"type": "notification",<br/>&nbsp;&nbsp;"code": "01001"<br/>&nbsp;&nbsp;"level": "info"<br/>&nbsp;&nbsp;"description": "The move task is started."<br/>} | 机器人主动发出通知给所有连接的client，客户端在收到通知后可以进行相应的动作，比如语音播报等。 |     

<h3 id="tcpexample">示例</h3>

1.机器人移动功能
-------------
**指令**  

    /bpi/move  

**例子**  

    发送:  
    /bpi/move?marker=target_name
    // 调用移动接口，移动至代号为"target_name"的目标点
	/bpi/move?location=15.0,4.0,1.5707963
    // 调用移动接口，移动至location(15.0, 4.0, pai/2)的目标点

**其他说明**  

> **协议中对于移动指令部分包括两大主要的形式：**
> 
> 1.   对于需要使机器人在运动过程中使用自动导航和避障功能的，请使用此接口.
> 2.   如果需要使用诸如手柄遥控功能的，请使用/bpi/move_access，会直接操控机器人两轮的速度.

    参数中的location的坐标是相对于“地图”坐标系的，由于直接调用(x、y、theta)在使用中不够直观和方便，提供“事先标锚点，而后使机器人重返锚点”的工作形式。之后“锚点”统一用marker代称，设置和查询已设锚点的方式见/bpi/markers/insert、bpi/markers/query_list。
    机器人采用自动导航和避障的过程中，机器人会自动规划路径和调节速度，过程中不需要操作者干预。操作者可以监听robot_status(机器人整体和行进状态)，或者等待相应的notification，以了解任务完成情况和整机状态。

2.移动取消功能
-------------
**指令**  

    /bpi/move/cancel  

**例子**  

    发送:  
    /bpi/move/cancel
    // 取消当前正在进行的移动指令

3.机器人直接控制指令
-------------
**指令**  

    /bpi/move_access  

**例子**  

    发送:  
    /bpi/move_access?avel=0.5&lvel=0.2  
    // 调用移动接口,机器人以角速度0.5rad/s逆时针转动，同时以线速度0.2m/s前进。

**其他说明**  

> **/bpi/move已提供了机器人带路径规划和自动避障的移动功能，相对而言，此接口提供人工控制的遥控移动功能。遥控的方式为控制机器人行进的线速度和角速度，其单位分别为m/s和rad/s；通过两值设置可以自行控制转弯半径等机器人运动表现形式**
> 
> =============================================================================================
> 机器人运动方向和角速度、线速度符号说明如下：  
>
> | 线速度 | 角速度 | 机器人行进表现 | 备注 |   
> | ------ | ------ | ------ | ------ |  
> | 0 | 正 | 机器人原地左转 | 机器人角速度设值范围为 (-1.0 ~ 1.0)rad/s |   
> | 0 | 负 | 机器人原地右转 | 机器人角速度设值范围为 (-1.0 ~ 1.0)rad/s |   
> | 正 | 0 | 机器人前进 | 机器人线速度设值范围为 (-0.5 ~ 0.5)m/s |   
> | 负 | 0 | 机器人后退 |  |  
> | 正 | 正 | 机器人前进且左转 |  |  
> | 正 | 负 | 机器人前进且右转 |  |  
> | 负 | 正 | 机器人倒车且左转 |  |  
> | 负 | 负 | 机器人倒车且右转 |  | 
>
> ***如果传入的参数超出限定范围，模块内部会按最大预设工作***  
> ***从安全方面考虑，单个命令的持续时间为0.5秒，但输入频率可以大于2Hz。连续的指令发送可使机器人运动连贯，比如把命令映射到手柄控制键位上***

4.机器人急停控制指令
-------------
**指令**  

    /bpi/istop  

**例子**  

    发送:  
    /bpi/istop?flag=true  //进入急停模式
    /bpi/istop?flag=false  //退出急停模式

**其他说明**  

    机器人硬件平台提供了一个急停控制按钮，按动此按钮可使机器人进行自动停车状态。除此硬件按钮之外，软件接口等价的提供一个急停控制指令，软件开启急停模式之后，也可使机器人进入自由停止模式。需要注意的是，软件和硬件的急停接口是分别控制机器人急停状态的，不可以相互解锁。

5.插入新的marker点位
-------------
**指令**  

    /bpi/markers/insert  

**例子**  

    发送:  
    /bpi/markers/insert?name=205_room
    //调用该接口，将机器人当前位置设为marker点位，名字为205_room。默认为1层一般点位。  
	/bpi/markers/insert?name=charge_dock_2&type=11  
    //调用该接口，将机器人当前位置设为marker点位，名字为charge_dock_2，类型为充电桩。

6.获取marker点位列表
-------------
**指令**  

    /bpi/markers/query_list  

**例子**  

    发送:  
    /bpi/markers/query_list

**其他说明**  

    orientation中的数据一般用户无需使用，它以四元数的方式保存机器人的角度，可以转化成前文阐述的坐标系中的theta

7.机器人初始位置校定
-------------
**指令**  

    /bpi/position_adjust  

**例子**  

    发送:  
    /bpi/position_adjust?marker=001
    //告知机器人当前处于代号为001的marker点位上

8.请求机器人实时数据
-------------
**指令**  

    /bpi/request_data  

**例子**  

    发送:  
    /bpi/request_data?topic=robot_status&switch=on&frequency=1
    //请求server以1HZ的频率发送机器人全局状态

**其他说明**  

> **成功请求后，server以1HZ的频率发送topic为robot_status的数据, type为callback**

    {
      "type": "callback",
      "topic": "robot_status",
      "results":
      {
         "move_target": "target_name",
         "move_status": "running",
         "move_retry_times": 3, //此次数每增加1，表示机器人进行了新一轮的路径重试；路径规划一次性成功此值默认为0
         "charge_state": bool, //true->充电中状态。false->未充电状态。
         "soft_istop_state": bool, // 通过API接口设置的软急停状态, true->急停中，false->非急停中
         "hard_istop_state": bool, // 通过硬件急停按钮设置的硬急停状态, true->急停中，false->非急停中
         "istop_state": bool,  // hard_istop_state || sofpt_istop_state, true->急停中，false->非急停中
         "power_percent": 100, //电量百分比，单位：%
         "current_pose": {
            "x": 11.0,     // 单位：m
            "y": 11.0,       // 单位：m
            "theta": 0.5, //单位：rad
         }
         "current_floor": 16
      }
	}


9.设置参数
-------------
**指令**  

    /bpi/set_params  

**例子**  

    发送:  
    /bpi/set_params?max_speed_ratio=0.5
    //设置机器人最大行进速度为0.5

**其他说明**  

    需要注意的是：调用此接口后无论是否成功，返回的json中“status”字段都是“OK”。如果想确定参数是否设置成功，请调用/bpi/get_params获取参数获取参数后查看参数的当前值。

10.获取参数
-------------
**指令**  

    /bpi/get_params  

**例子**  

    发送:  
    /bpi/get_params
    //获取参数列表和当前值

11.获取机器人当前可用的WiFi列表
-------------
**指令**  

    /bpi/wifi/list  

**例子**  

    发送:  
    /bpi/wifi/list

12.连接WiFi
-------------
**指令**  

    /bpi/wifi/connect 

**例子**  

    发送:  
    /bpi/wifi/connect?SSID=SSID1&password=123456

13.获取当前连接的WiFi
-------------
**指令**  

    /bpi/wifi/get_active_connection 

**例子**  

    发送:  
    /bpi/wifi/get_active_connection

14.获取机器人IP和无线网卡地址
-------------
**指令**  

    /bpi/wifi/info 

**例子**  

    发送:  
    /bpi/wifi/info

15.获取地图列表
-------------
**指令**  

    /bpi/map/list

**例子**  

    发送:  
    /bpi/map/list


16.设置当前地图
-------------
**指令**  

    /bpi/map/set_current_map

**例子**  

    发送:  
    /bpi/map/set_current_map?map_name=map_name_1&floor=5

17.获取当前地图
-------------
**指令**  

    /bpi/map/get_current_map 

**例子**  

    发送:  
    /bpi/map/get_current_map

18.关机重启接口
-------------
**指令**  

    /bpi/shutdown

**例子**  

	发送:  
    /bpi/shutdown   // 关机
	/bpi/shutdown?reboot=true    // 重启 

19.获取当前软件版本
-------------
**指令**  

    /bpi/soft/get_version

**例子**  

	发送:  
    /bpi/soft/get_version

20.检查更新
-------------
**指令**  

    /bpi/soft/check_for_update

**例子**  

	发送:  
    /bpi/soft/check_for_update


21.更新
-------------
**指令**  

    /bpi/soft/update

**例子**  

	发送:  
    /bpi/soft/update

**其他说明** 

> 1.状态代码返回说明（针对返回数据的status） 
>
> | 返回码 | 定义描述 |  
> | ------ | ------ |  
> | OK | 表示响应包含有效的 results |   
> | INVALID_REQUEST | 	表示提供的请求无效。这一状态的常见原因包括参数或参数值无效 |   
> | REQUEST_DENIED | 表示系统已拒绝您的请求 |   
> | UNKNOWN_ERROR | 表示由于服务器发生错误而无法处理请求。如果您重试一次，请求可能会成功 |
>
> 2.错误消息返回说明（针对返回数据的emsg）
>
> 如果状态代码不是 OK，在响应对象包含附加的 emsg 字段中更详细地说明了给定状态代码背后的原因。  
> **注：此字段不保证始终有内容，并且其内容可能会更改。**

22.机器人主动通知
-------------
**指令**  

    无(主动上报)

**通知列表**  

| code | description | 备注 | level | 支持开始版本 |   
| ------ | ------ | ------ | ------ | ------ |    
| 移动任务 |  |  |  |  |  
| “06001” | moving is started. | 移动任务开始了。 | info | 0.0.2 |   
| “06002” | moving is finished. | 移动任务完成了。 | info | 0.0.2 |   
| “06003” | moving is failed. | 移动任务失败了。 | info | 0.0.2 |   
| “06004” | moving is canceled. | 移动任务被取消了。 | info | 0.0.2 |   
| “06005” | moving is retried. | 移动重试。 | info | 0.0.2 |   
| “06011” | start to depart charging pile. | 开始离开充电桩。 | info | 未知 |   
| “06012” | succeed to depart charging pile. | 离开充电桩成功。 | info | 未知 |   
| “06013” | failed to depart charging plie. | 离开充电桩失败。 | warning | 未知 |   
| “06021” | start to dock to charging pile. | 开始停靠充电桩。 | info | 未知 |   
| “06022” | succced to dock to charging pile. | 停靠充电桩上成功。 | info | 未知 |   
| “06023” | failed to dock to charging pile. | 停靠充电桩上失败。 | warning | 未知 |   
| “06024” | failed to to receive valid data. | 回充失败原因1。 | warning | 未知 |   
| “06025” | failed to find any feature around the robot. | 回充失败原因2。 | warning | 未知 |   
| “06026” | failed to catch infrared signal. | 回充失败原因3。 | warning | 未知 |   
| “06027” | failed to catch power status. | 回充失败原因4。 | warning | 未知 |   
| 状态相关 |  |  |  |  |  
| “08001” | poweroff notice. | 关机断电。 | info | 0.0.2 |   
| “08002” | charge status on. | 未充电状态->充电状态。 | info | 未知 |   
| “08003” | charge status off. | 充电状态->未充电状态。 | info | 未知 |   
| “08004” | istop on. | 未急停状态->急停状态。 | info | 0.0.2 |   
| “08005” | istop off. | 急停状态->未急停状态。 | info | 0.0.2 |     

**字段解释** 

| 字段 | 说明 | 备注 |  
| ------ | ------ | ------ |   
| code | 通知的代码 | 同一通知所使用的代码不会发生改变， 后续将扩展新的通知 |   
| description | 代码的解释 | 不能作为参考，可作为打印信息 |   
| level | 通知的级别 | 限定为info/warning/error类型, 每个code的划分以后可能会改 |   
| 备注 | 中文解释，仅存在于文档内 |  |   

* * *

<h2 id="seruse">串口 接口使用说明</h2>

<h3 id="sergexp">通用解释</h3>

	后期更新

<h3 id="serprocont">协议内容</h3>

	后期更新

<h3 id="serexample">示例</h3>

	后期更新


<h2 id="docauthor">其他说明</h2>

此文档接口所属希格斯动力科技(珠海)有限公司相关智能机器人产品，更多咨询请联系email： liukai@higgsdynamics.com
