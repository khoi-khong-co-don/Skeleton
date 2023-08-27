#ifndef STATE_ID_SCREEN_LOGIN_NX_CLOUD_H
#define STATE_ID_SCREEN_LOGIN_NX_CLOUD_H

#include "QAppFramework.h"
#include "QQuickViewer.h"
#include "ViewsDefines.h"
#include "ViewsEnums.h"

void SCREEN_LOGIN_NX_CLOUD_Entry(QVariant msg, uchar source);
void SCREEN_LOGIN_NX_CLOUD_Exit(QVariant msg, uchar source);
void EVT_SCREEN_LOGIN_NX_CLOUD_BUTTON_NEXT_CLICKED_MSG(QVariant msg, uchar source);
void EVT_SCREEN_LOGIN_NX_CLOUD_BUTTON_BACK_CLICKED_MSG(QVariant msg, uchar source);

#endif // STATE_ID_SCREEN_LOGIN_NX_CLOUD_H
