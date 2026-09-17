## 概念卡 11：文件 IO 与 EOF

**是什么**：读文件三件套——fopen 打开（失败返回 NULL）、fgets 逐行读（读完或出错返回 NULL）、fclose 关闭归还资源；fgets 会把行尾的 `\n` 一起读进缓冲区再补 `\0`。
**为什么**：C 里"一行"的结束标志就是 `\n`，fgets 保留它是为了让你能区分"读到了一整行"和"缓冲区满被迫截断"。而返回 NULL 本身不区分是文件尾还是读错，要靠 feof/ferror 才能分辨。
**我代码里的位置**：`parts/06_config/step1_readlines.c`：`FILE *fp = fopen("config_test.conf", "r")` 后立刻判 NULL，`while (fgets(line, sizeof(line), fp) != NULL)` 逐行打印，最后 `fclose(fp)`。
**易错点**：fopen 失败不检查就对 NULL 调 fgets；忘了 `\n` 还留在行尾，后面比 key 永远不相等（下一张卡用 strchr 把它消掉）；fgets 第二个参数传 `sizeof(line)` 才对，传成指针的 sizeof 只等于 4/8；拿 `while (!feof(fp))` 当循环条件，会多处理一遍旧数据；不知道 stdin 也是一个 FILE*（`fgets(line, n, stdin)` 就是命令行输入循环），它不用 fopen，也不该 fclose。
**面试追问**：
- 问：`fgets` 返回 NULL 说明什么？
  答：说明这一行没读成，可能到了文件尾，也可能读出错，用 feof(fp)/ferror(fp) 区分。所以循环条件应该写"读到了才处理"，而不是 `while (!feof(fp))`——后者会在最后一次多处理一遍上一轮的旧数据。
- 问：处理配置文件时为什么要先把 `\n` 去掉？
  答：因为 fgets 把 `\n` 留在缓冲区里，`"key=value\n"` 和 `"key=value"` 用 strcmp 比就是不相等。把 `\n` 换成 `\0` 正好得到干净的字符串；注意最后一行可能没有换行符，strchr 会返回 NULL，要先判空再写。