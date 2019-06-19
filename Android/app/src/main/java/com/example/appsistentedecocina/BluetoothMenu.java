package com.example.appsistentedecocina;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class BluetoothMenu extends NGActivity {

    private Button buttonBuscar;
    private Button buttonConectar;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_bluetooth_menu);

        buttonBuscar = findViewById(R.id.buttonBuscar);
        buttonBuscar.setOnClickListener( new View.OnClickListener() {
            @Override
            public void onClick( View view){
                Intent intent;
                intent = new Intent(BluetoothMenu.this, BluetoothBusqueda.class);
                startActivity(intent);
            }
        });

        buttonConectar = findViewById(R.id.buttonConectar);
        buttonConectar.setOnClickListener( new View.OnClickListener() {
            @Override
            public void onClick( View view){
                Intent intent;
                intent=new Intent(BluetoothMenu.this, BluetoothConectar.class);
                startActivity(intent);
            }
        });
    }

}
