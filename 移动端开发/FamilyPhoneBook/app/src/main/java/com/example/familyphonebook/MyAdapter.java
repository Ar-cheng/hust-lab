package com.example.familyphonebook;

import android.content.Context;
import android.graphics.Color;
import android.provider.CallLog;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Filter;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Objects;

public class MyAdapter extends RecyclerView.Adapter<RecyclerView.ViewHolder> {
    public Context mContext;

    public List<Contact> mDatas;
    public List<Contact> mDatas_filters;


    private OnItemClickListener listener;

    public MyAdapter(Context context, List<Contact> datas) {
        this.mContext = context;
        this.mDatas = datas;
        this.mDatas_filters = datas;
    }

    public class ViewHolder extends RecyclerView.ViewHolder {
        ImageView photo;
        TextView info;
        TextView time;
        ImageView state;
        TextView duration;
        TextView address;

        private ViewHolder(@NonNull View itemView) {
            super(itemView);
            photo = itemView.findViewById(R.id.photo);
            info = itemView.findViewById(R.id.TextView_contact_info);
            time = itemView.findViewById(R.id.TextView_contact_time);
            state = itemView.findViewById(R.id.imageView_contact_state);
            duration = itemView.findViewById(R.id.TextView_contact_duration);
            address = itemView.findViewById(R.id.TextView_contact_address);
        }

        public void setVisibility(boolean isGone) {
            RecyclerView.LayoutParams param = (RecyclerView.LayoutParams) itemView.getLayoutParams();
            if (isGone) {
                param.height = 0;
                param.width = 0;
            } else {
                param.height = LinearLayout.LayoutParams.WRAP_CONTENT;
                param.width = LinearLayout.LayoutParams.MATCH_PARENT;
            }
            itemView.setLayoutParams(param);
        }
    }

    @NonNull
    @Override
    public RecyclerView.ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View item = LayoutInflater.from(mContext).inflate(R.layout.list_item_contact, parent, false);
        return new ViewHolder(item);
    }

    @Override
    public void onBindViewHolder(@NonNull RecyclerView.ViewHolder holder, final int position) {
        //数据绑定在这里面进行
        Contact contact = mDatas_filters.get(position);
        ViewHolder holder1 = (ViewHolder) holder;
        holder1.info.setText(contact.getName());
        holder1.time.setText(timeStamp2Date(contact.getDate(), null).substring(5, 16));
        holder1.photo.setImageResource(contact.getPhoto() == 0 ? R.drawable.iconfont_people : contact.getPhoto());
        holder1.address.setText(contact.getAddress() == null ? null : contact.getAddress().replace("省", " ").replace("市", ""));
        int duration = contact.getDuration();
        if (duration == 0)
            holder1.duration.setVisibility(View.GONE);
        else if (duration > 60)
            holder1.duration.setText(duration / 60 + "分" + duration % 60 + "秒");
        else
            holder1.duration.setText(duration % 60 + "秒");

        switch (contact.getState()) {
            case CallLog.Calls.INCOMING_TYPE:
                holder1.state.setImageResource(R.drawable.call_in);// = "打入";
                break;
            case CallLog.Calls.OUTGOING_TYPE:
                holder1.state.setImageResource(R.drawable.call_out);// = "打出";
                break;
            case CallLog.Calls.MISSED_TYPE:
                //"未接"
                holder1.state.setImageResource(R.drawable.call_missed);//"未接";
                holder1.info.setTextColor(Color.parseColor("#FF0000"));
                break;
            default:
                holder1.state.setImageResource(R.drawable.call_missed);//"未接";
                break;
        }
        holder.itemView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (listener != null) {
                    listener.onClick(position);
                }
            }
        });
    }

    @Override
    public int getItemCount() {
        return mDatas_filters.size();
    }

    public Filter getFilter() {
        return new Filter() {
            //执行过滤操作
            @Override
            protected FilterResults performFiltering(CharSequence charSequence) {
                String charString = charSequence.toString();
                if (charString.isEmpty()) {
                    //没有过滤的内容，则使用源数据
                    mDatas_filters = mDatas;
                } else {
                    List<Contact> filteredList = new ArrayList<>();
                    for (int i = 0; i < mDatas.size(); i++) {
                        if (mDatas.get(i).getName().contains(charString) || mDatas.get(i).getAddress().contains(charString) || mDatas.get(i).getPhonenumber().contains(charString)) {
                            filteredList.add(mDatas.get(i));
                        }
                    }
                    mDatas_filters = filteredList;
                }
                FilterResults filterResults = new FilterResults();
                filterResults.values = mDatas_filters;
                return filterResults;
            }
            //把过滤后的值返回出来
            @Override
            protected void publishResults(CharSequence charSequence, FilterResults filterResults) {
                mDatas_filters = (List<Contact>) filterResults.values;
                notifyDataSetChanged();
            }
        };
    }

    public interface OnItemClickListener {
        void onClick(int position);
    }

    public void setOnItemClickListener(OnItemClickListener listener) {
        this.listener = listener;
    }

    public static String timeStamp2Date(long time, String format) {//long date解析
        if (format == null || format.isEmpty()) {
            format = "yyyy-MM-dd HH:mm:ss";
        }
        SimpleDateFormat sdf = new SimpleDateFormat(format);
        return sdf.format(new Date(time));
    }

    public List<Contact> get_filters(){
        return mDatas_filters;
    }
}
