-- Glicko-2 MMR Module - Character Database Tables
-- Description: Stores battleground rating data for the Glicko-2 matchmaking system

DROP TABLE IF EXISTS `character_battleground_rating`;
CREATE TABLE `character_battleground_rating` (
  `guid` INT UNSIGNED NOT NULL COMMENT 'Character GUID',
  `rating` FLOAT NOT NULL DEFAULT 1500 COMMENT 'Glicko-2 rating',
  `rating_deviation` FLOAT NOT NULL DEFAULT 350 COMMENT 'Rating deviation (RD)',
  `volatility` FLOAT NOT NULL DEFAULT 0.06 COMMENT 'Rating volatility',
  `matches_played` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Total BG matches',
  `matches_won` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Total BG wins',
  `matches_lost` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Total BG losses',
  `last_match_time` INT UNSIGNED NOT NULL DEFAULT 0 COMMENT 'Unix timestamp of last match',
  PRIMARY KEY (`guid`),
  CONSTRAINT `character_battleground_rating_chk_1` CHECK (`guid` >= 0),
  CONSTRAINT `character_battleground_rating_chk_2` CHECK (`matches_played` >= 0),
  CONSTRAINT `character_battleground_rating_chk_3` CHECK (`matches_won` >= 0),
  CONSTRAINT `character_battleground_rating_chk_4` CHECK (`matches_lost` >= 0)
)
COMMENT = 'Battleground MMR data for each character'
CHARSET = utf8mb4
COLLATE = utf8mb4_unicode_ci
ENGINE = InnoDB
ROW_FORMAT = DEFAULT;

DROP TABLE IF EXISTS `character_battleground_rating_history`;
CREATE TABLE `character_battleground_rating_history` (
  `id` BIGINT UNSIGNED NOT NULL AUTO_INCREMENT,
  `guid` INT UNSIGNED NOT NULL COMMENT 'Character GUID',
  `rating` FLOAT NOT NULL COMMENT 'Rating after match',
  `rating_deviation` FLOAT NOT NULL COMMENT 'RD after match',
  `volatility` FLOAT NOT NULL COMMENT 'Volatility after match',
  `match_time` INT UNSIGNED NOT NULL COMMENT 'Unix timestamp of match',
  `match_result` TINYINT NOT NULL COMMENT '1=win, 0=loss',
  PRIMARY KEY (`id`),
  KEY `idx_guid_time` (`guid`, `match_time`),
  CONSTRAINT `character_battleground_rating_history_chk_1` CHECK (`guid` >= 0),
  CONSTRAINT `character_battleground_rating_history_chk_2` CHECK (`match_result` IN (0, 1))
)
COMMENT = 'Tracks BG rating changes over time'
CHARSET = utf8mb4
COLLATE = utf8mb4_unicode_ci
ENGINE = InnoDB
ROW_FORMAT = DEFAULT;
