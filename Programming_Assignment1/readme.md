# Welcome to use our Awesome Medical Management System!

Our system has the following **features**:

1. automatic simulation (simply enter 777 at the begining).
2. manual operation with the help of automatic patient information generation.
3. weekly/monthly report can be printed on the screen any time you like, and they will be saved to the file, too. (in the report folder).
4. Each patient's information is stored in one file. Easy for looking up and management.

Simply use `make` to compile the whole project and run `main`.

**NOTICE**

1. Automatic simulation will change the file in database_auto folder, so every time you want to do automatic simulation, you need to replace database_auto folder with the original one first. The original one can be find in database_auto.zip.
2. If you choose to use manual mode, you need to be sure that database folder is empty at first.
3. I am not sure whether Windows can make and run this program. If some compilation errors occur, please try Linux/MacOS/WSL again.

NOTICE很重要，我怕我表达不好，用中文复述一遍：
1. 自动模拟模式需调用database_auto里的文件。但是跑了一次程序之后，datebase_auto里的文件都会被改变，所以每次使用自动模拟之前要先解压缩database_auto.zip，用这里面的文件替换掉被更改的文件，才可以进行正确的模拟。
2. 如果是使用手动输入模式，则只需保证database文件夹为空即可。


**Limitation**

In auto-generate mode, some ID will have hash conflict, so the actually generated number of people may have a very small possibility to differ from what we expect.