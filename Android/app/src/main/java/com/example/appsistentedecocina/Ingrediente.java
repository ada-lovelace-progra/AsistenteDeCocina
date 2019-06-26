package com.example.appsistentedecocina;

import java.io.Serializable;

/**
 * cada ingrediente es un objeto de este tipo
 */
public class Ingrediente implements Serializable {

    private String titulo;
    private int cant;
    private byte id;


    public Ingrediente(String titulo, int cant, byte id) {
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

    public byte getId() {
        return id;
    }

    public void setId(byte id) {
        this.id = id;
    }


}
