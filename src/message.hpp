#ifndef _H_MESSAGE_
#define _H_MESSAGE_

class LB_Message
{
    public:
    enum MessageType
    {
        SERVER, BUGLE, REWARD, PENALTY, USER, POWER_USER, ADMIN_USER
    };

    static const Uint32 TIME_TO_LIVE = 5000; //Maximum time to display in milliseconds

    SDL_Surface *inGameText; //Colored text
    SDL_Surface *inChannelText; //White text

    LB_Message(MessageType type, std::string message, std::string author = "", std::string guild = "");
    ~LB_Message();

    void hideMessage();
    void updateMessageStatus();
    void exitGame();
    bool isDisplayed() const;
    void writeToChannel(SDL_Surface *channel, int x, int y, bool inGame = false);
    MessageType getMessageType() const;

    private:
    Uint32 creationTime;
    MessageType type;
    bool isDisplayedInChannel;

    std::string guild;
    std::string author;
    std::string message;
};

#endif
