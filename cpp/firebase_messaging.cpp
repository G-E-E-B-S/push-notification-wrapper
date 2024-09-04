#include "firebase_messaging.h"
#include "firebase_listener.h"
#include "firebase_app.h"
#include "cocos/base/Log.h"
#include "platform/java/jni/JniHelper.h"

    void FirebaseMessaging::init(const std::string &userId) {
        CC_LOG_DEBUG("<<Init Firebase Messaging>> %s", userId.c_str());
        auto app = wrapper::FirebaseApp::getApp();
        FirebaseListener::init(app);
        firebase::messaging::Initialize(*app, nullptr);
    }

    void FirebaseMessaging::subscribe(const std::string &topic) {
        firebase::messaging::Subscribe(topic.c_str());
    }

    void FirebaseMessaging::unSubscribe(const std::string &topic) {
        firebase::messaging::Unsubscribe(topic.c_str());
    }

    void FirebaseMessaging::requestPermission() {
#if (CC_PLATFORM == CC_PLATFORM_IOS)
        firebase::messaging::RequestPermission();
#endif
    }
