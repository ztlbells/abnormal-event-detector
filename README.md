# abnormal-event-detector

1、Platforms & Dependencies

Windows10+Visual Studio 2015+OpenCV 2.4.9+Qt 5.6.0（msvc2015）

Repositories：
..\opencv\build\x86\vc12\lib
..\opencv\build\x86\vc12\bin

Directories to include：
..\opencv\build\include\opencv2
..\opencv\build\include\opencv
..\opencv\build\include

*(All of above depends on your Opencv installation path.)

2、Files & brief descriptions

*main.cpp

*testwidget.cpp

*Thread.cpp*:processing each frame in video.

*GUI*: The area with abnormal optical flows will be marked in red; the direction distribution of pixes optical flows will be displayed in the polar coordinate system (in the lower right corner).

*Output*: data for training (in txt).
