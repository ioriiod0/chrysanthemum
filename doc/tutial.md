#chrysanthemum框架简介

##基本概念

chrysanthemum框架是一个使用C++11标准实现的面向对象的递归下降分析器生成框架，框架使用C++编译器的编译期推导能力，以及C++操作符重载的能力，构建了一个C++环境中的元语言，使用该元语言，能够使用户在C++环境中“书写ABNF范式”,框架能够从这些“ABNF范式”中自动推导并生成对应的匹配器或解析器，从而极大地缩短开发时间。

chrysanthemum框架主要包含3个部分，分别为扫描器、匹配器和语义动作器。基本工作流程如下：

                    扫描器  ->  匹配器  ->  语义动作 

扫描器主要负责接收一段线性输入，并将内容提供给匹配器进行匹配，同时（有必要的化）做一些文本的预处理和统计工作。
匹配器是整个框架的核心。匹配器尝试以一系列完整定义的规范来匹配扫描器提供的输入，这些规范被称为语法规则。成功匹配时，将执行预定义的语义动作（如果有语义动作的话）。最后，匹配器将成功匹配到的文本发送到语义动作器，语义动作器则负责提取出被匹配文本中的信息。


##扫描器

扫描器的任务是顺序的将输入数据流传递给匹配器。扫描器包含三个兼容STL标准的前向迭代器，beg、cur和end，其中beg和end描述了待扫描文本的总体区间范围，而cur则描述了下一个待扫描的字符所在位置。在匹配过程中，匹配器从扫描器获得数据，并通过扫描器对迭代器进行重定位。扫描器的接口是一个十分简洁但功能完备的集合，仅包含一个get函数、一个increase函数以及一个get_and_increase函数。
框架提供的扫描器是一个模板类,使用POLICY-BASED DESIGN方法进行设计:

    template <typename Iterator,template <class> class Policy>
        struct scanner:public Policy<Iterator>
    {
    /* 
    ... 
    */ 
    ////////////////////
     Iterator beg;
     Iterator end;
     Iterator cur;
    ////////////////////////// 
    };

其中模板参数Iterator指定了前向迭代器的类型，而模板参数Policy决定了扫描器的扫描策略，从而决定了扫描器的行为。
在大多数情况下，关于这些扫描策略的知识并不是必须的。然而对于构造一个符合本框架标准的匹配器时，有关扫描器的基本知识就是必须的了。基于POLICY-BASED DESIGN的设计使得扫描器很有弹性和扩展性。通过编写不同的扫描策略可以方便的指定扫描器的行为。一个例子就是不区分大小写的策略，这种策略在分析大小写不敏感的输入时，是很有用的。
定义一个合乎规范的扫描器策略，必须要满足下列要求：

* 扫描器策略应该是个只含有一个模板参数的模板类，该模板参数指定了前向迭代器的类型。
* 扫描器策略必须实现do_get,do_increase以及at_end三个函数。

以框架提供的字符统计扫描器策略为例：

    template <typename Iterator>
    struct line_counter_scanner_policy
    {
        //////////////////////////////////////////////
        const value_type& do_get(Iterator it) const
        {
            return *it;
        }
        value_type& do_get(Iterator it)
        {
            return *it;
        }
        void do_increase(Iterator& it)
        {
            ++consumed;
            if(character_type_traits<value_type>::isLF(*it))
            {
                ++line_no;
                col_no = 0;
            }
            else
                ++col_no;
            ++it;
        }
        bool at_end(Iterator it,Iterator end)
        {
            return it == end;
        }

        ///////////////////////
        std::size_t line_no;
        std::size_t col_no;
        std::size_t consumed;
    };

该扫描器策略能够在匹配过程中的统计当前行数，列数，与总匹配字符数，这些信息在匹配出错的时候，能够提供简单的诊断信息。


##匹配器

所有匹配器在概念上遵守一个公共的接口协议与规范。注意，这里的接口协议指的是C++泛型编程中泛化的接口概念，而非面向对象编程中所指的纯虚函数等概念。意即所有符合该接口协议的对象都可认为是一个概念上完备的匹配器。因此，只要依据协议和规范，任何人都可以轻易的完成一个能与本框架其他部分完美整合的匹配器。这也是chrysanthemum框架具有高扩展性的主要原因。
泛化的接口协议与规范的具体要求如下：

* 匹配器必须继承自模板类  template<typename Derived> parser_base，并且Derived模板参数是匹配器本身。
* 匹配器必须实现一个如下形式的成员模板函数。

    template <typename Scanner>
        bool operator()(Scanner& scan) {/* ... */ }

