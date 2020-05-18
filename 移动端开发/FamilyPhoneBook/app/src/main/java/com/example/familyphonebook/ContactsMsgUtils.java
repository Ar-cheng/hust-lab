package com.example.familyphonebook;
import android.annotation.SuppressLint;
import android.content.ContentResolver;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.os.Build;
import android.provider.CallLog;
import android.provider.ContactsContract;

import androidx.annotation.RequiresApi;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ContactsMsgUtils {
        @RequiresApi(api = Build.VERSION_CODES.LOLLIPOP)
        public List<Contact> getContact(Context context) {
        //Map<String, String> number_map = new HashMap<String, String>();//哈希存储电话-联系人键值对
        List<Contact> infos = new ArrayList<Contact>();
        ContentResolver cr = context.getContentResolver();
        String[] projection = new String[]{CallLog.Calls.NUMBER, CallLog.Calls.DATE,
                CallLog.Calls.TYPE,CallLog.Calls.CACHED_NAME,CallLog.Calls.DURATION};
        @SuppressLint("MissingPermission")
        Cursor cursor = cr.query(CallLog.Calls.CONTENT_URI, projection, null, null, CallLog.Calls.DEFAULT_SORT_ORDER);
        //number_map =  get_all_contact(context);

            while (cursor.moveToNext()) {
            String number = cursor.getString(0);
            long date = cursor.getLong(1);
            int type = cursor.getInt(2);
            String name = cursor.getString(3);
            int duration = cursor.getInt(4);
            if(name==null)
                name = number;
            String address = GetCity.getGeo(number);
            if(address.contains("襄樊"))
//                Log.d("sub", "replacement ");
                address = address.replace("襄樊","襄阳");
            infos.add(new Contact(name, number, date, type,duration,address,0));

        }
        cursor.close();
        return infos;
    }

    private Map get_all_contact(Context context){
        Map<String, String> number_num = new HashMap<>();
        ContentResolver cr= context.getContentResolver();
        Uri uri = ContactsContract.CommonDataKinds.Phone.CONTENT_URI;
        String[] projection = {
                ContactsContract.CommonDataKinds.Phone.DISPLAY_NAME,//姓名
                ContactsContract.CommonDataKinds.Phone.NUMBER,//电话号码
        };
        Cursor cursor  = cr.query(uri,projection,null,null,null);
        if(cursor == null)
            return null;
        //获取最终返回的hashmap
        while (cursor.moveToNext()){
            String name = cursor.getString(0);
            String num  = cursor.getString(1).replace(" ","");
            //保存
            number_num.put(num,name);
        }
        cursor.close();
        return number_num;
    }
}
