package com.example.familyphonebook;

import android.Manifest;
import android.content.ContentValues;
import android.content.Context;
import android.content.Intent;
import android.content.pm.ActivityInfo;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Matrix;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.provider.CallLog;
import android.provider.MediaStore;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;
import androidx.core.content.FileProvider;

import com.google.android.material.floatingactionbutton.FloatingActionButton;

import org.json.JSONArray;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.net.URLEncoder;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashMap;
import java.util.Objects;

public class SubActivity extends AppCompatActivity {
    private TextView weather_temper;
    private TextView weather_city;
    private TextView weather_type;
    private TextView weather_date;
    private TextView weather_notice;
    private ImageView weather_type_icon;

    /* 头像文件 */
    private static final String IMAGE_FILE_NAME = "temp_head_image.jpg";
    private static final String CROP_IMAGE_FILE_NAME = "bala_crop.jpg";
    /* 请求识别码 */
    private static final int CODE_GALLERY_REQUEST = 0xa0;
    private static final int CODE_CAMERA_REQUEST = 0xa1;
    private static final int CODE_RESULT_REQUEST = 0xa2;

    // 裁剪后图片的宽(X)和高(Y),480 X 480的正方形。
    private static int output_X = 480;
    private static int output_Y = 480;
    //改变头像的标记位
    private int new_icon = 0xa3;
    private ImageView headImage = null;
    private String mExtStorDir;
    private Uri mUriPath;

    private final int PERMISSION_READ_AND_CAMERA = 0;//读和相机权限
    private final int PERMISSION_READ = 1;//读取权限
    private final int PERMISSION_CALL = 3;//call权限

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);//保持竖屏
        setContentView(R.layout.activity_sub);

        mExtStorDir = Environment.getExternalStorageDirectory().toString();
        headImage = (ImageView) findViewById(R.id.imageView);
        Button buttonLocal = (Button) findViewById(R.id.buttonLocal);
        buttonLocal.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
//                choseHeadImageFromGallery();
                checkReadPermission();

            }
        });
        Button buttonCamera = (Button) findViewById(R.id.buttonCamera);
        buttonCamera.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