例如，假如我们想定义一个新的匹配器类型Parser，Parser的声明必须为：

    struct Parser:public parser_base<Parser>
    {
        template <typename Scanner>
        bool operator()(Scanner& scan)
        {    
        /*
        ...
        */
        }
        /*
         ...
         */
    };

也就是说，所有的匹配器对象都必须是一个仿函数，其接受一个扫描器的引用作为一个参数，并返回一个bool值表示匹配的成功与否。之所以要求所有的匹配器对象都必须是仿函数，一方面是因为仿函数能够与框架的函数式编程风格很好的配合，另外一个原因是仿函数可以被很方便的绑定到std::function对象当中，这种运行期的绑定能够为框架带来动态分析能力。

匹配器可以细分为：原子匹配器，合成物以及规则。

###原子匹配器

原子匹配器是匹配器的最小和最基本的单位。chrysanthemum提供了两种原子匹配器：1)charactor-level 2)literal

* charactor-level：字符级匹配器

字符级匹配器一般只匹配满足某个范围的一个字符。比如：digit_p用于匹配数字字符 ‘0’ 到 ‘9’中的任一个；lower_p 用于匹配任意小写字母，alpha_p用于匹配任意字母。基本字符集匹配器与C++库函数终的 isdigit islower 等函数一一对应。除此之外还有一些特殊的字符级匹配器，比如any_p匹配任意字符，而void_p不消耗任何输入，而且总是返回true。

* literal: 字面意义匹配器

字面意义匹配器用于匹配“字面意义”。比如表达式 auto p = _literal("hello world") 产生一个字面意义匹配器p，匹配字面意义的文本“hello world”。 auto q = _literal('x') 匹配单一字符‘x’。

###合成物与操作符

chrysanthemum框架提供了一系列的操作符，这些操作符重载自C++的操作符。通过这些操作符，我们可以将低阶的的匹配器组装成复杂的高阶的合成物，这些合成物也是匹配器，比如下面的表达式：

    lower_p a;
    upper_p b;
    auto c = a | b;  //框架重载了 | 操作符。
    auto d = a | b | digit_p(); 

表达式a | b 实际上构成了一个新的匹配器c，表示匹配a或者b。更进一步，a和b的类型分别是 upper_p和lower_p，那么他们所构成的新的合成匹配器表示匹配小写字母或者大写字母，因此c的类型实际上等价于 alpha_p。
而匹配器 d 表示匹配字母或数字，等价于预定义的字符级匹配器 alnum_p.

实际上c的类型由两个操作子a和b的类型已经组合器的类型组合而成。他们所构成的新的合成匹配器的类型为：

    or_p<upper_p,lower_p>

所以上边表达式也可以声明为：

    or_p<upper_p,lower_p> c = a | b;

对于稍简单的表达式，这种写法虽然可以接受，但是在很多情况下，如果a和b本身也是非常复杂的合成对象，这种显式的声明类型的方式，将会给框架的使用者造成极重的思维和打字的负担，而且往往最终结果的类型会复杂到使用者也无法理解的地步。得益于C++11新标准，我们可以将这种脏累活交给编译器去处理，使用auto关键字声明的对象，C++编译器会自动推导出其类型。

所有的二元操作符，当有至少有一方是匹配器时，另一方可以对字符或字符串进行隐式转换，比如：下面的表达式等价

    auto c = _literal('A') | 'B'  <=> auto c = _literal('A') | _literal('B')

而 

    auto c = 'A' | 'B' 不是个匹配器，而是对字符'A'和'B'作按为与运算。


####框架提供了多种操作符：

注：表格中a,b...表示匹配器，A,B...表示a,b...对应的ABNF范式。本文中所有表格均遵循相同的约定。



<table border=1>
    <tr>
        <th>操作符</th>
        <th>ABNF</th>
        <th>说明</th>
    </tr>
    <tr>
        <td>a|b</td>
        <td>A|B</td>
        <td>匹配a或者匹配b</td>
    </tr>
    <tr>
        <td>a&b</td>
        <td>A B</td>
        <td>先匹配a然后匹配b</td>
    </tr>
    <tr>
        <td>a-b</td>
        <td>无</td>
        <td>匹配a 但不匹配b</td>
    </tr>
    <tr>
        <td>!a</td>
        <td>无</td>
        <td>所有不匹配a的</td>
    </tr>
</table>

