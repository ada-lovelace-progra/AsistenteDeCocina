package com.example.appsistentedecocina;

import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.widget.Button;
import android.widget.ListView;

import com.example.appsistentedecocina.data.Producto;

import java.util.ArrayList;

public class List_Ingrediente extends AppCompatActivity {

    private ListView listview;
    private AdaptadorIngrediente adapter;

    private Button nuevo;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list__ingrediente);

        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        FloatingActionButton fab = findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Snackbar.make(view, "No esta implementado, bancame", Snackbar.LENGTH_LONG)
                        .setAction("Action", null).show();

            }
        });

        listview = (ListView)findViewById(R.id.ingrediente_list);
        ArrayList<Producto> listaIngredientes = new ArrayList<Producto>();

        listaIngredientes.add(new Producto("arroz",150));
        listaIngredientes.add(new Producto("yerba",500));

        adapter = new AdaptadorIngrediente(this, listaIngredientes);
        listview.setAdapter(adapter);
    }

}
