# embedded-linux

一句话：嵌入式 Linux 应用开发学习仓库，目标是一个 x86 + ARM 的 epoll 网关。

当前进度：**阶段○ · 网关零件车间**（2026-09-07 ~ 09-17）。这一段只做单机零件，
还没有任何网络代码，epoll/socket 是阶段一的事。

## 阶段○ · 网关零件车间

### 零件清单

| 模块 | 目录 | 能力点 | 状态 |
| --- | --- | --- | --- |
| 环境与工具链 | `setup_env.sh`、`hello.c` | 一键装 gcc/gdb/make/git/vim；第一个程序验证可编译运行 | ✅ `f001dae` |
| 设备表 | `parts/01_dev_table/` | struct 定义 vs 实例、数组+函数、按 id 查指针、经指针改字段 | ✅ `b75d7b8` |
| 模块化与构建 | `parts/01_dev_table/dev_table.{h,c}`、`Makefile` | 声明/定义分离、struct 收敛到单一头文件、make 按时间戳增量重编 | ✅ `4ab8c39` |
| 单链表 | `parts/02_list/` | 节点连接、尾插、遍历、按 id 查找、free 归还、删除指定节点 | ✅ `9a6f78b` |
| 动态 buffer | `parts/03_dynbuf/` | len/cap 双计数、翻倍扩容、realloc 失败不丢原数据 | ✅ `089a324` |
| CRC16 | `parts/04_crc16/` | 取余本质、模 2 减法=异或、0xA001 是 0x8005 的镜像、`0x4B37` 向量 | ✅ `e48c958` |
| 环形缓冲区 | `parts/05_ringbuf/` | 取模回绕、count 计数法判空满、部分写返回真实字节数 | ✅ `8ff2d79` |
| 配置解析 | `parts/06_config/` | fopen/fgets/fclose、去 `\n`、注释与空行过滤、用 `=` 零拷贝切两段 | ✅ `dcbcb2b` |
| 命令循环 | `parts/07_readloop/` | stdin 当 FILE* 反复读一行处理一行、quit / EOF 退出 | ✅ `ace09ec` |
| 概念卡 | `docs/概念卡/` | 13 张：是什么 / 为什么 / 代码位置 / 易错点，后 9 张多一栏面试追问 | ✅ `616ef4f` |

### 闭卷自检记录

| 项目 | 做法 | commit | 结果 |
| --- | --- | --- | --- |
| 单链表增删 | 不看书重写 append_to_tail / delete_node / free_all | `145e4bb` | 结构一次写对；复查时发现漏了 malloc 失败检查，次日补 `1b81f43` |
| CRC16 | 手写 crc16_modbus，配三组用例自测 | `2ae790e` | 通过：`"123456789"` = `0x4B37`，空数据 = `0xFFFF`（初值） |
| 命令循环 | 手写 stdin 循环 + quit / EOF | `2ae790e` | 基本流程通过，但漏了空行分支，09-17 才补 `ae62b37` |

产物分别在 `parts/08_rewrite_list/`、`parts/09_rewrite_misc/`。

### 踩坑精选

1. **crc16.c 没 include 自己的头文件** — `86e05e4`
   症状：编得过，一条警告都没有。根因：函数定义本身就是合法声明，编译器没机会拿它跟
   `crc16.h` 里的原型对照，签名写歪也拦不住。修法：源文件第一行 `#include "crc16.h"`。

2. **ringbuf_init 失败后留下半初始化对象** — `0ab80b5`、`93298f4`
   症状：malloc 失败的那条路径上，cap 已被写成调用方传进来的值，data 还是 NULL。
   根因：先赋值再分配，中途 return 时对象不是空态，后续 `% cap`、`data[i]` 全部踩 0 和 NULL。
   修法：五个字段先无条件清 0，malloc 成功后才补 cap 真值。

3. **append_to_tail 忘查 malloc，且返回 void 无法上报** — `1b81f43`
   症状：malloc 失败时直接写 `new_node->id`，段错误。
   根因："分配→检查→使用"三拍子缺了检查；返回 void 让调用方想处理也无从下手。
   修法：改签名 `int append_to_tail(...)`，失败 `return 0`，调用方判断。

4. **库函数里直接 printf** — `8a0d0cd`
   症状：find_by_id 自己打印 Found / Not found，换个用法（要拿返回值做后续处理）就复用不了。
   根因：把展示逻辑混进了模块。修法：库只返回指针（查不到返回 NULL），打印和判断挪到 `main.c`。

5. **输入循环不处理空行，EOF 静默退出** — `ae62b37`
   症状：直接回车被当成一条内容打印成 `收到：[]`；Ctrl-D 时只看到一个 EOF。
   根因：没区分空行与有内容的行；break 之前没有输出。修法：加 `strlen(line) == 0` 分支单独提示。

6. **int 与 size_t 混用** — `519bf99`
   症状：`-Wall -Wextra` 下 sign-compare 告警，计数为负时比较会回绕成大正数。
   根因：结构体字段和接口都用 size_t，本地变量却写成 int。修法：统一 `size_t count`。

### 能力自述

- 传值与传指针的区别，以及改头指针为什么必须二级指针 —— `parts/08_rewrite_list/list.c` 的 `append_to_tail`，概念卡 05。
- 单链表删除为什么必须持有前驱：`prev == NULL` 判头、`prev->next = cur->next` 判中 —— `delete_node`，概念卡 06。
- 堆内存借还配对与"分配→检查→使用"三拍子 —— `parts/03_dynbuf/dynbuf.c` 的 `dynbuf_append`，概念卡 07。
- realloc 为什么必须先用临时指针接：失败时不释放原块，直接回写就丢指针 —— 同处，概念卡 07。
- len/cap 双计数各自回答什么问题，以及翻倍扩容的摊还成本 —— `struct dynbuf`，概念卡 08。
- 环形缓冲区两套空满判据，以及 `(write + 1) % cap == read` 的取模为什么不能省 —— `parts/05_ringbuf/ringbuf.c`，概念卡 09。
- 部分写语义：write 只写进 space 个字节并返回真实数量，调用方必须比对 —— 同处，概念卡 09。
- 构造失败后每个接口都要能安全退化成空操作，以及"赋过值 ≠ 空态"的验收方法 —— `ringbuf_init` / `ringbuf_free` 的清零，概念卡 10。
- fgets 为什么保留 `\n`，以及为什么循环条件不该写 `while (!feof(fp))` —— `parts/06_config/step1_readlines.c`，概念卡 11。
- 用 `*eq = '\0'` 零拷贝把一行切成 key/value —— `parts/06_config/step2_parse.c`，概念卡 12。
- CRC16 的取余本质、模 2 加减=异或、0xA001 与 0x8005 的镜像关系 —— `parts/04_crc16/crc16.c`，概念卡 13。

### 延后项

- epoll / socket / 协议帧：阶段○ 全在单机，仓库目前零网络代码。
- 线程安全队列：等阶段一学完锁再包。
- 统一构建：只有 `parts/01_dev_table/Makefile` 一个 Makefile，其余模块手敲 gcc；
  `parts/09_rewrite_misc/` 下 `crc16_rewrite.c` 和 `loop_rewrite.c` 各带一个 `main`，一起编译会撞符号。
- `.gitignore` 目前只有 4 字节（忽略 `bin/`），建议补 `*.o` 和裸可执行文件。