#include "lexical_cast/lexical_cast_examples.h"

//! ************************************************************************************************
//!
//! ************************************************************************************************
void rdmp::CastFirst3SymbolsOfString(const std::string& value)
{
    try
    {
        BRR_LOGI("%d", boost::lexical_cast<int>(value.data(), 3));
    }
    catch(const boost::bad_lexical_cast& bad_cast)
    {
        BRR_LOGE("%s", bad_cast.what());
    }
}
