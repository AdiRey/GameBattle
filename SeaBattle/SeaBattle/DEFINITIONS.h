#pragma once

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600

enum AppStates {START, CHOICE , FRIEND_INIT, AI_INIT, ONLINE_INIT, GAME_FRIEND, WINNER_WND, NEW_START, VOLUME, SETTINGS, CLOSE};
extern AppStates appStates;

//extern sf::Music music;