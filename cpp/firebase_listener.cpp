#include "firebase_listener.h"
#if CC_VERSION_3_X
#include "cocos.h"
#include "cocos/base/Log.h"
#include "cocos/bindings/manual/jsb_conversions.h"
#include "jsb_helper_gapp.h"
#else
#include "platform/CCPlatformConfig.h"
#include "platform/CCApplication.h"
#include "base/CCScheduler.h"
#include "cocos2d.h"
#include "scripting/js-bindings/manual/jsb_conversions.hpp"
#endif

#define MAKE_V8_HAPPY \
se::ScriptEngine::getInstance()->clearException(); \
se::AutoHandleScope hs;

std::unique_ptr<FirebaseListener> FirebaseListener::_instance = std::unique_ptr<FirebaseListener>(
        nullptr);

void FirebaseListener::OnMessage(const Message &message) {
    CC_LOG_DEBUG("from: %s", message.from.c_str());
    CC_LOG_DEBUG("to: %s", message.to.c_str());
    CC_LOG_DEBUG("collapse key: %s", message.collapse_key.c_str());
    CC_LOG_DEBUG("message id: %s", message.message_id.c_str());
    CC_LOG_DEBUG("message type: %s", message.message_type.c_str());
    CC_LOG_DEBUG("priority: %s", message.priority.c_str());
    CC_LOG_DEBUG("TTL: %d", message.time_to_live);
    CC_LOG_DEBUG("Error: %s", message.error.c_str());
    CC_LOG_DEBUG("Error desc: %s", message.error_description.c_str());
    CC_LOG_DEBUG("Notif opened: %d", message.notification_opened);
    CC_LOG_DEBUG("Link: %s", message.link.c_str());
    CC_LOG_DEBUG("Data");
    for (auto obj: message.data) {
        CC_LOG_DEBUG("Data key: %s, val: %s", obj.first.c_str(), obj.second.c_str());
    }
    // regular FCM message
    if (message.message_type.size() == 0) {
#if CC_VERSION_3_X
        CC_CURRENT_ENGINE()->getScheduler()->
#else
                cocos2d::Application::getInstance()->getScheduler()->
#endif
                performFunctionInCocosThread([this, message]() {
            if (gapp::hasFunction(this, "onMessage")) {
                passMessageToJs(message);
            } else {
                _messageQueue.push(message);
            }
        });
    }
}

void FirebaseListener::getMessages() {
    while (!_messageQueue.empty()) {
        auto message = _messageQueue.front();
        _messageQueue.pop();
#if CC_VERSION_3_X
        CC_CURRENT_ENGINE()->getScheduler()->
#else
        cocos2d::Application::getInstance()->getScheduler()->
#endif
        performFunctionInCocosThread([this, message]() {
            passMessageToJs(message);
        });
    }
}

void FirebaseListener::OnTokenReceived(const char *token) {
    CC_LOG_DEBUG(">>Firebase token<<: %s", token);
#if CC_VERSION_3_X
    CC_CURRENT_ENGINE()->getScheduler()->
#else
    cocos2d::Application::getInstance()->getScheduler()->
#endif
    performFunctionInCocosThread([this, token]() {
                passTokenToJs(token);
            });
}

void FirebaseListener::testMessage()
{
    CC_LOG_DEBUG(">>test Message<<");
}

void FirebaseListener::passMessageToJs(const Message &message) {
    MAKE_V8_HAPPY
    se::HandleObject object(se::Object::createPlainObject());
    object->setProperty("isNotification", se::Value(message.notification_opened));
    se::Value data;
    std_map_string_string_to_seval(message.data, &data);
    object->setProperty("data", data);
    gapp::callVoidObjFunc(this, "onMessage", object);
}

void FirebaseListener::passTokenToJs(const std::string &token) {
    gapp::callVoidStringJSFunc(this, "OnTokenReceived", token);
}    
