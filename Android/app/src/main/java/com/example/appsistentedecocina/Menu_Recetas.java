package com.example.appsistentedecocina;

import android.content.Context;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInput;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

public class Menu_Recetas extends NGActivity {

    private ArrayList<Receta> recetas = new ArrayList<Receta>();

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

        if(! list_exists(this))
        {
            create_list();
        }
        open_list();

        //inicio los botones
        btn1 = (Button) findViewById(R.id.receta1);
        btn1.setText( recetas.get(0).getNombre());
        btn1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                enviarReceta(recetas.get(0));
            }
        });

        btn2 = (Button) findViewById(R.id.receta2);
        btn2.setText( recetas.get(1).getNombre());
        btn2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                enviarReceta(recetas.get(1));
            }
        });

        btn3 = (Button) findViewById(R.id.receta3);
        btn3.setText( recetas.get(2).getNombre());
        btn3.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                enviarReceta(recetas.get(2));
            }
        });

        btn4 = (Button) findViewById(R.id.receta4);
        btn4.setText( recetas.get(3).getNombre());
        btn4.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                enviarReceta(recetas.get(3));
            }
        });

    }

    /**
     * Va mandando de a uno los ingredientes de la receta dada al arduino
     *
     * @param receta la receta que estoy mandando
     */
    private void enviarReceta(Receta receta) {
        Toast.makeText(this, "Enviando receta " + receta.getNombre() + " al dispositivo",
                Toast.LENGTH_SHORT).show();


        for (Ingrediente i:receta.getIngredientes()
             ) {
            //aca va el codigo magico que le manda al arduino las cosas
            //por ahora es un toast
            Toast.makeText(this, i.getTitulo() + "  " + i.getCant()+"gr",
                    Toast.LENGTH_SHORT).show();
        }
    }


    //estos metodos hubiera estado bueno hacerlos con un webservice y que traiga 4 recetas de internet
    //pero no tenemos un servidor asi que las levanta de un archivo

    /**
     * crea el archivo con recetas (ahora mismo le mete 4 recetas default como para testearlo)
     */
    private void create_list(){
        File file = new File(this.getFilesDir(), "recetas");
        file.setWritable(true);
        file.setReadable(true);
        FileOutputStream fos  = null;
        ObjectOutputStream oos  = null;

        ArrayList<Ingrediente> listaIngredientes = new ArrayList<Ingrediente>();
        listaIngredientes.add(new Ingrediente("arroz", 90));
        recetas.add(new Receta(1,listaIngredientes,"Arroz"));

        listaIngredientes.add(new Ingrediente("porotos", 40));
        recetas.add(new Receta(2,listaIngredientes,"Moros y Cristianos"));

        listaIngredientes.clear();

        listaIngredientes.add(new Ingrediente("lentejas",50));
        recetas.add(new Receta(3,listaIngredientes,"Lentejas solas"));

        listaIngredientes.add(new Ingrediente("Arroz",90));
        recetas.add(new Receta(4,listaIngredientes,"Arroz con Lentejas"));

        try {
            fos = new FileOutputStream(file);
            oos = new ObjectOutputStream(fos);
            oos.writeObject( this.recetas );
            oos.close();
            fos.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    /**
     * verifica si existe o no el archivo donde guarda la lista de recetas
     * @param context
     * @return
     */
    public boolean list_exists(Context context) {
        File file = context.getFileStreamPath("recetas");
        if(file == null || !file.exists()) {
            return false;
        }
        return true;
    }

    /**
     * trae las recetas
     */
    private void open_list(){
        File directory = this.getFilesDir();
        File file = new File(directory, "recetas");
        FileInputStream fis  = null;
        ObjectInput ois  = null;
        //boolean            keep = true;


        try {
            fis = new FileInputStream(file);
            ois = new ObjectInputStream(fis);
            this.recetas = (ArrayList<Receta>) ois.readObject();
        }
        catch (Exception e) {
            //keep = false;
            //Log.e("MyAppName", "failed to suspend", e);
        }
        finally {
            try {
                if (ois != null)   ois.close();
                if (fis != null)   fis.close();
                //if (keep == false) file.delete();
            }
            catch (Exception e) { /* do nothing */ }
        }
    }
}
