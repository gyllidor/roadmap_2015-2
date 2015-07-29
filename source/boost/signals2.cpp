#include "signals2.h"
#include "BrrLogger.h"

#include <boost/signals2.hpp>
#include <vector>

//! ************************************************************************************************
//! @brief help structs
//! ************************************************************************************************
namespace
{
//! ************************************************************************************************
struct HellWorld
{
    void operator()()
    {
        BRR_LOGI("HelloWorld");
    }

}; // struct HelloWorld

//! ************************************************************************************************
struct Woo
{
    void operator()()
    {
        BRR_LOGE_WF("Woo");
    }

}; // struct Woo

//! ************************************************************************************************
struct Hoo
{
    void operator()()
    {
        BRR_LOGW_WF("Hoo");
    }

}; // struct Hoo

//! ************************************************************************************************
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

//! ************************************************************************************************
void PrintSumArguments(float arg1, float arg2)
{
    BRR_LOGI("Sum of arguments is %.2f", arg1 + arg2);
}

//! ************************************************************************************************
void PrintProductArguments(float arg1, float arg2)
{
    BRR_LOGI("Product of arguments is %.2f", arg1 * arg2);
}

//! ************************************************************************************************
void PrintDifferenceArguments(float arg1, float arg2)
{
    BRR_LOGI("The difference is %.2f", arg1 - arg2);
}

//! ************************************************************************************************
void PrintQuotient(float arg1, float arg2)
{
    BRR_LOGI("The quotient is %.2f", arg1 / arg2);
}

//! ************************************************************************************************
float RetSumArguments(float arg1, float arg2)
{
    return arg1 + arg2;
}

//! ************************************************************************************************
float RetProductArguments(float arg1, float arg2)
{
    return arg1 * arg2;
}

//! ************************************************************************************************
float RetDifferenceArguments(float arg1, float arg2)
{
    return arg1 - arg2;
}

//! ************************************************************************************************
float RetQuotient(float arg1, float arg2)
{
    return arg1 / arg2;
}

} //! @brief unnamed namespace

//! ************************************************************************************************
//! @brief Combiner returns the maximum value that all slots returned
//! ************************************************************************************************
template <typename Type>
struct MaximumValue
{
    typedef Type result_type;

    template <typename InputIterator>
    Type operator()(InputIterator first, InputIterator last)
    {
        if (first == last)
            return Type();

        Type maxValue = *first++;
        while(first != last)
        {
            if (maxValue < *first)
                maxValue = *first;
            ++first;
        }

        return maxValue;
    }

}; // struct MaximumValue

//! ************************************************************************************************
//! @brief Combiner that returns all returened values in std::vector or etc.
//! ************************************************************************************************
template <typename Combiner>
struct AggregateValues
{
    typedef Combiner result_type;

    template <typename InputIterator>
    Combiner operator()(InputIterator first, InputIterator last)
    {
        Combiner allValues;
        while(first != last)
            allValues.push_back(*first++);

        return allValues;
    }

}; // struct AggregateValues

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

//! ************************************************************************************************
//!
//! ************************************************************************************************
void rdmp::SimpleReturnedValue()
{
    boost::signals2::signal<float(float,float)> sig;
    sig.connect(3, &RetSumArguments);
    sig.connect(2, &RetProductArguments);
    sig.connect(1, &RetDifferenceArguments);
    sig.connect(0, &RetQuotient);

    //! @brief The default combiner returns a boost::optional containing the return
    //!        value of the last slot in the slot list, in this case the
    BRR_LOGI("return %.2f", *sig(3.2, 6.8));
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void rdmp::RetMaxValue()
{
    boost::signals2::signal<float(float, float), MaximumValue<float> > sig;
    sig.connect(&RetSumArguments);
    sig.connect(&RetProductArguments);
    sig.connect(&RetDifferenceArguments);
    sig.connect(&RetQuotient);

    BRR_LOGI("combiner returns %.2f", sig(3.2, 6.8));
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void rdmp::RetVectorValues()
{
    boost::signals2::signal<float(float, float), AggregateValues <std::vector<float> > > sig;
    sig.connect(&RetSumArguments);
    sig.connect(&RetProductArguments);
    sig.connect(&RetDifferenceArguments);
    sig.connect(&RetQuotient);

    BRR_LOGI_WF("aggregated values:");

    std::vector<float> allValues = sig(3.2, 6.8);
    for(float iter : allValues)
        BRR_LOGI_WF(" %.2f", iter);

    BRR_LOGI_WF("\n");

    //std::copy(allValues.begin(), allValues.end(), std::ostream_iterator <float> (std::cout, " "));
}
