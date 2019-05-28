package com.example.appsistentedecocina;

import android.app.Activity;
import android.app.Dialog;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

//public class Dialogo_Ingrediente extends AppCompatActivity {
public class Dialogo_Ingrediente extends Activity {

    private Button btnOK, btnCancelar;
    private EditText txtIngrediente, txtCantidad;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);


        //esto es para hacer que sea igual de ancho que el parent,
        // no me termina de convencer si queda bien o no, pero que se yo, de ultima lo volamos
        setContentView(R.layout.activity_dialogo__ingrediente);
        WindowManager.LayoutParams param = getWindow().getAttributes();
        param.width = WindowManager.LayoutParams.FILL_PARENT;
        getWindow().setAttributes((android.view.WindowManager.LayoutParams) param );

        //va a buscar los elementros del layout que me sirven
        btnOK = (Button) findViewById(R.id.btnOK);
        btnCancelar = (Button) findViewById(R.id.btnCancelar);
        txtIngrediente=(EditText)findViewById(R.id.txtDestino);
        txtCantidad=(EditText)findViewById(R.id.txtCant);

        //seteo el listener a la antigua
        btnOK.setOnClickListener(botonesListeners);
        btnCancelar.setOnClickListener(botonesListeners);
    }



    private View.OnClickListener botonesListeners = new View.OnClickListener()
    {
        public void onClick(View v) {

            switch (v.getId())
            {
                case R.id.btnOK:

                    Toast.makeText(getApplicationContext(), "todavia no lo implemente, mañana lo hago", Toast.LENGTH_SHORT).show();
                    //finish();
                    break;

                case R.id.btnCancelar:
                    finish();
                    break;
                default:
                    Toast.makeText(getApplicationContext(),"Error en Listener de botones",Toast.LENGTH_LONG).show();
            }
        }


    };
}