可以看出，差集操作符和求反操作符在ABNF中并没有与之对应的表示，这两个操作符实际上是Chrysanthemum框架对ABNF范式的补充，虽然在理论上，这两个操作符并不是必须的，但是在实际的编程操作中却是极为有用的。

    auto first_digit = _digit() - '0';

从集合的角度来看，_digit()用于匹配集合"0..9"中的任意元素，而从中排除掉“0”后，就是所需要的集合“1..9”。
再如如果你需要一个匹配所有非空白字符的匹配器时，只需要简单的对space_p匹配器求反即可:

    auto not_sapce = !_space();

需要注意的一点是操作符"|"的短路特性：“|”操作符以自左向右先到先得的方式一个一个测试它的操作子，当发现一个正确匹配的操作子后，匹配器就结束匹配，从而彻底的停止搜索潜在匹配。这种隐式的短路特性隐式的给与最左边地选项一最高的优先级。这种短路的特性在C/C++的表达式中同样存在：比如if(x<3||y<2)这个表达式里，如果x小于3成立，那么y<2这个条件根本就不会被测试。短路除了给予选项必要地隐式的优先级规则，还赋予Chrysanthemum分析器非确定性行为，从而缩短了执行时间。如果你的选项的位置在与表达式的逻辑没有关系，那么尽可能的把最可能出现的匹配项放在最前面可以将效率最大化。

<table border=1>
    <tr>
        <th>操作符</th>
        <th>ABNF</th>
        <th>说明</th>
    </tr>
    <tr>
        <td>*a</td>
        <td>无</td>
        <td>重复使用a匹配0到任意多次</td>
    </tr>
    <tr>
        <td>+a</td>
        <td>无</td>
        <td>重复使用a匹配1到任意多次</td>
    </tr>
    <tr>
        <td>-a</td>
        <td>[A]</td>
        <td>配a 0或1次</td>
    </tr>
    <tr>
        <td>a%b</td>
        <td>无</td>
        <td>重复使用a匹配一个序列，该序列以b所匹配的内容作为分隔符</td>
    </tr>
    <tr>
        <td>_N&lt;M&gt;(a)</td>
        <td>M A</td>
        <td>重复使用a匹配M次</td>
    </tr>
    <tr>
        <td>_repeat&lt;N,M&gt;(a)</td>
        <td>N*M A</td>
        <td>重复使用a匹配，至少N次，至多M次</td>
    </tr>
</table>


可以看出这组操作符均和循环有关。由于框架是基于C++的，所以框架提供的操作符也依赖于对C++操作符的重载。由于C++操作符中并没有合适的操作符与 N A 和 N*M A 相对应，所以框架并未提供对应的操作符，而是提供了2个对应的函数_N和_repeat。

上表中的克林星号操作符和加号操作符是框架对ABNF范式的扩充，但在工程实践当中，这两个操作符是经常用到，且十分重要的，请注意，与正则表达式不同，克林星号操作符和加号操作符是放在匹配器的前面而非后面的，这是C++操作符重载的限制。

我们可以很容易的看出下面这几对匹配器在效果上是等价的：

    *a     <=>    _repeat_p<0,INFINITE>(a)
    +a     <=>    _repeat_p<1,INFINITE>(a)
    -a     <=>    _repeat_p<0,1>(a)
    a % b  <=>    a & *(b&a) 

由于我们的操作符都是在C++里定义的，因此必须遵守C/C++的操作符优先级规则。把表达式用括号分组则可超越这个规则。比如,*(a|b)应当被理解为匹配a或b零到任意多次。 

###规则(rule)

规则是框架中另外一个非常重要的模块。规则也是匹配器。

规则有2个重要作用，第一是占位符，第二是在解析文本的过程中保存上下文。
rule容许我们在某个时间点声明一个匹配器，并在以后的某个时间再定义它，这点对于解析复杂的结构递归的文本至关重要。

    rule<scanner_t,int,no_skip> integer; //声明一个空的规则
    ...
    some code here..
    ...
    integer %=  -(_literal('+') | '-') & +_digit(); //定义一个规则
    ...
    some code here..
    ...
    integer %= +digit(); //重新定义规则

从上面可以看出，规则rule是模板类。其有3个模板参数，第一个是扫描器类型，第二个是context类型，即规则的上下文类型，最后一个是skiper的类型。注意定义一个规则使用的是 "%=" 操作符。

