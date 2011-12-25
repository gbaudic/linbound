#ifndef _H_ROOM_
#define _H_ROOM_

#include <SDL/SDL.h>
#include "player.hpp"
#include "map.hpp"

/**
 * \class LB_Room
 * Abstracts a room object with its properties
 */
class LB_Room
{
	public:
	enum RoomMode {SOLO, SCORE, TAG, JEWEL};
	enum RoomStatus {WAITING, FULL, PLAYING};
	enum SuddenDeathType {BIGBOMB, DOUBLE, SS};

    RoomMode getMode() const;
    RoomStatus getStatus() const;
    bool testPassword(std::string attempt);
    LB_Room(std::string name, Uint16 roomNumber, Uint8 maxPlayers, RoomMode mode, std::string password = "");
    void changeRoomStatus(RoomStatus newStatus);
    void changeRoomMode(RoomMode newMode);

    private:
    Uint16 iRoomNumber;
    bool bRoomIsPowerUser;
    bool bIsPasswordProtected;
    std::string password;
    std::string name;
    RoomMode mode;
    RoomStatus status;

    Uint8 iSuddenDeathTurns;
    SuddenDeathType sdType;

    LB_Map map;

    Uint8 iMaxPlayers;
    Uint8 iCurrentPlayers;

    LB_Player players[];
};

#endif
