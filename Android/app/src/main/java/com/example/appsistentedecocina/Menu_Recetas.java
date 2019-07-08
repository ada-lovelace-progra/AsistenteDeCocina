package com.example.appsistentedecocina;

import android.content.Context;
import android.os.Bundle;
import android.util.Log;
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

    public static final int CANT_BTNS = 4;
    public static final int ID_RECETA_ARROZ = 1;
    public static final int ID_RECETA_MOROS = 2;
    public static final int ID_RECETA_LENTEJAS = 3;
    public static final int ID_RECETA_ARROZYLENTEJAS = 4;
    public static final int DEFAUL_CANT_ARROZ = 90;
    public static final int ID_INGREDIENTE_ARROZ = 1;
    public static final int DEFAULT_CANT_POROTOS = 40;
    public static final int ID_INGREDIENTE_POROTOS = 2;
    public static final int ID_INGREDIENTE_LENTEJAS = 3;
    public static final int DEFAULT_CANT_LENTEJAS = 50;
    private ArrayList<Receta> recetas = new ArrayList<Receta>();

    private Button[] btn;
    private Button btn1;
    private Button btn2;
    private Button btn3;
    private Button btn4;
    private ArrayList<Ingrediente> ingredientesActuales;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_recetas);

        create_list();
        open_list();
        traerIngredientesActuales();

        //inicio los botones
        for (int i = 0; i < CANT_BTNS; i++) {
            int id = getResources().getIdentifier("receta" + i, "id", getPackageName());

            btn[i] = findViewById(id);
            btn[i].setText(recetas.get(i).getNombre());
            btn[i].setOnClickListener(new View.OnClickListener() {
                int recetaNum = 0;

                public View.OnClickListener init (int num) {
                    recetaNum = num;
                    return this;
                }

                @Override
                public void onClick(View view) {
                    enviarReceta(recetas.get(recetaNum));
                }
            }.init(i));
        }
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
            escribirBluetoothNum(i.getId()); // ACÁ HAY QUE MANDAR EL ID
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
        listaIngredientes.add(new Ingrediente("arroz", DEFAUL_CANT_ARROZ, ID_INGREDIENTE_ARROZ));
        recetas.add(new Receta(ID_RECETA_ARROZ, listaIngredientes,"Arroz"));

        listaIngredientes.add(new Ingrediente("porotos", DEFAULT_CANT_POROTOS, ID_INGREDIENTE_POROTOS));
        recetas.add(new Receta(ID_RECETA_MOROS, listaIngredientes,"Moros y Cristianos"));

        listaIngredientes.clear();

        listaIngredientes.add(new Ingrediente("lentejas", DEFAULT_CANT_LENTEJAS, ID_INGREDIENTE_LENTEJAS));
        recetas.add(new Receta(ID_RECETA_LENTEJAS, listaIngredientes,"Lentejas solas"));

        listaIngredientes.add(new Ingrediente("Arroz",DEFAUL_CANT_ARROZ, ID_INGREDIENTE_ARROZ));
        recetas.add(new Receta(ID_RECETA_ARROZYLENTEJAS, listaIngredientes,"Arroz con Lentejas"));

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


        try {
            fis = new FileInputStream(file);
            ois = new ObjectInputStream(fis);
            this.recetas = (ArrayList<Receta>) ois.readObject();
        }
        catch (Exception e) {
            Log.d("Menu_Recetas", "error al abrir archivo: " + e.getMessage());
        }
        finally {
            try {
                if (ois != null)   ois.close();
                if (fis != null)   fis.close();
            }
            catch (Exception e) { /* do nothing */ }
        }
    }

    /**
     * trae la lista de ingredientes, utilizado para verificar si las cantidades son suficientes
     */
    private void traerIngredientesActuales(){
        File directory = this.getFilesDir();
        File file = new File(directory, "ingredientes");
        FileInputStream fis = null;
        ObjectInput ois = null;

        try {
            fis = new FileInputStream(file);
            ois = new ObjectInputStream(fis);
            this.ingredientesActuales = (ArrayList<Ingrediente>) ois.readObject();
        } catch (Exception e) {
            Log.d("Menu_Recetas", "error al abrir archivo: " + e.getMessage());
        } finally {
            try {
                if (ois != null) ois.close();
                if (fis != null) fis.close();
            } catch (Exception e) { /* do nothing */ }
        }
    }

    /**
     * guarda los ingredientes en su estado modificado (con los ingredientes restados)
     */
    private void actualizarIngredientes(){
        File directory = this.getFilesDir();
        File file = new File(directory, "ingredientes");
        FileOutputStream fos = null;
        ObjectOutputStream oos = null;

        try {
            fos = new FileOutputStream(file);
            oos = new ObjectOutputStream(fos);
            oos.writeObject(this.ingredientesActuales);
        } catch (Exception e) {
            Log.d("Menu_Recetas", "error al abrir archivo: " + e.getMessage());
        } finally {
            try {
                if (oos != null) oos.close();
                if (fos != null) fos.close();
            } catch (Exception e) { /* do nothing */ }
        }
    }
}
