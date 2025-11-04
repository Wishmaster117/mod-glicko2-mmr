/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "Log.h"

void AddGlicko2PlayerScripts();
void AddGlicko2BGScripts();
void AddGlicko2CommandScripts();

void Addmod_glicko2_mmrScripts()
{
    LOG_INFO("server.loading", ">> Loading mod-glicko2-mmr module...");
    AddGlicko2PlayerScripts();
    AddGlicko2BGScripts();
    AddGlicko2CommandScripts();
    LOG_INFO("server.loading", ">> Module mod-glicko2-mmr loaded successfully!");
}
