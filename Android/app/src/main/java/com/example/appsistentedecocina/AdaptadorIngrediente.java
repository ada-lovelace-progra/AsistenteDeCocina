package com.example.appsistentedecocina;

import android.content.Context;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import com.example.appsistentedecocina.data.Producto;

import java.util.ArrayList;
import java.util.List;

public class AdaptadorIngrediente extends ArrayAdapter {

    private Context mContext;
    private List<Producto> ingList = new ArrayList<>();

    public AdaptadorIngrediente(@NonNull Context context, ArrayList<Producto> list) {
        super(context, 0, list);
        mContext = context;
        ingList = list;

    }

    @NonNull
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        View listItem = convertView;
        if(listItem == null)
            listItem = LayoutInflater.from(mContext).inflate(R.layout.list_item_ingredient,parent,false);

        Producto ingActual = ingList.get(position);

        TextView name = (TextView) listItem.findViewById(R.id.textView_name);
        name.setText(ingActual.getNombre());

        TextView cantidad = (TextView) listItem.findViewById(R.id.textView_cant);
        cantidad.setText(String.valueOf( ingActual.getCantidad()) );

        return listItem;
    }

}
