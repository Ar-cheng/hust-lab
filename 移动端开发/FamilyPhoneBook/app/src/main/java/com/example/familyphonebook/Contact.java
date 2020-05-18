package com.example.familyphonebook;

public class Contact {
    //姓名
    private String mName;
    //电话
    private String mPhonenumber;
    //头像
    private int mPhoto;
    //住址
    private String mAddress;
    //关键字，类型
    private long mDate;
    //通话记录类型
    private int mState;
    //通话时间
    private int mDuration;


    public int getDuration() {
        return mDuration;
    }

    public void setDuration(int duration) {
        mDuration = duration;
    }

    public String getName() {
        return mName;
    }

    public void setName(String name) {
        mName = name;
    }

    public String getPhonenumber() {
        return mPhonenumber;
    }

    public void setPhonenumber(String phonenumber) {
        mPhonenumber = phonenumber;
    }

    public int getPhoto() {
        return mPhoto;
    }

    public void setPhoto(int photo) {
        mPhoto = photo;
    }

    public String getAddress() {
        return mAddress;
    }

    public void setAddress(String address) {
        mAddress = address;
    }

    public int getState() {
        return mState;
    }

    public void setState(int state) {
        mState = state;
    }

    public long getDate() {
        return mDate;
    }

    public void setDate(long date) {
        this.mDate = date;
    }

    public Contact(String name,String number, long date, int state, int duration , String address,int photo) {
        this.mName = name;
        this.mPhonenumber = number;
        this.mDate = date;
        this.mState =state;
        this.mAddress = address;
        this.mPhoto = photo;
        this.mDuration = duration;
    }
}
