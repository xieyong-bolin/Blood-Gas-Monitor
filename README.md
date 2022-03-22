# BM

this repository is for continuous blood monitor.

1. Folder structure
|
|----doc
|----include
|----src
|----test

doc folder is for relative documents. 
include folder is for global head files. 
src folder for source code. 
test folder store all test case and unit test framework and mock.

2. How to build

2.1 set up build environment
2.1.1 apt-get install vscode
2.1.2 sudo apt-get install clang-format
2.1.3 apt-get install qt5-default

2.2 begin build
run compile bash to compile project. 

./Compile_Bash

if you want to build your unit test case, you should build it follow below instruction in terminal.

./Compile bash unittest


3. Logs
You can find all system logs in Folder src/Target/Logs. These logs can help you to track system bug.
