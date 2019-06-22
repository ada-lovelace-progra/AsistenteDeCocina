package com.example.appsistentedecocina;

import android.content.Intent;
import android.os.Bundle;
import android.os.CountDownTimer;
import android.util.Log;
import android.view.View;
import android.widget.Button;

public class MainActivity extends NGActivity {

    private Button btnIng;
    private Button btnRec;
    private Button btnBt;
    private Button btnS;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        btnIng = (Button) findViewById(R.id.bt_ingrediente);
        btnIng.setOnClickListener( new View.OnClickListener() {
            @Override
            public void onClick( View view){
                Intent intent;
                intent = new Intent(MainActivity.this, List_Ingrediente.class);
                startActivity(intent);
            }
        });

        btnRec = (Button) findViewById(R.id.bt_recetas);
        btnRec.setOnClickListener( new View.OnClickListener() {
            @Override
            public void onClick( View view){
                Intent intent;
                intent = new Intent(MainActivity.this, Menu_Recetas.class);
                startActivity(intent);
            }
        });

        btnBt = (Button) findViewById(R.id.bt_bluetooth);
        btnBt.setOnClickListener( new View.OnClickListener() {
            @Override
            public void onClick( View view){
                Intent intent;
                intent = new Intent(MainActivity.this, BluetoothMenu.class);
                startActivity(intent);
            }
        });

        btnS = (Button) findViewById(R.id.bt_sensores);
        btnS.setOnClickListener( new View.OnClickListener() {
            @Override
            public void onClick( View view){
                Intent intent;
                intent = new Intent(MainActivity.this, Sensores.class);
                startActivity(intent);
            }
        });
    }
}
