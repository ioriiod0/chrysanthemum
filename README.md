##chrysanthemum

chrysanthemum 是一个由C++写成的小巧灵活、高度可伸缩、模块化的词法/语法分析框架。
chrysanthemum 是一个纯模板库，包含头文件即可使用,且无任何第三方依赖。chrysanthemum 很大程度上受到 Joel de Guzman
所编写的boost.spirit库的启发。

chrysanthemum 能够极大的简化语法分析器的编写工作，使用户可以在C++环境中“书写”BNF范式从而
快速的构造出对应的词法/文法分析器。使用chrysanthemum可以在100多行代码以内完成一个JSON的解析器（参见example/test_json.cc）。
                    
注意：编译时请加上 -std=c++0x 或 -std=c++11 参数以打开C++0X支持.

进一步信息请参考doc目录下的tutial文件，如果您发现任何bug或者有好的建议请联系ioriiod0@gmail.com




