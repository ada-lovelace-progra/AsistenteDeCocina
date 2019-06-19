package com.example.appsistentedecocina;

import java.io.Serializable;
import java.util.ArrayList;

/**
 * Esta clase va a ser util, les juro
 */
public class Receta implements Serializable {
    private int id;
    private ArrayList<Ingrediente> ingredientes = new ArrayList<Ingrediente>();

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public Receta(int id, ArrayList<Ingrediente> ingredientes) {
        this.id = id;
        this.ingredientes = ingredientes;
    }

    public ArrayList<Ingrediente> getIngredientes() {
        return ingredientes;
    }

    public void setIngredientes(ArrayList<Ingrediente> ingredientes) {
        this.ingredientes = ingredientes;
    }
}
