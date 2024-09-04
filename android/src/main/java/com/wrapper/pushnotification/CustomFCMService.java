package com.wrapper.pushnotification;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.media.RingtoneManager;
import android.net.Uri;
import android.os.Build;
import android.util.Log;

import androidx.core.app.NotificationCompat;
import com.google.firebase.messaging.FirebaseMessagingService;
import com.google.firebase.messaging.RemoteMessage;

import java.net.URL;

public class CustomFCMService extends FirebaseMessagingService {

    private static final String TAG = "[DEBUG]";

    private static Context m_Context;

    public static void Init(Context context) {
        m_Context = context;
    }

    /**
     * Called when message is received.
     *
     * @param remoteMessage Object representing the message received from Firebase Cloud Messaging.
     */
    // [START receive_message]
    @Override
    public void onMessageReceived(RemoteMessage remoteMessage) {
        Log.d(TAG, "Remote message received");
        super.onMessageReceived(remoteMessage);

        // Check if message contains a notification payload.
        if (remoteMessage.getNotification() != null) {
            Log.d(TAG, "Message Notification Body: " + remoteMessage.getNotification().getBody());
            if (remoteMessage.getNotification().getBody() != null) {
                if (remoteMessage.getNotification().getImageUrl() != null) {
                    Thread thread = new Thread(new Runnable() {
                        @Override
                        public void run() {
                            try {
                                URL url = new URL(remoteMessage.getNotification().getImageUrl().toString());
                                Bitmap image = BitmapFactory.decodeStream(url.openConnection().getInputStream());
                                sendNotification(remoteMessage.getNotification(), image);
                            } catch (Exception e) {
                                Log.e("Notification Exception", e.toString());
                            }
                        }
                    });
                    thread.start();
                } else {
                    sendNotification(remoteMessage.getNotification(), null);
                }
            }
        }
    }
    // [END receive_message]

    // [START on_new_token]
    /**
     * There are two scenarios when onNewToken is called:
     * 1) When a new token is generated on initial app startup
     * 2) Whenever an existing token is changed
     * Under #2, there are three scenarios when the existing token is changed:
     * A) App is restored to a new device
     * B) User uninstalls/reinstalls the app
     * C) User clears app data
     */
    @Override
    public void onNewToken(String token) {
        Log.d(TAG, "Refreshed token: " + token);

        // If you want to send messages to this application instance or
        // manage this apps subscriptions on the server side, send the
        // FCM registration token to your app server.
        sendRegistrationToServer(token);
    }
    // [END on_new_token]

    /**
     * Persist token to third-party servers.
     * <p>
     * Modify this method to associate the user's FCM registration token with any
     * server-side account maintained by your application.
     *
     * @param token The new token.
     */
    private void sendRegistrationToServer(String token) {
        // TODO: Implement this method to send token to app server.
    }
    /**
     * Create and show a simple notification containing the received FCM message.
     *
     * @param notification FCM message received.
     * @param image FCM image received.
     */
    private void sendNotification(RemoteMessage.Notification notification, Bitmap image) {
        Intent intent = new Intent(this, m_Context.getClass());
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        PendingIntent pendingIntent = PendingIntent.getActivity(this, 0 /* Request code */, intent,
                PendingIntent.FLAG_IMMUTABLE);

        String channelId = getString(R.string.default_notification_channel_id);
        Uri defaultSoundUri = RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION);
        NotificationCompat.Builder notificationBuilder =
                new NotificationCompat.Builder(this, channelId)
                        .setSmallIcon(R.drawable.notif_anim)
                        .setAutoCancel(true)
                        .setSound(defaultSoundUri)
                        .setContentIntent(pendingIntent);

        if (notification.getTitle() != null) {
            notificationBuilder.setContentTitle(notification.getTitle());
        }

        if (notification.getBody() != null) {
            notificationBuilder.setContentText(notification.getBody());
        }

        if (image != null) {
            try {
                notificationBuilder.setLargeIcon(image)
                        .setStyle(new NotificationCompat.BigPictureStyle()
                                .bigPicture(image)
                                .bigLargeIcon(null));
            } catch (Exception e) {
                Log.e("Notification exception", e.toString());
            }
        }

        NotificationManager notificationManager =
                (NotificationManager) getSystemService(Context.NOTIFICATION_SERVICE);

        // Since android Oreo notification channel is needed.
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            NotificationChannel channel = new NotificationChannel(channelId,
                    "Channel human readable title",
                    NotificationManager.IMPORTANCE_HIGH);
            notificationManager.createNotificationChannel(channel);
        }

        notificationManager.notify(0, notificationBuilder.build());
    }
}
