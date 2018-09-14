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


21.更新
-------------
**指令**  

    /bpi/soft/update

**例子**  

	发送:  
    /bpi/soft/update
    
> 1.状态代码返回说明（针对返回数据的status） 
>
> | 返回码 | 定义描述 |  
> | ------ | ------ |  
> | OK | 表示响应包含有效的 results |   
> | INVALID_REQUEST | 	表示提供的请求无效。这一状态的常见原因包括参数或参数值无效 |   
> | REQUEST_DENIED | 表示系统已拒绝您的请求 |   
> | UNKNOWN_ERROR | 表示由于服务器发生错误而无法处理请求。如果您重试一次，请求可能会成功 |
>
> 2.错误消息返回说明（针对返回数据的error_message）
>
> 如果状态代码不是 OK，在响应对象包含附加的 error_message 字段中更详细地说明了给定状态代码背后的原因。  
> **注：此字段不保证始终有内容，并且其内容可能会更改。**

**通知列表**  

| code | description | 备注 | level | 支持开始版本 |   
| ------ | ------ | ------ | ------ | ------ |    
| 移动任务 |  |  |  |  |  
| “01001” | The move task is started. | 移动任务开始了。 | info | 0.0.2 |   
| “01002” | The move task is finished. | 移动任务完成了。 | info | 0.0.2 |   
| “01003” | The move task is failed. | 移动任务失败了。 | info | 0.0.2 |   
| “01004” | The move task is canceled. | 移动任务被取消了。 | info | 0.0.2 |   
| “01005” | The move task is retried. | 移动重试。 | info | 0.0.2 |   
| “01010” | Start to leave charging pile. | 开始离开充电桩。 | info | 0.0.2 |   
| “01011” | Succeed to leave charging pile. | 离开充电桩成功了。 | info | 0.0.2 |   
| “01012” | Failed to leave charging plie. | 离开充电桩失败了。 | warning | 0.0.2 |   
| “01020” | Start to auto dock to charging pile. | 开始自动停靠到充电桩。 | info | 0.0.2 |   
| “01021” | Succced to auto dock to charging pile. | 自动停靠到充电桩上成功了。 | info | 0.0.2 |   
| “01022” | Failed to auto dock to charging pile. | 自动停靠到充电桩上失败了。 | warning | 0.0.2 |   
| “01023” | Failed to to receive valid data. | 回充电失败原因1。 | warning | 0.0.2 |   
| “01024” | Failed to find any feature around the robot. | 回充电失败原因2。 | warning | 0.0.2 |   
| “01025” | Failed to catch power status. | 回充电失败原因3。 | warning | 0.0.2 |   
| “01026” | Failed to catch infrared signal. | 回充电失败原因4。 | warning | 0.0.2 |   
| 状态相关 |  |  |  |  |  
| “03001” | Poweroff notice. | 将关机断电。 | info | 0.0.2 |   
| “03002” | Charge status on. | 未充电状态=>充电状态。 | info | 0.0.2 |   
| “03003” | Charge status off. | 充电状态=>未充电状态。 | info | 0.0.2 |   
| “03004” | Estop on. | 未急停状态=>急停状态。 | info | 0.0.2 |   
| “03005” | Estop off. | 急停状态=>未急停状态。 | info | 0.0.2 |   

**字段解释** 

	| 字段 | 说明 | 备注 | 
	| ------ | ------ | ------ |  
	| code | 通知的代码 | 同一通知所使用的代码不会发生改变， 后续将扩展新的通知 |   
	| description | 代码的解释 | 不能作为参考，可作为打印信息 |   
	| level | 通知的级别 | 限定为info/warning/error类型, 每个code的划分以后可能会改 |   
	| 备注 | 中文解释，仅存在于文档内 |  |   

