/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#ifndef GLICKO2_PLAYER_STORAGE_H
#define GLICKO2_PLAYER_STORAGE_H

#include "ObjectGuid.h"
#include "DatabaseEnvFwd.h"
#include <unordered_map>
#include <shared_mutex>

class Player;

/// @brief Glicko-2 rating data for a player
struct BattlegroundRatingData
{
    float rating = 1500.0f;             ///< Player skill rating
    float ratingDeviation = 350.0f;     ///< Rating uncertainty (RD)
    float volatility = 0.06f;           ///< Performance consistency
    uint32 matchesPlayed = 0;           ///< Total matches played
    uint32 wins = 0;                    ///< Total wins
    uint32 losses = 0;                  ///< Total losses
    bool loaded = false;                ///< Whether data is loaded from DB

    BattlegroundRatingData() = default;

    BattlegroundRatingData(float r, float rd, float v, uint32 mp, uint32 w, uint32 l)
        : rating(r), ratingDeviation(rd), volatility(v),
          matchesPlayed(mp), wins(w), losses(l), loaded(true) { }
};

/// @brief Thread-safe external storage for player battleground ratings
class Glicko2PlayerStorage
{
public:
    static Glicko2PlayerStorage* instance();

    BattlegroundRatingData GetRating(ObjectGuid playerGuid);
    void SetRating(ObjectGuid playerGuid, BattlegroundRatingData const& data);
    bool HasRating(ObjectGuid playerGuid);
    void RemoveRating(ObjectGuid playerGuid);

    void LoadRating(ObjectGuid playerGuid);
    void SaveRating(ObjectGuid playerGuid);
    void SaveRating(ObjectGuid playerGuid, BattlegroundRatingData const& data);

    void SaveAll();
    void ClearCache();
    size_t GetCacheSize() const;

private:
    Glicko2PlayerStorage() = default;
    ~Glicko2PlayerStorage() = default;

    Glicko2PlayerStorage(Glicko2PlayerStorage const&) = delete;
    Glicko2PlayerStorage& operator=(Glicko2PlayerStorage const&) = delete;

    std::unordered_map<ObjectGuid, BattlegroundRatingData> _ratings;
    mutable std::shared_mutex _mutex;
};

#define sGlicko2Storage Glicko2PlayerStorage::instance()

#endif // GLICKO2_PLAYER_STORAGE_H
