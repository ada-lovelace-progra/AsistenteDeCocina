package com.example.appsistentedecocina;

import android.content.Context;
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
    private ArrayList<Ingrediente> ingredientesActuales;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_recetas);

        if(! list_exists(this))
        {
            create_list();
        }
        open_list();
        traerIngredientesActuales();

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

        //chequeo que puedo hacer la receta
        for( Ingrediente j : receta.getIngredientes())
        {
            boolean esta = false;
            for(Ingrediente i : this.ingredientesActuales){
                if( j.getId() == i.getId() )
                {
                    if(j.getCant() < i.getCant()){
                        esta = true;
                        i.setCant(i.getCant() - j.getCant() );
                    }
                }
            }
            if(!esta)
            {
                Toast.makeText(this, "No hay suficientes ingredientes disponibles",
                        Toast.LENGTH_SHORT).show();
                return;
            }
        }

        // envio byte de acción
        escribirBluetoothByte(ServicioBluetooth.LEER_MULTI_PROD);
        // envio 4 bytes con cantidad de productos
        escribirBluetoothNum(receta.getIngredientes().size());

        for (Ingrediente i : receta.getIngredientes()) {
            // por cada ingrediente
            // envio 1 byte de ID del producto
            escribirBluetoothByte((byte)i.getId()); // ACÁ HAY QUE MANDAR EL ID
            // envio 4 bytes con la cantidad
            escribirBluetoothNum(i.getCant());
        }

        actualizarIngredientes();
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
        listaIngredientes.add(new Ingrediente("arroz", 90, 1));
        recetas.add(new Receta(1,listaIngredientes,"Arroz"));

        listaIngredientes.add(new Ingrediente("porotos", 40, 2));
        recetas.add(new Receta(2,listaIngredientes,"Moros y Cristianos"));

        listaIngredientes.clear();

        listaIngredientes.add(new Ingrediente("lentejas",50, 3));
        recetas.add(new Receta(3,listaIngredientes,"Lentejas solas"));

        listaIngredientes.add(new Ingrediente("Arroz",90, 1));
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


    private void traerIngredientesActuales(){
        File directory = this.getFilesDir();
        File file = new File(directory, "ingredientes");
        FileInputStream fis = null;
        ObjectInput ois = null;
        //boolean            keep = true;


        try {
            fis = new FileInputStream(file);
            ois = new ObjectInputStream(fis);
            this.ingredientesActuales = (ArrayList<Ingrediente>) ois.readObject();
        } catch (Exception e) {
            //keep = false;
            //Log.e("MyAppName", "failed to suspend", e);
        } finally {
            try {
                if (ois != null) ois.close();
                if (fis != null) fis.close();
                //if (keep == false) file.delete();
            } catch (Exception e) { /* do nothing */ }
        }
    }

    private void actualizarIngredientes(){
        File directory = this.getFilesDir();
        File file = new File(directory, "ingredientes");
        FileOutputStream fos = null;
        ObjectOutputStream oos = null;
        //boolean            keep = true;


        try {
            fos = new FileOutputStream(file);
            oos = new ObjectOutputStream(fos);
            oos.writeObject(this.ingredientesActuales);
        } catch (Exception e) {
            //keep = false;
            //Log.e("MyAppName", "failed to suspend", e);
        } finally {
            try {
                if (oos != null) oos.close();
                if (fos != null) fos.close();
                //if (keep == false) file.delete();
            } catch (Exception e) { /* do nothing */ }
        }
    }
}
