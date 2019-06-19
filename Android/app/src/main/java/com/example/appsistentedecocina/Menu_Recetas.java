package com.example.appsistentedecocina;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

public class Menu_Recetas extends NGActivity {

    private Button btn1;
    private Button btn2;
    private Button btn3;
    private Button btn4;
    private Receta r1;
    private Receta r2;
    private Receta r3;
    private Receta r4;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_recetas);
        //inicio los botones
        btn1 = (Button) findViewById(R.id.receta1);
        btn1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                enviarReceta(1);
            }
        });
        btn2 = (Button) findViewById(R.id.receta2);
        btn2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                enviarReceta(2);
            }
        });
        btn3 = (Button) findViewById(R.id.receta3);
        btn3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                enviarReceta(3);
            }
        });
        btn4 = (Button) findViewById(R.id.receta4);
        btn4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                enviarReceta(4);
            }
        });

    }

    /**
     * le mando el id de receta y esto (con el service bluetooth), se fija que ingredientes
     * tiene la receta y se los va mandando al arduino
     *
     * @param i id de la receta
     */
    private void enviarReceta(int i) {
        Toast.makeText(this, "Enviando receta " + i + " al dispositivo",
                Toast.LENGTH_SHORT).show();
    }

    //habria que tener un archivo guardado con una lista de al menos 4 recetas
    
}
