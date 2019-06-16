package com.example.appsistentedecocina;

import android.app.Service;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Binder;
import android.os.IBinder;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.UUID;

public class ServicioBluetooth extends Service {

    /* Constantes utilizadas para comunicación Bluetooth */
    public static final String ACTION_ERROR = "ACTION_ERROR";

    private BluetoothAdapter btAdapter = null;
    private BluetoothSocket btSocket = null;
    private ConnectedThread connectedThread;
    private static final UUID BT_MODULE_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    private LocalBinder binder = new LocalBinder();

    @Override
    public void onCreate() {
        Log.d("ServicioBluetooth", "servicio creado.");
        super.onCreate();
    }

    @Override
    public IBinder onBind(Intent intent) {
        return binder;
    }

    public class LocalBinder extends Binder {
        ServicioBluetooth getService() {
            return ServicioBluetooth.this;
        }
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Log.d("ServicioBluetooth", "servicio iniciando...");
        //obtengo el adaptador del bluetooth
        btAdapter = BluetoothAdapter.getDefaultAdapter();

        Log.d("ServicioBluetooth", "servicio iniciando correctamente.");

        /*new CountDownTimer(5000, 1000) {
            public void onFinish() {
                Log.d("ServicioBluetooth", "Hola enviado.");
                sendBroadcast(new Intent("Hola"));
            }

            public void onTick(long millisUntilFinished) {
                // millisUntilFinished    The amount of time until finished.
            }
        }.start();*/

        return START_STICKY;
    }

    public void escribir(String s) {
        if(connectedThread != null) {
            connectedThread.write(s);
            Log.d("ServicioBluetooth", "Mensaje enviado a Bluetooth: " + s);
        } else {
            Intent i = new Intent(ACTION_ERROR);
            i.putExtra("Error", "No hay conexión establecida con dispositivo Bluetooth.");
            sendBroadcast(i);
        }
    }

    public void conectar (String btAddress) {
        if (btAdapter != null) {
            //se realiza la conexion del Bluetooth crea y se conectandose a a traves de un socket
            BluetoothDevice device = btAdapter.getRemoteDevice(btAddress);

            try {
                btSocket = device.createRfcommSocketToServiceRecord(BT_MODULE_UUID);
            } catch (IOException e) {
                sendBroadcast(new Intent("Error creación socket"));
                Log.d("ServicioBluetooth", "Error creación socket: " + e.getMessage());
            }

            try {
                btSocket.connect();
            } catch (IOException e) {
                try {
                    btSocket.close();
                } catch (IOException e2) {
                    sendBroadcast(new Intent("Error conexión socket"));
                    Log.d("ServicioBluetooth", "Error conexión socket: " + e.getMessage());
                }
            }

            connectedThread = new ConnectedThread(btSocket);
            connectedThread.start();

            //I send a character when resuming.beginning transmission to check device is connected
            //If it is not an exception will be thrown in the write method and finish() will be called
            connectedThread.write("]");
        }
    }

    private class ConnectedThread extends Thread {
        private final InputStream mmInStream;
        private final OutputStream mmOutStream;

        //Constructor de la clase del hilo secundario
        public ConnectedThread(BluetoothSocket socket) {
            Log.d("ServicioBluetooth", "creando hilo secundario...");
            InputStream tmpIn = null;
            OutputStream tmpOut = null;

            try {
                //Create I/O streams for connection
                tmpIn = socket.getInputStream();
                tmpOut = socket.getOutputStream();
            } catch (IOException e) {
                Log.d("ServicioBluetooth", "fallo al crear hilo sencundario..." + e.getMessage());
            }

            mmInStream = tmpIn;
            mmOutStream = tmpOut;
            Log.d("ServicioBluetooth", "hilo secundario creado.");
        }

        //metodo run del hilo, que va a entrar en una espera activa para recibir los msjs del HC05
        public void run() {
            Log.d("ServicioBluetooth", "hilo secundario en ejecución.");
            byte[] buffer = new byte[1024];
            String stringBuffer = new String();
            int bytes;

            //el hilo secundario se queda esperando mensajes del HC05
            while (true) {
                try {
                    //se leen los datos del Bluethoot
                    bytes = mmInStream.read(buffer);
                    String readMessage = new String(buffer, 0, bytes);
                    stringBuffer += readMessage;
                    int index = stringBuffer.indexOf("\n");

                    if (index > 0) {
                        //se muestran en el layout de la activity, utilizando el handler del hilo
                        // principal antes mencionado
                        //sendBroadcast(new Intent(readMessage));
                        Log.d("ServicioBluetooth", "Cadena: " + stringBuffer.substring(0, index));
                        stringBuffer = stringBuffer.substring(index);
                    } else if (index == 0) {
                        stringBuffer = stringBuffer.substring(1);
                    }
                } catch (IOException e) {
                    Log.d("ServicioBluetooth", "excepción en la ejecución del hilo secundario: " + e.getMessage());
                    break;
                }
            }
        }

        //write method
        public void write(String input) {
            byte[] msgBuffer = input.getBytes();           //converts entered String into bytes

            try {
                mmOutStream.write(msgBuffer);                //write bytes over BT connection via outstream
            } catch (IOException e) {
                Log.d("ServicioBluetooth", "excepción en escritura del hilo secundario: " + e.getMessage());
                sendBroadcast(new Intent("Error al escribir bluetooth"));
            }
        }
    }
}
