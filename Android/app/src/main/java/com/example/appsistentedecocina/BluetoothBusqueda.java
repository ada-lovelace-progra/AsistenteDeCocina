package com.example.appsistentedecocina;

import android.Manifest;
import android.app.ProgressDialog;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.os.Build;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.os.Bundle;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Switch;

import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;


public class BluetoothBusqueda extends NGActivity {

    private Switch switchBluetooth;
    private Button buttonActualizar;
    private ProgressDialog progressDialog;
    private ArrayList<BluetoothDevice> listaDispositivos = new ArrayList<BluetoothDevice>();
    private BluetoothAdapter adaptadorBluetooth;
    private ListView listaDispositivosView;
    private DeviceListAdapter deviceListAdapter;
    private int posDeviceList;

    public static final int REQ_COD = 666;

    //permisos a solicitar
    String[] permisos = new String[]{
            Manifest.permission.BLUETOOTH,
            Manifest.permission.BLUETOOTH_ADMIN,
            Manifest.permission.ACCESS_COARSE_LOCATION,
            Manifest.permission.WRITE_EXTERNAL_STORAGE,
            Manifest.permission.READ_PHONE_STATE,
            Manifest.permission.READ_EXTERNAL_STORAGE};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bluetooth_busqueda);

        switchBluetooth = findViewById(R.id.switchBluetooth);
        buttonActualizar = findViewById(R.id.buttonActualizar);

        /* Listeners */
        switchBluetooth.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                switchToggle(switchBluetooth.isChecked());
            }
        });

        buttonActualizar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (adaptadorBluetooth.isEnabled()) {
                    adaptadorBluetooth.startDiscovery();
                } else {
                    mostrarToast("Debe habilitar Bluetooth primero!");
                }
            }
        });
        /* Fin listeners */

        //defino los componentes de layout
        listaDispositivosView = (ListView) findViewById(R.id.listaDispositivosView);

        //defino un adaptador para el ListView donde se van mostrar en la activity los dispositivos encontrados
        deviceListAdapter = new DeviceListAdapter(this);

        adaptadorBluetooth = BluetoothAdapter.getDefaultAdapter();

        progressDialog = new ProgressDialog(this);

        progressDialog.setMessage("Buscando dispositivos...");
        progressDialog.setCancelable(false);

        // botón para cancelar búsqueda de dispositivos bluetooth
        progressDialog.setButton(DialogInterface.BUTTON_NEGATIVE, "Cancelar",
                btnDialogCancelarListener);

        // solicito permisos
        if (obtenerPermisos()) {
            // si llegamos hasta acá es porque logramos obtener los permisos para usar Bluetooth
            if (adaptadorBluetooth == null) {
                // el celular no soporta Bluetooth
                mostrarToast("Este dispositivo no soporta Bluetooth.");
                // deshabilitamos los botones
                buttonActualizar.setEnabled(false);
                switchBluetooth.setEnabled(false);
            } else {
                // el celular soporta Bluetooth, inicializamos para comenzar el uso
                inicializarBluetooth();
            }
        }
    }

    @Override
    public void onPause()
    {
        if (adaptadorBluetooth != null) {
            if (adaptadorBluetooth.isDiscovering()) {
                adaptadorBluetooth.cancelDiscovery();
            }
        }
        super.onPause();
    }

    private void switchToggle(boolean isChecked) {
        if (isChecked) {
            if (!adaptadorBluetooth.isEnabled()) {
                Intent intent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(intent, 1000);
            }
        } else {
            adaptadorBluetooth.disable();
        }
    }

    private  boolean obtenerPermisos() {
        List<String> listaPermisosSolicitados = new ArrayList<>();

        if (Build.VERSION.SDK_INT < Build.VERSION_CODES.M) {
            /*  Si la versión para la que estamos desarrollando es menor que la versión
                en la que se pusieron más estrictos con los permisos (M - Marshmallow),
                entonces los permisos ya se obtuvieron a través del manifest */
            return true;
        }

        for (String s : permisos) {
            if (ContextCompat.checkSelfPermission(this, s)
                    != PackageManager.PERMISSION_GRANTED) {
                /*  Si hay algún permisos que necesitamos y todavía no fue adquirido
                    se lo agrega a la lista de permisos a solicitar */
                listaPermisosSolicitados.add(s);
            }
        }
        if (!listaPermisosSolicitados.isEmpty()) {
            /*  Si la lista está vacía, entonces hay que solicitar los permisos */
            ActivityCompat.requestPermissions(this, listaPermisosSolicitados.toArray(
                    new String[listaPermisosSolicitados.size()]), REQ_COD);

            return false;
        }
        return true;
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String permissions[],
                                           int[] grantResults) {
        if (requestCode == REQ_COD) {
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                // Se obtuvieron los permisos solicitados
                inicializarBluetooth();
            } else {
                /*  No se obtuvieron los permisos solicitados, por lo tanto se le advierte
                    al usuario de que la app no funcionará "correctamente" (directamente
                    no va a funcionar) */
                mostrarToast("ADVERTENCIA: La aplicacion no funcionará "
                        + "correctamente debido a la falta de Permisos");
            }
        }
    }

    void inicializarBluetooth() {
        if (adaptadorBluetooth.isEnabled()) {
            // el celular tiene Bluetooth activado
            switchBluetooth.setChecked(true);
        } else {
            // el celular tiene Bluetooth desactivado
            switchBluetooth.setChecked(false);
        }

        IntentFilter filter = new IntentFilter();

        filter.addAction(BluetoothAdapter.ACTION_STATE_CHANGED);
        filter.addAction(BluetoothDevice.ACTION_FOUND);
        filter.addAction(BluetoothAdapter.ACTION_DISCOVERY_STARTED);
        filter.addAction(BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
        filter.addAction(BluetoothDevice.ACTION_BOND_STATE_CHANGED);

        // se registra el receiver para capturar los eventos sobre Bluetooth
        registerReceiver(receiver, filter);
    }

    // Handler que captura los brodacast que emite el SO de los eventos Bluetooth
    private final BroadcastReceiver receiver = new BroadcastReceiver() {
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            Log.d("BluetoothBusqueda", "recibí: " + action);
            switch (action){
                case BluetoothAdapter.ACTION_STATE_CHANGED:
                    /* Cambio de estado del Bluetooth (Activado/Desactivado) */
                    final int state = intent.getIntExtra(BluetoothAdapter.EXTRA_STATE,
                            BluetoothAdapter.ERROR);

                    if (state == BluetoothAdapter.STATE_ON) {
                        switchBluetooth.setChecked(true);
                    } else if (state == BluetoothAdapter.STATE_OFF) {
                        switchBluetooth.setChecked(false);
                    }
                    break;

                case BluetoothAdapter.ACTION_DISCOVERY_STARTED:
                    /* Inicio de búsqueda de dispositivos Bluetooth */
                    listaDispositivos = new ArrayList<BluetoothDevice>();

                    progressDialog.show();
                    break;

                case BluetoothAdapter.ACTION_DISCOVERY_FINISHED:
                    /* Finalización de búsqueda de dispositivos Bluetooth */
                    progressDialog.dismiss();
                    mostrarListaDispositivos();
                    break;

                case BluetoothDevice.ACTION_FOUND:
                    /* Dispositivo Bluetooth encontrado */
                    BluetoothDevice device =
                            (BluetoothDevice) intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
                    listaDispositivos.add(device);
                    String nombre = device.getName() != null ? device.getName() : "Dispositivo desconocido";
                    mostrarToast("Dispositivo Encontrado: " + nombre);
                    break;

                case BluetoothDevice.ACTION_BOND_STATE_CHANGED:
                    mostrarListaDispositivos();
                    /* Intento emparejar dispositivo */
                    final int bondState =
                            intent.getIntExtra(BluetoothDevice.EXTRA_BOND_STATE,
                                    BluetoothDevice.ERROR);
                    final int bondPrevState =
                            intent.getIntExtra(BluetoothDevice.EXTRA_PREVIOUS_BOND_STATE,
                                    BluetoothDevice.ERROR);

                    if (bondState == BluetoothDevice.BOND_BONDED &&
                            bondPrevState == BluetoothDevice.BOND_BONDING) {
                        /* Dispositivo emparejado */
                        Log.d("BluetoothBusqueda", "iniciando servicio bluetooth.");
                        BluetoothDevice dispositivo =
                                (BluetoothDevice) deviceListAdapter.getItem(posDeviceList);

                        /* conectamos con el dispositivo Bluetooth */
                        conectarDispositivoBluetooth(dispositivo.getAddress());
                    }  else if (bondState == BluetoothDevice.BOND_NONE &&
                            bondPrevState == BluetoothDevice.BOND_BONDED) {
                        /* Dispositivo desemparejado */
                        mostrarToast("Desemparejado");
                    }

                    deviceListAdapter.notifyDataSetChanged();
                    break;
            }
        }
    };

    private void mostrarListaDispositivos() {
        deviceListAdapter = new DeviceListAdapter(this);
        deviceListAdapter.setData(listaDispositivos);
        deviceListAdapter.setListener(listenerBotonEmparejar);
        listaDispositivosView.setAdapter(deviceListAdapter);
    }

    private DialogInterface.OnClickListener btnDialogCancelarListener =
            new DialogInterface.OnClickListener() {
        @Override
        public void onClick(DialogInterface dialog, int which) {
            dialog.dismiss();
            adaptadorBluetooth.cancelDiscovery();
        }
    };

    private void pairDevice(BluetoothDevice device) {
        try {
            Method method = device.getClass().getMethod("createBond", (Class[]) null);
            method.invoke(device, (Object[]) null);
        } catch (Exception e) {
            mostrarToast("Error al emparejar.");
            Log.d("BluetoothBusqueda", "Error al desemparejar: " + e.getMessage());
        }

        mostrarToast("" + device.getName() + " emparejado.");
    }

    private void unpairDevice(BluetoothDevice device) {
        try {
            Method method = device.getClass().getMethod("removeBond", (Class[]) null);
            method.invoke(device, (Object[]) null);
        } catch (Exception e) {
            mostrarToast("Error al desemparejar.");
            Log.d("BluetoothBusqueda", "Error al emparejar: " + e.getMessage());
        }

        mostrarToast("" + device.getName() + " desemparejado.");
    }

    /* Botón Emparejar / Desemparejar */
    private DeviceListAdapter.OnPairButtonClickListener listenerBotonEmparejar =
            new DeviceListAdapter.OnPairButtonClickListener() {
        @Override
        public void onPairButtonClick(int position) {
            //Obtengo los datos del dispostivo seleccionado del listview por el usuario
            BluetoothDevice device = listaDispositivos.get(position);

            //Se checkea si el dipositivo ya está emparejado
            if (device.getBondState() == BluetoothDevice.BOND_BONDED) {
                // Se desempareja el dispositivo
                mostrarToast("Desemparejando");
                unpairDevice(device);
            } else {
                // Se empareja el dispositivo
                mostrarToast("Emparejando");
                posDeviceList = position;
                pairDevice(device);
            }
        }
    };
}
