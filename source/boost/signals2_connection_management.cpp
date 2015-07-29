#include "signals2_connection_management.h"
#include "BrrLogger.h"

#include <boost/signals2/signal.hpp>
#include <boost/signals2/shared_connection_block.hpp>

//! ************************************************************************************************
//! @brief function helpers
//! ************************************************************************************************
void PrintHappiness()
{
    BRR_LOGI("looks like i am happy O_o");
}

//! ************************************************************************************************
void SoonWillBlock()
{
    BRR_LOGI("soon i will be blocked");
}

//! ************************************************************************************************
void ScopedConnection()
{
    BRR_LOGI("i am scoped connection and soon i will be destroyed");
}

//! ************************************************************************************************
void DisconnectEquivalentFirst()
{
    BRR_LOGI("first candidate for disconnect");
}

//! ************************************************************************************************
void DisconnectEquivalentSecond()
{
    BRR_LOGI("second candidate for disconnect");
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void rdmp::SimpleDisconnectSlot()
{
    boost::signals2::signal<void(void)> sig;
    boost::signals2::connection con = sig.connect(&PrintHappiness);

    sig();

    con.disconnect();

    sig();
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void rdmp::SimpleBlockSlot()
{
    boost::signals2::signal <void(void)> sig;
    boost::signals2::connection con = sig.connect(&SoonWillBlock);
    sig();

    {
        boost::signals2::shared_connection_block block(con);
        BRR_LOGI("slot is blocked");
        sig();
//        block.unblock();
    }

    BRR_LOGI("now slot unblocked");
    sig();
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void rdmp::SimpleScopedConnection()
{
    boost::signals2::signal<void(void)> sig;
    {
        boost::signals2::scoped_connection scopedCon(sig.connect(&ScopedConnection));
        // doesn't compile due to compiler attempting to copy a temporary scoped_connection object
        // boost::signals2::scoped_connection c0 = sig.connect(ShortLived());
        // okay
        // boost::signals2::scoped_connection c1(sig.connect(ShortLived()));
        // also okay
        // boost::signals2::scoped_connection c2;
        // c2 = sig.connect(ShortLived());
        sig();
    }

    BRR_LOGI("scoped connection now dead");
    sig();
}

//! ************************************************************************************************
//!
//! ************************************************************************************************
void rdmp::SimpleDisconnectEquivalentSlots()
{
    boost::signals2::signal<void(void)> sig;
    sig.connect(&DisconnectEquivalentFirst);
    sig.connect(&DisconnectEquivalentSecond);

    sig();
    sig.disconnect(&DisconnectEquivalentFirst);

    BRR_LOGI("someone disconnected, guess who?");
    sig();
}
