package com.example.appsistentedecocina.data;

public class Ingredientes {
    private int id;
    private int receta;
    private int productoid;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public int getReceta() {
        return receta;
    }

    public void setReceta(int receta) {
        this.receta = receta;
    }

    public int getProductoid() {
        return productoid;
    }

    public void setProductoid(int productoid) {
        this.productoid = productoid;
    }

    public int getCantidad() {
        return cantidad;
    }

    public void setCantidad(int cantidad) {
        this.cantidad = cantidad;
    }

    private int cantidad;
}
