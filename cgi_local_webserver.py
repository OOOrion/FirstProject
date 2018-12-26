from http.server import HTTPServer, CGIHTTPRequestHandler

HOST = ''               
PORT = 8000             

print('=== Local webserver ===')
HTTPServer((HOST, PORT), CGIHTTPRequestHandler).serve_forever()
