package com.omochimetaru.ironcaketest;

import android.app.Activity;
import android.app.ActionBar;
import android.app.Fragment;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.os.Build;
import android.widget.TextView;

public class MainActivity extends Activity {

    private boolean testStarted = false;
    private Thread testThread;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    @Override
    protected void onResume(){
        super.onResume();
        TextView textView = (TextView) findViewById(R.id.textview);
        textView.setText("test");

        if(!testStarted){
            testStarted = true;
            testThread = new Thread(){
                @Override
                public void run(){

                    doTest();

                    new Handler(Looper.getMainLooper()).post(new Runnable() {
                        @Override
                        public void run() {
                            try {
                                testThread.join();
                            } catch (InterruptedException e) {
                                throw new RuntimeException(e);
                            }
                            testThread = null;
                        }
                    });
                }
            };
            testThread.start();
        }
    }

    private native void doTest();

}
