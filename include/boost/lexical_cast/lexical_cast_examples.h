#ifndef LEXICAL_CAST_EXAMPLES_H
#define LEXICAL_CAST_EXAMPLES_H

#include "BrrLogger.h"

#include <boost/lexical_cast.hpp>
#include <boost/array.hpp>

//! ************************************************************************************************
//!
//! ************************************************************************************************
namespace rdmp
{

//! ************************************************************************************************
//! @brief convert some type to short
//! ************************************************************************************************
template <typename Type>
void TryCastTypeToShort(Type value)
{
    try
    {
        BRR_LOGI("%d", boost::lexical_cast<short>(value));
    }
    catch (const boost::bad_lexical_cast& bad_cast)
    {
        BRR_LOGE("%s", bad_cast.what());
    }
}

//! ************************************************************************************************
//! @brief cast without memory allocation
//! ************************************************************************************************
template <typename Type>
void CastWithoutMemoryAlloc(Type value)
{
    try
    {
        boost::array<char, 50> buffer = boost::lexical_cast<boost::array<char, 50>>(value);
        BRR_LOGI("%s", buffer.begin());
    }
    catch (const boost::bad_lexical_cast& bad_cast)
    {
        BRR_LOGE("%s", bad_cast.what());
    }
}

//! ************************************************************************************************
//! @brief cast only first three symbol of given std::string
//! ************************************************************************************************
void CastFirst3SymbolsOfString(const std::string& value);

} // namespace rdmp

#endif // LEXICAL_CAST_EXAMPLES_H
