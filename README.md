### :clap: Featured Demos

- 插件整合GDAL库，并基于UE4的智能指针封装了GDAL
- 根据GIS数据生成对应位置的静态网格体
- 支持自定义坐标转换参数与蓝图调用
- 提供方便、灵活的API

### :rocket: Get Started

- **Clone VirtualWorld，复制到项目的Plugins目录下**
- 在内容浏览器中找到VirtualWorld下的AGenerateWorld，将其拖入场景中
- 选中AGenerateWorld Actor，在细节面板中，输入坐标转换四参数和GIS数据，点击SpawnPointActor或者SpawnPolygonActor。

### Simple description

![Simple description](./Image/Image.gif)

### :green_book: License

[Apache 2.0](http://www.apache.org/licenses/LICENSE-2.0.html). WebSocketServer is free for both commercial and non-commercial use.

### :hammer_and_wrench: Developing with WebSocketServer
#### Windows
##### Prerequisities
* Unreal Engine 4.27.
* Visual Studio 2019.

##### Build Steps
1. Point your Unreal Engine Project, create Plugins  to the `VirtualWorld.uplugin` file to load the plugin into Unreal Engine.

2. To package the plugin, run the `RunUAT.bat` command :

   ```powershell
   %UE4.27 Path%/Engine/Build/BatchFiles/RunUAT.bat BuildPlugin Plugin=%Base Path%/WebSocketServer/VirtualWorld.uplugin -Package=%Base Path%/WebSocketPlugin/Package/ -VS2017 -TargetPlatforms=Win64 -Rocket
