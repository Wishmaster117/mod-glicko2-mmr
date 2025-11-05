/*
 * This file is part of the AzerothCore Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptMgr.h"
#include "ArenaScript.h"
#include "ArenaTeam.h"
#include "Player.h"
#include "Config.h"
#include "Log.h"

class Glicko2ArenaHookScript : public ArenaScript
{
public:
    Glicko2ArenaHookScript() : ArenaScript("Glicko2ArenaHookScript") { }

    bool OnBeforeArenaTeamMemberUpdate(ArenaTeam* /*team*/, Player* player, bool won,
                                       uint32 /*opponentMatchmakerRating*/, int32 /*matchmakerChange*/) override
    {
        if (!sConfigMgr->GetOption<bool>("Glicko2.Arena.Enabled", false))
            return false;

        LOG_DEBUG("module.glicko2", "[Glicko2] Skipping core arena rating update for player {} (won: {})",
                  player->GetName(), won);

        return true;
    }

    bool CanSaveArenaStatsForMember(ArenaTeam* /*team*/, ObjectGuid playerGuid) override
    {
        if (!sConfigMgr->GetOption<bool>("Glicko2.Arena.Enabled", false))
            return true;

        LOG_DEBUG("module.glicko2", "[Glicko2] Preventing core from saving arena stats for GUID {}",
                  playerGuid.ToString());

        return false;
    }
};

void AddGlicko2ArenaHookScripts()
{
    LOG_INFO("module.glicko2", "[Glicko2] Registering ArenaHookScript...");
    new Glicko2ArenaHookScript();
}
