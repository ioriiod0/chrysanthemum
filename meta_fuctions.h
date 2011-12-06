// ======================================================================================
// File         : meta_fuctions.h
// Author       : Gao Lei 
// Last Change  : 12/04/2011 | 23:24:58 PM | Sunday,December
// Description  : 
// ======================================================================================

//  //////////////////////////////is_type_in_types/////////////////////////////////////////////////
    template <typename T,typename... Args>
    struct is_type_in_types;

    template <typename T,typename Head,typename... Tails>
    struct is_type_in_types<T,Head,Tails...>
    {
        const static bool value =  std::is_same<T,Head>::value || is_type_in_types<T,Tails...>::value;
    };

    template <typename T,typename U>
    struct is_type_in_types<T,U>
    {
        const static bool value = std::is_same<T,U>::value;
    };
    ////////////////////////////////max_size//////////////////////////////////////////////////
    template <typename... Args>
    struct max_size_of;

    template <typename Head,typename... Tails>
    struct max_size_of<Head,Tails...>
    {
        const static std::size_t value = sizeof(Head) > max_size_of<Tails...>::value ?
                                sizeof(Head) : max_size_of<Tails...>::value;
    };

    template <typename T>
    struct max_size_of<T>
    {
        const static std::size_t value = sizeof(T);
    };


    ////////////////////////////////index_of///////////////////////////////////////////////////
    template <typename T,typename... Args>
    struct index_of;

    template <typename T,typename Head,typename... Tails>
    struct index_of<T,Head,Tails...>
    {
        const static std::size_t value = std::is_same<T,Head>::value?0:1+index_of<T,Tails...>::value;
    };

    template <typename T,typename Tail>
    struct index_of<T,Tail>
    {
        static_assert(std::is_same<T,Tail>::value,"the given type is not in variant's types!");
        const static std::size_t value = 0;
    };

    ////////////////////////////////at///////////////////////////////////////////////////
    template <std::size_t Idx,typename... Args>
    struct at;

    template <std::size_t Idx,typename Head,typename... Tails>
    struct at<Idx,Head,Tails...>
    {
        typedef typename at<Idx-1,Tails...>::type type;    
    };

    template <typename Head,typename... Tails>
    struct at<0,Head,Tails...>
    {
        typedef Head type;
    };
    ////////////////////////////if_else////////////////////////////////////////////////
    template <bool B,typename T,typename U>
    struct enable_if_else;

    template <typename T,typename U>
    struct enable_if_else<true,T,U>
    {
        typedef T type;
    };
    
    template <typename T,typename U>
    struct enable_if_else<false,T,U>
    {
        typedef U type;
    };
    



