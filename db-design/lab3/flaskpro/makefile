uwsgi:
	uwsgi --ini uwsgi.ini

uwsgi-d:
	uwsgi --socket 0.0.0.0:80 --protocol=http -p 3 -w run:app

find-python: 
	ps -ef | grep python

find-nginx:
	ps -ef | grep nginx

find-uwsgi:
	ps -ef | grep uwsgi