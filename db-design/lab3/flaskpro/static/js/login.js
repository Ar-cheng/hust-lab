const submitBtn = document.getElementById('submitBtn'); // 提交按钮
submitBtn.addEventListener('click', () => {
    const inputItems = ['uid', 'password'];// 表单项几个 key
    const values = {}; // 初始化返回数据
    inputItems.forEach(key => {
        // 遍历 inputItems，获取对应的 input 上的 value
        // 如果 value 有值， 则添加相应的项
        const value = document.getElementById(key).value;
        if (!value) return;
        values[key] = value
    });
    axios({
        method: 'post',
        url: '/login/post',
        data: values
    })
        .then(function (response) {//处理返回成功的结果
            if (response['data']['res'] === true) {
                console.log(response['data']);
                window.location.href = response['data']['target'];//重定向到目标页面
            }
            else
                alert("密码错误，请重试！")
        })
        .catch(function (error) {
            alert("密码或用户名错误！请重试");
            console.log(error);
        });
});