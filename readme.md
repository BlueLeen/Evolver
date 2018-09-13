指令定义：    

| 指令 | 参数 | 返回 | 描述 |
| ------ | ------ | ------ | ------ |
| /bpi/move | marker:目标点位代号<br/>location:(x,y,theta)<br>说明：marker和location二选一，location优先级高于marker | {<br/>&nbsp;&nbsp;"type":"response",<br/>&nbsp;&nbsp;"cmd":"/bpi/move",<br/>&nbsp;&nbsp;"uuid":"",<br/>&nbsp;&nbsp;"status":"OK",<br/>&nbsp;&nbsp;"emsg": ""<br/>} | 使机器人从当前位置移动至地图中已经标定的某个目标点。 |
| /bpi/move/cancel | N/A | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd": "/bpi/move/cancel",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": ""<br/>} | 使机器人主动放弃当前正在执行的移动任务，成功取消后可使机器人进入新的待命状态。在机器人执行/bpi/move移动命令过程中，如果需要终止机器人当前的移动状态，可以调用此接口。机器人会在接收“移动取消”命令之后，原地停止，等待再次的move指令。 |    
| /bpi/markers/insert | name:点位名字<br/>type:点位类型，0(一般点位)，1（充电桩）。可选，默认为0 | 操作成功时返回：<br/>{<br/>&nbsp;&nbsp;"type": <br/>&nbsp;&nbsp;"response",<br/>&nbsp;&nbsp;"cmd": "/bpi/markers/insert",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": ""<br/>} | 在当前地图中标记点位，让机器人记住这个点位（marker）。<br/>调用此接口时，机器人会捕捉当前相对于地图坐标系的(x,y,theta)，并自动把捕捉到的锚点位置，存储在机器人的锚点列表中，以随时响应move的调用。如果不使用充电功能，接口中的type可以不设置。 |   
| /bpi/markers/query_list | N/A | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"cmd":"/bpi/markers/query_list",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"emsg": "",<br/>&nbsp;&nbsp;"results":<br/>&nbsp;&nbsp;{<br/>&nbsp;&nbsp;&nbsp;"meeting_room": <br/>&nbsp;&nbsp;&nbsp;{<br/>&nbsp;&nbsp;&nbsp;&nbsp;"floor": 1, <br/>&nbsp;&nbsp;&nbsp;&nbsp;"pose": {<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"orientation": {<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"w": -0.899999976158142, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"x": 0, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"y": 0, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"z": -0.430000007152557<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"position": {<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"x": -8.57999992370605, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"y": 6.3600001335144, <br/> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"z": 0<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"marker_name":"meeting_room", <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"key": 0<br/>&nbsp;&nbsp;&nbsp;}, <br/>&nbsp;&nbsp;&nbsp;"bed_room": <br/>&nbsp;&nbsp;&nbsp;{<br/>&nbsp;&nbsp;&nbsp;&nbsp;"floor": 1, <br/>&nbsp;&nbsp;&nbsp;&nbsp;"pose": {<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"orientation": {<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"w": -0.899999976158142, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"x": 0, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"y": 0, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"z": -0.430000007152557<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"position": {<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"x": -8.57999992370605, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"y": 6.3600001335144, <br/> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"z": 0<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}<br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;}, <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"marker_name":"bed_room", <br/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"key": 0<br/>&nbsp;&nbsp;&nbsp;}<br/>&nbsp;&nbsp;}<br/>}// "marker_name"表示点位名称。"key"表示点位类型：0(一般点位)，11（充电桩）。"floor"表示点位所属楼层。"pose"表示具体坐标点。 | 获取机器人在某场景地图中的所有点位(markers)信息。<br/>通过/bpi/markers/insert设置的锚点位置，可以通过此接口进行json格式的锚点列表查阅。results内容以字典形式查阅，其中目前包括信息有“楼层”、“点位坐标”、“显示名称”和“类型”。 |   
| /bpi/move_access | avel:角速度<br/>lvel:线速度 | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"command": "/bpi/move_access",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"error_message": ""<br/>} | 对机器人进行部分的直接控制，如自转或停止（此控制优先级高于move指令），返回OK表示机器人已成功接收并开始运行此指令 |   
| /bpi/istop | flag:进入或退出急停模式(取值true/false) | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"command": "/bpi/istop",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"error_message": ""<br/>} | 使机器人进入自由停止模式，机器人可被推动。 |   
| /bpi/position_adjust | marker:用以校定位置的marker名 | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"command":"/bpi/position_adjust",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"error_message": ""<br/>} | 该接口用于机器人初始化自身位置，可将机器人推至已存入marker列表的任一位置，然后用指定的marker的坐标校定机器人当前位置。 |   
| /bpi/request_data | topic:请求的实时数据类型,目前仅接受”robot_status”类型<br/>switch:开启/停止数据发送(取值on/off)<br/>frequency:发送频率[1, 10] | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"command": "/bpi/request_data",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"error_message": ""<br/>} | 请求server端以一定频率发送topic类型的数据。当请求成功后，server端会以一定频率发送数据给请求的client。 |   
| 机器人主动通知 | code:通知的代码<br/>description:代码的解释<br/>level:通知的级别<br/> | 例如：<br/>{<br/>&nbsp;&nbsp;"type": "notification",<br/>&nbsp;&nbsp;"code": "01001"<br/>&nbsp;&nbsp;"level": "info"<br/>&nbsp;&nbsp;"description": "The move task is started."<br/>} | 机器人主动发出通知给所有连接的client，客户端在收到通知后可以进行相应的动作，比如语音播报等。 |   
| /bpi/set_params | max_speed_ratio:机器人最大行进速度(百分比,取值[0.3, 1.0]) | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"command": "/bpi/set_params",<br/>&nbsp;&nbsp; "uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"error_message": ""<br/>} | 设置机器人的参数。 |   
| /bpi/get_params | N/A | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"command": "/bpi/get_params",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"error_message": "",<br/>&nbsp;&nbsp;"results": {<br/>&nbsp;&nbsp;&nbsp;"max_speed_ratio": 0.5<br/>&nbsp;&nbsp;&nbsp;}<br/>} | 获取机器人可设置的参数列表以及当前值。 |   
| /bpi/wifi/list | N/A | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"command": "/bpi/wifi/list",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"error_message": "",<br/>&nbsp;&nbsp;"results": {<br/>&nbsp;&nbsp;&nbsp;"SSID1": 50,<br/>&nbsp;&nbsp;&nbsp;"SSID2": 30,<br/>&nbsp;&nbsp;&nbsp;"SSID3": 80,<br/>&nbsp;&nbsp;&nbsp;}<br/>} | 获取机器人当前可用的WiFi列表，返回中包含SSID和信号强度。 |   
| /api/wifi/connect | SSID:WiFi的SSID<br/>password:WiFi密码 | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"command": "/api/wifi/connect",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"error_message": "",<br/>} | 使机器人连接到环境WiFi或切换当前连接的环境WiFi。 |   
| /api/wifi/get_active_connection | N/A | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"command": "/api/wifi/get_active_connection",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"error_message": "",<br/>&nbsp;&nbsp;"results":"SSID1"   // 如果当前未连接到WiFi，则results为空""<br/>} | 获取机器人当前连接的WiFi的SSID. |   
| /api/wifi/info | N/A | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"command": "/api/wifi/info",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"error_message": "",<br/>&nbsp;&nbsp;"results":{<br/>&nbsp;&nbsp;&nbsp;&nbsp;"IPaddr": "192.168.XXX.XXX", // 如果未连接WiFi则为空“”<br/>&nbsp;&nbsp;&nbsp;&nbsp;"HWaddr": "xx:xx:xx:xx:xx:xx", // 连接WiFi网卡的物理地址<br/>&nbsp;&nbsp;&nbsp;&nbsp;},<br/>} | 获取机器人当前通过环境WiFi分配到的IP地址和无线网卡的物理地址。 |   
| /api/map/list | N/A | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"command": "/api/wifi/list",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"error_message": "",<br/>&nbsp;&nbsp;"results":{<br/>&nbsp;&nbsp;&nbsp;&nbsp;"map_name_1": [1,2,3,4,5], // 地图map_name_1中有1-5层<br/>&nbsp;&nbsp;&nbsp;&nbsp;"map_name_2": [10],<br/>&nbsp;&nbsp;&nbsp;&nbsp;},<br/>} | 获取机器人中所有的地图名称和楼层。 |    
| /api/map/set_current_map | map_name:地图名<br/>floor:楼层 | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"command": "/api/map/set_current_map",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"error_message": "",<br/>} | 设置机器人当前地图。 |   
| /api/map/get_current_map | N/A | {<br/>&nbsp;&nbsp;"type": "response",<br/>&nbsp;&nbsp;"command": "/api/map/get_current_map",<br/>&nbsp;&nbsp;"uuid": "",<br/>&nbsp;&nbsp;"status": "OK",<br/>&nbsp;&nbsp;"error_message": "",<br/>&nbsp;&nbsp;"results":{<br/>&nbsp;&nbsp;&nbsp;&nbsp;"hotel_id": "map_name_1",  // v0.5.2-v0.5.9(已弃用)<br/>&nbsp;&nbsp;&nbsp;&nbsp;"map_name": "map_name_1",<br/>&nbsp;&nbsp;&nbsp;&nbsp;  // v0.5.10以后<br/>&nbsp;&nbsp;&nbsp;&nbsp;"floor": "5"<br/>&nbsp;&nbsp;&nbsp;&nbsp;},<br/>} | 获取机器人当前地图。 |   
| 定义 | 0xFD | 帧长度 | 0xF8 |   
| 定义 | 0xFD | 帧长度 | 0xF8 |   
| 定义 | 0xFD | 帧长度 | 0xF8 |   
| 定义 | 0xFD | 帧长度 | 0xF8 |   
| 定义 | 0xFD | 帧长度 | 0xF8 |   
| 定义 | 0xFD | 帧长度 | 0xF8 |   
| 定义 | 0xFD | 帧长度 | 0xF8 |   

