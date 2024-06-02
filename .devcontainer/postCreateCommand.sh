#!/usr/bin/env bash

set -e

sudo apt-get update

# clang
sudo apt-get install -y lsb-release wget software-properties-common gnupg
wget https://apt.llvm.org/llvm.sh -O /tmp/llvm.sh
chmod +x /tmp/llvm.sh
sudo /tmp/llvm.sh 18

pip install -r /workspaces/library-checker-problems/requirements.txt
