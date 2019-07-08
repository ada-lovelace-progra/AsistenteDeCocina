package com.example.appsistentedecocina;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;

/**
 * Esta clase va a ser util, les juro
 */
public class Receta implements Serializable {
    private int id;

    private ArrayList<Ingrediente> ingredientes = new ArrayList<Ingrediente>();
    private String nombre;

    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

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

    public Receta(int id, ArrayList<Ingrediente> ingredientes, String nombre) {
        this.id = id;
        this.ingredientes.addAll(ingredientes);
        this.nombre = nombre;
    }

    public ArrayList<Ingrediente> getIngredientes() {
        return ingredientes;
    }

    public void setIngredientes(ArrayList<Ingrediente> ingredientes) {
        this.ingredientes = ingredientes;
    }
}