我们可以把rule的context理解为被解析内容在内存中的表述形式，即数据结构。实际上rule的context实际上被组织成了一个栈，访问当前的上下文使用rule的cur_ctx()函数,cur_ctx()函数将返回当前上下文的引用。框架提供了一个预定义的no_context类型，当指定了no_context后，rule将不再具有上下文。后面我们将在后面的例子终进一步了解context以及相关的一些函数。

skiper也是一个解析器，用于匹配在使用规则解析文本之前和解析之后应当被忽略掉的无意义字符。比如在C语言的赋值语句中变量与等号之间，等号与变量之间可以存在多个空格：

    int a = 0,b;
    b = a;

在上面的例子中，我们所使用的no_skip参数，是一个框架预定义的类型，用来告诉规则，在其解析之前和解析之后不忽略任何内容。


##语义动作

一个合成的匹配器构成了一个层次结构。分析过程由最顶层的器匹配器开始，它负责代理并为下层匹配器分配分析任务，这个过程不断递归下降，直至达到原子匹配器为止。借由将语义动作附着到这个层次的很多附着点上。我们可以将平滑的线性输入流转换为结构性的对象。
附着了语义动作的匹配器，即为解析器，因其不仅具备了匹配能力，同时能够会将匹配到的文本传递给语义动作，由语义动作对传递过来文本进行进一步深入的加工和处理。任何匹配器均可以与语义动作绑定。

语义动作的规范和要求相对来说比较简单。任何符合函数签名

    bool(Iterator,Iterator)

的函数或函数对象都可以作为语义动作。也就是说语义动作实际上是一个接受一对迭代器的函数或函数对象，返回值为bool类型，用以表示语义动作执行的成功与否。这对迭代器，[first,last)，描述了被匹配的文本在数据流中所在的范围。

假设我们要解析一个无符号10进制整数，如：12345
构造对应的匹配器如下：

    auto uint_p = (_digit() - '0') & *(_digit());

将一个函数或函数对象与之整体挂钩，我们就可以从中读取到数值。

    struct to_int
    {
        template <typename It>
        bool operator()(It first,It last)
        {
            std::string str(first,last);
            i = atoi(str.c_str());
            std::cout<<"the num is "<<i<<endl;
        }
        int i;
    };

    auto f = to_int();
    auto uint_p = ((_digit() - '0') & *(_digit())) <= f;

“<=”符号为“注入”符号，它将一个函数或函数对象与匹配器挂钩。这样，每当uint_p识别出一个有效数值时，函数f将会被调用，并且被匹配的文本的范围会作为参数传递给f。一般情况下，f会首先将匹配到的文本进行某种形式的转换，在这里则是转化int整形的一个数字，接着干什么事情就有函数f决定了。


##一些例子

我们将通过一些具体的例子来进一步了解chrysanthemum框架。请注意，下面的例子中大量使用了C++11的LAMBDA表达式。

###IP解析器
在这个例子中我们要定义一个IPV4地址的解析器，并且在解析的过程中验证IP地址的合法性。形式上，一个IP地址由‘.’分割的4个1-3位数字构成；逻辑上，IP地址的每个小节都应该 大于等于0 且 小于等于255；解析出的4个数字我们将放在 std::vector<std::size_t>中。下面是代码：

    typedef std::string::iterator IT; //定义迭代器
    rule<scanner_t,std::vector<std::size_t>,no_skip> ip_parser; //声明规则，并指定CONTEXT为td::vector<std::size_t>
    typedef scanner<IT,line_counter_scanner_policy> scanner_t; //定义扫描器

    //定义规则，首先是1-3位数字：_repeat<1,3>(_digit())
    //然后为它嵌入一个语义动作，每当一个小节被匹配，语义动作被调用
    //最后作为一个整体 % '.',构成列表
    ip_parser %= (_repeat<1,3>(_digit()) 
                    <= [&ip_parser](IT first,IT last){
                        std::size_t num = converter<std::size_t>::do_convert(first,last); //转换
                        if(num < 0 || num > 255) return false; //验证正确性
                        ip_parser.cur_ctx().push_back(num); //填充context
                        return true;
                    }) % '.';

    std::string str;
    std::cout<<"please input ip address"<<std::endl;
    std::cin>>str;
    //构造扫描器，指定扫描的范围
    scanner_t scan(str.begin(),str.end());
    //开始解析
    if(ip_parser(scan) && scan.at_end()) {
        std::for_each(ip_parser.cur_ctx().begin(),ip_parser.cur_ctx().end(),[](std::size_t i){
                      std::cout<<i<<" ";
        });
        std::cout<<"OK"<<std::endl;
    } else {

        std::cout<<"ERROR at:"<<scan.line_no<<" "<<scan.col_no<<std::endl;
    }


