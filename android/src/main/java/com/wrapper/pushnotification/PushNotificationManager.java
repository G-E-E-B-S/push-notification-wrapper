package com.wrapper.pushnotification;

import android.content.Context;
import android.content.Intent;
import android.util.Log;

import com.google.firebase.messaging.MessageForwardingService;

public class PushNotificationManager {
    private static final String TAG = "PushNotificationManager";

    private static Context m_Context;

    public static void Init(Context context) {
        m_Context = context;
        CustomFCMService.Init(context);
    }

    public static void onNewIntent(Intent intent) {
        Log.d(TAG, "A message was sent to this app while it was in the background.");

        Intent message = new Intent(m_Context, MessageForwardingService.class);
        message.setAction(MessageForwardingService.ACTION_REMOTE_INTENT);
        message.putExtras(intent);
        message.setData(intent.getData());
        // For older versions of Firebase C++ SDK (< 7.1.0), use `startService`.
        // startService(message);
        MessageForwardingService.enqueueWork(m_Context, message);
    }
}
