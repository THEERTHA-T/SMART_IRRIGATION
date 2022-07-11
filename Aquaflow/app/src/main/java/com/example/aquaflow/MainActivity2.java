package com.example.aquaflow;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.auth.FirebaseAuth;
import com.google.firebase.auth.FirebaseUser;

import java.io.IOException;

import okhttp3.Call;
import okhttp3.Callback;
import okhttp3.OkHttpClient;
import okhttp3.Request;
import okhttp3.Response;


public class MainActivity2 extends AppCompatActivity {
    ImageButton b2;
    ImageButton b1;
    Button btnLogOut;
    FirebaseAuth mAuth;
    private TextView mTextViewResult;
    private TextView mTextViewResult2;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        // call esp32 function
        load_value();

        btnLogOut = findViewById(R.id.btnLogout);
        b1=findViewById(R.id.b1);
        b2=findViewById(R.id.b3);
        mAuth = FirebaseAuth.getInstance();

        btnLogOut.setOnClickListener(view -> {
            mAuth.signOut();
            startActivity(new Intent(MainActivity2.this, LoginActivity.class));
        });

        mTextViewResult = findViewById(R.id.tv1);
        mTextViewResult2 = findViewById(R.id.tv2);


        OkHttpClient client = new OkHttpClient();

        b1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String url = "http://192.168.43.92/on_motor\n";


                Request request = new Request.Builder()
                        .url(url)
                        .build();

                client.newCall(request).enqueue(new Callback() {
                    @Override
                    public void onFailure(Call call, IOException e) {
                        e.printStackTrace();
                    }

                    @Override
                    public void onResponse(Call call, Response response) throws IOException {
                        if (response.isSuccessful()) {
                            final String myResponse = response.body().string();

                            MainActivity2.this.runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    mTextViewResult.setText(myResponse);
                                    Toast.makeText(MainActivity2.this, "Motor turned ON", Toast.LENGTH_SHORT).show();
                                }
                            });
                        }
                    }
                });

            }
        });
        b2.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                String url = "http://192.168.43.92/off_motor\n";


                Request request = new Request.Builder()
                        .url(url)
                        .build();

                client.newCall(request).enqueue(new Callback() {
                    @Override
                    public void onFailure(Call call, IOException e) {
                        e.printStackTrace();
                    }

                    @Override
                    public void onResponse(Call call, Response response) throws IOException {
                        if (response.isSuccessful()) {
                            final String myResponse = response.body().string();

                            MainActivity2.this.runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    mTextViewResult.setText(myResponse);
                                    Toast.makeText(MainActivity2.this, "Motor turned OFF", Toast.LENGTH_SHORT).show();
                                }
                            });
                        }
                    }
                });
            }
        });
    }

    @Override
    protected void onStart() {
        super.onStart();
        FirebaseUser user = mAuth.getCurrentUser();
        if (user == null) {
            startActivity(new Intent(MainActivity2.this, LoginActivity.class));
        }
    }

    // function start
    public void load_value()
    {
        final Handler handler=new Handler();
        final int delay=1000;
        handler.postDelayed(new Runnable() {
            @Override
            public void run() {
                OkHttpClient client = new OkHttpClient();
                String url = "http://192.168.43.92/load_motor\n";
                Request request = new Request.Builder()
                        .url(url)
                        .build();
                client.newCall(request).enqueue(new Callback()
                {
                    @Override
                    public void onFailure(Call call, IOException e)
                    {
                        e.printStackTrace();
                    }
                    @Override
                    public void onResponse(Call call, Response response) throws IOException {
                        if (response.isSuccessful()) {
                            final String myResponse = response.body().string();
                            MainActivity2.this.runOnUiThread(new Runnable() {
                                @Override
                                public void run() {
                                    mTextViewResult2.setText(myResponse);
                                    //Toast.makeText(MainActivity2.this, "load sensor value", Toast.LENGTH_SHORT).show();
                                }
                            });
                        }
                    }
                });
                handler.postDelayed(this,delay);
            }
        },delay);

    }

    // function end
}