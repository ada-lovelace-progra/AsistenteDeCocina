package com.example.appsistentedecocina.data;

public class Producto {
    private String nombre;
    private int cantidad;

    public Producto(String titulo, int cantidad) {
        this.nombre = titulo;
        this.cantidad = cantidad;
    }

    public String getNombre() {
        return nombre;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public int getCantidad() {
        return cantidad;
    }

    public void setCantidad(int cantidad) {
        this.cantidad = cantidad;
    }

}
