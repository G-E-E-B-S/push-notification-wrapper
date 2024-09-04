
// clang-format off
#include "jsb_push_notification_auto.h"
#include "cocos/bindings/manual/jsb_conversions.h"
#include "cocos/bindings/manual/jsb_global.h"
#include "firebase_messaging.h"

#ifndef JSB_ALLOC
#define JSB_ALLOC(kls, ...) new (std::nothrow) kls(__VA_ARGS__)
#endif

#ifndef JSB_FREE
#define JSB_FREE(ptr) delete ptr
#endif

#if CC_DEBUG
static bool js_fcm_getter_return_true(se::State& s) // NOLINT(readability-identifier-naming)
{
    s.rval().setBoolean(true);
    return true;
}
SE_BIND_PROP_GET(js_fcm_getter_return_true)
#endif
se::Object* __jsb_FirebaseMessaging_proto = nullptr; // NOLINT
se::Class* __jsb_FirebaseMessaging_class = nullptr;  // NOLINT

static bool js_fcm_FirebaseMessaging_init_static(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::string, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr);
        SE_PRECONDITION2(ok, false, "Error processing arguments");
        FirebaseMessaging::init(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_fcm_FirebaseMessaging_init_static)

static bool js_fcm_FirebaseMessaging_requestPermission_static(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    size_t argc = args.size();
    if (argc == 0) {
        FirebaseMessaging::requestPermission();
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 0);
    return false;
}
SE_BIND_FUNC(js_fcm_FirebaseMessaging_requestPermission_static)

static bool js_fcm_FirebaseMessaging_subscribe_static(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::string, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr);
        SE_PRECONDITION2(ok, false, "Error processing arguments");
        FirebaseMessaging::subscribe(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_fcm_FirebaseMessaging_subscribe_static)

static bool js_fcm_FirebaseMessaging_unSubscribe_static(se::State& s) // NOLINT(readability-identifier-naming)
{
    const auto& args = s.args();
    size_t argc = args.size();
    CC_UNUSED bool ok = true;
    if (argc == 1) {
        HolderType<std::string, true> arg0 = {};
        ok &= sevalue_to_native(args[0], &arg0, nullptr);
        SE_PRECONDITION2(ok, false, "Error processing arguments");
        FirebaseMessaging::unSubscribe(arg0.value());
        return true;
    }
    SE_REPORT_ERROR("wrong number of arguments: %d, was expecting %d", (int)argc, 1);
    return false;
}
SE_BIND_FUNC(js_fcm_FirebaseMessaging_unSubscribe_static)

bool js_register_fcm_FirebaseMessaging(se::Object* obj) // NOLINT(readability-identifier-naming)
{
    auto* cls = se::Class::create("FirebaseMessaging", obj, nullptr, nullptr);

#if CC_DEBUG
    cls->defineStaticProperty("isJSBClass", _SE(js_fcm_getter_return_true), nullptr);
#endif
    cls->defineStaticFunction("init", _SE(js_fcm_FirebaseMessaging_init_static));
    cls->defineStaticFunction("requestPermission", _SE(js_fcm_FirebaseMessaging_requestPermission_static));
    cls->defineStaticFunction("subscribe", _SE(js_fcm_FirebaseMessaging_subscribe_static));
    cls->defineStaticFunction("unSubscribe", _SE(js_fcm_FirebaseMessaging_unSubscribe_static));
    cls->install();
    JSBClassType::registerClass<FirebaseMessaging>(cls);

    __jsb_FirebaseMessaging_proto = cls->getProto();
    __jsb_FirebaseMessaging_class = cls;


    se::ScriptEngine::getInstance()->clearException();
    return true;
}
bool register_all_fcm(se::Object* obj)    // NOLINT
{
    // Get the ns
    se::Value nsVal;
    if (!obj->getProperty("fcm", &nsVal, true))
    {
        se::HandleObject jsobj(se::Object::createPlainObject());
        nsVal.setObject(jsobj);
        obj->setProperty("fcm", nsVal);
    }
    se::Object* ns = nsVal.toObject();

    js_register_fcm_FirebaseMessaging(ns);
    return true;
}

// clang-format on