package com.omochimetaru.ironcaketest;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import android.widget.TextView;

import com.omochimetaru.ironcake.IronCake;

public class MainActivity extends Activity {

    static {
        System.loadLibrary("IronCake");
        System.loadLibrary("IronCakeTest");
    }

    private TextView textView;

    private boolean testStarted = false;
    private Thread testThread;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        textView = (TextView) findViewById(R.id.textview);
    }

    @Override
    protected void onResume(){
        super.onResume();

        if(!testStarted){
            testStarted = true;
            testThread = new Thread(){
                @Override
                public void run(){

                    doTest();

                    final String report = String.format(
                            "test case count: %d\n" +
                            "    succeeded  : %d\n" +
                            "    failed     : %d\n" +
                            "test count     : %d\n" +
                            "    succeeded  : %d\n" +
                            "    failed     : %d",
                            getTotalTestCaseCount(),
                            getSuccessfulTestCaseCount(),
                            getFailedTestCaseCount(),
                            getTotalTestCount(),
                            getSuccessfulTestCount(),
                            getFailedTestCount()
                    );

                    new Handler(Looper.getMainLooper()).post(new Runnable() {
                        @Override
                        public void run() {
                            textView.setText(report);

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

    private native int getTotalTestCaseCount();
    private native int getSuccessfulTestCaseCount();
    private native int getFailedTestCaseCount();
    private native int getTotalTestCount();
    private native int getSuccessfulTestCount();
    private native int getFailedTestCount();

}
