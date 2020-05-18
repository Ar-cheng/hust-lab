package com.example.familyphonebook;

import android.Manifest;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.util.Log;
import android.widget.EditText;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;

import java.util.List;



public class MainActivity extends AppCompatActivity {

    private RecyclerView mRecyclerView;
    private List<Contact> mDataList;


    @RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);//保持竖屏
        setContentView(R.layout.activity_main);
        mRecyclerView = findViewById(R.id.RecyclerView_main);
        mRecyclerView.setLayoutManager(new LinearLayoutManager(this));
        final List<Contact> mDataList = initdata();
            final MyAdapter myAdapter = new MyAdapter(this, mDataList);
            myAdapter.setOnItemClickListener(new MyAdapter.OnItemClickListener() {
                @Override
                public void onClick(int position) {
                    Intent intent = new Intent();//新建一个intent
                    List<Contact> mData_filters = myAdapter.get_filters();
                    intent.putExtra("name",mData_filters.get(position).getName());
                    intent.putExtra("phone",mData_filters.get(position).getPhonenumber());
                    intent.putExtra("state",mData_filters.get(position).getState());
                    intent.putExtra("duration",mData_filters.get(position).getDuration());
                    intent.putExtra("date",mData_filters.get(position).getDate());
                    intent.putExtra("address",mData_filters.get(position).getAddress());

                    intent.setClass(MainActivity.this, SubActivity.class);//指定要启动的类
                    startActivity(intent);//启动新的intent
                    MainActivity.this.finish();//关闭当前的activity
                }
            });
            mRecyclerView.setAdapter(myAdapter);
            EditText edit_find = findViewById(R.id.EditText_find);
            edit_find.addTextChangedListener(new TextWatcher() {
                @Override
                public void beforeTextChanged(CharSequence s, int start, int count, int after) {

                }

                @Override
                public void onTextChanged(CharSequence s, int start, int before, int count) {
                    myAdapter.getFilter().filter(s.toString());
//                    Log.d("ddddd", s.toString());
                }

                @Override
                public void afterTextChanged(Editable s) {

                }
            });
        }

    @RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
    private List<Contact> initdata() {
        List<Contact> infos = null;
        if (ContextCompat.checkSelfPermission(MainActivity.this, Manifest.permission.READ_CALL_LOG) == PackageManager.PERMISSION_GRANTED && ContextCompat.checkSelfPermission(MainActivity.this, Manifest.permission.READ_CONTACTS) == PackageManager.PERMISSION_GRANTED) {
            //已授权
            ContactsMsgUtils contactsMsgUtils = new ContactsMsgUtils();
            infos = contactsMsgUtils.getContact(MainActivity.this);
            return infos;
        } else {
            ActivityCompat.requestPermissions(MainActivity.this, new String[]{Manifest.permission.READ_CALL_LOG, Manifest.permission.READ_CONTACTS}, 0);
            infos.add(new Contact("未读取","1",2,0,4,null,0));
            return infos;
        }
    }
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        switch (requestCode) {
            case 0: {              //这个0是requestCode，上面requestPermissions有用到
                // If request is cancelled, the result arrays are empty.
                if (grantResults.length > 0
                        && grantResults[0] == PackageManager.PERMISSION_GRANTED&&grantResults[1]==PackageManager.PERMISSION_GRANTED) {
                    Toast.makeText(MainActivity.this, "已获取权限,可以读取联系人", Toast.LENGTH_SHORT).show();
                } else {
                    Toast.makeText(MainActivity.this, "您拒绝了权限，即将退出程序", Toast.LENGTH_SHORT).show();
                }
                return;
            }
        }
    }
}
