package com.example.appsistentedecocina;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import java.util.ArrayList;
import android.app.ListActivity;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;


public class Ingredientes extends ListActivity{

    /** Items entered by the user is stored in this ArrayList variable */
    ArrayList<String> list = new ArrayList<String>();

    /** Declaring an ArrayAdapter to set items to ListView */
    ArrayAdapter<String> adapter;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ingredientes);

        /** Reference to the button of the layout main.xml */
        Button btn = (Button) findViewById(R.id.btnAdd);

        /** Defining the ArrayAdapter to set items to ListView */
        adapter = new ArrayAdapter<String>(this, R.layout.list_item_ingredient, list);

        /** Defining a click event listener for the button "Add" */
        OnClickListener listener = new OnClickListener() {
            @Override
            public void onClick(View v) {
                String txt;
                EditText edit = (EditText) findViewById(R.id.txtItem);
                txt = edit.getText().toString();
                if(txt.matches("")) {
                    Toast.makeText(getApplicationContext(), "No escribiste nada", Toast.LENGTH_SHORT).show();
                    return;
                }
                list.add(edit.getText().toString());
                edit.setText("");
                adapter.notifyDataSetChanged();

            }
        };

        /** Setting the event listener for the add button */
        btn.setOnClickListener(listener);

        /** Setting the adapter to the ListView */
        setListAdapter(adapter);
    }
}
