#include "signals2.h"
#include "BrrLogger.h"

#include <boost/signals2.hpp>

//! ************************************************************************************************
//! @brief help structs
//! ************************************************************************************************
namespace
{
struct HellWorld
{
    void operator()()
    {
        BRR_LOGI("HelloWorld");
    }

}; // struct HelloWorld

struct Woo
{
    void operator()()
    {
        BRR_LOGE_WF("Woo");
    }

}; // struct Woo

struct Hoo
{
    void operator()()
    {
        BRR_LOGW_WF("Hoo");
    }

}; // struct Hoo

struct Newline
{
    void operator()()
    {
        BRR_LOGI_WF("\n");
    }
}; // struct newline

//! ************************************************************************************************
//! @brief help functions
//! ************************************************************************************************
void PrintArguments(float arg1, float arg2)
{
    BRR_LOGI("Passed arguments are %.2f | %.2f", arg1, arg2);
}

void PrintSumArguments(float arg1, float arg2)
{
    BRR_LOGI("Sum of arguments is %.2f", arg1 + arg2);
}

void PrintProductArguments(float arg1, float arg2)
{
    BRR_LOGI("Product of arguments is %.2f", arg1 * arg2);
}

void PrintDifferenceArguments(float arg1, float arg2)
{
    BRR_LOGI("The difference is %.2f", arg1 - arg2);
}

void PrintQuotient(float arg1, float arg2)
{
    BRR_LOGI("The quotient is %.2f", arg1 / arg2);
}

} //! @brief unnamed namespace

//! ************************************************************************************************
//!
//! ************************************************************************************************
void rdmp::SignalsHelloWorld()
{
    boost::signals2::signal<void()> sigHellWorld;
    sigHellWorld.connect(HellWorld());
    sigHellWorld();

    boost::signals2::signal<void()> sigWooHoo;
    sigWooHoo.connect(Woo());
    sigWooHoo.connect(Hoo());
    sigWooHoo.connect(Newline());
    sigWooHoo();

    // slots are invoked this order:
    // 1) ungrouped slots connected with boost::signals2::at_front
    // 2) grouped slots according to ordering of their groups
    // 3) ungrouped slots connected with boost::signals2::at_back
    boost::signals2::signal<void()> sigHooWoo;
    sigHooWoo.connect(1, Woo());
    sigHooWoo.connect(0, Hoo());
    sigHooWoo.connect(2, Newline());
    sigHooWoo();
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void rdmp::SignalsWithArgs()
{
    boost::signals2::signal<void(float,float)> sig;
    sig.connect(&PrintArguments);
    sig.connect(&PrintSumArguments);
    sig.connect(&PrintProductArguments);
    sig.connect(&PrintDifferenceArguments);
    sig.connect(&PrintQuotient);

    sig(3.2, 6.8);
}
