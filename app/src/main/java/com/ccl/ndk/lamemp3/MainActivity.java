package com.ccl.ndk.lamemp3;

import android.os.Bundle;
import android.os.Environment;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        tv.setText("version:" + LameUtil.getVersion());
        findViewById(R.id.btn_start).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                final long start = System.currentTimeMillis();
                LameUtil.pcm2mp3(Environment.getExternalStorageDirectory().getAbsolutePath() + "/att.pcm",
                        false,
                        Environment.getExternalStorageDirectory().getAbsolutePath() + "/att-final.mp3");
                LameUtil.pcm2mp3withParm(Environment.getExternalStorageDirectory().getAbsolutePath() + "/att.pcm",
                        false,
                        Environment.getExternalStorageDirectory().getAbsolutePath() + "/att-final-high.mp3",
                        1, 16000, 16, LameUtil.QUALITY_HIGH);
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(MainActivity.this, "转换完毕 cast = " + (System.currentTimeMillis() - start), Toast.LENGTH_SHORT).show();
                    }
                });
            }
        });
    }
}