###递归定义的列表
在这个例子中，我们将解析一个递归定义的列表。列表的定义如下：

1. 一个列表以“{”开始，以“}”结束。
2. 列表中包含以以逗号分开的多个元素，每个元素是一个小写字符串或者列表。
3. 列表不能为空，列表元素之间容许有零到多个空格。

一个这种列表的例子是：

    { aaa , {bbb , ccc} , { ddd } ,eee }

实际上我们可以把rule的context理解为被解析内容在内存中的表述形式，即数据结构，因此我们先为这种列表设计一个数据结构。可以很容易的看出，实际上这种列表可以表达为一棵树，书中有两种节点，一种代表列表本身，一种代表小写字符串。代码如下：

    enum NODE_TYPE
    {
        STRING_NODE = 0,
        LIST_NODE = 1,
    };

    struct node 
    {
        NODE_TYPE type;
        node() {}
        node(NODE_TYPE t):type(t) {}
        virtual ~node() {}
    };

    struct list_node:public node
    {
        list_node():node(LIST_NODE) {}
        std::vector<node*> nodes_;

        void add_child(node* p)

        {
            nodes_.push_back(p);
        }

        virtual ~list_node() 
        {
            std::for_each(nodes_.begin(),nodes_.end(),[](node* p){delete p;} );
        }
    };

    struct string_node:public node
    {
        string_node():node(STRING_NODE) {}
        virtual ~string_node() {}

        template <typename IT>
        void assign(IT first,IT last) 
        {
            str.assign(first,last);
        }

        std::string str;
    };


前面我们讲到，实际上context在rule内部被维护成了一个栈，每当开始一次匹配的时候，规则会自动新建一个栈，作为当前的上下文，这样做的原因在于列表是递归定义的。在列表解析器执行的过程中，有可能递归的调用其自身，因此需要像函数一样，每次调用过程都新开辟一个上下文。

访问规则当前的上下文使用cur_ctx()函数。cur_ctx()函数返回当前上下文的引用。

有压栈必然会有退栈，那么规则在什么时候退栈呢？有两种情况：

1 当前上下文解析完成后，我们需要回到上次解析的上下文中，并获取此次解析的结果，此时需要调用函数pop_ctx(),pop_ctx()将返回当前的上下文，并退栈。
2 当前上下文解析失败后，规则会自动退栈。

在第一种情况下，何时退栈由程序决定，第二种情况下，是自动退栈。

同时，规则提供2个函数，on_init和on_error，用于指定回调函数，这些回调函数会在压栈和解析失败退栈时被调用，其参数为当前的上下文的引用。我们可以利用他们做一些上下文的初始化和回收的工作。

总结规则中context的相关行为如下：

* 每次开始解析时，新建一个上下文并压栈，如果通过on_init指定了回调函数，则调用该回调函数。
* 解析失败时，如果通过on_error指定了回调函数，则调用该回调函数。
* 解析成功时，退栈通过pop_ctx()实现，调用pop_ctx()的时机由用户确定

以下是解析器部分的代码：

    //定义迭代器和扫描器的类型
    typedef std::string::iterator IT;
    typedef scanner<IT,line_counter_scanner_policy> scanner_t;

    //这里我们定义一个语法类，并将所有需要用到的解析器全部定义在这个语法类里面。
    struct grammer
    {
        //这里我们将两个解析期的第三个参数指定为_space,因此，它们将自动忽略掉某个元素两端多余的空格。
        //注意:为了多态的特性，这里的context都被指定为指针。
        rule<scanner_t,list_node*,_space> list;//列表的规则
        rule<scanner_t,string_node*,_space> str;//字符串的规则

        grammer()
        {
            //定义on_init 和 on_error回调函数。
            list.on_init([](list_node*& p){p=new list_node();});
            list.on_error([](list_node*& p){delete p;});

            //一个列表以“{”开始，以“}”结束。
            //列表中包含以以逗号分开的多个元素，每个元素是一个字符串或者列表。
            list %=  '{'
                   & (   
                         str <= [=](IT first,IT last) { 
                                    //规则str解析成功后，退栈并将结果合并到当前list的上下文中。
                                    list.cur_ctx()->add_child(str.pop_ctx());
                                    return true;
                                }
                       | list <= [=](IT first,IT last) {    
                                    //规则list解析成功后，首先退栈，然后将结果合并到之前解析的上下文中
                                    auto p = list.pop_ctx();
                                    list.cur_ctx()->add_child(p);
                                    return true;
                                } 
                     )  % ','
                   & '}';

            //定义on_init 和 on_error回调函数。
            str.on_init([](string_node*& p){p=new string_node();});
            str.on_error([](string_node*& p){delete p;});
            //字符串的规则
            str %= +_lower() <= [=](IT first,IT last) {
                                        str.cur_ctx()->assign(first,last);
                                        return true;
                                };
                 
            
        }
    }


        //使用语法类。
        grammer g;
        std::string str = "{ aaa  , bbb ,{ccc}, {{ddd},eee} } ";
        std::cout<<str<<std::endl;
        scanner_t scan(str.begin(),str.end());
        if(g.obj(scan))
        {
            std::cout<<"OK"<<std::endl;
            auto p = g.obj.pop_ctx();
            delete p;
        }
        else
        {
            std::cout<<"FAILED"<<std::endl;
        }

