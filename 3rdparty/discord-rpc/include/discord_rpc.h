#pragma once
#include <stdint.h>

namespace discord_rpc {

struct RichPresence {
    int type = 0;
    const char* name = nullptr;   /* max 128 bytes */
    const char* state = nullptr;   /* max 128 bytes */
    const char* details = nullptr; /* max 128 bytes */
    int64_t startTimestamp = 0;
    int64_t endTimestamp = 0;
    const char* largeImageKey = nullptr;  /* max 32 bytes */
    const char* largeImageText = nullptr; /* max 128 bytes */
    const char* smallImageKey = nullptr;  /* max 32 bytes */
    const char* smallImageText = nullptr; /* max 128 bytes */
    const char* partyId = nullptr;        /* max 128 bytes */
    int partySize = 0;
    int partyMax = 0;
    int partyPrivacy = 0;
    const char* matchSecret = nullptr;    /* max 128 bytes */
    const char* joinSecret = nullptr;     /* max 128 bytes */
    const char* spectateSecret = nullptr; /* max 128 bytes */
    int8_t instance = 0;
};

struct DiscordUser {
    const char* userId;
    const char* username;
    const char* discriminator;
    const char* avatar;
};

struct DiscordEventHandlers {
    void (*ready)(const DiscordUser* request);
    void (*disconnected)(int errorCode, const char* message);
    void (*errored)(int errorCode, const char* message);
    void (*joinGame)(const char* joinSecret);
    void (*spectateGame)(const char* spectateSecret);
    void (*joinRequest)(const DiscordUser* request);
};

#define DISCORD_REPLY_NO 0
#define DISCORD_REPLY_YES 1
#define DISCORD_REPLY_IGNORE 2
#define DISCORD_PARTY_PRIVATE 0
#define DISCORD_PARTY_PUBLIC 1

void Initialize(const char* applicationId,
                                       DiscordEventHandlers* handlers,
                                       int autoRegister,
                                       const char* optionalSteamId);
void Shutdown(void);

/* checks for incoming messages, dispatches callbacks */
void RunCallbacks(void);

void UpdateRichPresence(const RichPresence* presence);
void ClearRichPresence(void);

void Respond(const char* userid, /* DISCORD_REPLY_ */ int reply);

void UpdateHandlers(DiscordEventHandlers* handlers);

}  // namespace discord_rpc

