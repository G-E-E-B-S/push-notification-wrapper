#pragma once

#include <string>


    class FirebaseMessaging {
    public:
        static void init(const std::string &userId);
        static void subscribe(const std::string &topic);
        static void unSubscribe(const std::string &topic);
        //ios only
        static void requestPermission();
    };