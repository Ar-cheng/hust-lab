const getValues = () => {
    return Ajax({
        method: 'get',
        url: '/course/get'
    })
}

const updateTable = (data = []) => {
    const table = document.querySelector('#courseTable'); // 获取页面的table

    // table 的项， 这里初始化会添加表格头
    let tableItems = [
    `<tr>
        <th>课程名称</th>
        <th>老师</th>
        <th>开始时间</th>
        <th>结束时间</th>
    </tr>`];

    // 对数据做一个遍历， 处理为 HTML 字符串并添加到对应的 tableItems 的项中。
    data.forEach(item => {
        const {name, teacher, startTime, endTime} = item
        tableItems.push(
            `<tr>
                <td>${name}</td>
                <td>${teacher}</td>
                <td>${moment(startTime).format('YYYY-MM-DD')}</td>
                <td>${moment(endTime).format('YYYY-MM-DD')}</td>
            </tr>`
        );
        table.innerHTML = tableItems.join(''); // 数组转为字符串， 添加到 table 中
    })
}


const updateTableProcess = () => {
    return getValues().then(res => {
        const {code, data} = res
        if (code === 0) { // 返回结果 code 为 0， 这里视为正确响应
            const {items} = data // 获取返回结果中的列表
            updateTable(items) // 更新表格
        }
    }).catch(e => {
        alert('获取数据失败啦')
    })
}

updateTableProcess(); // 执行


const submitBtn = document.getElementById('submitBtn'); // 提交按钮

/**
* 提交数据函数， 返回的是一个 promise
*/
const submitValues = (values) => {
    return Ajax({
        method: 'post',
        url: '/course/post',
        data: values
    })
}

// 提交按钮绑定点击事件处理函数
submitBtn.addEventListener('click', () => {
    const inputItems = ['name', 'teacher', 'startTime', 'endTime'] // 表单项几个 key
    const values = {} // 初始化返回数据
    inputItems.forEach(key => {
        // 遍历 inputItems，获取对应的 input 上的 value
        // 如果 value 有值， 则添加相应的项
        const value = document.getElementById(key).value;
        if (!value) return;
        values[key] = value
    })

    // 最后发送提交请求
    submitValues(values).then(data => {
        updateTableProcess(); // 成功后重新更新表格
    })
})