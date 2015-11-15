#ifndef LEXICAL_CAST_STRINGIZE_H
#define LEXICAL_CAST_STRINGIZE_H

#include "BrrLogger.h"

#include <string>

#include <boost/lexical_cast.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/include/for_each.hpp>

//! ************************************************************************************************
//!
//! ************************************************************************************************
namespace rdmp
{
//! ************************************************************************************************
//! @brief stringization functor
//! ************************************************************************************************
class StringizeFunctor
{
public:
    explicit StringizeFunctor(std::string& to_stringize);

    template <typename Type>
    void operator()(Type& to_stringize) const
    {
    m_output += boost::lexical_cast<std::string>(to_stringize);
    }

private:
    std::string& m_output;

}; // class StringizeFunctor

//! ************************************************************************************************
//! @brief Run small exmaple of using StringizeFunctor
//! ************************************************************************************************
void RunStrigizeExample();

} // namespace rdmp

#endif // LEXICAL_CAST_STRINGIZE_H
