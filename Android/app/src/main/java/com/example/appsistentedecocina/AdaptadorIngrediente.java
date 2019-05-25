package com.example.appsistentedecocina;

import android.content.Context;
import android.support.annotation.LayoutRes;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import java.util.ArrayList;
import java.util.List;

public class AdaptadorIngrediente extends ArrayAdapter {

    private Context mContext;
    private List<Ingrediente> ingList = new ArrayList<>();

    public AdaptadorIngrediente(@NonNull Context context, ArrayList<Ingrediente> list) {
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

        Ingrediente ingActual = ingList.get(position);

        TextView name = (TextView) listItem.findViewById(R.id.textView_name);
        name.setText(ingActual.getTitulo());

        TextView cantidad = (TextView) listItem.findViewById(R.id.textView_cant);
        cantidad.setText(String.valueOf( ingActual.getCant()) );

        return listItem;
    }

}
