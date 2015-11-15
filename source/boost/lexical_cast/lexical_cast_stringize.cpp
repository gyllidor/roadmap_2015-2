#include "lexical_cast_stringize.h"

//! ************************************************************************************************
//!
//! ************************************************************************************************
rdmp::StringizeFunctor::StringizeFunctor(std::__cxx11::string &to_stringize)
    : m_output(to_stringize)
{
}

//! ************************************************************************************************
void rdmp::RunStrigizeExample()
{
    std::string result;
    rdmp::StringizeFunctor functor(result);
    functor("item1 + ");

    int t = 2;
    functor(t);

    BRR_LOGI("%s", result.c_str());
}
