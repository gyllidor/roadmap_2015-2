#ifndef SIGNALS2_CONNECTION_MANAGEMENT_H
#define SIGNALS2_CONNECTION_MANAGEMENT_H

namespace rdmp
{
//! ************************************************************************************************
//! @brief disconnect slot
//! ************************************************************************************************
void SimpleDisconnectSlot();

//! ************************************************************************************************
//! @brief temporary block some slot
//! ************************************************************************************************
void SimpleBlockSlot();

//! ************************************************************************************************
//! @brief simple example of scoped connection
//! ************************************************************************************************
void SimpleScopedConnection();

//! ************************************************************************************************
//! @brief disconnect equivalent slots
//! ************************************************************************************************
void SimpleDisconnectEquivalentSlots();

//! ************************************************************************************************
//! @brief track object live via track(shared_ptr)
//! ************************************************************************************************
void TrackObjectLive();

//! ************************************************************************************************
//! @brief simple example of a button - subrscribe on button press event (simulation)
//! ************************************************************************************************
void SimpleButton();

} // namespace rdmp

#endif // SIGNALS2_CONNECTION_MANAGEMENT_H