#!/usr/bin/env python3

import http.server
import socket
import subprocess
import sys
import threading
import time

def pickport():
        # pick a free port number
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        s.bind(('', 0))
        port = s.getsockname()[1]
        s.close()
        return port

class Handler(http.server.BaseHTTPRequestHandler):
    def log_message(self, format, *args):
        # add a # at the beginning of the line to not mess up Mtest diffs
        sys.stderr.write("#%s - - [%s] %s\n" %
                         (self.address_string(),
                          self.log_date_time_string(),
                          format%args))

    def do_GET(self):
        if self.path == '/42a':
            self.send_response(http.HTTPStatus.OK)
            self.send_header('Content-Type', 'text/plain')
            self.end_headers()
            self.wfile.write(b'a' * 42)
        elif self.path == '/40Ka':
            self.send_response(http.HTTPStatus.OK)
            self.send_header('Content-Type', 'text/plain')
            self.end_headers()
            self.wfile.write(b'a' * 40 * 1024)
        elif self.path == '/sleep':
            time.sleep(60)
            self.send_response(http.HTTPStatus.OK)
            self.send_header('Content-Type', 'text/plain')
            self.end_headers()
            self.wfile.write(b"now i'm well rested")
        else:
            self.send_response(http.HTTPStatus.NOT_FOUND)
            self.send_header('Content-Type', 'text/plain')
            self.end_headers()
            self.wfile.write(b'NOT FOUND\n')

def runserver(port):
    addr = ('', port)
    print(f"#Listening on {port}")
    srv = http.server.HTTPServer(addr, Handler)
    srv.serve_forever()

# Start the http server
port = pickport()
t = threading.Thread(target=lambda: runserver(port), daemon=True)
t.start()
time.sleep(0.5)
url = f'http://localhost:{port}'

def streamcat(suffix):
    u = url + suffix
    cmd = ['streamcat', 'read', u, 'urlstream']
    print(f'FETCHING {suffix}')
    PIPE = subprocess.PIPE
    p = subprocess.run(cmd, check=False, stdout=PIPE, stderr=PIPE)
    return (p.returncode, p.stdout, p.stderr)


(code, out, err) = streamcat('/42a')
assert code == 0
assert out == 42 * b'a'
assert err == b''

(code, out, err) = streamcat('/40Ka')
assert code == 0
assert out == 40 * 1024 * b'a'
assert err == b''

