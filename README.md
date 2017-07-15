# dedacker

> 这是一个检验目标框标注数据是否正确的工具，基本功能就是对目标框进行处理，加入到图片上。

# 介绍

目标检测领域中，有时候需要一个工具去检验标注结果是否正确，dedacker便是为此而设计的。目前dedacker实现的功能有：

* 显示bouding box到图片上，并且会实时的对照打印出box的坐标和在图片中的位置；
* 自动计算出标注图片的数目；
* 会在标记框上显示标记的class index；

当然dedacker不仅于此，还可以拓展性的导入text格式，json格式的标记，可以根据label的形式来修改，非常简单易用。

<center><img src="http://ofwzcunzi.bkt.clouddn.com/debd8aUtypVCvh6X.png"></center>

# 使用

dedacker使用也非常简单：
```
mkdir build
cd build
cmake ..
make -j8
./dedacker ../example/images ../example/label.txt
```

# 声明

本项目基于c++实现，如果在大型项目中使用本项目的相关，请注明代码出处：
```
Original implement by Jin Fagang, source code: https://github.com/jinfagang/dedacker.git
```
