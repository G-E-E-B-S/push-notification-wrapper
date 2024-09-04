set(PROJ_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/cpp/firebase_messaging.cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp/firebase_listener.cpp
    ${CMAKE_CURRENT_LIST_DIR}/bindings/auto/jsb_push_notification_auto.cpp
)

add_library(push_notification STATIC ${PROJ_SOURCES})

target_include_directories(push_notification PUBLIC
    ${COCOS_X_PATH}
    ${COCOS_X_PATH}/cocos
    ${COCOS_X_PATH}/cocos/renderer
    ${platform_spec_path}/include/v8
    ${JSB_HELPER}
    ${FIREBASE_CPP_DIR}/include
    ${NATIVE_FIREBASE_DIR}/cpp
    ${CMAKE_CURRENT_LIST_DIR}/cpp
    ${CMAKE_CURRENT_LIST_DIR}/bindings/auto
)
target_link_libraries(push_notification ${FIREBASE_CPP_DIR}/libs/android/${ANDROID_ABI}/libfirebase_messaging.a)