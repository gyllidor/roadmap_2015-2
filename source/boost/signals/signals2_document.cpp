#include "signals2_document.h"
#include "BrrLogger.h"

#include <boost/signals2.hpp>

//! ************************************************************************************************
//!
//! ************************************************************************************************
namespace
{

//! ************************************************************************************************
class Document
{
public: // types
    typedef boost::signals2::signal <void()> Signal;
    typedef boost::signals2::connection      Connection;
    typedef Signal::slot_type                Slot;

public: // methods
    Document()
        : m_signal()
    {}

    Connection Connect(const Slot& slot)
    {
        return m_signal.connect(slot);
    }

    void Append(const std::string& text)
    {
        m_text.append(text);
        m_signal();
    }

    const std::string& GetText() const
    {
        return m_text;
    }

private: // members
    Signal      m_signal;
    std::string m_text;

}; // class Document

//! ************************************************************************************************
class IView
{
public: // methods
    IView(Document& doc)
        : m_document(doc)
        , m_documentConnection()
    {
        m_documentConnection = m_document.Connect(boost::bind(&IView::Refresh, this));
    }

    virtual ~IView()
    {
        m_documentConnection.disconnect();
    }

    virtual void Refresh() = 0;

protected: // members
    Document&            m_document;
    Document::Connection m_documentConnection;

}; // class IView

//! ************************************************************************************************
class ViewText : public IView
{
public: // methods
    ViewText(Document& doc)
        : IView(doc)
    {}

    ~ViewText()
    {}

    void Refresh() override
    {
        BRR_LOGI("Pew new text pushed to document: %s", m_document.GetText().c_str());
    }

}; // class ViewText

//! ************************************************************************************************
class ViewHex : public IView
{
public: // methods
    ViewHex(Document& doc)
        : IView(doc)
    {}

    ~ViewHex()
    {}

    void Refresh() override
    {
        const std::string& c_text = m_document.GetText();
        std::cout << "Hex View:" << std::endl;
        for (auto element : c_text)
            std::cout << ' ' << std::hex << static_cast <int> (element);
        std::cout << std::endl;
    }

}; // class ViewHex

} // unnamed namespace

//! ************************************************************************************************
//! ************************************************************************************************
//! ************************************************************************************************

//! ************************************************************************************************
//!
//! ************************************************************************************************
void rdmp::SimpleExampleOfDocumentView()
{
    BRR_LOGI("you should uncoment function body");
    /*Document doc;
    ViewHex  vhex(doc);
    ViewText vtext(doc);

    std::cout << "Type some text: ";
    std::string text;
    std::cin >> text;
    doc.Append(text);

    std::cout << "Type some text: ";
    std::cin >> text;
    doc.Append(" " + text);*/
}
