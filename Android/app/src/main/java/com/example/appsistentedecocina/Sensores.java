package com.example.appsistentedecocina;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.text.DecimalFormat;


public class Sensores extends AppCompatActivity implements SensorEventListener {

    private SensorManager mSensorManager;

    private Button playpause;

    private Sensor mProximity;
    private TextView tvProximity;

    private Sensor mGravity;
    private TextView tvGravity;

    private Sensor mLuz;
    private TextView tvLuz;

    DecimalFormat dosdecimales = new DecimalFormat("###.###");

    private static final int SENSOR_SENSITIVITY = 4;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sensores);

        playpause = findViewById(R.id.pausa);
        playpause.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick( View view){
                        play();
                    }
                }
        );

        mSensorManager = (SensorManager) getSystemService(Context.SENSOR_SERVICE);

        mProximity = mSensorManager.getDefaultSensor(Sensor.TYPE_PROXIMITY);
        tvProximity = (TextView) findViewById(R.id.proximidad);

        mGravity = mSensorManager.getDefaultSensor(Sensor.TYPE_GRAVITY);
        tvGravity = (TextView) findViewById(R.id.gravedad);

        mLuz = mSensorManager.getDefaultSensor(Sensor.TYPE_LIGHT);
        tvLuz = (TextView) findViewById(R.id.luminosidad);
    }

    @Override
    protected void onResume() {
        super.onResume();
        mSensorManager.registerListener(this, mProximity, SensorManager.SENSOR_DELAY_NORMAL);
        mSensorManager.registerListener(this, mGravity, SensorManager.SENSOR_DELAY_NORMAL);
        mSensorManager.registerListener(this, mLuz, SensorManager.SENSOR_DELAY_NORMAL);
    }

    @Override
    protected void onPause() {
        super.onPause();
        mSensorManager.unregisterListener(this, mSensorManager.getDefaultSensor(Sensor.TYPE_GRAVITY));
        mSensorManager.unregisterListener(this, mSensorManager.getDefaultSensor(Sensor.TYPE_PROXIMITY));
        mSensorManager.unregisterListener(this, mSensorManager.getDefaultSensor(Sensor.TYPE_LIGHT));

    }

    @Override
    public void onSensorChanged(SensorEvent event) {
//        if (event.sensor.getType() == Sensor.TYPE_PROXIMITY) {
//            if (event.values[0] >= -SENSOR_SENSITIVITY && event.values[0] <= SENSOR_SENSITIVITY) {
//                //near
//                //Toast.makeText(getApplicationContext(), "Pausando el sinfin", Toast.LENGTH_SHORT).show();
//                tvProximity.setText("Proximidad: Cerca");
//            } else {
//                //far
//                //Toast.makeText(getApplicationContext(), "far", Toast.LENGTH_SHORT).show();
//                tvProximity.setText("Proximidad: Lejos");
//            }
//        }
        String txt = "";
        synchronized (this) {
            switch (event.sensor.getType()) {
//            case Sensor.TYPE_GYROSCOPE:
//                txt += "Giroscopo:\n";
//                txt += "x: " + dosdecimales.format(event.values[0]) + " deg/s \n";
//                txt += "y: " + dosdecimales.format(event.values[1]) + " deg/s \n";
//                txt += "z: " + dosdecimales.format(event.values[2]) + " deg/s \n";
//                giroscopo.setText(txt);
//                break;

                case Sensor.TYPE_GRAVITY:
                    txt += "Gravedad:\t\t";
//                    txt += "x: " + event.values[0] + "\n";
//                    txt += "y: " + event.values[1] + "\n";
//                    txt += "z: " + event.values[2] + "\n";

                    if (event.values[1] < 0){
                        txt += "▼▼▼";
                        invertirSentido( 0);
                    }
                    else{
                        txt += "▲▲▲";
                        invertirSentido( 1 );
                    }

                    tvGravity.setText(txt);
                    break;

                case Sensor.TYPE_PROXIMITY:
                    txt += "Proximidad:\t";
//                    txt += event.values[0] + "\n";

                    if (event.values[0] <= 4){
                        txt += "Sinfin Pausado";
                        pausa();
                    }


                    tvProximity.setText(txt);
                    break;

                case Sensor.TYPE_LIGHT:
                    txt += "Luminosidad:\t";
//                    txt += event.values[0] + " Lux \n";

                    if (event.values[0] <= 5)
                        txt += "X (encender un led)";
                    else
                        txt += "\uD83D\uDCA1";

                    tvLuz.setText(txt);
                    break;

            }
        }
    }

    @Override
    public void onAccuracyChanged(Sensor sensor, int accuracy) {

    }

    /**
     * hace que el arduino gire
     */
    public void play(){
        playpause.setText("||️");
    }


    /**
     * envia señal de pausa al Arduino
     */
    public void pausa(){
        playpause.setText(">>");
    }

    /**
     * le dice al arduino que vaya en diferente sentido
     * @param i sentido (?
     */
    public void invertirSentido(int i){

    }



}
