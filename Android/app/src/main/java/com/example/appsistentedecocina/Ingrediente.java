package com.example.appsistentedecocina;

public class Ingrediente {

    public Ingrediente(String titulo, int cant) {
        this.titulo = titulo;
        this.cant = cant;
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

    private String titulo;
    private int cant;
}
