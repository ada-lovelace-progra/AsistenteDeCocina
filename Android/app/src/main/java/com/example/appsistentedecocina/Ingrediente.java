package com.example.appsistentedecocina;

import java.io.Serializable;

/**
 * cada ingrediente es un objeto de este tipo
 */
public class Ingrediente implements Serializable {

    private String titulo;
    private int cant;
    private int id;


    public Ingrediente(String titulo, int cant, int id) {
        this.titulo = titulo;
        this.cant = cant;
        this.id = id;
    }

    public String getTitulo() {
        return titulo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public int getCant() {
        return cant;
    }

    public void setCant(int cant) {
        this.cant = cant;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }


}
