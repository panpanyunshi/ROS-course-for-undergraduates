### 彩图转灰度图

```
roslaunch usb_cam usb_cam-test.launch
rosrun demo02_opencv image_to_grey
```
### 彩图转灰二值图

```
roslaunch usb_cam usb_cam-test.launch
rosrun demo02_opencv image_to_binary
```
### 检测人脸位置

```
roslaunch usb_cam usb_cam-test.launch
rosrun demo02_opencv image_face_detect
```
### 图片翻转

```
rosrun demo02_opencv image_flip
rqt_image_view
```
