package com.wrapper.pushnotification;

import android.util.Log;

import com.google.firebase.messaging.RemoteMessage;
import com.google.firebase.messaging.cpp.ListenerService;

public class PsNListenerService extends ListenerService {
    // TODO(amablue): Add an IfChange/ThenChange block around this, and the other copy of these
    // variables in com.google.firebase.messaging.RemoteMessageBuilder.
    public static final String MESSAGE_TYPE_DELETED = "deleted_messages";
    public static final String MESSAGE_TYPE_SEND_EVENT = "send_event";
    public static final String MESSAGE_TYPE_SEND_ERROR = "send_error";

    private static final String TAG = "[DEBUG]";

    @Override
    public void onDeletedMessages() {
        Log.d(TAG, "onDeletedMessages");
        super.onDeletedMessages();
    }

    @Override
    public void onMessageReceived(RemoteMessage message) {
        Log.d(TAG, "onMessageReceived");
        super.onMessageReceived(message);
    }

    @Override
    public void onMessageSent(String messageId) {
        Log.d(TAG, String.format("onMessageSent messageId=%s", messageId));
        super.onMessageSent(messageId);
    }

    @Override
    public void onSendError(String messageId, Exception exception) {
        Log.d(TAG,
                String.format("onSendError messageId=%s exception=%s", messageId, exception.toString()));
        super.onSendError(messageId, exception);
    }

    @Override
    public void onNewToken(String token) {
        Log.d(TAG, String.format("onNewToken token=%s", token));
        super.onNewToken(token);
    }
}
