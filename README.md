# Study Tour
练手向以及收集我见到的炫酷的实现

## environment
- Oracle VM VirtualBox
- Ubuntu 20.04 LTS
- gcc 11.1.0
- cmake 3.23.0-rc1
- vscode
- doxygen

## base rule
- indent = 2, tab = 2
- 尽量使用STL和封装类，比如std::string和const char\*的选择，尽量用std::string，迫不得已时(比如底层接口只接受const char\*，那就只能传递const char\*)用const char\*。可能std::string会在某些地方产生额外的开销，所以在作为参数传递时，参数考虑使用std::string_view，在需要保存时，使用std::string
- 因为用了doxygen，所以看起来注释会很多，考虑只在函数签名和类声明的地方使用doxygen注释，显而易见的地方，比如复制，移动，析构函数，暂时先不考虑
- log，可以通过logoff之类的方式来消除log对运行时的影响，所以多打log并不影响效率，只是函数体会变得十分难看，不过项目一般都会打很多log，所以这也算是随大流吧
  - 在public函数的入口和出口都添加log，level = info
  - 在需要的地方打上对应的log
  - private函数不需要log，特别简单的函数也不需要
  - log (spdlog)
    - pattern: [%Y-%m-%d %H:%M:%S.%e][%^%l%$][%@ %!][%P %t] %v
    - 为了输出func和文件等信息，所以必须使用macro形式的log接口

## others
C++ header template
```c++
#ifndef STUDY_TOUR_TEMPLATE_H
#define STUDY_TOUR_TEMPLATE_H


namespace st {


} // namespace st

#endif // STUDY_TOUR_TEMPLATE_H
```