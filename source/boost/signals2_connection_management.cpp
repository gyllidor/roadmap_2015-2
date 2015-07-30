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
//! @brief news items
//! ************************************************************************************************
struct NewsItem
{
    NewsItem(const std::string& news)
        : m_news(news)
    {}

    const std::string& GetNews() const
    {
        return m_news;
    }

private: // members
    std::string m_news;

}; // struct NewsItem

//! ************************************************************************************************
//! @brief news consumer
//! ************************************************************************************************
struct NewsConsumer
{
    void ReadNews(const NewsItem& newsItem) const
    {
        BRR_LOGI("NewsConsumer %d read - %s", m_count++, newsItem.GetNews().c_str());
    }

private: // members
    static int m_count;

}; // struct NewConsumer

int NewsConsumer::m_count = 0;

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

//! ************************************************************************************************
//!
//! ************************************************************************************************
void rdmp::TrackObjectLive()
{
    typedef boost::signals2::signal <void(const NewsItem&)> NewsMaker;
    typedef boost::function <void(const NewsItem&)> FunctionConsumer;

    NewsConsumer* pNewsConsumerFirst  = new NewsConsumer;
    NewsConsumer* pNewsConsumerSecond = new NewsConsumer;

    NewsMaker newsMaker;
    FunctionConsumer firstConsumer  = boost::bind(&NewsConsumer::ReadNews, pNewsConsumerFirst,  _1);
    FunctionConsumer secondConsumer = boost::bind(&NewsConsumer::ReadNews, pNewsConsumerSecond, _1);
    newsMaker.connect(firstConsumer);
    newsMaker.connect(secondConsumer);

    newsMaker(NewsItem("Just do it"));
    delete pNewsConsumerFirst;
    delete pNewsConsumerSecond;

    NewsMaker coolNewsMaker;
    {
        boost::shared_ptr <NewsConsumer> pFirstConsumer(new NewsConsumer);
        boost::shared_ptr <NewsConsumer> pSecondConsumer(new NewsConsumer);
        coolNewsMaker.connect(NewsMaker::slot_type(&NewsConsumer::ReadNews,
                                                   pFirstConsumer.get(),
                                                   _1).track(pFirstConsumer));

        coolNewsMaker.connect(NewsMaker::slot_type(&NewsConsumer::ReadNews,
                                                   pSecondConsumer.get(),
                                                   _1).track(pSecondConsumer));
        coolNewsMaker(NewsItem("this real coool news :)"));
    }

    coolNewsMaker(NewsItem("object destroyed"));
}
