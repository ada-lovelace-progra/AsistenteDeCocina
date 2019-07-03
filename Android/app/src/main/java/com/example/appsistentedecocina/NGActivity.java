package com.example.appsistentedecocina;

import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.graphics.Color;
import android.os.Bundle;
import android.os.IBinder;
import android.support.constraint.ConstraintLayout;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.FrameLayout;
import android.widget.TextView;
import android.widget.Toast;

public class NGActivity extends AppCompatActivity {

    private ServicioBluetoothReceiver sbtReceiver;
    ServicioBluetooth sbtService;
    boolean sbtBound = false;
    private TextView textViewEstado;

    @Override
    public void setContentView(int layoutResID)
    {
        ConstraintLayout fullView = (ConstraintLayout) getLayoutInflater().inflate(R.layout.activity_bar, null);
        FrameLayout activityContainer = (FrameLayout) fullView.findViewById(R.id.activity_content);
        getLayoutInflater().inflate(layoutResID, activityContainer, true);
        super.setContentView(fullView);
        textViewEstado = fullView.findViewById(R.id.textEstado);
    }

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

        /* Registramos el receiver a los broadcasts del servicio */
        if (sbtReceiver == null) {
            sbtReceiver = new ServicioBluetoothReceiver();
        }

        IntentFilter intentFilter = new IntentFilter();

        intentFilter.addAction(String.valueOf(ServicioBluetooth.ACTION_ERROR));
        intentFilter.addAction(String.valueOf(ServicioBluetooth.ACTION_ESTADO));
        intentFilter.addAction(String.valueOf(ServicioBluetooth.ACTION_NOTIFICACION));

        registerReceiver(sbtReceiver, intentFilter);

        /* Solicitamos estado para mostrarlo */
        if(sbtService != null) {
            sbtService.enviarEstado();
        }

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

            /* Solicitamos al servicio el estado actual del arduino */
            sbtService.enviarEstado();
        }
    };

    private class ServicioBluetoothReceiver extends BroadcastReceiver {
        @Override
        public void onReceive(Context context, Intent intent) {

            switch (Integer.valueOf(intent.getAction())) {
                case ServicioBluetooth.ACTION_ERROR:
                    recibidoError(intent);
                    break;
                case ServicioBluetooth.ACTION_ESTADO:
                    cambiarEstado(intent);
                    break;
                case ServicioBluetooth.ACTION_NOTIFICACION:
                    recibidaNotificacion(intent);
                    break;
            }

            Log.d("NGActivity", "Intent del servicio Bluetooth recibido: " + intent.getAction());
        }
    }

    /* Métodos que serán llamados al recibir un boradcast de error del Servicio Bluetooth */
    protected void recibidoError (Intent i) {
        mostrarToast("ERROR: " + i.getStringExtra("Error"));
    }

    /* Métodos que serán llamados al recibir un estado del Arduino */
    protected void cambiarEstado (Intent i) {
        textViewEstado.setText(i.getStringExtra("Estado"));
        textViewEstado.setTextColor(i.getIntExtra("Color", Color.WHITE));
    }

    private void recibidaNotificacion(Intent i) {
        mostrarToast(i.getStringExtra("Notificacion"));
    }
}
