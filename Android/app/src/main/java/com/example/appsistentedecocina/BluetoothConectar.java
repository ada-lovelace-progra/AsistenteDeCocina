package com.example.appsistentedecocina;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;

public class BluetoothConectar extends NGActivity {

    private ListView listaDispositivosView;
    private Button buttonActualizar;
    private BluetoothAdapter adaptadorBluetooth;
    private ArrayAdapter<String> adapter;
    List<String> listaDirecciones;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bluetooth_conectar);

        buttonActualizar = findViewById(R.id.buttonActualizar);
        listaDispositivosView = findViewById(R.id.listaDispositivosView);
        adapter = new ArrayAdapter<String>(this,
                android.R.layout.simple_expandable_list_item_1);

        buttonActualizar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (adaptadorBluetooth.isEnabled()) {

                    listaDirecciones = new ArrayList<String>();
                    for(BluetoothDevice bt : adaptadorBluetooth.getBondedDevices()) {
                        String s = bt.getName();
                        listaDirecciones.add(bt.getAddress());
                        adapter.add(s != null ? s : bt.getAddress());
                    }
                    listaDispositivosView.setAdapter(adapter);

                } else {
                    mostrarToast("Debe habilitar Bluetooth primero!");
                }
            }
        });

        listaDispositivosView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                conectarDispositivoBluetooth(listaDirecciones.get(i));
            }
        });

        adaptadorBluetooth = BluetoothAdapter.getDefaultAdapter();
    }
}
