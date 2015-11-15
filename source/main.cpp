#include "lexical_cast_stringize.h"
#include "lexical_cast_examples.h"
#include "signals2.h"
#include "signals2_connection_management.h"
#include "signals2_document.h"
#include "rdmp_bind.h"
#include "BrrLogger.h"

int main()
{
    BRR_LOGI("################# 1 step");
    rdmp::SignalsHelloWorld();
    rdmp::SignalsWithArgs();
    rdmp::SimpleReturnedValue();
    rdmp::RetMaxValue();
    rdmp::RetVectorValues();

    BRR_LOGI("################# 2 step");
    rdmp::SimpleDisconnectSlot();
    rdmp::SimpleBlockSlot();
    rdmp::SimpleScopedConnection();
    rdmp::SimpleDisconnectEquivalentSlots();
    rdmp::TrackObjectLive();
    rdmp::SimpleButton();

    BRR_LOGI("################# 3 step");
    rdmp::SimpleExampleOfDocumentView();

    BRR_LOGI("################# 4 step");
    rdmp::BindEmpty();
    rdmp::BindWithTwoArgs();
    rdmp::BindObjectMethodWithArgs();
    rdmp::BindObjectOverloadedMethod();
    rdmp::BindReferenceAsArgs();

    BRR_LOGI("################# 5 step");
    rdmp::TryCastTypeToShort('5');
    rdmp::TryCastTypeToShort("5a");
    rdmp::TryCastTypeToShort(std::string("5"));
    rdmp::CastWithoutMemoryAlloc(6);
    rdmp::CastWithoutMemoryAlloc('6');
    rdmp::CastWithoutMemoryAlloc("6");
    rdmp::CastWithoutMemoryAlloc(std::string("6a"));
    rdmp::CastFirst3SymbolsOfString("32104");
    rdmp::RunStrigizeExample();


    return 0;
}

