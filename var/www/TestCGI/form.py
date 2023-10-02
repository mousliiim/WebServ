#!/usr/bin/env python
import cgi, cgitb
cgitb.enable()
input_data = cgi.FieldStorage()

name = input_data["name"].value
email = input_data["email"].value
print(	"<html lang=\"en\">\n\
			<body style=\"background-color: darkslateblue; color: lightgrey;\">\n\
				<div style=\"display: flex; flex-direction: column; align-items: center; justify-content: center; height: 100%;\">\n\
					<h1>form.py</h1>\n\
					<p>name: {0}</br>email: {1}</p>\n\
				</div>\n\
			</body>\n\
		</html>".format(name, email))