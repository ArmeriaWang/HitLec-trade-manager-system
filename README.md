## 简易交易管理系统

#### 关于本项目

这是一个简易交易管理系统。它支持用户信息、商品信息、记录信息的增删改查等基本操作。关于本项目详细信息，请参考根目录下的Report.docx。

#### 关于编译

  - 如果你用的IDE是CLion，你可以直接导入trade_manager_system这个Project进行编译，语言标准为C11；或者如果你会使用CMake进行编译，你也可以用它轻松地在对应目录下编译出可执行文件。
  - 你也可以在PowerShell（Windows下，直接在开始菜单的搜索栏内搜索PowerShell），或者Terminal（Linux和macOS）下，进入程序目录，执行命令 "gcc -o ./cmake-build-debug/trade_manager_system main.c" (不含引号，且你需要确保你的的gcc已被添加进环境变量中），然后进入./cmake-build-debug目录运行。
  - 你还可以直接用Code::Blocks等IDE编译，编译对象为 main.c ，语言标准为C11。但是，一定要将编译出的.exe可执行文件放入cmake-build-debug文件夹中再运行！如果直接在原目录下运行，会出现文件载入错误。

#### 关于清屏命令

  - 如果你使用Linux或macOS系统，请忽略这一条。
  - 如果你使用Windows系统，清屏命令可能会失效。若介意使用体验，这里提供两种解决方案。
      - 将lib目录下的basic_io.h、surface.h两个头文件中的 system("clear") 语句改为 system("cls") 后再编译（可使用你的IDE的查找/替换功能）。
      - 不要直接打开这个.exe文件。先打开PowerShell，然后进入这个可执行文件的目录，运行命令 ./*.exe （*改为真实文件名）即可。

#### 测试技巧

- 你可以在搜索界面搜索通配符 * ，以获取所有商品的列表