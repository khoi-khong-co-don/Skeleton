#ifndef QCOMMONSTRUCTS_H
#define QCOMMONSTRUCTS_H
#include <QString>
#include <QVariant>
#include <stddef.h>
#include "QCommonDefines.h"
#include "QCommonEnums.h"

typedef struct popup_data
{
    uchar       id;
    LIMIT       duration;
    QString     QmlPath;
    QVariant    msg;
    void        (*funcEntry)(QVariant msg, uchar viewerIndex);
    void        (*funcExit)(QVariant msg, uchar viewerIndex);
} POPUP_DATA;

typedef struct st_application_states
{
    uchar       id;
    void        (*funcEntry)(QVariant msg, uchar viewerIndex);
    void        (*funcExit)(QVariant msg, uchar viewerIndex);
    LAYER       layerbase;
    LIMIT       duration;
    QString     QmlPath;
    QVariant    msg;
} APPLICATION_STATE;

typedef struct _st_state_trigger
{
    uchar                   evt;
    void                    (*func)(QVariant msg, uchar viewerIndex);
    const APPLICATION_STATE *trans;
}STATE_TRIGGER;

typedef struct _st_state_system
{
    uchar                   id;
    const STATE_TRIGGER     *trigger;
    uint                    size;
    const APPLICATION_STATE *state;
}STATE_SYSTEM;

#endif // QCOMMONSTRUCTS_H
