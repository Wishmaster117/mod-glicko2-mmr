# Glicko-2 MMR Module - SQL Installation

## Overview

This module requires two database tables in the `acore_characters` database.

## Installation

### Manual Installation

Run the following SQL file against your `acore_characters` database:

```bash
mysql -u acore -pacore acore_characters < db-characters/base/character_battleground_rating.sql
```

Or import via MySQL client:

```sql
USE acore_characters;
SOURCE /path/to/modules/mod-glicko2-mmr/data/sql/db-characters/base/character_battleground_rating.sql;
```

### Tables Created

1. **`character_battleground_rating`** - Stores current rating for each player
   - `guid` - Character GUID (primary key)
   - `rating` - Current Glicko-2 rating (default: 1500)
   - `rating_deviation` - Rating uncertainty (default: 350)
   - `volatility` - Rating volatility (default: 0.06)
   - `matches_played` - Total battleground matches
   - `matches_won` - Total wins
   - `matches_lost` - Total losses
   - `last_match_time` - Unix timestamp of last match

2. **`character_battleground_rating_history`** - Tracks rating changes over time
   - `id` - Auto-increment primary key
   - `guid` - Character GUID
   - `rating` - Rating after match
   - `rating_deviation` - RD after match
   - `volatility` - Volatility after match
   - `match_time` - Unix timestamp of match
   - `match_result` - 1=win, 0=loss

## Verification

After installation, verify the tables exist:

```sql
USE acore_characters;
SHOW TABLES LIKE 'character_battleground_rating%';
```

Expected output:
```
+--------------------------------------------------+
| Tables_in_acore_characters                       |
+--------------------------------------------------+
| character_battleground_rating                    |
| character_battleground_rating_history            |
+--------------------------------------------------+
```

## Uninstallation

To remove the module's database tables:

```sql
USE acore_characters;
DROP TABLE IF EXISTS `character_battleground_rating_history`;
DROP TABLE IF EXISTS `character_battleground_rating`;
```

**Warning**: This will permanently delete all rating data!

## Maintenance

### Clear All Rating Data

To reset all player ratings (but keep tables):

```sql
USE acore_characters;
TRUNCATE TABLE `character_battleground_rating_history`;
TRUNCATE TABLE `character_battleground_rating`;
```

### View Top Players

```sql
USE acore_characters;
SELECT
    guid,
    rating,
    matches_played,
    matches_won,
    matches_lost,
    ROUND((matches_won / matches_played * 100), 1) AS win_rate_pct
FROM character_battleground_rating
WHERE matches_played > 0
ORDER BY rating DESC
LIMIT 10;
```

### Rating Distribution

```sql
USE acore_characters;
SELECT
    FLOOR(rating / 100) * 100 AS rating_bracket,
    COUNT(*) AS player_count
FROM character_battleground_rating
WHERE matches_played > 0
GROUP BY rating_bracket
ORDER BY rating_bracket;
```
