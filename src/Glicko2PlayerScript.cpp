/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Glicko2PlayerStorage.h"
#include "Log.h"

/// @brief Handles loading and saving of player BG ratings
class Glicko2PlayerScript : public PlayerScript
{
public:
    Glicko2PlayerScript() : PlayerScript("Glicko2PlayerScript") { }

    void OnPlayerLogin(Player* player) override
    {
        if (!sConfigMgr->GetOption<bool>("Glicko2.Enabled", true))
            return;

        sGlicko2Storage->LoadRating(player->GetGUID());
        LOG_INFO("module.glicko2", "[Glicko2] Player {} logged in, BG rating loaded.", player->GetName());
    }

    void OnPlayerLogout(Player* player) override
    {
        if (!sConfigMgr->GetOption<bool>("Glicko2.Enabled", true))
            return;

        sGlicko2Storage->SaveRating(player->GetGUID());
        LOG_DEBUG("module.glicko2", "Player {} logged out, BG rating saved.", player->GetName());
    }

    void OnPlayerSave(Player* player) override
    {
        if (!sConfigMgr->GetOption<bool>("Glicko2.Enabled", true))
            return;

        sGlicko2Storage->SaveRating(player->GetGUID());
    }

    void OnPlayerDelete(ObjectGuid guid, uint32 /*accountId*/) override
    {
        if (!sConfigMgr->GetOption<bool>("Glicko2.Enabled", true))
            return;

        sGlicko2Storage->RemoveRating(guid);
        LOG_DEBUG("module.glicko2", "Player GUID {} deleted, BG rating removed from cache.", guid.ToString());
    }
};

void AddGlicko2PlayerScripts()
{
    LOG_INFO("module.glicko2", "[Glicko2] Registering PlayerScript...");
    new Glicko2PlayerScript();
}
