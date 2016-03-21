# abnormal-event-detector
testWidget代码说明

1、运行环境

Windows10+Visual Studio 2015+OpenCV 2.4.9+Qt 5.6.0（msvc2015）

库目录：
C:\opencv\build\x86\vc12\lib
C:\opencv\build\x86\vc12\bin

包含目录：
C:\opencv\build\include\opencv2
C:\opencv\build\include\opencv
C:\opencv\build\include

引用目录：
$(VC_ReferencesPath_x86);

注：目录随opencv安装路径更改而更改。

2、主要源文件

main.cpp：打开窗口进程，运行，显示窗口。

testwidget.cpp:进行GUI上的交互操作。

Thread.cpp:底层图像（视频帧）分析处理线程。

3、主要功能

运行本程序，弹出主界面。此时应为初始化状态，各区域均无有效数据。
单击“打开视频”，视频信息区域自动读取相关数值，将数值返回在主界面上，并开始对视频进行分析处理。
每一视频帧的处理结果将返回在主界面上，分为异常光流区域（以红色标出）和光流方向图（右下角极坐标图）。
视频处理完毕后输出交以分类器处理的训练数据，以txt格式保存。

4、移植性问题

本程序在可移植上做得不够好，主要原因是文件打开路径上采用的是直接打开特定字符串指定的路径。若要使本程序正常运行，需要修改一下几处的路径：

testWidget.cpp中：

视频文件地址：
L43：cap.open("E:/28-prp/vids/pos_003.avi");

分析处理完毕后的图像输出地址：
L90：QString addressKmeans("D://pictures/pic_of");
L95：QString addressVideo("D://pictures/pic_of");

Thread.cpp中：

视频文件地址：
L30: cap.open("E:/28-prp/vids/pos_003.avi");

数据输出地址：
L134: sprintf(outfilepath, "D:/data_of%d.txt", abnormal[ab_cnt]);

训练用数据输出地址：
L144： sprintf(outfilepath, "D:/data/train.txt");
L157： sprintf(outfilepath, "D:/data/train.txt");

分析处理完毕后的图像输出地址：
L183：sprintf(ss, "D://pictures/pic_of%d_lightflow.jpg", count_of_picture);
L185：sprintf(ss, "D://pictures/pic_of%d_original.jpg", count_of_picture);
		