//                choseHeadImageFromCameraCapture();
                checkStoragePermission();//检查是否有权限
            }
        });


        Intent intent = getIntent();
        String name = intent.getStringExtra("name");
        final String phone = intent.getStringExtra("phone");
        String phone_split = phone;
        if (phone.length() == 11)
            phone_split = phone.substring(0, 3) + " " + phone.substring(3, 7) + " " + phone.substring(7, 11);
        int duration = intent.getIntExtra("duration", 0);
        long date = intent.getLongExtra("date", 0);
        String address = intent.getStringExtra("address");
        int state = intent.getIntExtra("state", 0);
        Toolbar toolbar = findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        FloatingActionButton fab = findViewById(R.id.fab);


        ImageButton buton_call = findViewById(R.id.button_call);
        ImageButton buton_message = findViewById(R.id.button_message);
        TextView text_info = findViewById(R.id.info);
        TextView text_phonenumber = findViewById(R.id.phonenumber);
        TextView text_date = findViewById(R.id.date);
        TextView text_state = findViewById(R.id.state);
        TextView text_address = findViewById(R.id.address);
        TextView text_phonenumber_s = findViewById(R.id.phonenumber_s);

        weather_temper = findViewById(R.id.weather_temper);
        weather_city = findViewById(R.id.weather_city);
        weather_date = findViewById(R.id.weather_date);
        weather_notice = findViewById(R.id.weather_type_notice);
        weather_type_icon = findViewById(R.id.weather_type_icon);
        weather_type = findViewById(R.id.weather_type);


        text_info.setText(Objects.equals(name, phone) ? "陌生联系人" : name);
        text_address.setText(address);
        text_date.setText(timeStamp2Date(date, null));
        text_phonenumber_s.setText(phone_split);
        text_phonenumber.setText(phone);

        String duratio_text = null;
        if (duration == 0)
            duratio_text = "";
        else if (duration > 60)
            duratio_text = (duration / 60 + "分" + duration % 60 + "秒");
        else
            duratio_text = (duration % 60 + "秒");

        switch (state) {
            case CallLog.Calls.INCOMING_TYPE:
                text_state.setText("接入" + duratio_text);// = "打入";
                break;
            case CallLog.Calls.OUTGOING_TYPE:
                text_state.setText("接出" + duratio_text);
                ;// = "打出";
                break;
            case CallLog.Calls.MISSED_TYPE:
                //"未接"
                text_state.setText("未接");//"未接";
                break;
            default:
                text_state.setText("未接");//"未接";
                break;
        }


        if (address != null) {
            String cityname = address.substring(address.contains("省") ? address.indexOf("省") + 1 : 0).replace("市", "");
            if (isNetworkConnected(this) == true)
                get_weather(cityname);

        }
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent();//新建一个intent
                intent.setClass(SubActivity.this, MainActivity.class);//指定要启动的类
                startActivity(intent);//启动新的intent
                SubActivity.this.finish();//关闭当前的activity
            }
        });

        buton_message.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Uri uri2 = Uri.parse("smsto:" + phone);
                Intent intentMessage = new Intent(Intent.ACTION_VIEW, uri2);
                intentMessage.putExtra("sms_body", weather_notice.getText());
                startActivity(intentMessage);
            }
        });

        buton_call.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (ContextCompat.checkSelfPermission(SubActivity.this, Manifest.permission.CALL_PHONE) == PackageManager.PERMISSION_GRANTED) {
                    Uri uri = Uri.parse("tel:" + phone);
                    Intent intent = new Intent(Intent.ACTION_CALL, uri);
                    startActivity(intent);
                } else {
                    ActivityCompat.requestPermissions(SubActivity.this, new String[]{Manifest.permission.CALL_PHONE}, PERMISSION_CALL);
                }
            }
        });
    }

    public static String timeStamp2Date(long time, String format) {//long date解析
        if (format == null || format.isEmpty()) {
            format = "yyyy-MM-dd HH:mm:ss";
        }
        SimpleDateFormat sdf = new SimpleDateFormat(format);
        return sdf.format(new Date(time));
    }

    private void get_weather(final String cityname) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                HttpURLConnection connection = null;
                BufferedReader reader;
                StringBuilder response = new StringBuilder();
                try {
                    Log.d("sub", "cityname " + cityname);
                    URL url = new URL("http://toy1.weather.com.cn/search?cityname=" + URLEncoder.encode(cityname, "utf-8"));
                    connection = (HttpURLConnection) url.openConnection();
                    connection.setReadTimeout(3000);
                    connection.setReadTimeout(3000);
                    InputStream in = connection.getInputStream();
                    reader = new BufferedReader(new InputStreamReader(in));
                    String line;
                    while ((line = reader.readLine()) != null) {
                        response.append(line);
                    }
                    connection.disconnect();
                } catch (Exception e) {
                    e.printStackTrace();
                    Log.d("sub1", e.toString());
                }
                HashMap<String, String> weather = new HashMap<>();
                // 定义url字符串
                try {
                    String cityCode = response.toString().substring(10, 19);
                    Log.d("sub1", "citycode:" + cityCode);
                    String strUrl = "http://t.weather.sojson.com/api/weather/city/" + cityCode;
                    URL url = new URL(strUrl);
                    connection = (HttpURLConnection) url.openConnection();
                    connection.setReadTimeout(3000);
                    connection.setReadTimeout(3000);
                    InputStream in = connection.getInputStream();
                    if (connection.getResponseCode() == 200) {
                        StringBuilder response_info = new StringBuilder();
                        reader = new BufferedReader(new InputStreamReader(in));
                        String line;
                        while ((line = reader.readLine()) != null) {
                            response_info.append(line);
                        }
                        String info = response_info.toString();
                        // 将json字符串转换成json对象
                        JSONObject weatherInfoJsonObj = new JSONObject(info);
                        JSONObject cityInfoJsonObj = new JSONObject(weatherInfoJsonObj.getString("cityInfo"));
                        Log.d("allinfo", weatherInfoJsonObj.toString());
                        weather.put("city", cityInfoJsonObj.getString("parent") + " " + cityInfoJsonObj.getString("city"));
                        JSONArray forcastJsonArr = new JSONArray(new JSONObject(weatherInfoJsonObj.getString("data")).getString("forecast"));
                        weather.put("date", weatherInfoJsonObj.getString("time") + " " + forcastJsonArr.getJSONObject(0).getString("week"));
                        weather.put("temper", forcastJsonArr.getJSONObject(0).getString("high") + " " + forcastJsonArr.getJSONObject(0).getString("low"));
                        weather.put("type", forcastJsonArr.getJSONObject(0).getString("type"));
                        weather.put("notice", forcastJsonArr.getJSONObject(0).getString("notice"));

                    } else {
                        weather.put("错误：", "[" + "武汉" + "]不存在！");
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                    Log.d("sub1", e.toString());
                }
                show(weather);
                Log.d("sub1", "info:" + weather.toString());
            }
        }).start();
    }

    private void show(final HashMap<String, String> weather) {
        runOnUiThread(new Runnable() {
            @Override
            public void run() {
                weather_city.setText(weather.get("city"));
                weather_date.setText(weather.get("date"));
                weather_notice.setText(weather.get("notice"));
                weather_temper.setText(weather.get("temper"));
                weather_type.setText(weather.get("type"));
                String type = weather.get("type");
                assert type != null;
                if (type.contains("晴"))
                    weather_type_icon.setImageResource(R.drawable.sunny);
                else if (type.contains("多云"))
                    weather_type_icon.setImageResource(R.drawable.pretty_cloudy);
                else if (type.contains("阴"))
                    weather_type_icon.setImageResource(R.drawable.cloudy);
                else if (type.contains("小雨"))
                    weather_type_icon.setImageResource(R.drawable.rain_s);
                else if (type.contains("中雨"))
                    weather_type_icon.setImageResource(R.drawable.rain_m);
                else if (type.contains("暴雨"))
                    weather_type_icon.setImageResource(R.drawable.rain_l);
                else if (type.contains("雨夹雪"))
                    weather_type_icon.setImageResource(R.drawable.iceandrain);
                else if (type.contains("雪"))
                    weather_type_icon.setImageResource(R.drawable.ice);
            }
        });
    }

    //判断联网情况
    public boolean isNetworkConnected(Context context) {
        if (context != null) {
            ConnectivityManager mConnectivityManager = (ConnectivityManager) context
                    .getSystemService(Context.CONNECTIVITY_SERVICE);
            NetworkInfo mNetworkInfo = mConnectivityManager.getActiveNetworkInfo();
            if (mNetworkInfo != null) {
                return mNetworkInfo.isAvailable();
            }
        }
        return false;
    }


    // 从本地相册选取图片作为头像
    private void choseHeadImageFromGallery() {
        // 设置文件类型    （在华为手机中不能获取图片，要替换代码）
        /*Intent intentFromGallery = new Intent();
        intentFromGallery.setType("image*//*");
        intentFromGallery.setAction(Intent.ACTION_GET_CONTENT);
        startActivityForResult(intentFromGallery, CODE_GALLERY_REQUEST);*/

        Intent intentFromGallery = new Intent(Intent.ACTION_PICK, null);
        intentFromGallery.setDataAndType(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, "image/*");
        startActivityForResult(intentFromGallery, CODE_GALLERY_REQUEST);

    }

    // 启动手机相机拍摄照片作为头像
    private void choseHeadImageFromCameraCapture() {
        String savePath = mExtStorDir;

        Intent intent = null;
        // 判断存储卡是否可以用，可用进行存储

        if (hasSdcard()) {
            //设定拍照存放到自己指定的目录,可以先建好
            File file = new File(savePath);
            if (!file.exists()) {
                file.mkdirs();
            }
            Uri pictureUri;
            File pictureFile = new File(savePath, IMAGE_FILE_NAME);
            if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
                intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);

                pictureUri = FileProvider.getUriForFile(this, getPackageName() + ".fileProvider", pictureFile);
    /*ContentValues contentValues = new ContentValues(1);
    contentValues.put(MediaStore.Images.Media.DATA, pictureFile.getAbsolutePath());
    pictureUri = getContentResolver().insert(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, contentValues);*/
            } else {
                intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
                intent.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
                pictureUri = Uri.fromFile(pictureFile);
            }
            /*if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.N) {
                intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
                ContentValues contentValues = new ContentValues(1);
                contentValues.put(MediaStore.Images.Media.DATA, pictureFile.getAbsolutePath());
                pictureUri = getContentResolver().insert(MediaStore.Images.Media.EXTERNAL_CONTENT_URI, contentValues);
            } else {
                intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
                pictureUri = Uri.fromFile(pictureFile);
            }*/
            if (intent != null) {
                intent.putExtra(MediaStore.EXTRA_OUTPUT,
                        pictureUri);
                startActivityForResult(intent, CODE_CAMERA_REQUEST);
            }
        }
    }

    public Uri getImageContentUri(File imageFile) {
        String filePath = imageFile.getAbsolutePath();
        Cursor cursor = getContentResolver().query(
                MediaStore.Images.Media.EXTERNAL_CONTENT_URI,
                new String[]{MediaStore.Images.Media._ID},
                MediaStore.Images.Media.DATA + "=? ",
                new String[]{filePath}, null);

        if (cursor != null && cursor.moveToFirst()) {
            int id = cursor.getInt(cursor
                    .getColumnIndex(MediaStore.MediaColumns._ID));
            Uri baseUri = Uri.parse("content://media/external/images/media");
            return Uri.withAppendedPath(baseUri, "" + id);
        } else {
            if (imageFile.exists()) {
                ContentValues values = new ContentValues();
                values.put(MediaStore.Images.Media.DATA, filePath);
                return getContentResolver().insert(
                        MediaStore.Images.Media.EXTERNAL_CONTENT_URI, values);
            } else {
                return null;
            }
        }
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode,
                                    Intent intent) {

        // 用户没有进行有效的设置操作，返回
        if (resultCode == RESULT_CANCELED) {
            Toast.makeText(getApplication(), "取消", Toast.LENGTH_LONG).show();
            return;
        }

        switch (requestCode) {
            case CODE_GALLERY_REQUEST:
                cropRawPhoto(intent.getData());
                break;

            case CODE_CAMERA_REQUEST:
                if (hasSdcard()) {
                    File tempFile = new File(
                            Environment.getExternalStorageDirectory(),
                            IMAGE_FILE_NAME);
//                    cropRawPhoto(Uri.fromFile(tempFile));
                    cropRawPhoto(getImageContentUri(tempFile));
                } else {
                    Toast.makeText(getApplication(), "没有SDCard!", Toast.LENGTH_LONG)
                            .show();
                }

                break;

            case CODE_RESULT_REQUEST:
                /*if (intent != null) {
                    setImageToHeadView(intent);    //此代码在小米有异常，换以下代码
                }*/
                try {
                    Bitmap bitmap = BitmapFactory.decodeStream(getContentResolver().openInputStream(mUriPath));
                    setImageToHeadView(intent, bitmap);
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }

                break;
        }

        super.onActivityResult(requestCode, resultCode, intent);
    }

    private void checkStoragePermission() {
        int result = ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE);
        int resultCAMERA = ActivityCompat.checkSelfPermission(this, Manifest.permission.CAMERA);
        if (result == PackageManager.PERMISSION_DENIED || resultCAMERA == PackageManager.PERMISSION_DENIED) {
            String[] permissions = {/*Manifest.permission.WRITE_EXTERNAL_STORAGE
                    ,*/Manifest.permission.CAMERA, Manifest.permission.READ_EXTERNAL_STORAGE};
            ActivityCompat.requestPermissions(this, permissions, PERMISSION_READ_AND_CAMERA);
        } else {
            choseHeadImageFromCameraCapture();
        }
    }

    private void checkReadPermission() {
        int permission = ActivityCompat.checkSelfPermission(this, Manifest.permission.READ_EXTERNAL_STORAGE);
        if (permission == PackageManager.PERMISSION_DENIED) {
            String[] permissions = {Manifest.permission.READ_EXTERNAL_STORAGE};
            ActivityCompat.requestPermissions(this, permissions, PERMISSION_READ);
        } else {
            choseHeadImageFromGallery();
        }
    }

    //权限申请回调
    @Override
    public void onRequestPermissionsResult(int requestCode, @NonNull String[] permissions, @NonNull int[] grantResults) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);

        switch (requestCode) {
            case PERMISSION_READ_AND_CAMERA: {
                for (int i = 0; i < grantResults.length; i++) {
                    if (grantResults[i] == PackageManager.PERMISSION_DENIED) {
                        Toast.makeText(this, "获取权限失败", Toast.LENGTH_SHORT).show();
                        return;
                    }
                }
            }
            choseHeadImageFromCameraCapture();
            break;
            case PERMISSION_READ: {
                if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    choseHeadImageFromGallery();
                }
                break;
            }
            case PERMISSION_CALL: {              //这个0是requestCode，上面requestPermissions有用到
                // If request is cancelled, the result arrays are empty.
                if (grantResults.length > 0
                        && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    Toast.makeText(SubActivity.this, "已获取权限,可以拨打目标电话", Toast.LENGTH_SHORT).show();
                } else {
                    Toast.makeText(SubActivity.this, "您拒绝了权限，无法使用此功能", Toast.LENGTH_SHORT).show();
                }
            }
        }

    }

    /**
     * 裁剪原始的图片
     */
    public void cropRawPhoto(Uri uri) {

        Intent intent = new Intent("com.android.camera.action.CROP");
        intent.setDataAndType(uri, "image/*");

        // 设置裁剪
        intent.putExtra("crop", "true");

        // aspectX , aspectY :宽高的比例
        intent.putExtra("aspectX", 1);
        intent.putExtra("aspectY", 1);

        // outputX , outputY : 裁剪图片宽高
        intent.putExtra("outputX", output_X);
        intent.putExtra("outputY", output_Y);
        intent.putExtra("return-data", true);

        //startActivityForResult(intent, CODE_RESULT_REQUEST); //直接调用此代码在小米手机有异常，换以下代码
        String mLinshi = System.currentTimeMillis() + CROP_IMAGE_FILE_NAME;
        File mFile = new File(mExtStorDir, mLinshi);
//        mHeadCachePath = mHeadCacheFile.getAbsolutePath();

        mUriPath = Uri.parse("file://" + mFile.getAbsolutePath());
        //将裁剪好的图输出到所建文件中
        intent.putExtra(MediaStore.EXTRA_OUTPUT, mUriPath);
        intent.putExtra("outputFormat", Bitmap.CompressFormat.JPEG.toString());
        //注意：此处应设置return-data为false，如果设置为true，是直接返回bitmap格式的数据，耗费内存。设置为false，然后，设置裁剪完之后保存的路径，即：intent.putExtra(MediaStore.EXTRA_OUTPUT, uriPath);
//        intent.putExtra("return-data", true);
        intent.putExtra("return-data", false);
//        intent.addFlags(Intent.FLAG_GRANT_READ_URI_PERMISSION);
        startActivityForResult(intent, CODE_RESULT_REQUEST);
    }

    /**
     * 提取保存裁剪之后的图片数据，并设置头像部分的View
     */
    private void setImageToHeadView(Intent intent, Bitmap b) {
        /*Bundle extras = intent.getExtras();
        if (extras != null) {
            Bitmap photo = extras.getParcelable("data");
            headImage.setImageBitmap(photo);
        }*/
        try {
            if (intent != null) {
//                Bitmap bitmap = imageZoom(b);//看个人需求，可以不压缩
                headImage.setImageBitmap(b);
//                long millis = System.currentTimeMillis();
                /*File file = FileUtil.saveFile(mExtStorDir, millis+CROP_IMAGE_FILE_NAME, bitmap);
                if (file!=null){
                    //传递新的头像信息给我的界面
                    Intent ii = new Intent();
                    setResult(new_icon,ii);
                    Glide.with(this).load(file).apply(RequestOptions.circleCropTransform())
//                                .apply(RequestOptions.fitCenterTransform())
                            .apply(RequestOptions.placeholderOf(R.mipmap.user_logo)).apply(RequestOptions.errorOf(R.mipmap.user_logo))
                            .into(mIvTouxiangPersonal);
//                uploadImg(mExtStorDir,millis+CROP_IMAGE_FILE_NAME);
                    uploadImg(mExtStorDir,millis+CROP_IMAGE_FILE_NAME);
                }*/

            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * 检查设备是否存在SDCard的工具方法
     */
    public static boolean hasSdcard() {
        String state = Environment.getExternalStorageState();
        if (state.equals(Environment.MEDIA_MOUNTED)) {
            // 有存储的SDCard
            return true;
        } else {
            return false;
        }
    }

    private Bitmap imageZoom(Bitmap bitMap) {
        //图片允许最大空间   单位：KB
        double maxSize = 1000.00;
        //将bitmap放至数组中，意在bitmap的大小（与实际读取的原文件要大）
        ByteArrayOutputStream baos = new ByteArrayOutputStream();
        bitMap.compress(Bitmap.CompressFormat.JPEG, 100, baos);
        byte[] b = baos.toByteArray();
        //将字节换成KB
        double mid = b.length / 1024;
        //判断bitmap占用空间是否大于允许最大空间  如果大于则压缩 小于则不压缩
        if (mid > maxSize) {
            //获取bitmap大小 是允许最大大小的多少倍
            double i = mid / maxSize;
            //开始压缩  此处用到平方根 将宽带和高度压缩掉对应的平方根倍 （1.保持刻度和高度和原bitmap比率一致，压缩后也达到了最大大小占用空间的大小）
            bitMap = zoomImage(bitMap, bitMap.getWidth() / Math.sqrt(i),
                    bitMap.getHeight() / Math.sqrt(i));
        }
        return bitMap;
    }

    /***
     * 图片的缩放方法
     *
     * @param bgimage
     *            ：源图片资源
     * @param newWidth
     *            ：缩放后宽度
     * @param newHeight
     *            ：缩放后高度
     * @return
     */
    public static Bitmap zoomImage(Bitmap bgimage, double newWidth,
                                   double newHeight) {
        // 获取这个图片的宽和高
        float width = bgimage.getWidth();
        float height = bgimage.getHeight();
        // 创建操作图片用的matrix对象
        Matrix matrix = new Matrix();
        // 计算宽高缩放率
        float scaleWidth = ((float) newWidth) / width;
        float scaleHeight = ((float) newHeight) / height;
        // 缩放图片动作
        matrix.postScale(scaleWidth, scaleHeight);
        Bitmap bitmap = Bitmap.createBitmap(bgimage, 0, 0, (int) width,
                (int) height, matrix, true);
        return bitmap;
    }
}