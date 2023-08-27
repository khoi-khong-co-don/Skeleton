/*
 * This file was generated by Mr. ThanhNV22 via his tool.
 * This is an auto-generated file, DON'T TRY TO CHANGE ANYTHING OF THIS FILE.
 * Author: ThanhNV22, FPT Software
*/
#ifndef VIEWS_H
#define VIEWS_H

#include "QAppFramework.h"
#include "QQuickViewer.h"
#include "ViewStates.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const APPLICATION_STATE STATE_ID_ROOT                    = {E::STATE_ID_ROOT    , ROOT_Entry    , ROOT_Exit    , LAYER::LAYER_BASE  , LIMIT::NONE  , ROOT     };
static const APPLICATION_STATE STATE_ID_SCREEN_A                = {E::STATE_ID_SCREEN_A, SCREEN_A_Entry, SCREEN_A_Exit, LAYER::LAYER_SCREEN, LIMIT::NONE  , SCREEN_A };
static const APPLICATION_STATE STATE_ID_POPUP_A                 = {E::STATE_ID_POPUP_A , NULL          , POPUP_A_Exit , LAYER::LAYER_POPUP , LIMIT::SEC_30 , POPUP_A  };
static const APPLICATION_STATE STATE_ID_POPUP_B                 = {E::STATE_ID_POPUP_B , POPUP_B_Entry , POPUP_B_Exit , LAYER::LAYER_POPUP , LIMIT::SEC_20, POPUP_B  };
static const APPLICATION_STATE STATE_ID_SCREEN_B                = {E::STATE_ID_SCREEN_B, SCREEN_B_Entry, SCREEN_B_Exit, LAYER::LAYER_SCREEN, LIMIT::NONE  , SCREEN_B };
static const APPLICATION_STATE STATE_ID_SCREEN_LOGIN_NX_CLOUD   = {E::STATE_ID_SCREEN_LOGIN_NX_CLOUD, SCREEN_LOGIN_NX_CLOUD_Entry, SCREEN_LOGIN_NX_CLOUD_Exit, LAYER::LAYER_SCREEN, LIMIT::NONE  , SCREEN_LOGIN_NX_CLOUD };
static const APPLICATION_STATE STATE_ID_POPUP_edit_server       = {E::STATE_ID_POPUP_edit_server , POPUP_edit_server_Entry , POPUP_edit_server_Exit , LAYER::LAYER_POPUP , LIMIT::NONE, POPUP_edit_server  };
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const STATE_TRIGGER STATE_ID_POPUP_A_trigger[2] = 
{
	{E::EVT_POPUP_A_BUTTON_YYY_CLICKED, NULL, &STATE_ID_SCREEN_B },
	{E::EVT_POPUP_A_BUTTON_XXX_CLICKED, NULL, &STATE_ID_SCREEN_A },
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const STATE_TRIGGER STATE_ID_POPUP_B_trigger[2] = 
{
	{E::EVT_POPUP_B_BUTTON_XXX_CLICKED, EVT_POPUP_B_BUTTON_XXX_CLICKED_MSG, &STATE_ID_SCREEN_B },
	{E::EVT_POPUP_B_BUTTON_YYY_CLICKED, EVT_POPUP_B_BUTTON_YYY_CLICKED_MSG, &STATE_ID_SCREEN_A },
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const STATE_TRIGGER STATE_ID_POPUP_edit_server_trigger[3] =
{
        {E::EVT_POPUP_edit_server_BUTTON_BACK_CLICKED, EVT_POPUP_edit_server_BUTTON_BACK_CLICKED_MSG, &STATE_ID_SCREEN_B },
        {E::EVT_POPUP_edit_server_BUTTON_CONNECT_CLICKED, EVT_POPUP_edit_server_BUTTON_CONNECT_CLICKED_MSG, &STATE_ID_SCREEN_A },
        {E::EVT_POPUP_edit_server_BUTTON_DELETE_CLICKED, EVT_POPUP_edit_server_BUTTON_DELETE_CLICKED_MSG, &STATE_ID_SCREEN_B },
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const STATE_TRIGGER STATE_ID_ROOT_trigger[4] = 
{
	{E::EVT_BLK_TO_SCREEN_B, NULL                   , &STATE_ID_SCREEN_B },
	{E::EVT_BLK_TO_SCREEN_A, EVT_BLK_TO_SCREEN_A_MSG, &STATE_ID_SCREEN_A },
	{E::EVT_BLK_TO_POPUP_A , NULL                   , &STATE_ID_POPUP_A  },
	{E::EVT_BLK_TO_POPUP_B , EVT_BLK_TO_POPUP_B_MSG , &STATE_ID_POPUP_B  },
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const STATE_TRIGGER STATE_ID_SCREEN_A_trigger[4] = 
{
	{E::BUT_A_CLICKED                  , BTN_A_MSG                          , NULL               },
	{E::EVT_SCREEN_A_BUTTON_YYY_CLICKED, EVT_SCREEN_A_BUTTON_YYY_CLICKED_MSG, &STATE_ID_POPUP_A  },
	{E::EVT_SCREEN_A_BUTTON_ZZZ_CLICKED, NULL                               , &STATE_ID_POPUP_B  },
	{E::EVT_SCREEN_A_BUTTON_XXX_CLICKED, EVT_SCREEN_A_BUTTON_XXX_CLICKED_MSG, &STATE_ID_SCREEN_B },
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const STATE_TRIGGER STATE_ID_SCREEN_B_trigger[4] =
{
//	{E::EVT_SCREEN_B_BUTTON_XXX_CLICKED, EVT_SCREEN_B_BUTTON_XXX_CLICKED_MSG, &STATE_ID_SCREEN_A },
//	{E::EVT_SCREEN_B_BUTTON_YYY_CLICKED, EVT_SCREEN_B_BUTTON_YYY_CLICKED_MSG, &STATE_ID_POPUP_B  },
//	{E::EVT_SCREEN_B_BUTTON_ZZZ_CLICKED, NULL                               , &STATE_ID_POPUP_A  },

    {E::EVT_SCREEN_B_BUTTON_SERVER_CLICKED, EVT_SCREEN_B_BUTTON_SERVER_CLICKED_MSG, &STATE_ID_SCREEN_A },
    {E::EVT_SCREEN_B_BUTTON_YYY_CLICKED, EVT_SCREEN_B_BUTTON_YYY_CLICKED_MSG, &STATE_ID_POPUP_B  },
    {E::EVT_SCREEN_B_BUTTON_ZZZ_CLICKED, NULL                               , &STATE_ID_SCREEN_LOGIN_NX_CLOUD  },
    {E::EVT_SCREEN_B_BUTTON_EDIT_SERVER_CLICKED, EVT_SCREEN_B_BUTTON_EDIT_SERVER_CLICKED_MSG, &STATE_ID_POPUP_edit_server  },
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const STATE_TRIGGER STATE_ID_SCREEN_LOGIN_NX_CLOUD_trigger[2] =
{
    {E::EVT_SCREEN_NX_LOGIN_CLOUD_BUTTON_NEXT_CLICKED, EVT_SCREEN_LOGIN_NX_CLOUD_BUTTON_NEXT_CLICKED_MSG, &STATE_ID_POPUP_A },
    {E::EVT_SCREEN_NX_LOGIN_CLOUD_BUTTON_BACK_CLICKED, EVT_SCREEN_LOGIN_NX_CLOUD_BUTTON_BACK_CLICKED_MSG, &STATE_ID_SCREEN_B  },
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static const STATE_SYSTEM STATE_ALL[7] =
{
	{E::STATE_ID_ROOT    , STATE_ID_ROOT_trigger    , ALEN(STATE_ID_ROOT_trigger)    , &STATE_ID_ROOT     },
	{E::STATE_ID_SCREEN_A, STATE_ID_SCREEN_A_trigger, ALEN(STATE_ID_SCREEN_A_trigger), &STATE_ID_SCREEN_A },
	{E::STATE_ID_POPUP_A , STATE_ID_POPUP_A_trigger , ALEN(STATE_ID_POPUP_A_trigger) , &STATE_ID_POPUP_A  },
	{E::STATE_ID_POPUP_B , STATE_ID_POPUP_B_trigger , ALEN(STATE_ID_POPUP_B_trigger) , &STATE_ID_POPUP_B  },
	{E::STATE_ID_SCREEN_B, STATE_ID_SCREEN_B_trigger, ALEN(STATE_ID_SCREEN_B_trigger), &STATE_ID_SCREEN_B },
    {E::STATE_ID_SCREEN_LOGIN_NX_CLOUD, STATE_ID_SCREEN_LOGIN_NX_CLOUD_trigger, ALEN(STATE_ID_SCREEN_LOGIN_NX_CLOUD_trigger), &STATE_ID_SCREEN_LOGIN_NX_CLOUD },
    {E::STATE_ID_POPUP_edit_server , STATE_ID_POPUP_edit_server_trigger , ALEN(STATE_ID_POPUP_edit_server_trigger) , &STATE_ID_POPUP_edit_server  },

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // VIEWS_H