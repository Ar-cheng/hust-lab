var vue = new Vue({
    el: "#main",
    vuetify: new Vuetify(),
    data: {
        display: {
            employee_info: true,
            employee_info_add: false,
            bonus_info: false,
            department_info: false,
            kind_info: false,
            log_info: false,
            salary_info: false,
            attendance_info: false,
            salary_report: false
        },

        search: '',

        //employee
        employee_headers: [
            {
                text: 'UID',
                align: 'start',
                sortable: true,
                value: 'UID',
            },
            { text: '姓名', value: 'UName' },
            { text: '年龄', value: 'Age' },
            { text: '性别', value: 'Sex' },
            { text: '部门', value: 'DName' },
            { text: '工种', value: 'KName' },
            { text: '基本薪资', value: 'Base_salary' },
            { text: '职阶', value: 'Level' },
            { text: '工种编号', value: 'KID'  },
            { text: '部门编号', value: 'DID' }
        ],
        employee_info: [],

        //employee_info_add or update or delete
        valid: false,
        employee_info_add: {
            UID: null,
            UName: null,
            Age: null,
            KID: null,
            DID: null,
            Sex: null,
        },
        Sex_info: [0, 1],


        //department_info
        department_headers: [
            {
                text: 'DID',
                align: 'start',
                sortable: true,
                value: 'DID',
            },
            { text: '部门名', value: 'DName' },
            { text: '部门人数', value: 'DNum' },
            { text: '备注', value: 'DRef' },
        ],
        department_info: [],

        //department_info_add
        department_info_add: {
            DID: null,
            DName: null,
            DRef: null
        },

        //bonus_info
        bonus_headers: [
            {
                text: 'UID',
                align: 'start',
                sortable: true,
                value: 'UID',
            },
            { text: '日期', value: 'BDate' },
            { text: '津贴类型', value: 'BType' },
            { text: '天数', value: 'BDays' },
            { text: '津贴数目', value: 'Bonus' },
        ],
        bonus_info: [],

        //bonus_info_add
        bonus_info_add: {
            UID: null,
            BDate: null,
            Btype: null,
            BDays: null,
            Bonus: null,
        },

        //salary_info
        salary_headers: [
            {
                text: 'UID',
                align: 'start',
                sortable: true,
                value: 'UID',
            },
            { text: '月份', value: 'Month' },
            { text: '基础薪资', value: 'Base_salary' },
            { text: '出勤次数', value: 'attendance_times' },
            { text: '出勤率', value: 'attendance_rate' },
            { text: '津贴', value: 'Bonus' },
            { text: '总薪资', value: 'Total_salary' },
        ],


        salary_info: [],

        //attendance_info,
        attendance_headers: [
            {
                text: 'UID',
                align: 'start',
                sortable: true,
                value: 'UID',
            },
            { text: '出勤日期', value: 'ADate' },
            { text: '签到时间', value: 'ATime' },
            { text: '签退时间', value: 'STime' },
        ],
        attendance_info: [],

        //kind_info
        kind_headers: [
            {
                text: 'KID',
                align: 'start',
                sortable: true,
                value: 'KID',
            },
            { text: '工种', value: 'KName' },
            { text: '职级', value: 'Level' },
            { text: '基础薪资', value: 'Base_salary' },
        ],
        kind_info: [],

        //kind_info_add
        kind_info_add: {
            KID: null,
            KName: null,
            Level: null,
            Base_salary: null
        },


        //log_info
        log_headers: [
            {
                text: 'UID',
                align: 'start',
                sortable: true,
                value: 'UID',
            },
            { text: 'Password', value: 'Password' },
            { text: 'Authority', value: 'Authority' },
        ],
        log_info: [],

        //kind_info_add
        log_info_add: {
            UID: null,
            Password: null,
            Authoruty: null,
        },
        log_authority_items:[0,1],



        //salary_report
        salary_report_headers: [
            {
                text: 'UID',
                align: 'start',
                sortable: true,
                value: 'UID',
            },
            { text: '姓名', value: 'UName' },
            { text: '部门', value: 'DName' },
            { text: '年度薪资', value: 'Salary' },
            { text: '年终奖', value: 'Award' },
            { text: '合计', value: 'Total' }
        ],
        salary_report: [],
        
       
    },

    methods: {
        show: function (target) {
            for (each in this.display) {
                if (target === each)
                    this.display[each] = true;
                else
                    this.display[each] = false;
            }
        },

        logout:function(){
            axios.get('/logout')
            .then(function (res) {
                window.location.href="login"
            }).catch(function (error) {
                alert(error);
            });
        },

        info_refresh: function (tar) {
            var _this = this;
            axios.get('/index/get/' + tar)
                .then(function (res) {
                    _this[tar] = [];
                    for (var i of res.data) {
                        _this[tar].push(i);
                    }
                }).catch(function (error) {
                    alert(error);
                });
        },

        get_department: function () {
            this.show('department_info');
            if (this.department_info.length === 0)
                this.info_refresh('department_info');
        },

        get_kind: function () {
            this.show('kind_info');
            if (this.kind_info.length === 0)
                this.info_refresh('kind_info');
        },

        get_bonus: function () {
            this.show('bonus_info');
            if (this.bonus_info.length === 0)
                this.info_refresh('bonus_info');
        },

        get_salary: function () {
            this.show('salary_info');
            if (this.salary_info.length === 0)
                this.info_refresh('salary_info');
        },

        get_attendance: function () {
            this.show('attendance_info');
            if (this.attendance_info.length === 0)
                this.info_refresh('attendance_info');
        },

        get_log: function () {
            this.show('log_info');
            if (this.log_info.length === 0)
                this.info_refresh('log_info');
        },

        get_salary_report: function () {
            this.show('salary_report');
            if (this.salary_report.length === 0)
                this.info_refresh('salary_report');
        },

        employee_info_reset:function(){
            for (each in this.employee_info_add) {
                this.employee_info_add[each] = null;
            }
        },

        employee_info_submit: function () {
            var _this = this;
            axios.post('/index/add/employee_info', _this.employee_info_add)
                .then(function (res) {
                    for (each in _this.employee_info_add) {
                        _this.employee_info_add[each] = null;
                    }
                    console.log(res);
                }).catch(function (error) {
                    alert(error);
                });
        },

        employee_info_update: function () {
            var _this = this;
            axios.post('/index/update/employee_info', _this.employee_info_add)
                .then(function (res) {
                    for (each in _this.employee_info_add) {
                        _this.employee_info_add[each] = null;
                    }
                    console.log(res);
                }).catch(function (error) {
                    alert(error);
                });
        },

        employee_info_delete: function () {
            var _this = this;
            axios.post('/index/delete/employee_info', _this.employee_info_add)
                .then(function (res) {
                    for (each in _this.employee_info_add) {
                        _this.employee_info_add[each] = null;
                    }
                    console.log(res);
                }).catch(function (error) {
                    alert(error);
                });
        },

        kind_info_submit: function () {
            var _this = this;
            axios.post('/index/add/kind_info', _this.kind_info_add)
                .then(function (res) {
                    for (each in _this.kind_info_add) {
                        _this.kind_info_add[each] = null;
                    }
                    console.log(res);
                }).catch(function (error) {
                    alert(error);
                });
        },

        kind_info_update: function () {
            var _this = this;
            axios.post('/index/update/kind_info', _this.kind_info_add)
                .then(function (res) {
                    for (each in _this.kind_info_add) {
                        _this.kind_info_add[each] = null;
                    }
                    console.log(res);
                }).catch(function (error) {
                    alert(error);
                });
        },

        kind_info_delete: function () {
            var _this = this;
            axios.post('/index/delete/kind_info', _this.kind_info_add)
                .then(function (res) {
                    for (each in _this.kind_info_add) {
                        _this.kind_info_add[each] = null;
                    }
                    console.log(res);
                }).catch(function (error) {
                    alert(error);
                });
        },

        bonus_info_submit: function () {
            var _this = this;
            axios.post('/index/add/bonus_info', _this.bonus_info_add)
                .then(function (res) {
                    for (each in _this.bonus_info_add) {
                        _this.bonus_info_add[each] = null;
                    }
                    console.log(res);
                }).catch(function (error) {
                    alert(error);
                });
        },

        bonus_info_update: function () {
            var _this = this;
            axios.post('/index/update/bonus_info', _this.bonus_info_add)
                .then(function (res) {
                    for (each in _this.bonus_info_add) {
                        _this.bonus_info_add[each] = null;
                    }
                    console.log(res);
                }).catch(function (error) {
                    alert(error);
                });
        },

        bonus_info_delete: function () {
            var _this = this;
            axios.post('/index/delete/bonus_info', _this.bonus_info_add)
                .then(function (res) {
                    for (each in _this.bonus_info_add) {
                        _this.bonus_info_add[each] = null;
                    }
                    console.log(res);
                }).catch(function (error) {
                    alert(error);
                });
        },

        department_info_submit: function () {
            var _this = this;
            axios.post('/index/add/department_info', _this.department_info_add)
                .then(function (res) {
                    for (each in _this.department_info_add) {
                        _this.department_info_add[each] = null;
                    }
                    console.log(res);
                }).catch(function (error) {
                    alert(error);
                });
        },

        department_info_update: function () {
            var _this = this;
            axios.post('/index/update/department_info', _this.department_info_add)
                .then(function (res) {
                    for (each in _this.department_info_add) {
                        _this.department_info_add[each] = null;
                    }
                    console.log(res);
                }).catch(function (error) {
                    alert(error);
                });
        },

        department_info_delete: function () {
            var _this = this;
            axios.post('/index/delete/department_info', _this.department_info_add)
                .then(function (res) {
                    for (each in _this.department_info_add) {
                        _this.department_info_add[each] = null;
                    }
                    console.log(res);
                }).catch(function (error) {
                    alert(error);
                });
        },

        log_info_update: function () {
            var _this = this;
            axios.post('/index/update/log_info', _this.log_info_add)
                .then(function (res) {
                    for (each in _this.log_info_add) {
                        _this.log_info_add[each] = null;
                    }
                    console.log(res);
                }).catch(function (error) {
                    alert(error);
                });
        },
        
        analysis:function(){
            var option = {
                tooltip: {
                    trigger: 'item',
                    formatter: '{a} <br/>{b}: {c} ({d}%)'
                },
                title: {
                    text: '部门薪资占比分析',
                    left: 'center',
                    top: 20,
                    textStyle: {
                        color: '#293c55'
                    }
                },
                series: [
                    {
                        name: '部门总薪资占比',
                        type: 'pie',
                        radius: ['50%', '70%'],
                        avoidLabelOverlap: false,
                        label: {
                            show: false,
                            position: 'center'
                        },
                        emphasis: {
                            label: {
                                show: true,
                                fontSize: '30',
                                fontWeight: 'bold'
                            }
                        },
                        labelLine: {
                            show: false
                        },
                        data: [
                        ]
                    }
                ]
            };

            this.get_salary_report();

            var total = [];

            for (each in this.salary_report){
                if (total[this.salary_report[each].DName]==undefined)
                    total[this.salary_report[each].DName] = this.salary_report[each].Total;
                else
                    total[this.salary_report[each].DName] += this.salary_report[each].Total;
            }

            // console.log(total);

            for(each in total){
                option.series[0].data.push({ value: total[each], name: each });
            }

            option.series[0].data.sort(function (a, b) { return a.value - b.value; });
            var myChart = echarts.init(document.getElementById("mycharts"));
            myChart.setOption(option, true);
        }
    },
    mounted: function () {
        var _this = this;
        axios.get('/index/get/employee_info')
            .then(function (res) {
                for (var i of res.data) {
                    _this.employee_info.push(i);
                }
            }).catch(function (error) {
                alert(error);
            });
    }
});