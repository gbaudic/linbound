#ifndef _H_MESSAGE_
#define _H_MESSAGE_

class LB_Message
{
    public:
    enum MessageType
    {
        SERVER, BUGLE, USER, POWER_USER, ADMIN_USER, REWARD, PENALTY
    };

    static const Uint32 TIME_TO_LIVE = 5000; //Maximum time to display in milliseconds

    SDL_Surface *inGameText;
    SDL_Surface *inChannelText;

    LB_Message(MessageType type, std::string message, std::string author = "", std::string guild = "");
    //~LB_Message();

    void hideMessage();
    void updateMessageStatus();
    void exitGame();
    bool isDisplayed() const;


    private:
    Uint32 creationTime;
    MessageType type;
    bool isDisplayedInChannel;

    std::string guild;
    std::string author;
    std::string message;

};

#endif
