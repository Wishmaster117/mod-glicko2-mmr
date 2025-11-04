#!/usr/bin/env bash

## ADD MODULE INCLUDE DIRECTORIES
ModGlicko2MMR_SOURCES_DIR=$(<AC_PATH_MODULE>/"mod-glicko2-mmr")

AC_ADD_SCRIPT_INCLUDE("${ModGlicko2MMR_SOURCES_DIR}/include")
