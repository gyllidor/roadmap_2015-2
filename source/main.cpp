#include "signals2.h"
#include "signals2_connection_management.h"
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

    return 0;
}

