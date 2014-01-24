package com.omochimetaru.ironcakesample;

import android.app.Activity;
import android.app.ActionBar;
import android.app.Fragment;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.os.Build;

import com.omochimetaru.ironcake.IronCake;

public class MainActivity extends com.omochimetaru.ironcake.Activity {

    static {
        System.loadLibrary("IronCakeSample");
    }

    @Override
    protected native long controllerConstruct();

}
