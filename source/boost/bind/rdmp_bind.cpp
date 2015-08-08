#include "rdmp_bind.h"
#include "BrrLogger.h"

#include <boost/bind.hpp>

//! ************************************************************************************************
//!
//! ************************************************************************************************
namespace
{
//! ************************************************************************************************
void PrintNothing()
{
    BRR_LOGI("just nothing");
}

//! ************************************************************************************************
void PrintTwoArgs(int val, const std::string& c_str)
{
    BRR_LOGI("just print %d %s", val, c_str.c_str());
}

//! ************************************************************************************************
void PrintReferences(int val1, int val2)
{
    BRR_LOGI("references are %d ++%d", val1, ++val2);
}

//! ************************************************************************************************
struct JustPrintArgs
{
    void Print(const std::string& c_str1, const std::string& c_str2)
    {
        BRR_LOGI("JustPrintArgs struct %s %s", c_str1.c_str(), c_str2.c_str());
    }

    void PrintNum(int number)
    {
        BRR_LOGI("integer number %d", number);
    }

    void PrintNum(float number)
    {
        BRR_LOGI("float number %f", number);
    }

}; // struct JustPrintArgs

} // unnamed namespace

//! ************************************************************************************************
//!
//! ************************************************************************************************
void rdmp::BindEmpty()
{
    auto PrintNothingFunc = boost::bind(&PrintNothing);
    PrintNothingFunc();
}

//! ************************************************************************************************
void rdmp::BindWithTwoArgs()
{
    auto PrintTwoArgsFunc           = boost::bind(&PrintTwoArgs, _1, _2);
    auto PrintTwoArgsFuncSwappedArg = boost::bind(&PrintTwoArgs, _2, _1);

    PrintTwoArgsFunc(5, "pew pew");

    BRR_LOGI("now will be called function object with swapped arguments order");
    PrintTwoArgsFuncSwappedArg("ewp ewp", 5);
}


//! ************************************************************************************************
void rdmp::BindObjectMethodWithArgs()
{
    JustPrintArgs justPrintArgs;
    auto PrintMethod = boost::bind(&JustPrintArgs::Print, &justPrintArgs, _1, _2);
    PrintMethod("pew pew and", "wep wep");
}

//! ************************************************************************************************
void rdmp::BindObjectOverloadedMethod()
{
    typedef void(JustPrintArgs::*PrintInteger)(int);
    typedef void(JustPrintArgs::*PrintFloat)  (float);

    JustPrintArgs justPrintArgs;
    auto PrintIntFunc   = boost::bind(static_cast <PrintInteger>(&JustPrintArgs::PrintNum),
                                      &justPrintArgs, _1);
    auto PrintFloatFunc = boost::bind(static_cast <PrintFloat>(&JustPrintArgs::PrintNum),
                                      &justPrintArgs, _1);

    PrintIntFunc(6);
    PrintFloatFunc(3.45f);
}

//! ************************************************************************************************
void rdmp::BindReferenceAsArgs()
{
    int val1 = 0;
    int val2 = 0;

    auto PrintRef = boost::bind(&PrintReferences, boost::cref(val1), boost::ref(val2));
    PrintRef();

    val1 = 5;
    val2 = 7;
    PrintRef();
}
