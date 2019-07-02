package com.example.appsistentedecocina;

import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.Toast;

public class NGActivity extends AppCompatActivity {

    private ServicioBluetoothReceiver sbtReceiver;
    ServicioBluetooth sbtService;
    boolean sbtBound = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        Log.d("NGActivity", "onCreate(): " + this.getClass().getSimpleName());
        super.onCreate(savedInstanceState);

        if (!ServicioBluetooth.IS_STARTED) {
            iniciarServicioBluetooth();
        }
        Log.d("NGActivity", "Vinculando con servicio... : " + this.getClass().getSimpleName());
        vincularServicioBluetooth();
    }

    @Override
    protected void onStart() {
        Log.d("NGActivity", "onStart(): " + this.getClass().getSimpleName());

        super.onStart();
    }

    @Override
    protected void onRestart() {
        Log.d("NGActivity", "onRestart(): " + this.getClass().getSimpleName());

        super.onRestart();
    }

    @Override
    protected void onPause() {
        Log.d("NGActivity", "onPause(): " + this.getClass().getSimpleName());

        if (sbtReceiver != null) {
            unregisterReceiver(sbtReceiver);
        }

        super.onPause();
    }

    @Override
    protected void onDestroy() {
        Log.d("NGActivity", "onDestroy(): " + this.getClass().getSimpleName());

        unbindService(sbtServiceConnection);
        super.onDestroy();
    }

    @Override
    protected void onStop() {
        Log.d("NGActivity", "onStop(): " + this.getClass().getSimpleName());

        super.onStop();
    }

    @Override
    protected void onResume() {
        Log.d("NGActivity", "onResume(): " + this.getClass().getSimpleName());

        if (sbtReceiver == null) {
            sbtReceiver = new ServicioBluetoothReceiver();
        }

        IntentFilter intentFilter = new IntentFilter();

        intentFilter.addAction(ServicioBluetooth.ACTION_ERROR);

        registerReceiver(sbtReceiver, intentFilter);

        super.onResume();
    }

    protected void mostrarToast (String mensaje) {
        Toast.makeText(getApplicationContext(), mensaje, Toast.LENGTH_LONG).show();
    }

    protected void iniciarServicioBluetooth () {
        Intent i = new Intent(NGActivity.this, ServicioBluetooth.class);
        startService(i);
    }

    protected void vincularServicioBluetooth () {
        Intent i = new Intent(NGActivity.this, ServicioBluetooth.class);
        bindService(i, sbtServiceConnection, Context.BIND_AUTO_CREATE);
    }

    protected void escribirBluetooth (String s) {
        if (sbtService != null) {
            Log.d("NGActivity", "Enviando mensaje a Bluetooth: " + s);
            sbtService.escribir(s);
        } else {
            Log.d("NGActivity", "Se intentó enviar un mensaje Bluetooth cuando" +
                    " el serviocio aún no estaba vinculado." + s);
        }

    }

    protected void escribirBluetoothNum(Integer num) {
        if (sbtService != null) {
            Log.d("NGActivity", "Enviando mensaje a Bluetooth: " + num);
            sbtService.escribirNum(num);
        } else {
            Log.d("NGActivity", "Se intentó enviar un mensaje Bluetooth cuando" +
                    " el serviocio aún no estaba vinculado." + num);
        }
    }

    protected void escribirBluetoothByte (byte b) {
        if (sbtService != null) {
            Log.d("NGActivity", "Enviando mensaje a Bluetooth: " + b);
            sbtService.escribirByte(b);
        } else {
            Log.d("NGActivity", "Se intentó enviar un mensaje Bluetooth cuando" +
                    " el serviocio aún no estaba vinculado." + b);
        }
    }

    protected void conectarDispositivoBluetooth (String address) {
        sbtService.conectar(address);
    }

    private ServiceConnection sbtServiceConnection = new ServiceConnection() {
        @Override
        public void onServiceDisconnected(ComponentName name) {
            sbtBound = false;
        }

        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            ServicioBluetooth.LocalBinder myBinder = (ServicioBluetooth.LocalBinder) service;
            Log.d("NGActivity", "Vinculado con servicio: " + this.getClass().getSimpleName());
            sbtService = myBinder.getService();
            sbtBound = true;
        }
    };

    private class ServicioBluetoothReceiver extends BroadcastReceiver {
        @Override
        public void onReceive(Context context, Intent intent) {

            switch (intent.getAction()) {
                case ServicioBluetooth.ACTION_ERROR:
                    recibidoError(intent);
                    break;
            }

            Log.d("NGActivity", "Intent del servicio Bluetooth recibido: " + intent.getAction());
        }
    }

    /* Métodos que serán llamados al recibir broadcasts del Servicio Bluetooth */
    protected void recibidoError (Intent i) {
        mostrarToast("ERROR: " + i.getStringExtra("Error"));
    }
}
