#ifndef __FIREBASE_LISTENER__
#define __FIREBASE_LISTENER__

#include "firebase/messaging.h"
#include <string>
#include <memory>
#include <queue>

using firebase::messaging::Message;
class FirebaseListener : public firebase::messaging::Listener {

public:
    firebase::App* m_app;
    std::string m_useId;
    FirebaseListener(firebase::App *app) {
        m_app = app;
    }

    static void init(firebase::App *app) {
        if (_instance.get() == nullptr) {
            _instance.reset(new FirebaseListener(app));
        }
    }

    static FirebaseListener *getInstance() {
         return _instance.get();
     }

     void setUserId(const std::string& userId) {
        m_useId = userId;
    }

    /// Called on the client when a message arrives.
    ///
    /// @param[in] message The data describing this message.
    virtual void OnMessage(const Message &message) override;

    /// Called on the client when a registration token arrives. This function
    /// will eventually be called in response to a call to
    /// firebase::messaging::Initialize(...).
    ///
    /// @param[in] token The registration token.
    virtual void OnTokenReceived(const char *token) override;

    void getMessages();

    void testMessage();

private:
    void passMessageToJs(const Message &message);
    void passTokenToJs(const std::string &token);

    static std::unique_ptr<FirebaseListener> _instance;
    std::queue<Message> _messageQueue;
};
#endif //__FIREBASE_LISTENER__
