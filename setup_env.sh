#!/bin/bash

echo "===== 开始部署开发环境 ====="

sudo apt update

sudo apt install -y gcc gdb make git vim

echo "===== 部署完成 ====="
echo "请执行 gcc --version 验证环境是否安装成功"
