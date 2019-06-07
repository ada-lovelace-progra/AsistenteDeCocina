package com.example.appsistentedecocina;

import android.content.Context;
import android.content.DialogInterface;
import android.support.annotation.LayoutRes;
import android.support.annotation.NonNull;
import android.support.annotation.Nullable;
import android.support.v7.app.AlertDialog;
import android.text.InputType;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

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
    public View getView(final int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        View listItem = convertView;
        if (listItem == null)
            listItem = LayoutInflater.from(mContext).inflate(R.layout.list_item_ingredient, parent, false);

        final Ingrediente ingActual = ingList.get(position);

        TextView name = (TextView) listItem.findViewById(R.id.textView_name);
        name.setText(ingActual.getTitulo());

        TextView cantidad = (TextView) listItem.findViewById(R.id.textView_cant);
        cantidad.setText(String.valueOf(ingActual.getCant()));

        listItem.setOnClickListener(new View.OnClickListener() {
            public void onClick(View view) {

                AlertDialog.Builder builder = new AlertDialog.Builder(mContext);
                builder.setTitle(ingActual.getTitulo());
                //contexto
                LinearLayout layout = new LinearLayout(mContext);
                layout.setOrientation(LinearLayout.VERTICAL);
                // Set up the input
                final TextView cantidad = new TextView(mContext);
                final EditText input2 = new EditText(mContext);
                // Specify the type of input expected; this, for example, sets the input as a password, and will mask the text
                cantidad.setText(" cantidad (gr):");
                input2.setInputType(InputType.TYPE_CLASS_NUMBER | InputType.TYPE_CLASS_NUMBER);
                //lo meto en el layout este
                layout.addView(cantidad);
                layout.addView(input2);
                //lo seteo
                builder.setView(layout);
                // Set up the buttons
                builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        if (!input2.getText().toString().equals("")) {
                            ingActual.setCant(Integer.parseInt(input2.getText().toString()));
                            //Toast.makeText(mContext, "no se como modificarlo a " + input2.getText().toString() + " gr", Toast.LENGTH_SHORT).show();
                        }else {
                            ingList.remove(position);
                        }
                    }
                });
                builder.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                    @Override
                    public void onClick(DialogInterface dialog, int which) {
                        dialog.cancel();
                    }
                });
                builder.show();
            }
        });

        return listItem;
    }

}