通过观察语义动作和分析解析的过程，可以看出，整个树形结构（更一般的情形下，称之为抽象语法树ADT）在递归下降的解析过程中自动构建了起来。

###简单的计算器
在这个例子中，我们将实现一个简单的计算器，只支持正整数的加减乘除。
这样的一个例子包括：

    20+ 2 * 3 + 6/2/3 +1000 

首先，我们可以确定这样的计算表达式的EBNF范式(EBNF范式的确定过程不在本文的讨论范围内,EBNF和ABNF范式基本类似)：
    
    factor –> number
    expr –> term { + term }
         | term { – term }
    term –> factor { * factor }
             | factor { / factor }

然后来考虑将上面的ebnf范式使用chrysanthemum框架翻译出来，并将计算的过程糅合进解析的过程中：

    struct grammer
    {

        typedef std::string::iterator IT;
        typedef scanner<IT,line_counter_scanner_policy> scanner_t;

        rule<scanner_t,int,_space> integer; //对应上面的factor
        rule<scanner_t,int,_space> term; //对应上面的term
        rule<scanner_t,int,_space> expression;//对应上面的expression

        grammer()
        {
            //对应于上面的factor –> number
            integer %= (+_digit()) <= [&](IT first,IT last){ integer.cur_ctx() = converter<int>::do_convert(first,last); return true;};
            //对应于    expr –> term { + term }
            //              | term { – term }
            term %=   integer <= [&](IT first,IT last){ term.cur_ctx() = integer.pop_ctx(); return true;}
                    //提取左操作数，首先保存在term的上下文中
                    & *(
                                    ('*' & integer ) <= [&](IT first,IT last){  term.cur_ctx() *= integer.pop_ctx(); return true; } 
                                    //提取右操作数，并计算乘法，结果保存于 term 的上下文中
                                  | ('/' & integer ) <= [&](IT first,IT last){  term.cur_ctx() /= integer.pop_ctx(); return true; } 
                                  //提取右操作数，并计算除法，结果保存于 term 的上下文中                
                        );
            //对应于上面的    expr –> term { + term }
            //                  | term { – term }
            expression %=   term <= [&](IT first,IT last){ expression.cur_ctx() = term.pop_ctx(); return true; }
                            //提取左操作数，首先保存在expression的上下文中
                          & *(
                                    ('+' & term ) <= [&](IT first,IT last){ expression.cur_ctx() += term.pop_ctx(); return true; } 
                                    //提取右操作数，并计算加法，结果保存于 expression 的上下文中
                                  | ('-' & term ) <= [&](IT first,IT last){  expression.cur_ctx() -= term.pop_ctx(); return true; }
                                    //提取右操作数，并计算减法，结果保存于 expression 的上下文中 
                             ) ;
        }

        int excute(std::string& str) {
            scanner_t scan(str.begin(),str.end());
            if(expression(scan) && scan.at_end()) {
                std::cout<<"result:"<<expression.pop_ctx()<<std::endl;
            } else {
                std::cout<<"syntax error:("<<scan.line_no<<","<<scan.col_no<<")"<<std::endl;
            }
        }
        
    };

    int main() {
        grammer g;
        std::string str = " 20+ 2 * 3 + 6/2/3 +1000 ";
        g.excute(str);

        str = " 20 +2 +3";
        g.excute(str);

        str = " 20*2*3 ";
        g.excute(str);

        str = " 20+ 2 * 3a + 6/2/3 +1000 ";
        g.excute(str);
             
    }



###JSON解析器

细节请参考 exmaple/json.cc 


