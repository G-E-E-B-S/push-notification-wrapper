// clang-format off
#pragma once

#include <type_traits>
#include "cocos/bindings/jswrapper/SeApi.h"
#include "cocos/bindings/manual/jsb_conversions.h"
#include "../../cpp/firebase_messaging.h"

bool register_all_fcm(se::Object *obj);                   // NOLINT

JSB_REGISTER_OBJECT_TYPE(FirebaseMessaging);


extern se::Object *__jsb_FirebaseMessaging_proto;   // NOLINT
extern se::Class *__jsb_FirebaseMessaging_class;    // NOLINT

bool js_register_FirebaseMessaging(se::Object *obj); // NOLINT

SE_DECLARE_FUNC(js_fcm_FirebaseMessaging_init);
SE_DECLARE_FUNC(js_fcm_FirebaseMessaging_requestPermission);
SE_DECLARE_FUNC(js_fcm_FirebaseMessaging_subscribe);
SE_DECLARE_FUNC(js_fcm_FirebaseMessaging_unSubscribe);
// clang-format on
