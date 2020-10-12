var vue = new Vue({
    el: "#main",
    vuetify: new Vuetify(),
    data: {
        display: {
            employee_info: true,
            bonus_info: false,
            salary_info: false,
            attendance_info: false
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
            {text: '姓名', value: 'UName'},
            {text: '年龄', value: 'Age'},
            {text: '性别', value: 'Sex'},
            {text: '部门', value: 'DName'},
            {text: '工种', value: 'KName'},
            {text: '职阶', value: 'Level'},
            {text: '基本薪资', value: 'Base_salary'},
            {text: '工种编号', value: 'KID'}
        ],
        employee_info: [],

        //bonus_info
        bonus_headers: [
            {
                text: '日期',
                align: 'start',
                sortable: true,
                value: 'BDate',
            },
            {text: '津贴类型', value: 'BType'},
            {text: '天数', value: 'BDays'},
            {text: '津贴数目', value: 'Bonus'},
        ],
        bonus_info: [],

        //salary_info
        salary_headers: [
            {
                text: '月份',
                align: 'start',
                sortable: true,
                value: 'Month',
            },
            { text: '基础薪资', value: 'Base_salary' },
            { text: '出勤次数', value: 'attendance_times' },
            { text: '出勤率', value: 'attendance_rate' },
            {text: '津贴', value: 'Bonus'},
            {text: '总薪资', value: 'Total_salary'},
        ],
        salary_info: [],

        //attendance_info,
        attendance_headers: [
            {
                text: '出勤日期', value: 'ADate', align: 'start',
                sortable: true,
            },
            {text: '签到时间', value: 'ATime'},
            {text: '签退时间', value: 'STime'},
        ],
        attendance_info: [],

        //attendance_info_add
        attendance_info_add: {
            type: null,
            ADate: null,
            ATime: null,
            STime: null,
        },
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

        logout: function () {
            axios.get('/logout')
                .then(function (res) {
                    window.location.href = "login"
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

        attendance_sign_in: function () {
            var mydate = new Date();
            this.attendance_info_add.type = 0;
            this.attendance_info_add.ADate = mydate.toLocaleDateString().replace(/\//g, '-')
            this.attendance_info_add.ATime = mydate.toLocaleTimeString('chinese', {hour12: false});
            var _this = this;
            axios.post('/index/update/attendance_info', _this.attendance_info_add)
                .then(function (res) {
                }).catch(function (error) {
                alert(error);
            });
        },

        attendance_sign_out: function () {
            var mydate = new Date();
            this.attendance_info_add.type = 1;
            this.attendance_info_add.ADate = mydate.toLocaleDateString().replace(/\//g, '-')
            this.attendance_info_add.STime = mydate.toLocaleTimeString('chinese', {hour12: false});
            var _this = this;
            axios.post('/index/update/attendance_info', _this.attendance_info_add)
                .then(function (res) {
                }).catch(function (error) {
                alert(error);
            });
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