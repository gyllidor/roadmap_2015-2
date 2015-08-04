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

    return 0;
}

